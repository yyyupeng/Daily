#!/usr/bin/env python
# coding=utf-8

from __future__ import print_function
from bcc import BPF
import ctypes
import subprocess
import logging
import sys

"""
kernel-tcp_state
enum {
	TCP_ESTABLISHED = 1,
	TCP_SYN_SENT,
	TCP_SYN_RECV,
	TCP_FIN_WAIT1,
	TCP_FIN_WAIT2,
	TCP_TIME_WAIT,
	TCP_CLOSE,
	TCP_CLOSE_WAIT,
	TCP_LAST_ACK,
	TCP_LISTEN,
	TCP_CLOSING,	
	TCP_NEW_SYN_RECV,

	TCP_MAX_STATES	
};

enum tcp_ca_state {
	TCP_CA_Open = 0,
#define TCPF_CA_Open	(1<<TCP_CA_Open)
	TCP_CA_Disorder = 1,
#define TCPF_CA_Disorder (1<<TCP_CA_Disorder)
	TCP_CA_CWR = 2,
#define TCPF_CA_CWR	(1<<TCP_CA_CWR)
	TCP_CA_Recovery = 3,
#define TCPF_CA_Recovery (1<<TCP_CA_Recovery)
	TCP_CA_Loss = 4
#define TCPF_CA_Loss	(1<<TCP_CA_Loss)
};
"""

bpf_text = """
#define KBUILD_MODNAME "foo"
#include <net/sock.h>
#include <bcc/proto.h>
#include <uapi/linux/ptrace.h>
#include <linux/net.h>
#include <linux/tcp.h>
#include <net/tcp.h>

struct rcv_evt {
    int pid;
    int tgid;
    int state;
    int ca_state;
    u32 cwnd;
    u32 ssthresh;
};
BPF_PERF_OUTPUT(rcv_evt);

int tcp_rcv(struct pt_regs *ctx, struct sock *sk, struct sk_buff *skb)
{
    struct tcp_sock *tp = (struct tcp_sock *)sk;
    struct inet_connection_sock *icsk = (struct inet_connection_sock *)sk;

    // 获取ca_state
    u8 _ca = *(&(icsk->icsk_retransmits)-1);
    u8 ca = _ca >> 2;

    /*
    u64 cur_pid = bpf_get_current_pid_tgid();
    u32 pid = cur_pid;
    u32 tgid = cur_pid >> 32;
    */

    // 获取task_struct
    struct task_struct *task = (struct task_struct *)bpf_get_current_task();
    int pid = task->pid;
    int tgid = task->tgid;

    if(pid != 449)
    {
        struct rcv_evt evt = {
            .pid = pid,
            .tgid = tgid,
            .state = sk->sk_state,
            .ca_state = ca,
            .cwnd = tp->snd_cwnd,
            .ssthresh = tp->snd_ssthresh,
        };
        rcv_evt.perf_submit(ctx, &evt, sizeof(evt));
    }

    // bpf_trace_printk("pid: %d, tgid: %d, state: %d\\n", pid, tgid, sk->sk_state);
    return 0;
}
"""

b = BPF(text=bpf_text)
b.attach_kprobe(event="tcp_v4_do_rcv", fn_name="tcp_rcv")

# log设置
logger = logging.getLogger('warning_logger')
logger.setLevel(logging.DEBUG)
warning_log = logging.FileHandler('warning.log','a',encoding='utf-8')
warning_log.setLevel(logging.DEBUG)
formatter = logging.Formatter('%(asctime)s - %(filename)s - line:%(lineno)d - %(levelname)s - %(message)s')
warning_log.setFormatter(formatter)
logger.addHandler(warning_log)

class rcvEvt(ctypes.Structure):
    _fields_ = [
        ("pid", ctypes.c_int),
        ("tgid", ctypes.c_int),
        ("state", ctypes.c_int),
        ("ca_state", ctypes.c_int),
        ("cwnd", ctypes.c_uint),
        ("ssthresh", ctypes.c_uint),
    ]

# 获取进程名称
def pid_to_comm(pid):
    try:
        comm = open("/proc/%s/comm" % pid, "r").read().rstrip()
        return comm
    except IOError:
        return str(pid)

# 打印信息
def print_info(evt, cca):
    print("comm: %s, pid: %d, tgid: %d, state: %d, ca_state: %d, cwnd: %u, cca: %s" %(
        pid_to_comm(evt.tgid), evt.pid, evt.tgid, evt.state, evt.ca_state, evt.cwnd, cca,
    ))

# bbr拥塞处理
def handle_bbr(evt):
    if __name__ == "__main__":
        logger.info('bbr')

# reno拥塞处理
def handle_reno(evt, cwnd_record):
    if __name__ == "__main__":
        logger.info('reno')
        # 可能发生拥塞
        if evt.cwnd >= evt.ssthresh+evt.ssthresh/3*2:
            logger.info('%s/%d network congestion may occur' % (pid_to_comm(evt.tgid), evt.tgid))
        # 是否发生拥塞
        if evt.ssthresh == cwnd_record/2 and evt.cwnd >= cwnd_record/2:
            logger.info('%s/%d network congestion warning' % (pid_to_comm(evt.tgid), evt.tgid))
        # 记录cwnd
        cwnd_record = evt.cwnd

# cubic拥塞处理
# cubic窗口增长函数: W = C(t − K)^3 + Wmax; K = (Wmax * β / C)^(1 / 3)
# C是调节因子, t是离最近一次(丢包)窗口减小的时间, K是窗口从W增加到Wmax所用的时间
# Wmax所是上一次发生拥塞时的窗口大小, β是乘法减小因子
def handle_cubic(evt, cwnd_record, mul_red_factor):
    if __name__ == "__main__":
        logger.info('cubic')
        # 可能发生拥塞
        if evt.cwnd >= evt.ssthresh+evt.ssthresh/3*2:
            logger.info('%s/%d network congestion may occur' % (pid_to_comm(evt.tgid), evt.tgid))
        # 是否发生拥塞
        if evt.cwnd >= cwnd_record*(1 - mul_red_factor):
            logger.info('%s/%d network congestion warning' % (pid_to_comm(evt.tgid), evt.tgid))
        # 记录cwnd
        cwnd_record = evt.cwnd

# 逻辑处理函数
def handle_func(cpu, data, size):
    evt = ctypes.cast(data, ctypes.POINTER(rcvEvt)).contents

    # 记录cwnd
    cwnd_record = sys.maxsize
    # 乘法减小因子
    mul_red_factor = 0.2
    
    # 获取系统当前拥塞控制算法
    cmd = subprocess.check_output("cat /proc/sys/net/ipv4/tcp_congestion_control", shell=True).decode()
    if cmd.find("bbr") >= 0:
        handle_bbr(evt)
    elif cmd.find("reno") >= 0: 
        handle_reno(evt, cwnd_record)
    elif cmd.find("cubic") >= 0: 
        handle_cubic(evt, cwnd_record, mul_red_factor)

    print_info(evt, cmd)

b["rcv_evt"].open_perf_buffer(handle_func)
while True:
    b.kprobe_poll()


