#!/usr/bin/env python
# coding=utf-8

from __future__ import print_function
from bcc import BPF
from time import sleep
import ctypes
import subprocess
import socket
import struct
import pymysql
import datetime

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
#include <linux/inet_diag.h>
#include <linux/sock_diag.h>
#include <linux/net.h>
#include <linux/tcp.h>
#include <net/tcp.h>

struct info_evt {
    int state;
    int ca_state;
    u32 cwnd;
    u32 saddr;
    u32 daddr;
};
BPF_PERF_OUTPUT(info_evt);

int tcp_info(struct pt_regs *ctx, struct sock *sk, struct inet_diag_msg *r, void *_info)
{
    struct tcp_sock *tp = (struct tcp_sock *)sk;
    struct inet_connection_sock *icsk = (struct inet_connection_sock *)sk;
    
    // 获取ca_state
    u8 _ca = *(&(icsk->icsk_retransmits)-1);
    u8 ca = _ca >> 2;

    u32 _saddr = 0;
    u32 _daddr = 0;
    bpf_probe_read(&_saddr, sizeof(_saddr), &sk->__sk_common.skc_rcv_saddr);
    bpf_probe_read(&_daddr, sizeof(_daddr), &sk->__sk_common.skc_daddr);

    struct info_evt evt = {
        .state = sk->sk_state,
        .ca_state = ca,
        .cwnd = tp->snd_cwnd,
        .saddr = _saddr,
        .daddr = _daddr,
    };
    info_evt.perf_submit(ctx, &evt, sizeof(evt));

    // bpf_trace_printk("state: %d\\n", sk->sk_state);
    return 0;
}
"""

b = BPF(text=bpf_text)
b.attach_kprobe(event="tcp_diag_get_info", fn_name="tcp_info")

class infoEvt(ctypes.Structure):
    _fields_ = [
        ("state", ctypes.c_int),
        ("ca_state", ctypes.c_int),
        ("cwnd", ctypes.c_uint),
        ("saddr", ctypes.c_uint),
        ("daddr", ctypes.c_uint),
    ]

def print_evt(cpu, data, size):
    evt = ctypes.cast(data, ctypes.POINTER(infoEvt)).contents

    # 获取系统当前拥塞控制算法
    cca = subprocess.check_output("cat /proc/sys/net/ipv4/tcp_congestion_control", shell=True).decode()
    if cca.find("bbr") >= 0:
        cca = "bbr"
    elif cca.find("reno") >= 0: 
        cca = "reno"
    elif cca.find("cubic") >= 0: 
        cca = "cubic"

    # 执行sql语句
    # 先删除原先数据
    cur.execute("TRUNCATE TABLE tcp_show;")
    conn.commit()
    # 再插入最新数据
    dt = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    cur.execute("INSERT INTO tcp_show(state, ca_state, saddr, daddr, cwnd, cca, time) VALUES (%s, %s, '%s', '%s', %s, '%s', '%s');" % (
        evt.state, evt.ca_state,
        socket.inet_ntoa(struct.pack('I',socket.htonl(evt.saddr))),
        socket.inet_ntoa(struct.pack('I',socket.htonl(evt.daddr))),
        evt.cwnd, cca, dt))
    conn.commit()

    # 命令行打印
    print("state: %d, ca_state: %d, saddr: %s, daddr: %s, cwnd: %u, cca: %s" %(
        evt.state, 
        evt.ca_state,
        socket.inet_ntoa(struct.pack('I',socket.htonl(evt.saddr))),
        socket.inet_ntoa(struct.pack('I',socket.htonl(evt.daddr))),
        evt.cwnd, 
        cca,
    ))

# 连接mysql
pymysql.install_as_MySQLdb()
conn = pymysql.connect(host='127.0.0.1', user='root', passwd='Lyp20000617', db='ebpf',charset='utf8')
cur = conn.cursor()

b["info_evt"].open_perf_buffer(print_evt)
while True:
    # 调用ss命令以触发tcp_diag模块
    subprocess.check_output("ss -t", shell=True)
    b.kprobe_poll()
    print("......\n")
    sleep(3)

# 关闭mysql连接
conn.close()
