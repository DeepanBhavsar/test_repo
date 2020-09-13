obj-m += rw.o
KDIR := /lib/modules/$(shell uname -r)/build
all:
	$(MAKE) -C $(KDIR) M=`pwd` modules
clean:
	$(MAKE) -C $(KDIR) M=`pwd` clean

