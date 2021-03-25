#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

#define NODE_DATA_ADDR 0xffffffff9ce44420

static enum zone_type_u {
	ZONE_DMA_U,
	ZONE_DMA32_U,
	ZONE_NORMAL_U,
	ZONE_HIGHMEM_U,
	ZONE_DEVICE_U,
	MAX_NR_ZONES_U
};

static struct zone_u {
	struct pglist_data *zone_pgdata;
};

static struct zoneref_u {
	struct zone_u *zone;
	int zone_idx;
};

static struct zonelist_u {
	struct zoneref_u _zonerefs[6];	
};

typedef struct pglist_data_u {
	struct zone_u node_zones[MAX_NR_ZONES_U];
	struct zonelist_u node_zonelists[2];
} pg_data_t_u;

#define zone_idx(zone) ((zone) - (zone)->zone_pgdata->node_zones)

static void zoneref_set_zone_u(struct zone_u *zone, struct zoneref_u *zoneref) 
{
	zoneref->zone = zone;
	zoneref->zone_idx = zone_idx(zone);
}

static int build_zonerefs_node_u(pg_data_t_u *pgdat, struct zoneref *zonerefs)
{
	struct zone_u *zone;
	enum zone_type_u zone_type = MAX_NR_ZONES_U;
	int nr_zones = 0;

	do {
		zone_type--;
		zone = pgdat->node_zones + zone_type;
		
		zoneref_set_zone_u(zone, &zonerefs[nr_zones++]);
	} while (zone_type);

	return nr_zones;
}	

static int __init obtain_zone_idx_init(void)
{
	pg_data_t *node = *((pg_data_t *)NODE_DATA_ADDR);
	struct zoneref_u *zonerefs;

	zonerefs = node->node_zonelists[0]._zonerefs;

	int nr_zones = build_zonerefs_node_u(node, zonerefs);
	printk("nr_zones value:%d", nr_zones);

	printk("node_idx: %d", node->node_zonelists[0]._zonerefs[0].zone_idx);
	
	return 0;
}

static int __exit obtain_zone_idx_exit(void)
{
	printk("Goodbye kernel...\n");
}

module_init(obtain_zone_idx_init);
module_exit(obtain_zone_idx_exit);
MODULE_LICENSE("GPL");


