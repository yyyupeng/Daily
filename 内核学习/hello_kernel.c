#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init lkp_init(void)
{
    printk(KERN_INFO"Hello! from the kernel space...\n");
    return 0;
}

static void __exit lkp_cleanup(void)
{
    printk(KERN_INFO"Goodbye! leaving kernel space...\n");
}

module_init(lkp_init);
module_exit(lkp_cleanup);
MODULE_LICENSE("GPL");
