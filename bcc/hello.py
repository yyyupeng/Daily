#!/usr/bin/env python
# coding=utf-8

# 有新进程被创建时程序打印"hello, world!" 

from bcc import BPF
BPF(text='int kprobe__sys_clone(void *ctx) { bpf_trace_printk("Hello, World!\\n"); return 0; }').trace_print()

