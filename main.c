/*
 * Texas Instruments DS92LX1621 serializer driver
 *
 * Copyright (C) 2015 Digger DTR
 * Alexandre Schnegg <aschnegg@digger.ch>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include "ds92lx1621.h"
#include <linux/module.h>
#include <linux/i2c.h>

static int ds92lx1621_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	s32 temp;
	s32 deviceId = i2c_smbus_read_byte_data(client, DEVICE_ID_REG_ADDR);
	if (deviceId > 0)
	{
		pr_info("device id: %d\n", deviceId);
	}
	else
	{
		pr_err("error reading ID\n");
	}
	if (0 > i2c_smbus_write_byte_data(client, STANDBY_ADDR_REG, STANDBY_MASK))
	{
		pr_err("error standby\n");
	}
/*
	temp = i2c_smbus_read_byte_data(client, TRFB_REG_ADDR);
	if (temp > 0)
	{
		if(0>i2c_smbus_write_byte_data(client, TRFB_REG_ADDR, temp & ~TRFB_REG_ADDR))
		{
			pr_err("error write trfb ID\n");
		}
	}
	else
	{
		pr_err("error read trfb ID\n");
	}
*/
	if (0 > i2c_smbus_write_byte_data(client, SLAVE_ID_REG_ADDR, 0x42))
	{
		pr_err("error slave ID\n");
	}
	return 0;
}

static int ds92lx1621_remove(struct i2c_client *client)
{

	return 0;
}

static const struct of_device_id ds92lx1621_camera_of_match[] = {
	{ .compatible = "ti,ds92lx1621", },
	{},
};
MODULE_DEVICE_TABLE(of, ds92lx1621_camera_of_match);

static const struct i2c_device_id ds92lx1621_id[] =
{
{ "ds92lx1621", 0 },
{ } };

MODULE_DEVICE_TABLE( i2c, ds92lx1621_id);

static struct i2c_driver ds92lx1621_driver =
{ .probe = ds92lx1621_probe, .remove = ds92lx1621_remove, .id_table = ds92lx1621_id, .driver =
{ .name = "ds92lx1621", .owner = THIS_MODULE,.of_match_table=of_match_ptr(ds92lx1621_camera_of_match),}, };

module_i2c_driver( ds92lx1621_driver);

MODULE_AUTHOR("Alexandre Schnegg <aschnegg@digger.ch>");
MODULE_DESCRIPTION("DS92LX1621 driver");
MODULE_LICENSE("GPL v2");
