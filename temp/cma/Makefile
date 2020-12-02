obj-m:=cma_alloc.o
CURRENT_PATH:=$(shell pwd)  #将模块源码路径保存在CURRENT_PATH中
LINUX_KERNEL:=$(shell uname -r) #将当前内核版本保存在LINUX_KERNEL中
LINUX_KERNEL_PATH:=/usr/src/linux-headers-$(LINUX_KERNEL) #将内核源代码的绝对路径保存在LINUX_KERNEL_PATH中
all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules #编译模块
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean   #清理

