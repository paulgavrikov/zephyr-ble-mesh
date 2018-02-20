/* main.c - Application main entry point */

/*
 * Copyright (c) 2015-2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/types.h>
#include <stddef.h>
#include <misc/util.h>
#include <zephyr.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>


#define ADV_INT(_ms) ((_ms) * 8 / 5)


static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA_BYTES(BT_DATA_NAME_COMPLETE, 0xde,0xad,0xbe,0xef),
};

static void start_advd()
{
	struct bt_le_adv_param param;
	param.options = 0;
	param.interval_min = ADV_INT(K_MSEC(20)); // pick high to prevent regular transmission
	param.interval_max = param.interval_min;
	param.own_addr = NULL;

	
	int err = bt_le_adv_start(&param, ad, ARRAY_SIZE(ad), NULL, 0);
	if (err) {
		return;
	}
}

void main(void)
{
	int err;
	printk("Starting Scanner/Advertiser Demo\n");

	/* Initialize the Bluetooth Subsystem */
	err = bt_enable(NULL);
	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		return;
	}
	printk("Bluetooth initialized\n");
	
	start_advd();
}
