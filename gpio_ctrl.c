/*
    This is to write a device driver to control gpio pins.

    to see if the device can you this device driver we need to detect
    if gpios are available using this

    to get the gpio chip numbers use this cmd "gpiodetect",
    and you will see gpiochip0 ..., gpiochip1 ...

    now go to gpio folder using this cmd "cd /sys/class/gpio/"
    and try to find something like this "raspberrypi-exp-gpio"

    To use this driver we need to make and build this file using this cmd
    "make"
    to check the kernel msg we will use this cmd in another terminal
    "sudo dmesg -W" or dmsg 
    to insert this driver we will use this cmd
    "sudo insmod gpio_ctrl.ko"
    and to remove this driver we wil use this cmd
    "sudo rmmod gpio_ctrl"
*/

#include <linux/modules.h>
#include <linux/init.h>
#include <linux/gpio/consumer.h>

#define LED_PIN 21
#define BUTTON_PIN 20

#define ADDRESS_OFFSET 0

static struct gpio_desc *led, *button;

static int __init my_init(void){
    int status;

    led = gpio_to_desc(LED_PIN + ADDRESS_OFFSET);
    if(!led){
        printk("Error getting pin 21\n");
        return -ENODEV;
    }

    button = gpio_to_desc(BUTTON_PIN + ADDRESS_OFFSET);
    if(!button){
        printk("Error getting pin 20\n");
        return -ENODEV;
    }

    status = gpiod_direction_output(led, 0);
    if(status){
        printk("Error setting pin 20 to input\n");
        return status;
    }

    status = gpio_direction_input(button);
    if(status){
        printk("Error setting pin 21 to input");
        return status;
    }

    gpio_set_value(led, 1);

    printk("Button is %spressed\n", gpio_get_value(button) ? "" : "not ");

    return 0;
}

static __exit my_exit(void){
    gpiod_set_value(led, 0);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shivam Shah");
MOUDLE_DESCRIPTION("This is the device driver test to control the GPIO pins");