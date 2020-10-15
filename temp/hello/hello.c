#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mmzone.h>
#include <asm-generic/atomic-long.h>

static int __init zone_init(void)
{
	printk("hello, kernel...\n");

	return 0;
}

static void __exit zone_cleanup(void)
{
	printk("Goodbye, kernel...\n");
}

module_init(zone_init);
module_exit(zone_cleanup);
MODULE_LICENSE("GPL");


