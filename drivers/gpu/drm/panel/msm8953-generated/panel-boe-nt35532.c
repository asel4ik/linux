// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2022 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/regulator/consumer.h>

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>

struct boe_nt35532 {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct regulator_bulk_data supplies[2];
	struct gpio_desc *reset_gpio;
	bool prepared;
};

static inline struct boe_nt35532 *to_boe_nt35532(struct drm_panel *panel)
{
	return container_of(panel, struct boe_nt35532, panel);
}

#define dsi_generic_write_seq(dsi, seq...) do {				\
		static const u8 d[] = { seq };				\
		int ret;						\
		ret = mipi_dsi_generic_write(dsi, d, ARRAY_SIZE(d));	\
		if (ret < 0)						\
			return ret;					\
	} while (0)

static void boe_nt35532_reset(struct boe_nt35532 *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	msleep(20);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	msleep(20);
}

static int boe_nt35532_on(struct boe_nt35532 *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
	struct device *dev = &dsi->dev;
	int ret;

	dsi_generic_write_seq(dsi, 0xff, 0xee);
	dsi_generic_write_seq(dsi, 0x18, 0x40);
	dsi_generic_write_seq(dsi, 0x18, 0x00);
	dsi_generic_write_seq(dsi, 0xff, 0x01);
	dsi_generic_write_seq(dsi, 0xfb, 0x01);
	dsi_generic_write_seq(dsi, 0x68, 0x13);
	dsi_generic_write_seq(dsi, 0x75, 0x00);
	dsi_generic_write_seq(dsi, 0x76, 0x00);
	dsi_generic_write_seq(dsi, 0x77, 0x00);
	dsi_generic_write_seq(dsi, 0x78, 0x22);
	dsi_generic_write_seq(dsi, 0x79, 0x00);
	dsi_generic_write_seq(dsi, 0x7a, 0x51);
	dsi_generic_write_seq(dsi, 0x7b, 0x00);
	dsi_generic_write_seq(dsi, 0x7c, 0x73);
	dsi_generic_write_seq(dsi, 0x7d, 0x00);
	dsi_generic_write_seq(dsi, 0x7e, 0x8d);
	dsi_generic_write_seq(dsi, 0x7f, 0x00);
	dsi_generic_write_seq(dsi, 0x80, 0xa4);
	dsi_generic_write_seq(dsi, 0x81, 0x00);
	dsi_generic_write_seq(dsi, 0x82, 0xb8);
	dsi_generic_write_seq(dsi, 0x83, 0x00);
	dsi_generic_write_seq(dsi, 0x84, 0xca);
	dsi_generic_write_seq(dsi, 0x85, 0x00);
	dsi_generic_write_seq(dsi, 0x86, 0xd9);
	dsi_generic_write_seq(dsi, 0x87, 0x01);
	dsi_generic_write_seq(dsi, 0x88, 0x0d);
	dsi_generic_write_seq(dsi, 0x89, 0x01);
	dsi_generic_write_seq(dsi, 0x8a, 0x36);
	dsi_generic_write_seq(dsi, 0x8b, 0x01);
	dsi_generic_write_seq(dsi, 0x8c, 0x75);
	dsi_generic_write_seq(dsi, 0x8d, 0x01);
	dsi_generic_write_seq(dsi, 0x8e, 0xa7);
	dsi_generic_write_seq(dsi, 0x8f, 0x01);
	dsi_generic_write_seq(dsi, 0x90, 0xf2);
	dsi_generic_write_seq(dsi, 0x91, 0x02);
	dsi_generic_write_seq(dsi, 0x92, 0x2b);
	dsi_generic_write_seq(dsi, 0x93, 0x02);
	dsi_generic_write_seq(dsi, 0x94, 0x2b);
	dsi_generic_write_seq(dsi, 0x95, 0x02);
	dsi_generic_write_seq(dsi, 0x96, 0x61);
	dsi_generic_write_seq(dsi, 0x97, 0x02);
	dsi_generic_write_seq(dsi, 0x98, 0x9d);
	dsi_generic_write_seq(dsi, 0x99, 0x02);
	dsi_generic_write_seq(dsi, 0x9a, 0xc6);
	dsi_generic_write_seq(dsi, 0x9b, 0x03);
	dsi_generic_write_seq(dsi, 0x9c, 0x01);
	dsi_generic_write_seq(dsi, 0x9d, 0x03);
	dsi_generic_write_seq(dsi, 0x9e, 0x27);
	dsi_generic_write_seq(dsi, 0x9f, 0x03);
	dsi_generic_write_seq(dsi, 0xa0, 0x63);
	dsi_generic_write_seq(dsi, 0xa2, 0x03);
	dsi_generic_write_seq(dsi, 0xa3, 0x6b);
	dsi_generic_write_seq(dsi, 0xa4, 0x03);
	dsi_generic_write_seq(dsi, 0xa5, 0x72);
	dsi_generic_write_seq(dsi, 0xa6, 0x03);
	dsi_generic_write_seq(dsi, 0xa7, 0x7e);
	dsi_generic_write_seq(dsi, 0xa9, 0x03);
	dsi_generic_write_seq(dsi, 0xaa, 0x87);
	dsi_generic_write_seq(dsi, 0xab, 0x03);
	dsi_generic_write_seq(dsi, 0xac, 0x93);
	dsi_generic_write_seq(dsi, 0xad, 0x03);
	dsi_generic_write_seq(dsi, 0xae, 0x9b);
	dsi_generic_write_seq(dsi, 0xaf, 0x03);
	dsi_generic_write_seq(dsi, 0xb0, 0xa2);
	dsi_generic_write_seq(dsi, 0xb1, 0x03);
	dsi_generic_write_seq(dsi, 0xb2, 0xff);
	dsi_generic_write_seq(dsi, 0xb3, 0x00);
	dsi_generic_write_seq(dsi, 0xb4, 0x00);
	dsi_generic_write_seq(dsi, 0xb5, 0x00);
	dsi_generic_write_seq(dsi, 0xb6, 0x22);
	dsi_generic_write_seq(dsi, 0xb7, 0x00);
	dsi_generic_write_seq(dsi, 0xb8, 0x51);
	dsi_generic_write_seq(dsi, 0xb9, 0x00);
	dsi_generic_write_seq(dsi, 0xba, 0x73);
	dsi_generic_write_seq(dsi, 0xbb, 0x00);
	dsi_generic_write_seq(dsi, 0xbc, 0x8d);
	dsi_generic_write_seq(dsi, 0xbd, 0x00);
	dsi_generic_write_seq(dsi, 0xbe, 0xa4);
	dsi_generic_write_seq(dsi, 0xbf, 0x00);
	dsi_generic_write_seq(dsi, 0xc0, 0xb8);
	dsi_generic_write_seq(dsi, 0xc1, 0x00);
	dsi_generic_write_seq(dsi, 0xc2, 0xca);
	dsi_generic_write_seq(dsi, 0xc3, 0x00);
	dsi_generic_write_seq(dsi, 0xc4, 0xd9);
	dsi_generic_write_seq(dsi, 0xc5, 0x01);
	dsi_generic_write_seq(dsi, 0xc6, 0x0d);
	dsi_generic_write_seq(dsi, 0xc7, 0x01);
	dsi_generic_write_seq(dsi, 0xc8, 0x36);
	dsi_generic_write_seq(dsi, 0xc9, 0x01);
	dsi_generic_write_seq(dsi, 0xca, 0x75);
	dsi_generic_write_seq(dsi, 0xcb, 0x01);
	dsi_generic_write_seq(dsi, 0xcc, 0xa7);
	dsi_generic_write_seq(dsi, 0xcd, 0x01);
	dsi_generic_write_seq(dsi, 0xce, 0xf2);
	dsi_generic_write_seq(dsi, 0xcf, 0x02);
	dsi_generic_write_seq(dsi, 0xd0, 0x2b);
	dsi_generic_write_seq(dsi, 0xd1, 0x02);
	dsi_generic_write_seq(dsi, 0xd2, 0x2b);
	dsi_generic_write_seq(dsi, 0xd3, 0x02);
	dsi_generic_write_seq(dsi, 0xd4, 0x61);
	dsi_generic_write_seq(dsi, 0xd5, 0x02);
	dsi_generic_write_seq(dsi, 0xd6, 0x9d);
	dsi_generic_write_seq(dsi, 0xd7, 0x02);
	dsi_generic_write_seq(dsi, 0xd8, 0xc6);
	dsi_generic_write_seq(dsi, 0xd9, 0x03);
	dsi_generic_write_seq(dsi, 0xda, 0x01);
	dsi_generic_write_seq(dsi, 0xdb, 0x03);
	dsi_generic_write_seq(dsi, 0xdc, 0x27);
	dsi_generic_write_seq(dsi, 0xdd, 0x03);
	dsi_generic_write_seq(dsi, 0xde, 0x63);
	dsi_generic_write_seq(dsi, 0xdf, 0x03);
	dsi_generic_write_seq(dsi, 0xe0, 0x6b);
	dsi_generic_write_seq(dsi, 0xe1, 0x03);
	dsi_generic_write_seq(dsi, 0xe2, 0x72);
	dsi_generic_write_seq(dsi, 0xe3, 0x03);
	dsi_generic_write_seq(dsi, 0xe4, 0x7e);
	dsi_generic_write_seq(dsi, 0xe5, 0x03);
	dsi_generic_write_seq(dsi, 0xe6, 0x87);
	dsi_generic_write_seq(dsi, 0xe7, 0x03);
	dsi_generic_write_seq(dsi, 0xe8, 0x93);
	dsi_generic_write_seq(dsi, 0xe9, 0x03);
	dsi_generic_write_seq(dsi, 0xea, 0x9b);
	dsi_generic_write_seq(dsi, 0xeb, 0x03);
	dsi_generic_write_seq(dsi, 0xec, 0xa2);
	dsi_generic_write_seq(dsi, 0xed, 0x03);
	dsi_generic_write_seq(dsi, 0xee, 0xff);
	dsi_generic_write_seq(dsi, 0xef, 0x00);
	dsi_generic_write_seq(dsi, 0xf0, 0xd6);
	dsi_generic_write_seq(dsi, 0xf1, 0x00);
	dsi_generic_write_seq(dsi, 0xf2, 0xdd);
	dsi_generic_write_seq(dsi, 0xf3, 0x00);
	dsi_generic_write_seq(dsi, 0xf4, 0xea);
	dsi_generic_write_seq(dsi, 0xf5, 0x00);
	dsi_generic_write_seq(dsi, 0xf6, 0xf7);
	dsi_generic_write_seq(dsi, 0xf7, 0x01);
	dsi_generic_write_seq(dsi, 0xf8, 0x03);
	dsi_generic_write_seq(dsi, 0xf9, 0x01);
	dsi_generic_write_seq(dsi, 0xfa, 0x0d);
	dsi_generic_write_seq(dsi, 0xff, 0x02);
	dsi_generic_write_seq(dsi, 0xfb, 0x01);
	dsi_generic_write_seq(dsi, 0x00, 0x01);
	dsi_generic_write_seq(dsi, 0x01, 0x17);
	dsi_generic_write_seq(dsi, 0x02, 0x01);
	dsi_generic_write_seq(dsi, 0x03, 0x21);
	dsi_generic_write_seq(dsi, 0x04, 0x01);
	dsi_generic_write_seq(dsi, 0x05, 0x2a);
	dsi_generic_write_seq(dsi, 0x06, 0x01);
	dsi_generic_write_seq(dsi, 0x07, 0x4b);
	dsi_generic_write_seq(dsi, 0x08, 0x01);
	dsi_generic_write_seq(dsi, 0x09, 0x68);
	dsi_generic_write_seq(dsi, 0x0a, 0x01);
	dsi_generic_write_seq(dsi, 0x0b, 0x98);
	dsi_generic_write_seq(dsi, 0x0c, 0x01);
	dsi_generic_write_seq(dsi, 0x0d, 0xc0);
	dsi_generic_write_seq(dsi, 0x0e, 0x02);
	dsi_generic_write_seq(dsi, 0x0f, 0x00);
	dsi_generic_write_seq(dsi, 0x10, 0x02);
	dsi_generic_write_seq(dsi, 0x11, 0x34);
	dsi_generic_write_seq(dsi, 0x12, 0x02);
	dsi_generic_write_seq(dsi, 0x13, 0x35);
	dsi_generic_write_seq(dsi, 0x14, 0x02);
	dsi_generic_write_seq(dsi, 0x15, 0x68);
	dsi_generic_write_seq(dsi, 0x16, 0x02);
	dsi_generic_write_seq(dsi, 0x17, 0xa4);
	dsi_generic_write_seq(dsi, 0x18, 0x02);
	dsi_generic_write_seq(dsi, 0x19, 0xcc);
	dsi_generic_write_seq(dsi, 0x1a, 0x03);
	dsi_generic_write_seq(dsi, 0x1b, 0x07);
	dsi_generic_write_seq(dsi, 0x1c, 0x03);
	dsi_generic_write_seq(dsi, 0x1d, 0x2f);
	dsi_generic_write_seq(dsi, 0x1e, 0x03);
	dsi_generic_write_seq(dsi, 0x1f, 0x6a);
	dsi_generic_write_seq(dsi, 0x20, 0x03);
	dsi_generic_write_seq(dsi, 0x21, 0x71);
	dsi_generic_write_seq(dsi, 0x22, 0x03);
	dsi_generic_write_seq(dsi, 0x23, 0x85);
	dsi_generic_write_seq(dsi, 0x24, 0x03);
	dsi_generic_write_seq(dsi, 0x25, 0x9a);
	dsi_generic_write_seq(dsi, 0x26, 0x03);
	dsi_generic_write_seq(dsi, 0x27, 0xb2);
	dsi_generic_write_seq(dsi, 0x28, 0x03);
	dsi_generic_write_seq(dsi, 0x29, 0xca);
	dsi_generic_write_seq(dsi, 0x2a, 0x03);
	dsi_generic_write_seq(dsi, 0x2b, 0xe2);
	dsi_generic_write_seq(dsi, 0x2d, 0x03);
	dsi_generic_write_seq(dsi, 0x2f, 0xf5);
	dsi_generic_write_seq(dsi, 0x30, 0x03);
	dsi_generic_write_seq(dsi, 0x31, 0xff);
	dsi_generic_write_seq(dsi, 0x32, 0x00);
	dsi_generic_write_seq(dsi, 0x33, 0xd6);
	dsi_generic_write_seq(dsi, 0x34, 0x00);
	dsi_generic_write_seq(dsi, 0x35, 0xdd);
	dsi_generic_write_seq(dsi, 0x36, 0x00);
	dsi_generic_write_seq(dsi, 0x37, 0xea);
	dsi_generic_write_seq(dsi, 0x38, 0x00);
	dsi_generic_write_seq(dsi, 0x39, 0xf7);
	dsi_generic_write_seq(dsi, 0x3a, 0x01);
	dsi_generic_write_seq(dsi, 0x3b, 0x03);
	dsi_generic_write_seq(dsi, 0x3d, 0x01);
	dsi_generic_write_seq(dsi, 0x3f, 0x0d);
	dsi_generic_write_seq(dsi, 0x40, 0x01);
	dsi_generic_write_seq(dsi, 0x41, 0x17);
	dsi_generic_write_seq(dsi, 0x42, 0x01);
	dsi_generic_write_seq(dsi, 0x43, 0x21);
	dsi_generic_write_seq(dsi, 0x44, 0x01);
	dsi_generic_write_seq(dsi, 0x45, 0x2a);
	dsi_generic_write_seq(dsi, 0x46, 0x01);
	dsi_generic_write_seq(dsi, 0x47, 0x4b);
	dsi_generic_write_seq(dsi, 0x48, 0x01);
	dsi_generic_write_seq(dsi, 0x49, 0x68);
	dsi_generic_write_seq(dsi, 0x4a, 0x01);
	dsi_generic_write_seq(dsi, 0x4b, 0x98);
	dsi_generic_write_seq(dsi, 0x4c, 0x01);
	dsi_generic_write_seq(dsi, 0x4d, 0xc0);
	dsi_generic_write_seq(dsi, 0x4e, 0x02);
	dsi_generic_write_seq(dsi, 0x4f, 0x00);
	dsi_generic_write_seq(dsi, 0x50, 0x02);
	dsi_generic_write_seq(dsi, 0x51, 0x34);
	dsi_generic_write_seq(dsi, 0x52, 0x02);
	dsi_generic_write_seq(dsi, 0x53, 0x35);
	dsi_generic_write_seq(dsi, 0x54, 0x02);
	dsi_generic_write_seq(dsi, 0x55, 0x68);
	dsi_generic_write_seq(dsi, 0x56, 0x02);
	dsi_generic_write_seq(dsi, 0x58, 0xa4);
	dsi_generic_write_seq(dsi, 0x59, 0x02);
	dsi_generic_write_seq(dsi, 0x5a, 0xcc);
	dsi_generic_write_seq(dsi, 0x5b, 0x03);
	dsi_generic_write_seq(dsi, 0x5c, 0x07);
	dsi_generic_write_seq(dsi, 0x5d, 0x03);
	dsi_generic_write_seq(dsi, 0x5e, 0x2f);
	dsi_generic_write_seq(dsi, 0x5f, 0x03);
	dsi_generic_write_seq(dsi, 0x60, 0x6a);
	dsi_generic_write_seq(dsi, 0x61, 0x03);
	dsi_generic_write_seq(dsi, 0x62, 0x71);
	dsi_generic_write_seq(dsi, 0x63, 0x03);
	dsi_generic_write_seq(dsi, 0x64, 0x85);
	dsi_generic_write_seq(dsi, 0x65, 0x03);
	dsi_generic_write_seq(dsi, 0x66, 0x9a);
	dsi_generic_write_seq(dsi, 0x67, 0x03);
	dsi_generic_write_seq(dsi, 0x68, 0xb2);
	dsi_generic_write_seq(dsi, 0x69, 0x03);
	dsi_generic_write_seq(dsi, 0x6a, 0xca);
	dsi_generic_write_seq(dsi, 0x6b, 0x03);
	dsi_generic_write_seq(dsi, 0x6c, 0xe2);
	dsi_generic_write_seq(dsi, 0x6d, 0x03);
	dsi_generic_write_seq(dsi, 0x6e, 0xf5);
	dsi_generic_write_seq(dsi, 0x6f, 0x03);
	dsi_generic_write_seq(dsi, 0x70, 0xff);
	dsi_generic_write_seq(dsi, 0x71, 0x00);
	dsi_generic_write_seq(dsi, 0x72, 0xcd);
	dsi_generic_write_seq(dsi, 0x73, 0x00);
	dsi_generic_write_seq(dsi, 0x74, 0xd5);
	dsi_generic_write_seq(dsi, 0x75, 0x00);
	dsi_generic_write_seq(dsi, 0x76, 0xe3);
	dsi_generic_write_seq(dsi, 0x77, 0x00);
	dsi_generic_write_seq(dsi, 0x78, 0xef);
	dsi_generic_write_seq(dsi, 0x79, 0x00);
	dsi_generic_write_seq(dsi, 0x7a, 0xfb);
	dsi_generic_write_seq(dsi, 0x7b, 0x01);
	dsi_generic_write_seq(dsi, 0x7c, 0x06);
	dsi_generic_write_seq(dsi, 0x7d, 0x01);
	dsi_generic_write_seq(dsi, 0x7e, 0x11);
	dsi_generic_write_seq(dsi, 0x7f, 0x01);
	dsi_generic_write_seq(dsi, 0x80, 0x1b);
	dsi_generic_write_seq(dsi, 0x81, 0x01);
	dsi_generic_write_seq(dsi, 0x82, 0x24);
	dsi_generic_write_seq(dsi, 0x83, 0x01);
	dsi_generic_write_seq(dsi, 0x84, 0x46);
	dsi_generic_write_seq(dsi, 0x85, 0x01);
	dsi_generic_write_seq(dsi, 0x86, 0x63);
	dsi_generic_write_seq(dsi, 0x87, 0x01);
	dsi_generic_write_seq(dsi, 0x88, 0x94);
	dsi_generic_write_seq(dsi, 0x89, 0x01);
	dsi_generic_write_seq(dsi, 0x8a, 0xbb);
	dsi_generic_write_seq(dsi, 0x8b, 0x01);
	dsi_generic_write_seq(dsi, 0x8c, 0xfc);
	dsi_generic_write_seq(dsi, 0x8d, 0x02);
	dsi_generic_write_seq(dsi, 0x8e, 0x32);
	dsi_generic_write_seq(dsi, 0x8f, 0x02);
	dsi_generic_write_seq(dsi, 0x90, 0x32);
	dsi_generic_write_seq(dsi, 0x91, 0x02);
	dsi_generic_write_seq(dsi, 0x92, 0x66);
	dsi_generic_write_seq(dsi, 0x93, 0x02);
	dsi_generic_write_seq(dsi, 0x94, 0xa3);
	dsi_generic_write_seq(dsi, 0x95, 0x02);
	dsi_generic_write_seq(dsi, 0x96, 0xcc);
	dsi_generic_write_seq(dsi, 0x97, 0x03);
	dsi_generic_write_seq(dsi, 0x98, 0x0b);
	dsi_generic_write_seq(dsi, 0x99, 0x03);
	dsi_generic_write_seq(dsi, 0x9a, 0x38);
	dsi_generic_write_seq(dsi, 0x9b, 0x03);
	dsi_generic_write_seq(dsi, 0x9c, 0x8a);
	dsi_generic_write_seq(dsi, 0x9d, 0x03);
	dsi_generic_write_seq(dsi, 0x9e, 0x97);
	dsi_generic_write_seq(dsi, 0x9f, 0x03);
	dsi_generic_write_seq(dsi, 0xa0, 0x97);
	dsi_generic_write_seq(dsi, 0xa2, 0x03);
	dsi_generic_write_seq(dsi, 0xa3, 0x99);
	dsi_generic_write_seq(dsi, 0xa4, 0x03);
	dsi_generic_write_seq(dsi, 0xa5, 0x9b);
	dsi_generic_write_seq(dsi, 0xa6, 0x03);
	dsi_generic_write_seq(dsi, 0xa7, 0x9d);
	dsi_generic_write_seq(dsi, 0xa9, 0x03);
	dsi_generic_write_seq(dsi, 0xaa, 0x9f);
	dsi_generic_write_seq(dsi, 0xab, 0x03);
	dsi_generic_write_seq(dsi, 0xac, 0xa1);
	dsi_generic_write_seq(dsi, 0xad, 0x03);
	dsi_generic_write_seq(dsi, 0xae, 0xa2);
	dsi_generic_write_seq(dsi, 0xaf, 0x00);
	dsi_generic_write_seq(dsi, 0xb0, 0xcd);
	dsi_generic_write_seq(dsi, 0xb1, 0x00);
	dsi_generic_write_seq(dsi, 0xb2, 0xd5);
	dsi_generic_write_seq(dsi, 0xb3, 0x00);
	dsi_generic_write_seq(dsi, 0xb4, 0xe3);
	dsi_generic_write_seq(dsi, 0xb5, 0x00);
	dsi_generic_write_seq(dsi, 0xb6, 0xef);
	dsi_generic_write_seq(dsi, 0xb7, 0x00);
	dsi_generic_write_seq(dsi, 0xb8, 0xfb);
	dsi_generic_write_seq(dsi, 0xb9, 0x01);
	dsi_generic_write_seq(dsi, 0xba, 0x06);
	dsi_generic_write_seq(dsi, 0xbb, 0x01);
	dsi_generic_write_seq(dsi, 0xbc, 0x11);
	dsi_generic_write_seq(dsi, 0xbd, 0x01);
	dsi_generic_write_seq(dsi, 0xbe, 0x1b);
	dsi_generic_write_seq(dsi, 0xbf, 0x01);
	dsi_generic_write_seq(dsi, 0xc0, 0x24);
	dsi_generic_write_seq(dsi, 0xc1, 0x01);
	dsi_generic_write_seq(dsi, 0xc2, 0x46);
	dsi_generic_write_seq(dsi, 0xc3, 0x01);
	dsi_generic_write_seq(dsi, 0xc4, 0x63);
	dsi_generic_write_seq(dsi, 0xc5, 0x01);
	dsi_generic_write_seq(dsi, 0xc6, 0x94);
	dsi_generic_write_seq(dsi, 0xc7, 0x01);
	dsi_generic_write_seq(dsi, 0xc8, 0xbb);
	dsi_generic_write_seq(dsi, 0xc9, 0x01);
	dsi_generic_write_seq(dsi, 0xca, 0xfc);
	dsi_generic_write_seq(dsi, 0xcb, 0x02);
	dsi_generic_write_seq(dsi, 0xcc, 0x32);
	dsi_generic_write_seq(dsi, 0xcd, 0x02);
	dsi_generic_write_seq(dsi, 0xce, 0x32);
	dsi_generic_write_seq(dsi, 0xcf, 0x02);
	dsi_generic_write_seq(dsi, 0xd0, 0x66);
	dsi_generic_write_seq(dsi, 0xd1, 0x02);
	dsi_generic_write_seq(dsi, 0xd2, 0xa3);
	dsi_generic_write_seq(dsi, 0xd3, 0x02);
	dsi_generic_write_seq(dsi, 0xd4, 0xcc);
	dsi_generic_write_seq(dsi, 0xd5, 0x03);
	dsi_generic_write_seq(dsi, 0xd6, 0x0b);
	dsi_generic_write_seq(dsi, 0xd7, 0x03);
	dsi_generic_write_seq(dsi, 0xd8, 0x38);
	dsi_generic_write_seq(dsi, 0xd9, 0x03);
	dsi_generic_write_seq(dsi, 0xda, 0x8a);
	dsi_generic_write_seq(dsi, 0xdb, 0x03);
	dsi_generic_write_seq(dsi, 0xdc, 0x97);
	dsi_generic_write_seq(dsi, 0xdd, 0x03);
	dsi_generic_write_seq(dsi, 0xde, 0x97);
	dsi_generic_write_seq(dsi, 0xdf, 0x03);
	dsi_generic_write_seq(dsi, 0xe0, 0x99);
	dsi_generic_write_seq(dsi, 0xe1, 0x03);
	dsi_generic_write_seq(dsi, 0xe2, 0x9b);
	dsi_generic_write_seq(dsi, 0xe3, 0x03);
	dsi_generic_write_seq(dsi, 0xe4, 0x9d);
	dsi_generic_write_seq(dsi, 0xe5, 0x03);
	dsi_generic_write_seq(dsi, 0xe6, 0x9f);
	dsi_generic_write_seq(dsi, 0xe7, 0x03);
	dsi_generic_write_seq(dsi, 0xe8, 0xa1);
	dsi_generic_write_seq(dsi, 0xe9, 0x03);
	dsi_generic_write_seq(dsi, 0xea, 0xa2);
	dsi_generic_write_seq(dsi, 0xff, 0x00);
	dsi_generic_write_seq(dsi, 0x36, 0x00);
	dsi_generic_write_seq(dsi, 0x35, 0x00);
	dsi_generic_write_seq(dsi, 0xff, 0x01);
	dsi_generic_write_seq(dsi, 0xfb, 0x01);
	dsi_generic_write_seq(dsi, 0x6e, 0x00);
	dsi_generic_write_seq(dsi, 0xff, 0x04);
	dsi_generic_write_seq(dsi, 0xfb, 0x01);
	dsi_generic_write_seq(dsi, 0x08, 0x06);
	dsi_generic_write_seq(dsi, 0xff, 0x00);
	dsi_generic_write_seq(dsi, 0xfb, 0x01);
	dsi_generic_write_seq(dsi, 0x53, 0x24);
	dsi_generic_write_seq(dsi, 0x55, 0x00);
	dsi_generic_write_seq(dsi, 0xd3, 0x0a);
	dsi_generic_write_seq(dsi, 0xd4, 0x0a);

	ret = mipi_dsi_dcs_exit_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to exit sleep mode: %d\n", ret);
		return ret;
	}
	msleep(120);

	ret = mipi_dsi_dcs_set_display_on(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to set display on: %d\n", ret);
		return ret;
	}

	return 0;
}

static int boe_nt35532_off(struct boe_nt35532 *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
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
	msleep(150);

	return 0;
}

static int boe_nt35532_prepare(struct drm_panel *panel)
{
	struct boe_nt35532 *ctx = to_boe_nt35532(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	if (ctx->prepared)
		return 0;

	ret = regulator_bulk_enable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
	if (ret < 0) {
		dev_err(dev, "Failed to enable regulators: %d\n", ret);
		return ret;
	}

	boe_nt35532_reset(ctx);

	ret = boe_nt35532_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		regulator_bulk_disable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
		return ret;
	}

	ctx->prepared = true;
	return 0;
}

static int boe_nt35532_unprepare(struct drm_panel *panel)
{
	struct boe_nt35532 *ctx = to_boe_nt35532(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	if (!ctx->prepared)
		return 0;

	ret = boe_nt35532_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	regulator_bulk_disable(ARRAY_SIZE(ctx->supplies), ctx->supplies);

	ctx->prepared = false;
	return 0;
}

static const struct drm_display_mode boe_nt35532_mode = {
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
};

static int boe_nt35532_get_modes(struct drm_panel *panel,
				 struct drm_connector *connector)
{
	struct drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &boe_nt35532_mode);
	if (!mode)
		return -ENOMEM;

	drm_mode_set_name(mode);

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;
	drm_mode_probed_add(connector, mode);

	return 1;
}

static const struct drm_panel_funcs boe_nt35532_panel_funcs = {
	.prepare = boe_nt35532_prepare,
	.unprepare = boe_nt35532_unprepare,
	.get_modes = boe_nt35532_get_modes,
};

static int boe_nt35532_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct boe_nt35532 *ctx;
	int ret;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->supplies[0].supply = "vsn";
	ctx->supplies[1].supply = "vsp";
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(ctx->supplies),
				      ctx->supplies);
	if (ret < 0)
		return dev_err_probe(dev, ret, "Failed to get regulators\n");

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ctx->reset_gpio))
		return dev_err_probe(dev, PTR_ERR(ctx->reset_gpio),
				     "Failed to get reset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_CLOCK_NON_CONTINUOUS | MIPI_DSI_MODE_LPM;

	drm_panel_init(&ctx->panel, dev, &boe_nt35532_panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	ret = drm_panel_of_backlight(&ctx->panel);
	if (ret)
		return dev_err_probe(dev, ret, "Failed to get backlight\n");

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to attach to DSI host: %d\n", ret);
		drm_panel_remove(&ctx->panel);
		return ret;
	}

	return 0;
}

static void boe_nt35532_remove(struct mipi_dsi_device *dsi)
{
	struct boe_nt35532 *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id boe_nt35532_of_match[] = {
	{ .compatible = "boe,nt35532" }, // FIXME
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, boe_nt35532_of_match);

static struct mipi_dsi_driver boe_nt35532_driver = {
	.probe = boe_nt35532_probe,
	.remove = boe_nt35532_remove,
	.driver = {
		.name = "panel-boe-nt35532",
		.of_match_table = boe_nt35532_of_match,
	},
};
module_mipi_dsi_driver(boe_nt35532_driver);

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for boe nt35532 1080p video mode dsi panel");
MODULE_LICENSE("GPL");
