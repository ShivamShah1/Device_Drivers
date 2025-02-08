/*
    This will be normal character driver where I have registered
    the driver and assigned the region and also creating the 
    device file to communicate with driver manually.

    To create the device file we will use this cmds
        Creation of the device file
            "sudo mknod /dev/char_driver_file c <Major_Number> <Minor_number>"
                Here we will need to find the Major and Minor number 
                by inserting the module and looking in the kernel space using
                "dmesg" cmd.

        To read from the device file
            "sudo cat /dev/char_driver_file"


    To use this driver we need to make and build this file using this cmd
        "make"
    to check the kernel msg we will use this cmd in another terminal
        "sudo dmesg -WT" or dmsg 
    to insert this driver we will use this cmd
        "sudo insmod gpio_ctrl.ko"
    and to remove this driver we wil use this cmd
        "sudo rmmod gpio_ctrl"
*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

static int major;
static struct file_operations fops = {};

static int __init my_init(void){
    major = register_chrdev(0, "char_driver", &fops);
    if(major<0){
        printk(KERN_ERR "Error registering chrdev\n");
        return major;
    }

    printk(KERN_INFO "Major device number: %d\n", major);
    return 0;
}

static ssize_t my_read(struct file *f, char __user *u, size_t l, loff_t *o){
    printk(KERN_INFO "Read is called");
    return 0;
}

static struct file_operations fops = {
    .read = my_read
}

static void __exit my_exit(void){
    unregister_chrdev(major, "char_driver");
    pr_info("Removing the char_driver module\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_LICENSE("Shivam Shah");
MODULE_DESCRIPTION("A normal character driver");