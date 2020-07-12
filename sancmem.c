#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("Dual BSD/GPL");

static int __init hello_init(void)
{
    printk(KERN_ALERT "hello,i am edsionte/n");
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_ALERT "goodbye,kernel/n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("gesefudiao");
MODULE_DESCRIPTION("This is a simple example!/n");
MODULE_ALIAS("A simple example");

