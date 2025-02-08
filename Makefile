obj-m +=gpio_ctrl.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/mosules/$(shell uname 0r)/build M=$(PWD) clean