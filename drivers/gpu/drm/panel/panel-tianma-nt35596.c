// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2021 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/of.h>

#include "panel-mipi-dsi-common.h"

static void tianma_nt35596_reset(struct gpio_desc *reset_gpio)
{
	gpiod_set_value_cansleep(reset_gpio, 0);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(reset_gpio, 1);
	usleep_range(1000, 2000);
	gpiod_set_value_cansleep(reset_gpio, 0);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(reset_gpio, 1);
	usleep_range(1000, 2000);
	gpiod_set_value_cansleep(reset_gpio, 0);
	msleep(20);
}

static int tianma_nt35596_on(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	int ret;

	dsi_generic_write_seq(dsi, 0xff, 0xee);
	dsi_generic_write_seq(dsi, 0x18, 0x40);
	usleep_range(10000, 11000);
	dsi_generic_write_seq(dsi, 0x18, 0x00);
	msleep(20);
	dsi_generic_write_seq(dsi, 0xfb, 0x01);
	dsi_generic_write_seq(dsi, 0x7c, 0x31);
	dsi_generic_write_seq(dsi, 0xff, 0x01);
	dsi_generic_write_seq(dsi, 0xfb, 0x01);
	dsi_generic_write_seq(dsi, 0x75, 0x00);
	dsi_generic_write_seq(dsi, 0x76, 0x00);
	dsi_generic_write_seq(dsi, 0x77, 0x00);
	dsi_generic_write_seq(dsi, 0x78, 0x21);
	dsi_generic_write_seq(dsi, 0x79, 0x00);
	dsi_generic_write_seq(dsi, 0x7a, 0x4a);
	dsi_generic_write_seq(dsi, 0x7b, 0x00);
	dsi_generic_write_seq(dsi, 0x7c, 0x66);
	dsi_generic_write_seq(dsi, 0x7d, 0x00);
	dsi_generic_write_seq(dsi, 0x7e, 0x7f);
	dsi_generic_write_seq(dsi, 0x7f, 0x00);
	dsi_generic_write_seq(dsi, 0x80, 0x94);
	dsi_generic_write_seq(dsi, 0x81, 0x00);
	dsi_generic_write_seq(dsi, 0x82, 0xa7);
	dsi_generic_write_seq(dsi, 0x83, 0x00);
	dsi_generic_write_seq(dsi, 0x84, 0xb8);
	dsi_generic_write_seq(dsi, 0x85, 0x00);
	dsi_generic_write_seq(dsi, 0x86, 0xc7);
	dsi_generic_write_seq(dsi, 0x87, 0x00);
	dsi_generic_write_seq(dsi, 0x88, 0xfb);
	dsi_generic_write_seq(dsi, 0x89, 0x01);
	dsi_generic_write_seq(dsi, 0x8a, 0x25);
	dsi_generic_write_seq(dsi, 0x8b, 0x01);
	dsi_generic_write_seq(dsi, 0x8c, 0x61);
	dsi_generic_write_seq(dsi, 0x8d, 0x01);
	dsi_generic_write_seq(dsi, 0x8e, 0x94);
	dsi_generic_write_seq(dsi, 0x8f, 0x01);
	dsi_generic_write_seq(dsi, 0x90, 0xe2);
	dsi_generic_write_seq(dsi, 0x91, 0x02);
	dsi_generic_write_seq(dsi, 0x92, 0x20);
	dsi_generic_write_seq(dsi, 0x93, 0x02);
	dsi_generic_write_seq(dsi, 0x94, 0x22);
	dsi_generic_write_seq(dsi, 0x95, 0x02);
	dsi_generic_write_seq(dsi, 0x96, 0x5c);
	dsi_generic_write_seq(dsi, 0x97, 0x02);
	dsi_generic_write_seq(dsi, 0x98, 0x9e);
	dsi_generic_write_seq(dsi, 0x99, 0x02);
	dsi_generic_write_seq(dsi, 0x9a, 0xc9);
	dsi_generic_write_seq(dsi, 0x9b, 0x03);
	dsi_generic_write_seq(dsi, 0x9c, 0x01);
	dsi_generic_write_seq(dsi, 0x9d, 0x03);
	dsi_generic_write_seq(dsi, 0x9e, 0x28);
	dsi_generic_write_seq(dsi, 0x9f, 0x03);
	dsi_generic_write_seq(dsi, 0xa0, 0x55);
	dsi_generic_write_seq(dsi, 0xa2, 0x03);
	dsi_generic_write_seq(dsi, 0xa3, 0x62);
	dsi_generic_write_seq(dsi, 0xa4, 0x03);
	dsi_generic_write_seq(dsi, 0xa5, 0x6f);
	dsi_generic_write_seq(dsi, 0xa6, 0x03);
	dsi_generic_write_seq(dsi, 0xa7, 0x7e);
	dsi_generic_write_seq(dsi, 0xa9, 0x03);
	dsi_generic_write_seq(dsi, 0xaa, 0x8f);
	dsi_generic_write_seq(dsi, 0xab, 0x03);
	dsi_generic_write_seq(dsi, 0xac, 0x9c);
	dsi_generic_write_seq(dsi, 0xad, 0x03);
	dsi_generic_write_seq(dsi, 0xae, 0xa2);
	dsi_generic_write_seq(dsi, 0xaf, 0x03);
	dsi_generic_write_seq(dsi, 0xb0, 0xab);
	dsi_generic_write_seq(dsi, 0xb1, 0x03);
	dsi_generic_write_seq(dsi, 0xb2, 0xb2);
	dsi_generic_write_seq(dsi, 0xb3, 0x00);
	dsi_generic_write_seq(dsi, 0xb4, 0x00);
	dsi_generic_write_seq(dsi, 0xb5, 0x00);
	dsi_generic_write_seq(dsi, 0xb6, 0x21);
	dsi_generic_write_seq(dsi, 0xb7, 0x00);
	dsi_generic_write_seq(dsi, 0xb8, 0x4a);
	dsi_generic_write_seq(dsi, 0xb9, 0x00);
	dsi_generic_write_seq(dsi, 0xba, 0x66);
	dsi_generic_write_seq(dsi, 0xbb, 0x00);
	dsi_generic_write_seq(dsi, 0xbc, 0x7f);
	dsi_generic_write_seq(dsi, 0xbd, 0x00);
	dsi_generic_write_seq(dsi, 0xbe, 0x94);
	dsi_generic_write_seq(dsi, 0xbf, 0x00);
	dsi_generic_write_seq(dsi, 0xc0, 0xa7);
	dsi_generic_write_seq(dsi, 0xc1, 0x00);
	dsi_generic_write_seq(dsi, 0xc2, 0xb8);
	dsi_generic_write_seq(dsi, 0xc3, 0x00);
	dsi_generic_write_seq(dsi, 0xc4, 0xc7);
	dsi_generic_write_seq(dsi, 0xc5, 0x00);
	dsi_generic_write_seq(dsi, 0xc6, 0xfb);
	dsi_generic_write_seq(dsi, 0xc7, 0x01);
	dsi_generic_write_seq(dsi, 0xc8, 0x25);
	dsi_generic_write_seq(dsi, 0xc9, 0x01);
	dsi_generic_write_seq(dsi, 0xca, 0x61);
	dsi_generic_write_seq(dsi, 0xcb, 0x01);
	dsi_generic_write_seq(dsi, 0xcc, 0x94);
	dsi_generic_write_seq(dsi, 0xcd, 0x01);
	dsi_generic_write_seq(dsi, 0xce, 0xe2);
	dsi_generic_write_seq(dsi, 0xcf, 0x02);
	dsi_generic_write_seq(dsi, 0xd0, 0x20);
	dsi_generic_write_seq(dsi, 0xd1, 0x02);
	dsi_generic_write_seq(dsi, 0xd2, 0x22);
	dsi_generic_write_seq(dsi, 0xd3, 0x02);
	dsi_generic_write_seq(dsi, 0xd4, 0x5c);
	dsi_generic_write_seq(dsi, 0xd5, 0x02);
	dsi_generic_write_seq(dsi, 0xd6, 0x9e);
	dsi_generic_write_seq(dsi, 0xd7, 0x02);
	dsi_generic_write_seq(dsi, 0xd8, 0xc9);
	dsi_generic_write_seq(dsi, 0xd9, 0x03);
	dsi_generic_write_seq(dsi, 0xda, 0x01);
	dsi_generic_write_seq(dsi, 0xdb, 0x03);
	dsi_generic_write_seq(dsi, 0xdc, 0x28);
	dsi_generic_write_seq(dsi, 0xdd, 0x03);
	dsi_generic_write_seq(dsi, 0xde, 0x55);
	dsi_generic_write_seq(dsi, 0xdf, 0x03);
	dsi_generic_write_seq(dsi, 0xe0, 0x62);
	dsi_generic_write_seq(dsi, 0xe1, 0x03);
	dsi_generic_write_seq(dsi, 0xe2, 0x6f);
	dsi_generic_write_seq(dsi, 0xe3, 0x03);
	dsi_generic_write_seq(dsi, 0xe4, 0x7e);
	dsi_generic_write_seq(dsi, 0xe5, 0x03);
	dsi_generic_write_seq(dsi, 0xe6, 0x8f);
	dsi_generic_write_seq(dsi, 0xe7, 0x03);
	dsi_generic_write_seq(dsi, 0xe8, 0x9c);
	dsi_generic_write_seq(dsi, 0xe9, 0x03);
	dsi_generic_write_seq(dsi, 0xea, 0xa2);
	dsi_generic_write_seq(dsi, 0xeb, 0x03);
	dsi_generic_write_seq(dsi, 0xec, 0xab);
	dsi_generic_write_seq(dsi, 0xed, 0x03);
	dsi_generic_write_seq(dsi, 0xee, 0xb2);
	dsi_generic_write_seq(dsi, 0xef, 0x00);
	dsi_generic_write_seq(dsi, 0xf0, 0x00);
	dsi_generic_write_seq(dsi, 0xf1, 0x00);
	dsi_generic_write_seq(dsi, 0xf2, 0x21);
	dsi_generic_write_seq(dsi, 0xf3, 0x00);
	dsi_generic_write_seq(dsi, 0xf4, 0x4a);
	dsi_generic_write_seq(dsi, 0xf5, 0x00);
	dsi_generic_write_seq(dsi, 0xf6, 0x66);
	dsi_generic_write_seq(dsi, 0xf7, 0x00);
	dsi_generic_write_seq(dsi, 0xf8, 0x7f);
	dsi_generic_write_seq(dsi, 0xf9, 0x00);
	dsi_generic_write_seq(dsi, 0xfa, 0x94);
	dsi_generic_write_seq(dsi, 0xff, 0x02);
	dsi_generic_write_seq(dsi, 0xfb, 0x01);
	dsi_generic_write_seq(dsi, 0x00, 0x00);
	dsi_generic_write_seq(dsi, 0x01, 0xa7);
	dsi_generic_write_seq(dsi, 0x02, 0x00);
	dsi_generic_write_seq(dsi, 0x03, 0xb8);
	dsi_generic_write_seq(dsi, 0x04, 0x00);
	dsi_generic_write_seq(dsi, 0x05, 0xc7);
	dsi_generic_write_seq(dsi, 0x06, 0x00);
	dsi_generic_write_seq(dsi, 0x07, 0xfb);
	dsi_generic_write_seq(dsi, 0x08, 0x01);
	dsi_generic_write_seq(dsi, 0x09, 0x25);
	dsi_generic_write_seq(dsi, 0x0a, 0x01);
	dsi_generic_write_seq(dsi, 0x0b, 0x61);
	dsi_generic_write_seq(dsi, 0x0c, 0x01);
	dsi_generic_write_seq(dsi, 0x0d, 0x94);
	dsi_generic_write_seq(dsi, 0x0e, 0x01);
	dsi_generic_write_seq(dsi, 0x0f, 0xe2);
	dsi_generic_write_seq(dsi, 0x10, 0x02);
	dsi_generic_write_seq(dsi, 0x11, 0x20);
	dsi_generic_write_seq(dsi, 0x12, 0x02);
	dsi_generic_write_seq(dsi, 0x13, 0x22);
	dsi_generic_write_seq(dsi, 0x14, 0x02);
	dsi_generic_write_seq(dsi, 0x15, 0x5c);
	dsi_generic_write_seq(dsi, 0x16, 0x02);
	dsi_generic_write_seq(dsi, 0x17, 0x9e);
	dsi_generic_write_seq(dsi, 0x18, 0x02);
	dsi_generic_write_seq(dsi, 0x19, 0xc9);
	dsi_generic_write_seq(dsi, 0x1a, 0x03);
	dsi_generic_write_seq(dsi, 0x1b, 0x01);
	dsi_generic_write_seq(dsi, 0x1c, 0x03);
	dsi_generic_write_seq(dsi, 0x1d, 0x28);
	dsi_generic_write_seq(dsi, 0x1e, 0x03);
	dsi_generic_write_seq(dsi, 0x1f, 0x55);
	dsi_generic_write_seq(dsi, 0x20, 0x03);
	dsi_generic_write_seq(dsi, 0x21, 0x62);
	dsi_generic_write_seq(dsi, 0x22, 0x03);
	dsi_generic_write_seq(dsi, 0x23, 0x6f);
	dsi_generic_write_seq(dsi, 0x24, 0x03);
	dsi_generic_write_seq(dsi, 0x25, 0x7e);
	dsi_generic_write_seq(dsi, 0x26, 0x03);
	dsi_generic_write_seq(dsi, 0x27, 0x8f);
	dsi_generic_write_seq(dsi, 0x28, 0x03);
	dsi_generic_write_seq(dsi, 0x29, 0x9c);
	dsi_generic_write_seq(dsi, 0x2a, 0x03);
	dsi_generic_write_seq(dsi, 0x2b, 0xa2);
	dsi_generic_write_seq(dsi, 0x2d, 0x03);
	dsi_generic_write_seq(dsi, 0x2f, 0xab);
	dsi_generic_write_seq(dsi, 0x30, 0x03);
	dsi_generic_write_seq(dsi, 0x31, 0xb2);
	dsi_generic_write_seq(dsi, 0x32, 0x00);
	dsi_generic_write_seq(dsi, 0x33, 0x00);
	dsi_generic_write_seq(dsi, 0x34, 0x00);
	dsi_generic_write_seq(dsi, 0x35, 0x21);
	dsi_generic_write_seq(dsi, 0x36, 0x00);
	dsi_generic_write_seq(dsi, 0x37, 0x4a);
	dsi_generic_write_seq(dsi, 0x38, 0x00);
	dsi_generic_write_seq(dsi, 0x39, 0x66);
	dsi_generic_write_seq(dsi, 0x3a, 0x00);
	dsi_generic_write_seq(dsi, 0x3b, 0x7f);
	dsi_generic_write_seq(dsi, 0x3d, 0x00);
	dsi_generic_write_seq(dsi, 0x3f, 0x94);
	dsi_generic_write_seq(dsi, 0x40, 0x00);
	dsi_generic_write_seq(dsi, 0x41, 0xa7);
	dsi_generic_write_seq(dsi, 0x42, 0x00);
	dsi_generic_write_seq(dsi, 0x43, 0xb8);
	dsi_generic_write_seq(dsi, 0x44, 0x00);
	dsi_generic_write_seq(dsi, 0x45, 0xc7);
	dsi_generic_write_seq(dsi, 0x46, 0x00);
	dsi_generic_write_seq(dsi, 0x47, 0xfb);
	dsi_generic_write_seq(dsi, 0x48, 0x01);
	dsi_generic_write_seq(dsi, 0x49, 0x25);
	dsi_generic_write_seq(dsi, 0x4a, 0x01);
	dsi_generic_write_seq(dsi, 0x4b, 0x61);
	dsi_generic_write_seq(dsi, 0x4c, 0x01);
	dsi_generic_write_seq(dsi, 0x4d, 0x94);
	dsi_generic_write_seq(dsi, 0x4e, 0x01);
	dsi_generic_write_seq(dsi, 0x4f, 0xe2);
	dsi_generic_write_seq(dsi, 0x50, 0x02);
	dsi_generic_write_seq(dsi, 0x51, 0x20);
	dsi_generic_write_seq(dsi, 0x52, 0x02);
	dsi_generic_write_seq(dsi, 0x53, 0x22);
	dsi_generic_write_seq(dsi, 0x54, 0x02);
	dsi_generic_write_seq(dsi, 0x55, 0x5c);
	dsi_generic_write_seq(dsi, 0x56, 0x02);
	dsi_generic_write_seq(dsi, 0x58, 0x9e);
	dsi_generic_write_seq(dsi, 0x59, 0x02);
	dsi_generic_write_seq(dsi, 0x5a, 0xc9);
	dsi_generic_write_seq(dsi, 0x5b, 0x03);
	dsi_generic_write_seq(dsi, 0x5c, 0x01);
	dsi_generic_write_seq(dsi, 0x5d, 0x03);
	dsi_generic_write_seq(dsi, 0x5e, 0x28);
	dsi_generic_write_seq(dsi, 0x5f, 0x03);
	dsi_generic_write_seq(dsi, 0x60, 0x55);
	dsi_generic_write_seq(dsi, 0x61, 0x03);
	dsi_generic_write_seq(dsi, 0x62, 0x62);
	dsi_generic_write_seq(dsi, 0x63, 0x03);
	dsi_generic_write_seq(dsi, 0x64, 0x6f);
	dsi_generic_write_seq(dsi, 0x65, 0x03);
	dsi_generic_write_seq(dsi, 0x66, 0x7e);
	dsi_generic_write_seq(dsi, 0x67, 0x03);
	dsi_generic_write_seq(dsi, 0x68, 0x8f);
	dsi_generic_write_seq(dsi, 0x69, 0x03);
	dsi_generic_write_seq(dsi, 0x6a, 0x9c);
	dsi_generic_write_seq(dsi, 0x6b, 0x03);
	dsi_generic_write_seq(dsi, 0x6c, 0xa2);
	dsi_generic_write_seq(dsi, 0x6d, 0x03);
	dsi_generic_write_seq(dsi, 0x6e, 0xab);
	dsi_generic_write_seq(dsi, 0x6f, 0x03);
	dsi_generic_write_seq(dsi, 0x70, 0xb2);
	dsi_generic_write_seq(dsi, 0x71, 0x00);
	dsi_generic_write_seq(dsi, 0x72, 0x00);
	dsi_generic_write_seq(dsi, 0x73, 0x00);
	dsi_generic_write_seq(dsi, 0x74, 0x1e);
	dsi_generic_write_seq(dsi, 0x75, 0x00);
	dsi_generic_write_seq(dsi, 0x76, 0x48);
	dsi_generic_write_seq(dsi, 0x77, 0x00);
	dsi_generic_write_seq(dsi, 0x78, 0x57);
	dsi_generic_write_seq(dsi, 0x79, 0x00);
	dsi_generic_write_seq(dsi, 0x7a, 0x6a);
	dsi_generic_write_seq(dsi, 0x7b, 0x00);
	dsi_generic_write_seq(dsi, 0x7c, 0x80);
	dsi_generic_write_seq(dsi, 0x7d, 0x00);
	dsi_generic_write_seq(dsi, 0x7e, 0x90);
	dsi_generic_write_seq(dsi, 0x7f, 0x00);
	dsi_generic_write_seq(dsi, 0x80, 0xa0);
	dsi_generic_write_seq(dsi, 0x81, 0x00);
	dsi_generic_write_seq(dsi, 0x82, 0xae);
	dsi_generic_write_seq(dsi, 0x83, 0x00);
	dsi_generic_write_seq(dsi, 0x84, 0xe3);
	dsi_generic_write_seq(dsi, 0x85, 0x01);
	dsi_generic_write_seq(dsi, 0x86, 0x0e);
	dsi_generic_write_seq(dsi, 0x87, 0x01);
	dsi_generic_write_seq(dsi, 0x88, 0x50);
	dsi_generic_write_seq(dsi, 0x89, 0x01);
	dsi_generic_write_seq(dsi, 0x8a, 0x88);
	dsi_generic_write_seq(dsi, 0x8b, 0x01);
	dsi_generic_write_seq(dsi, 0x8c, 0xda);
	dsi_generic_write_seq(dsi, 0x8d, 0x02);
	dsi_generic_write_seq(dsi, 0x8e, 0x19);
	dsi_generic_write_seq(dsi, 0x8f, 0x02);
	dsi_generic_write_seq(dsi, 0x90, 0x1b);
	dsi_generic_write_seq(dsi, 0x91, 0x02);
	dsi_generic_write_seq(dsi, 0x92, 0x58);
	dsi_generic_write_seq(dsi, 0x93, 0x02);
	dsi_generic_write_seq(dsi, 0x94, 0x9c);
	dsi_generic_write_seq(dsi, 0x95, 0x02);
	dsi_generic_write_seq(dsi, 0x96, 0xc6);
	dsi_generic_write_seq(dsi, 0x97, 0x03);
	dsi_generic_write_seq(dsi, 0x98, 0x01);
	dsi_generic_write_seq(dsi, 0x99, 0x03);
	dsi_generic_write_seq(dsi, 0x9a, 0x28);
	dsi_generic_write_seq(dsi, 0x9b, 0x03);
	dsi_generic_write_seq(dsi, 0x9c, 0x55);
	dsi_generic_write_seq(dsi, 0x9d, 0x03);
	dsi_generic_write_seq(dsi, 0x9e, 0x62);
	dsi_generic_write_seq(dsi, 0x9f, 0x03);
	dsi_generic_write_seq(dsi, 0xa0, 0x6f);
	dsi_generic_write_seq(dsi, 0xa2, 0x03);
	dsi_generic_write_seq(dsi, 0xa3, 0x7e);
	dsi_generic_write_seq(dsi, 0xa4, 0x03);
	dsi_generic_write_seq(dsi, 0xa5, 0x8f);
	dsi_generic_write_seq(dsi, 0xa6, 0x03);
	dsi_generic_write_seq(dsi, 0xa7, 0x9c);
	dsi_generic_write_seq(dsi, 0xa9, 0x03);
	dsi_generic_write_seq(dsi, 0xaa, 0xa2);
	dsi_generic_write_seq(dsi, 0xab, 0x03);
	dsi_generic_write_seq(dsi, 0xac, 0xab);
	dsi_generic_write_seq(dsi, 0xad, 0x03);
	dsi_generic_write_seq(dsi, 0xae, 0xb2);
	dsi_generic_write_seq(dsi, 0xaf, 0x00);
	dsi_generic_write_seq(dsi, 0xb0, 0x00);
	dsi_generic_write_seq(dsi, 0xb1, 0x00);
	dsi_generic_write_seq(dsi, 0xb2, 0x1e);
	dsi_generic_write_seq(dsi, 0xb3, 0x00);
	dsi_generic_write_seq(dsi, 0xb4, 0x48);
	dsi_generic_write_seq(dsi, 0xb5, 0x00);
	dsi_generic_write_seq(dsi, 0xb6, 0x57);
	dsi_generic_write_seq(dsi, 0xb7, 0x00);
	dsi_generic_write_seq(dsi, 0xb8, 0x6a);
	dsi_generic_write_seq(dsi, 0xb9, 0x00);
	dsi_generic_write_seq(dsi, 0xba, 0x80);
	dsi_generic_write_seq(dsi, 0xbb, 0x00);
	dsi_generic_write_seq(dsi, 0xbc, 0x90);
	dsi_generic_write_seq(dsi, 0xbd, 0x00);
	dsi_generic_write_seq(dsi, 0xbe, 0xa0);
	dsi_generic_write_seq(dsi, 0xbf, 0x00);
	dsi_generic_write_seq(dsi, 0xc0, 0xae);
	dsi_generic_write_seq(dsi, 0xc1, 0x00);
	dsi_generic_write_seq(dsi, 0xc2, 0xe3);
	dsi_generic_write_seq(dsi, 0xc3, 0x01);
	dsi_generic_write_seq(dsi, 0xc4, 0x0e);
	dsi_generic_write_seq(dsi, 0xc5, 0x01);
	dsi_generic_write_seq(dsi, 0xc6, 0x50);
	dsi_generic_write_seq(dsi, 0xc7, 0x01);
	dsi_generic_write_seq(dsi, 0xc8, 0x88);
	dsi_generic_write_seq(dsi, 0xc9, 0x01);
	dsi_generic_write_seq(dsi, 0xca, 0xda);
	dsi_generic_write_seq(dsi, 0xcb, 0x02);
	dsi_generic_write_seq(dsi, 0xcc, 0x19);
	dsi_generic_write_seq(dsi, 0xcd, 0x02);
	dsi_generic_write_seq(dsi, 0xce, 0x1b);
	dsi_generic_write_seq(dsi, 0xcf, 0x02);
	dsi_generic_write_seq(dsi, 0xd0, 0x58);
	dsi_generic_write_seq(dsi, 0xd1, 0x02);
	dsi_generic_write_seq(dsi, 0xd2, 0x9c);
	dsi_generic_write_seq(dsi, 0xd3, 0x02);
	dsi_generic_write_seq(dsi, 0xd4, 0xc6);
	dsi_generic_write_seq(dsi, 0xd5, 0x03);
	dsi_generic_write_seq(dsi, 0xd6, 0x01);
	dsi_generic_write_seq(dsi, 0xd7, 0x03);
	dsi_generic_write_seq(dsi, 0xd8, 0x28);
	dsi_generic_write_seq(dsi, 0xd9, 0x03);
	dsi_generic_write_seq(dsi, 0xda, 0x55);
	dsi_generic_write_seq(dsi, 0xdb, 0x03);
	dsi_generic_write_seq(dsi, 0xdc, 0x62);
	dsi_generic_write_seq(dsi, 0xdd, 0x03);
	dsi_generic_write_seq(dsi, 0xde, 0x6f);
	dsi_generic_write_seq(dsi, 0xdf, 0x03);
	dsi_generic_write_seq(dsi, 0xe0, 0x7e);
	dsi_generic_write_seq(dsi, 0xe1, 0x03);
	dsi_generic_write_seq(dsi, 0xe2, 0x8f);
	dsi_generic_write_seq(dsi, 0xe3, 0x03);
	dsi_generic_write_seq(dsi, 0xe4, 0x9c);
	dsi_generic_write_seq(dsi, 0xe5, 0x03);
	dsi_generic_write_seq(dsi, 0xe6, 0xa2);
	dsi_generic_write_seq(dsi, 0xe7, 0x03);
	dsi_generic_write_seq(dsi, 0xe8, 0xab);
	dsi_generic_write_seq(dsi, 0xe9, 0x03);
	dsi_generic_write_seq(dsi, 0xea, 0xb2);
	dsi_generic_write_seq(dsi, 0xff, 0x00);
	dsi_generic_write_seq(dsi, 0xff, 0x00);
	dsi_generic_write_seq(dsi, 0x51, 0x00);
	dsi_generic_write_seq(dsi, 0x53, 0x2c);
	dsi_generic_write_seq(dsi, 0x55, 0x00);
	dsi_generic_write_seq(dsi, 0xff, 0x00);
	dsi_generic_write_seq(dsi, 0xd3, 0x0a);
	dsi_generic_write_seq(dsi, 0xd4, 0x0a);

	ret = mipi_dsi_dcs_exit_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to exit sleep mode: %d\n", ret);
		return ret;
	}
	msleep(100);

	ret = mipi_dsi_dcs_set_display_on(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to set display on: %d\n", ret);
		return ret;
	}

	return 0;
}

static int tianma_nt35596_off(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	int ret;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to set display off: %d\n", ret);
		return ret;
	}
	msleep(150);

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to enter sleep mode: %d\n", ret);
		return ret;
	}
	msleep(60);

	return 0;
}

static const struct panel_mipi_dsi_info tianma_nt35596_info = {
	.mode = {
		.clock = (1080 + 98 + 8 + 98) * (1920 + 10 + 2 + 8) * 60 / 1000,
		.hdisplay = 1080,
		.hsync_start = 1080 + 98,
		.hsync_end = 1080 + 98 + 8,
		.htotal = 1080 + 98 + 8 + 98,
		.vdisplay = 1920,
		.vsync_start = 1920 + 10,
		.vsync_end = 1920 + 10 + 2,
		.vtotal = 1920 + 10 + 2 + 8,
		.width_mm = 70,
		.height_mm = 128,
	},

	.reset = tianma_nt35596_reset,
	.power_on = tianma_nt35596_on,
	.power_off = tianma_nt35596_off,

	.lanes = 4,
	.format = MIPI_DSI_FMT_RGB888,
	.mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
		      MIPI_DSI_CLOCK_NON_CONTINUOUS | MIPI_DSI_MODE_LPM
};

MIPI_DSI_PANEL_DRIVER(tianma_nt35596, "tianma-nt35596", "tianma,nt35596");

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for tianma nt35596 1080p video mode dsi panel");
MODULE_LICENSE("GPL v2");
