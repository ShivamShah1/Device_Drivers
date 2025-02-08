obj-m += char_driver.c

all:
	make -C /lib/modules/$(shell uname -r)/build $(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build $(PWD) clean