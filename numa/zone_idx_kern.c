#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/mmzone.h>

//#define NODE_DATA_ADDR 0xffffffff9ce44420

/*
enum zone_type {
	ZONE_DMA,
	ZONE_DMA32,
	ZONE_NORMAL,
	ZONE_MOVABLE,
	ZONE_DEVICE,
	__MAX_NR_ZONES
};
*/

static void zoneref_set_zone_u(struct zone *zone, struct zoneref *zonerefs)
{
	zonerefs->zone = zone;
	zonerefs->zone_idx = zone_idx(zone);
}	

static int build_zonerefs_node_u(struct pglist_data *pgdat, struct zoneref *zonerefs)
{
	struct zone *zone;
	enum zone_type zone_type = __MAX_NR_ZONES;
	int nr_zones = 0;

	do {
		zone_type--;
		zone = pgdat->node_zones + zone_type;
		
		zoneref_set_zone_u(zone, &zonerefs[nr_zones++]);
	} while (zone_type);

	return nr_zones;
}	

static int __init zone_idx_init(void)
{
	struct pglist_data *node = (struct pglist_data *)0xffffffff9ce44420;
	struct zoneref *zonerefs;

	zonerefs = node->node_zonelists[0]._zonerefs;

	int nr_zones = build_zonerefs_node_u(node, zonerefs);
	printk("nr_zones value:%d\n", nr_zones);

	printk("node_idx: %d\n", node->node_zonelists[0]._zonerefs[0].zone_idx);
	
	return 0;
}

static void __exit zone_idx_exit(void)
{
	printk("Goodbye kernel...\n");
}

module_init(zone_idx_init);
module_exit(zone_idx_exit);
MODULE_LICENSE("GPL");


