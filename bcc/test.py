#!/usr/bin/env python
# coding=utf-8

from __future__ import print_function
from bcc import BPF

bpf_text = """
#define KBUILD_MODNAME "foo"
#include <net/sock.h>
#include <bcc/proto.h>
#include <linux/net.h>
#include <linux/tcp.h>
#include <net/tcp.h>

int tcp_info(struct pt_regs *ctx, struct sock *sk, struct inet_diag_msg *r, void *_info)
{
    struct tcp_sock *tp = (struct tcp_sock *)sk;
    struct inet_connection_sock *icsk = (struct inet_connection_sock *)sk;
    

    u8 _ca = *(&(icsk->icsk_retransmits)-1);
    u8 ca = _ca >> 2;
    // bpf_probe_read(&ca, sizeof(ca), &icsk->icsk_ca_state);

    bpf_trace_printk("state: %d, ca_state: %d\\n", sk->sk_state, ca);
    return 0;
}

"""

b = BPF(text=bpf_text)
b.attach_kprobe(event="tcp_diag_get_info", fn_name="tcp_info")

while True:
    print(b.trace_readline())
    

