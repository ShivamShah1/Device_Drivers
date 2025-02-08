/*
    A basic hello world device driver which does nothing 
    just print "hello world" in kernel space when driver 
    inserted and while removing it will print "goodbye".

    To use this driver we need to make and build this file using this cmd
    "make"
    to check the kernel msg we will use this cmd in another terminal
    "sudo dmesg -W" or dmsg 
    to insert this driver we will use this cmd
    "sudo insmod hello_world.ko"
    and to remove this driver we wil use this cmd
    "sudo rmmod hello_world"
*/
#include <linux/module.h>
#include <linux/init.h>

static int __init my_init(void){
    printk("Hello world!!!!!!!!\n");
    return 0;
}

static void __exit my_exit(void){
    printk("Goodbye.....\n");
}

module_init(my_init);
module_exit(my_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shivam Shah");
MODULE_DESCRIPTION("A simple hellow world device driver");
