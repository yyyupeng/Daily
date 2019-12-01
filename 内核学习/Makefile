obj-m := hello_kernel.o										#产生hello_kernel模块的目标文件
CURRENT_PATH := $(shell pwd)								#模块当前所在的路径
LINUX_KERNEL := $(shell uname -r)							#Linux内核源代码的版本
LINUX_KERNEL_PATH := /usr/src/linux-headers-$(LINUX_KERNEL)	#Linux内核源代码的绝对路径

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules	#编译模块
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean 		#清理
