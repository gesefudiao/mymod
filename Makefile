CONFIG_MODULE_SIG=n

obj-m += getpidofile.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(shell pwd) modules

clean:
	rm -rf *.o  *.mod.c .*.cmd .tmp_versions *.order *.symvers
