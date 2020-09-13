obj-m += char_sys_file.o
KDIR := /lib/modules/$(shell uname -r)/build
all:
	$(MAKE) -C $(KDIR) M=`pwd` modules
clean:
	$(MAKE) -C $(KDIR) M=`pwd` clean

