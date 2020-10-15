#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mmzone.h>
#include <linux/kallsyms.h>
#include <asm-generic/atomic-long.h>

struct pglist_data * (* export_first_online_pgdat)(void);
struct zone * (* export_next_zone)(struct zone * zone);


static int __init zone_init(void)
{
	struct zone * zone;
	atomic_long_t l;

	export_first_online_pgdat = (void *)kallsyms_lookup_name("first_online_pgdat");
	export_next_zone = (void *)kallsyms_lookup_name("next_zone");
	
	for (zone = (export_first_online_pgdat())->node_zones; \
	     zone;					\
	     zone = export_next_zone(zone)) {
		l = zone->vm_stat[NR_FREE_PAGES];
		printk("hello world %ld\n", l);
	}
	
	return 0;
}

static void __exit zone_exit(void)
{
	printk("Goodbye, kernel...\n");
}

module_init(zone_init);
module_exit(zone_exit);
MODULE_LICENSE("GPL");


