#!/usr/bin/env python
# coding=utf-8

# 检测到sync时打印"sys_sync() called"

from bcc import BPF
print("Modified by liangjinrong")
print("Tracing sys_sync()... Ctrl-C to end.")
BPF(text='int kprobe__sys_sync(void *ctx) { bpf_trace_printk("sys_sync() called\\n"); return 0; }').trace_print()
