// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2022 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/backlight.h>
#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/regulator/consumer.h>

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>

struct boe_nt35596s_5p5boe_vdo {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct regulator_bulk_data supplies[2];
	struct gpio_desc *reset_gpio;
	bool prepared;
};

static inline
struct boe_nt35596s_5p5boe_vdo *to_boe_nt35596s_5p5boe_vdo(struct drm_panel *panel)
{
	return container_of(panel, struct boe_nt35596s_5p5boe_vdo, panel);
}

#define dsi_generic_write_seq(dsi, seq...) do {				\
		static const u8 d[] = { seq };				\
		int ret;						\
		ret = mipi_dsi_generic_write(dsi, d, ARRAY_SIZE(d));	\
		if (ret < 0)						\
			return ret;					\
	} while (0)

#define dsi_dcs_write_seq(dsi, seq...) do {				\
		static const u8 d[] = { seq };				\
		int ret;						\
		ret = mipi_dsi_dcs_write_buffer(dsi, d, ARRAY_SIZE(d));	\
		if (ret < 0)						\
			return ret;					\
	} while (0)

static void boe_nt35596s_5p5boe_vdo_reset(struct boe_nt35596s_5p5boe_vdo *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
}

static int boe_nt35596s_5p5boe_vdo_on(struct boe_nt35596s_5p5boe_vdo *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
	struct device *dev = &dsi->dev;
	int ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	dsi_generic_write_seq(dsi, 0xff, 0xf0);
	dsi_generic_write_seq(dsi, 0xfb, 0x01);
	dsi_generic_write_seq(dsi, 0xe5, 0x02);
	dsi_generic_write_seq(dsi, 0xff, 0x20);
	dsi_generic_write_seq(dsi, 0xfb, 0x01);
	dsi_generic_write_seq(dsi, 0x30, 0x0f);
	dsi_generic_write_seq(dsi, 0x01, 0x55);
	dsi_generic_write_seq(dsi, 0x02, 0x55);
	dsi_generic_write_seq(dsi, 0x05, 0x50);
	dsi_generic_write_seq(dsi, 0x06, 0x99);
	dsi_generic_write_seq(dsi, 0x07, 0xa3);
	dsi_generic_write_seq(dsi, 0x13, 0x00);
	dsi_generic_write_seq(dsi, 0x0b, 0xaf);
	dsi_generic_write_seq(dsi, 0x0c, 0xaf);
	dsi_generic_write_seq(dsi, 0x0e, 0xab);
	dsi_generic_write_seq(dsi, 0x0f, 0xae);
	dsi_generic_write_seq(dsi, 0x58, 0x82);
	dsi_generic_write_seq(dsi, 0x59, 0x02);
	dsi_generic_write_seq(dsi, 0x5a, 0x00);
	dsi_generic_write_seq(dsi, 0x5b, 0x02);
	dsi_generic_write_seq(dsi, 0x5c, 0x82);
	dsi_generic_write_seq(dsi, 0x5d, 0x82);
	dsi_generic_write_seq(dsi, 0x5e, 0x00);
	dsi_generic_write_seq(dsi, 0x5f, 0x02);
	dsi_generic_write_seq(dsi, 0x60, 0x02);
	dsi_generic_write_seq(dsi, 0x61, 0x02);
	dsi_generic_write_seq(dsi, 0x62, 0x02);
	dsi_generic_write_seq(dsi, 0x63, 0x02);
	dsi_generic_write_seq(dsi, 0x15, 0x01);
	dsi_generic_write_seq(dsi, 0x44, 0x72);
	dsi_generic_write_seq(dsi, 0x45, 0x68);
	dsi_generic_write_seq(dsi, 0x46, 0x81);
	dsi_generic_write_seq(dsi, 0xff, 0x20);
	dsi_generic_write_seq(dsi, 0xfb, 0x01);
	dsi_generic_write_seq(dsi, 0x75, 0x00);
	dsi_generic_write_seq(dsi, 0x76, 0x00);
	dsi_generic_write_seq(dsi, 0x77, 0x00);
	dsi_generic_write_seq(dsi, 0x78, 0x0f);
	dsi_generic_write_seq(dsi, 0x79, 0x00);
	dsi_generic_write_seq(dsi, 0x7a, 0x2b);
	dsi_generic_write_seq(dsi, 0x7b, 0x00);
	dsi_generic_write_seq(dsi, 0x7c, 0x44);
	dsi_generic_write_seq(dsi, 0x7d, 0x00);
	dsi_generic_write_seq(dsi, 0x7e, 0x5a);
	dsi_generic_write_seq(dsi, 0x7f, 0x00);
	dsi_generic_write_seq(dsi, 0x80, 0x6f);
	dsi_generic_write_seq(dsi, 0x81, 0x00);
	dsi_generic_write_seq(dsi, 0x82, 0x81);
	dsi_generic_write_seq(dsi, 0x83, 0x00);
	dsi_generic_write_seq(dsi, 0x84, 0x92);
	dsi_generic_write_seq(dsi, 0x85, 0x00);
	dsi_generic_write_seq(dsi, 0x86, 0xa2);
	dsi_generic_write_seq(dsi, 0x87, 0x00);
	dsi_generic_write_seq(dsi, 0x88, 0xd5);
	dsi_generic_write_seq(dsi, 0x89, 0x00);
	dsi_generic_write_seq(dsi, 0x8a, 0xfe);
	dsi_generic_write_seq(dsi, 0x8b, 0x01);
	dsi_generic_write_seq(dsi, 0x8c, 0x3c);
	dsi_generic_write_seq(dsi, 0x8d, 0x01);
	dsi_generic_write_seq(dsi, 0x8e, 0x6c);
	dsi_generic_write_seq(dsi, 0x8f, 0x01);
	dsi_generic_write_seq(dsi, 0x90, 0xb5);
	dsi_generic_write_seq(dsi, 0x91, 0x01);
	dsi_generic_write_seq(dsi, 0x92, 0xef);
	dsi_generic_write_seq(dsi, 0x93, 0x01);
	dsi_generic_write_seq(dsi, 0x94, 0xf1);
	dsi_generic_write_seq(dsi, 0x95, 0x02);
	dsi_generic_write_seq(dsi, 0x96, 0x29);
	dsi_generic_write_seq(dsi, 0x97, 0x02);
	dsi_generic_write_seq(dsi, 0x98, 0x6c);
	dsi_generic_write_seq(dsi, 0x99, 0x02);
	dsi_generic_write_seq(dsi, 0x9a, 0x99);
	dsi_generic_write_seq(dsi, 0x9b, 0x02);
	dsi_generic_write_seq(dsi, 0x9c, 0xd9);
	dsi_generic_write_seq(dsi, 0x9d, 0x02);
	dsi_generic_write_seq(dsi, 0x9e, 0xfc);
	dsi_generic_write_seq(dsi, 0x9f, 0x03);
	dsi_generic_write_seq(dsi, 0xa0, 0x2f);
	dsi_generic_write_seq(dsi, 0xa2, 0x03);
	dsi_generic_write_seq(dsi, 0xa3, 0x41);
	dsi_generic_write_seq(dsi, 0xa4, 0x03);
	dsi_generic_write_seq(dsi, 0xa5, 0x53);
	dsi_generic_write_seq(dsi, 0xa6, 0x03);
	dsi_generic_write_seq(dsi, 0xa7, 0x66);
	dsi_generic_write_seq(dsi, 0xa9, 0x03);
	dsi_generic_write_seq(dsi, 0xaa, 0x7a);
	dsi_generic_write_seq(dsi, 0xab, 0x03);
	dsi_generic_write_seq(dsi, 0xac, 0x90);
	dsi_generic_write_seq(dsi, 0xad, 0x03);
	dsi_generic_write_seq(dsi, 0xae, 0xa9);
	dsi_generic_write_seq(dsi, 0xaf, 0x03);
	dsi_generic_write_seq(dsi, 0xb0, 0xc7);
	dsi_generic_write_seq(dsi, 0xb1, 0x03);
	dsi_generic_write_seq(dsi, 0xb2, 0xd3);
	dsi_generic_write_seq(dsi, 0xb3, 0x00);
	dsi_generic_write_seq(dsi, 0xb4, 0x00);
	dsi_generic_write_seq(dsi, 0xb5, 0x00);
	dsi_generic_write_seq(dsi, 0xb6, 0x0f);
	dsi_generic_write_seq(dsi, 0xb7, 0x00);
	dsi_generic_write_seq(dsi, 0xb8, 0x2b);
	dsi_generic_write_seq(dsi, 0xb9, 0x00);
	dsi_generic_write_seq(dsi, 0xba, 0x44);
	dsi_generic_write_seq(dsi, 0xbb, 0x00);
	dsi_generic_write_seq(dsi, 0xbc, 0x5a);
	dsi_generic_write_seq(dsi, 0xbd, 0x00);
	dsi_generic_write_seq(dsi, 0xbe, 0x6f);
	dsi_generic_write_seq(dsi, 0xbf, 0x00);
	dsi_generic_write_seq(dsi, 0xc0, 0x81);
	dsi_generic_write_seq(dsi, 0xc1, 0x00);
	dsi_generic_write_seq(dsi, 0xc2, 0x92);
	dsi_generic_write_seq(dsi, 0xc3, 0x00);
	dsi_generic_write_seq(dsi, 0xc4, 0xa2);
	dsi_generic_write_seq(dsi, 0xc5, 0x00);
	dsi_generic_write_seq(dsi, 0xc6, 0xd5);
	dsi_generic_write_seq(dsi, 0xc7, 0x00);
	dsi_generic_write_seq(dsi, 0xc8, 0xfe);
	dsi_generic_write_seq(dsi, 0xc9, 0x01);
	dsi_generic_write_seq(dsi, 0xca, 0x3c);
	dsi_generic_write_seq(dsi, 0xcb, 0x01);
	dsi_generic_write_seq(dsi, 0xcc, 0x6c);
	dsi_generic_write_seq(dsi, 0xcd, 0x01);
	dsi_generic_write_seq(dsi, 0xce, 0xb5);
	dsi_generic_write_seq(dsi, 0xcf, 0x01);
	dsi_generic_write_seq(dsi, 0xd0, 0xef);
	dsi_generic_write_seq(dsi, 0xd1, 0x01);
	dsi_generic_write_seq(dsi, 0xd2, 0xf1);
	dsi_generic_write_seq(dsi, 0xd3, 0x02);
	dsi_generic_write_seq(dsi, 0xd4, 0x29);
	dsi_generic_write_seq(dsi, 0xd5, 0x02);
	dsi_generic_write_seq(dsi, 0xd6, 0x6c);
	dsi_generic_write_seq(dsi, 0xd7, 0x02);
	dsi_generic_write_seq(dsi, 0xd8, 0x99);
	dsi_generic_write_seq(dsi, 0xd9, 0x02);
	dsi_generic_write_seq(dsi, 0xda, 0xd9);
	dsi_generic_write_seq(dsi, 0xdb, 0x02);
	dsi_generic_write_seq(dsi, 0xdc, 0xfc);
	dsi_generic_write_seq(dsi, 0xdd, 0x03);
	dsi_generic_write_seq(dsi, 0xde, 0x2f);
	dsi_generic_write_seq(dsi, 0xdf, 0x03);
	dsi_generic_write_seq(dsi, 0xe0, 0x41);
	dsi_generic_write_seq(dsi, 0xe1, 0x03);
	dsi_generic_write_seq(dsi, 0xe2, 0x53);
	dsi_generic_write_seq(dsi, 0xe3, 0x03);
	dsi_generic_write_seq(dsi, 0xe4, 0x66);
	dsi_generic_write_seq(dsi, 0xe5, 0x03);
	dsi_generic_write_seq(dsi, 0xe6, 0x7a);
	dsi_generic_write_seq(dsi, 0xe7, 0x03);
	dsi_generic_write_seq(dsi, 0xe8, 0x90);
	dsi_generic_write_seq(dsi, 0xe9, 0x03);
	dsi_generic_write_seq(dsi, 0xea, 0xa9);
	dsi_generic_write_seq(dsi, 0xeb, 0x03);
	dsi_generic_write_seq(dsi, 0xec, 0xc7);
	dsi_generic_write_seq(dsi, 0xed, 0x03);
	dsi_generic_write_seq(dsi, 0xee, 0xd3);
	dsi_generic_write_seq(dsi, 0xef, 0x00);
	dsi_generic_write_seq(dsi, 0xf0, 0x00);
	dsi_generic_write_seq(dsi, 0xf1, 0x00);
	dsi_generic_write_seq(dsi, 0xf2, 0x0f);
	dsi_generic_write_seq(dsi, 0xf3, 0x00);
	dsi_generic_write_seq(dsi, 0xf4, 0x2b);
	dsi_generic_write_seq(dsi, 0xf5, 0x00);
	dsi_generic_write_seq(dsi, 0xf6, 0x44);
	dsi_generic_write_seq(dsi, 0xf7, 0x00);
	dsi_generic_write_seq(dsi, 0xf8, 0x5a);
	dsi_generic_write_seq(dsi, 0xf9, 0x00);
	dsi_generic_write_seq(dsi, 0xfa, 0x6f);
	dsi_generic_write_seq(dsi, 0xff, 0x21);
	dsi_generic_write_seq(dsi, 0xfb, 0x01);
	dsi_generic_write_seq(dsi, 0x00, 0x00);
	dsi_generic_write_seq(dsi, 0x01, 0x81);
	dsi_generic_write_seq(dsi, 0x02, 0x00);
	dsi_generic_write_seq(dsi, 0x03, 0x92);
	dsi_generic_write_seq(dsi, 0x04, 0x00);
	dsi_generic_write_seq(dsi, 0x05, 0xa2);
	dsi_generic_write_seq(dsi, 0x06, 0x00);
	dsi_generic_write_seq(dsi, 0x07, 0xd5);
	dsi_generic_write_seq(dsi, 0x08, 0x00);
	dsi_generic_write_seq(dsi, 0x09, 0xfe);
	dsi_generic_write_seq(dsi, 0x0a, 0x01);
	dsi_generic_write_seq(dsi, 0x0b, 0x3c);
	dsi_generic_write_seq(dsi, 0x0c, 0x01);
	dsi_generic_write_seq(dsi, 0x0d, 0x6c);
	dsi_generic_write_seq(dsi, 0x0e, 0x01);
	dsi_generic_write_seq(dsi, 0x0f, 0xb5);
	dsi_generic_write_seq(dsi, 0x10, 0x01);
	dsi_generic_write_seq(dsi, 0x11, 0xef);
	dsi_generic_write_seq(dsi, 0x12, 0x01);
	dsi_generic_write_seq(dsi, 0x13, 0xf1);
	dsi_generic_write_seq(dsi, 0x14, 0x02);
	dsi_generic_write_seq(dsi, 0x15, 0x29);
	dsi_generic_write_seq(dsi, 0x16, 0x02);
	dsi_generic_write_seq(dsi, 0x17, 0x6c);
	dsi_generic_write_seq(dsi, 0x18, 0x02);
	dsi_generic_write_seq(dsi, 0x19, 0x99);
	dsi_generic_write_seq(dsi, 0x1a, 0x02);
	dsi_generic_write_seq(dsi, 0x1b, 0xd9);
	dsi_generic_write_seq(dsi, 0x1c, 0x02);
	dsi_generic_write_seq(dsi, 0x1d, 0xfc);
	dsi_generic_write_seq(dsi, 0x1e, 0x03);
	dsi_generic_write_seq(dsi, 0x1f, 0x2f);
	dsi_generic_write_seq(dsi, 0x20, 0x03);
	dsi_generic_write_seq(dsi, 0x21, 0x41);
	dsi_generic_write_seq(dsi, 0x22, 0x03);
	dsi_generic_write_seq(dsi, 0x23, 0x53);
	dsi_generic_write_seq(dsi, 0x24, 0x03);
	dsi_generic_write_seq(dsi, 0x25, 0x66);
	dsi_generic_write_seq(dsi, 0x26, 0x03);
	dsi_generic_write_seq(dsi, 0x27, 0x7a);
	dsi_generic_write_seq(dsi, 0x28, 0x03);
	dsi_generic_write_seq(dsi, 0x29, 0x90);
	dsi_generic_write_seq(dsi, 0x2a, 0x03);
	dsi_generic_write_seq(dsi, 0x2b, 0xa9);
	dsi_generic_write_seq(dsi, 0x2d, 0x03);
	dsi_generic_write_seq(dsi, 0x2f, 0xc7);
	dsi_generic_write_seq(dsi, 0x30, 0x03);
	dsi_generic_write_seq(dsi, 0x31, 0xd3);
	dsi_generic_write_seq(dsi, 0x32, 0x00);
	dsi_generic_write_seq(dsi, 0x33, 0x00);
	dsi_generic_write_seq(dsi, 0x34, 0x00);
	dsi_generic_write_seq(dsi, 0x35, 0x0f);
	dsi_generic_write_seq(dsi, 0x36, 0x00);
	dsi_generic_write_seq(dsi, 0x37, 0x2b);
	dsi_generic_write_seq(dsi, 0x38, 0x00);
	dsi_generic_write_seq(dsi, 0x39, 0x44);
	dsi_generic_write_seq(dsi, 0x3a, 0x00);
	dsi_generic_write_seq(dsi, 0x3b, 0x5a);
	dsi_generic_write_seq(dsi, 0x3d, 0x00);
	dsi_generic_write_seq(dsi, 0x3f, 0x6f);
	dsi_generic_write_seq(dsi, 0x40, 0x00);
	dsi_generic_write_seq(dsi, 0x41, 0x81);
	dsi_generic_write_seq(dsi, 0x42, 0x00);
	dsi_generic_write_seq(dsi, 0x43, 0x92);
	dsi_generic_write_seq(dsi, 0x44, 0x00);
	dsi_generic_write_seq(dsi, 0x45, 0xa2);
	dsi_generic_write_seq(dsi, 0x46, 0x00);
	dsi_generic_write_seq(dsi, 0x47, 0xd5);
	dsi_generic_write_seq(dsi, 0x48, 0x00);
	dsi_generic_write_seq(dsi, 0x49, 0xfe);
	dsi_generic_write_seq(dsi, 0x4a, 0x01);
	dsi_generic_write_seq(dsi, 0x4b, 0x3c);
	dsi_generic_write_seq(dsi, 0x4c, 0x01);
	dsi_generic_write_seq(dsi, 0x4d, 0x6c);
	dsi_generic_write_seq(dsi, 0x4e, 0x01);
	dsi_generic_write_seq(dsi, 0x4f, 0xb5);
	dsi_generic_write_seq(dsi, 0x50, 0x01);
	dsi_generic_write_seq(dsi, 0x51, 0xef);
	dsi_generic_write_seq(dsi, 0x52, 0x01);
	dsi_generic_write_seq(dsi, 0x53, 0xf1);
	dsi_generic_write_seq(dsi, 0x54, 0x02);
	dsi_generic_write_seq(dsi, 0x55, 0x29);
	dsi_generic_write_seq(dsi, 0x56, 0x02);
	dsi_generic_write_seq(dsi, 0x58, 0x6c);
	dsi_generic_write_seq(dsi, 0x59, 0x02);
	dsi_generic_write_seq(dsi, 0x5a, 0x99);
	dsi_generic_write_seq(dsi, 0x5b, 0x02);
	dsi_generic_write_seq(dsi, 0x5c, 0xd9);
	dsi_generic_write_seq(dsi, 0x5d, 0x02);
	dsi_generic_write_seq(dsi, 0x5e, 0xfc);
	dsi_generic_write_seq(dsi, 0x5f, 0x03);
	dsi_generic_write_seq(dsi, 0x60, 0x2f);
	dsi_generic_write_seq(dsi, 0x61, 0x03);
	dsi_generic_write_seq(dsi, 0x62, 0x41);
	dsi_generic_write_seq(dsi, 0x63, 0x03);
	dsi_generic_write_seq(dsi, 0x64, 0x53);
	dsi_generic_write_seq(dsi, 0x65, 0x03);
	dsi_generic_write_seq(dsi, 0x66, 0x66);
	dsi_generic_write_seq(dsi, 0x67, 0x03);
	dsi_generic_write_seq(dsi, 0x68, 0x7a);
	dsi_generic_write_seq(dsi, 0x69, 0x03);
	dsi_generic_write_seq(dsi, 0x6a, 0x90);
	dsi_generic_write_seq(dsi, 0x6b, 0x03);
	dsi_generic_write_seq(dsi, 0x6c, 0xa9);
	dsi_generic_write_seq(dsi, 0x6d, 0x03);
	dsi_generic_write_seq(dsi, 0x6e, 0xc7);
	dsi_generic_write_seq(dsi, 0x6f, 0x03);
	dsi_generic_write_seq(dsi, 0x70, 0xd3);
	dsi_generic_write_seq(dsi, 0x71, 0x00);
	dsi_generic_write_seq(dsi, 0x72, 0x00);
	dsi_generic_write_seq(dsi, 0x73, 0x00);
	dsi_generic_write_seq(dsi, 0x74, 0x0f);
	dsi_generic_write_seq(dsi, 0x75, 0x00);
	dsi_generic_write_seq(dsi, 0x76, 0x2b);
	dsi_generic_write_seq(dsi, 0x77, 0x00);
	dsi_generic_write_seq(dsi, 0x78, 0x44);
	dsi_generic_write_seq(dsi, 0x79, 0x00);
	dsi_generic_write_seq(dsi, 0x7a, 0x5a);
	dsi_generic_write_seq(dsi, 0x7b, 0x00);
	dsi_generic_write_seq(dsi, 0x7c, 0x6f);
	dsi_generic_write_seq(dsi, 0x7d, 0x00);
	dsi_generic_write_seq(dsi, 0x7e, 0x81);
	dsi_generic_write_seq(dsi, 0x7f, 0x00);
	dsi_generic_write_seq(dsi, 0x80, 0x92);
	dsi_generic_write_seq(dsi, 0x81, 0x00);
	dsi_generic_write_seq(dsi, 0x82, 0xa2);
	dsi_generic_write_seq(dsi, 0x83, 0x00);
	dsi_generic_write_seq(dsi, 0x84, 0xd5);
	dsi_generic_write_seq(dsi, 0x85, 0x00);
	dsi_generic_write_seq(dsi, 0x86, 0xfe);
	dsi_generic_write_seq(dsi, 0x87, 0x01);
	dsi_generic_write_seq(dsi, 0x88, 0x3c);
	dsi_generic_write_seq(dsi, 0x89, 0x01);
	dsi_generic_write_seq(dsi, 0x8a, 0x6c);
	dsi_generic_write_seq(dsi, 0x8b, 0x01);
	dsi_generic_write_seq(dsi, 0x8c, 0xb5);
	dsi_generic_write_seq(dsi, 0x8d, 0x01);
	dsi_generic_write_seq(dsi, 0x8e, 0xef);
	dsi_generic_write_seq(dsi, 0x8f, 0x01);
	dsi_generic_write_seq(dsi, 0x90, 0xf1);
	dsi_generic_write_seq(dsi, 0x91, 0x02);
	dsi_generic_write_seq(dsi, 0x92, 0x29);
	dsi_generic_write_seq(dsi, 0x93, 0x02);
	dsi_generic_write_seq(dsi, 0x94, 0x6c);
	dsi_generic_write_seq(dsi, 0x95, 0x02);
	dsi_generic_write_seq(dsi, 0x96, 0x99);
	dsi_generic_write_seq(dsi, 0x97, 0x02);
	dsi_generic_write_seq(dsi, 0x98, 0xd9);
	dsi_generic_write_seq(dsi, 0x99, 0x02);
	dsi_generic_write_seq(dsi, 0x9a, 0xfc);
	dsi_generic_write_seq(dsi, 0x9b, 0x03);
	dsi_generic_write_seq(dsi, 0x9c, 0x2f);
	dsi_generic_write_seq(dsi, 0x9d, 0x03);
	dsi_generic_write_seq(dsi, 0x9e, 0x41);
	dsi_generic_write_seq(dsi, 0x9f, 0x03);
	dsi_generic_write_seq(dsi, 0xa0, 0x53);
	dsi_generic_write_seq(dsi, 0xa2, 0x03);
	dsi_generic_write_seq(dsi, 0xa3, 0x66);
	dsi_generic_write_seq(dsi, 0xa4, 0x03);
	dsi_generic_write_seq(dsi, 0xa5, 0x7a);
	dsi_generic_write_seq(dsi, 0xa6, 0x03);
	dsi_generic_write_seq(dsi, 0xa7, 0x90);
	dsi_generic_write_seq(dsi, 0xa9, 0x03);
	dsi_generic_write_seq(dsi, 0xaa, 0xa9);
	dsi_generic_write_seq(dsi, 0xab, 0x03);
	dsi_generic_write_seq(dsi, 0xac, 0xc7);
	dsi_generic_write_seq(dsi, 0xad, 0x03);
	dsi_generic_write_seq(dsi, 0xae, 0xd3);
	dsi_generic_write_seq(dsi, 0xaf, 0x00);
	dsi_generic_write_seq(dsi, 0xb0, 0x00);
	dsi_generic_write_seq(dsi, 0xb1, 0x00);
	dsi_generic_write_seq(dsi, 0xb2, 0x0f);
	dsi_generic_write_seq(dsi, 0xb3, 0x00);
	dsi_generic_write_seq(dsi, 0xb4, 0x2b);
	dsi_generic_write_seq(dsi, 0xb5, 0x00);
	dsi_generic_write_seq(dsi, 0xb6, 0x44);
	dsi_generic_write_seq(dsi, 0xb7, 0x00);
	dsi_generic_write_seq(dsi, 0xb8, 0x5a);
	dsi_generic_write_seq(dsi, 0xb9, 0x00);
	dsi_generic_write_seq(dsi, 0xba, 0x6f);
	dsi_generic_write_seq(dsi, 0xbb, 0x00);
	dsi_generic_write_seq(dsi, 0xbc, 0x81);
	dsi_generic_write_seq(dsi, 0xbd, 0x00);
	dsi_generic_write_seq(dsi, 0xbe, 0x92);
	dsi_generic_write_seq(dsi, 0xbf, 0x00);
	dsi_generic_write_seq(dsi, 0xc0, 0xa2);
	dsi_generic_write_seq(dsi, 0xc1, 0x00);
	dsi_generic_write_seq(dsi, 0xc2, 0xd5);
	dsi_generic_write_seq(dsi, 0xc3, 0x00);
	dsi_generic_write_seq(dsi, 0xc4, 0xfe);
	dsi_generic_write_seq(dsi, 0xc5, 0x01);
	dsi_generic_write_seq(dsi, 0xc6, 0x3c);
	dsi_generic_write_seq(dsi, 0xc7, 0x01);
	dsi_generic_write_seq(dsi, 0xc8, 0x6c);
	dsi_generic_write_seq(dsi, 0xc9, 0x01);
	dsi_generic_write_seq(dsi, 0xca, 0xb5);
	dsi_generic_write_seq(dsi, 0xcb, 0x01);
	dsi_generic_write_seq(dsi, 0xcc, 0xef);
	dsi_generic_write_seq(dsi, 0xcd, 0x01);
	dsi_generic_write_seq(dsi, 0xce, 0xf1);
	dsi_generic_write_seq(dsi, 0xcf, 0x02);
	dsi_generic_write_seq(dsi, 0xd0, 0x29);
	dsi_generic_write_seq(dsi, 0xd1, 0x02);
	dsi_generic_write_seq(dsi, 0xd2, 0x6c);
	dsi_generic_write_seq(dsi, 0xd3, 0x02);
	dsi_generic_write_seq(dsi, 0xd4, 0x99);
	dsi_generic_write_seq(dsi, 0xd5, 0x02);
	dsi_generic_write_seq(dsi, 0xd6, 0xd9);
	dsi_generic_write_seq(dsi, 0xd7, 0x02);
	dsi_generic_write_seq(dsi, 0xd8, 0xfc);
	dsi_generic_write_seq(dsi, 0xd9, 0x03);
	dsi_generic_write_seq(dsi, 0xda, 0x2f);
	dsi_generic_write_seq(dsi, 0xdb, 0x03);
	dsi_generic_write_seq(dsi, 0xdc, 0x41);
	dsi_generic_write_seq(dsi, 0xdd, 0x03);
	dsi_generic_write_seq(dsi, 0xde, 0x53);
	dsi_generic_write_seq(dsi, 0xdf, 0x03);
	dsi_generic_write_seq(dsi, 0xe0, 0x66);
	dsi_generic_write_seq(dsi, 0xe1, 0x03);
	dsi_generic_write_seq(dsi, 0xe2, 0x7a);
	dsi_generic_write_seq(dsi, 0xe3, 0x03);
	dsi_generic_write_seq(dsi, 0xe4, 0x90);
	dsi_generic_write_seq(dsi, 0xe5, 0x03);
	dsi_generic_write_seq(dsi, 0xe6, 0xa9);
	dsi_generic_write_seq(dsi, 0xe7, 0x03);
	dsi_generic_write_seq(dsi, 0xe8, 0xc7);
	dsi_generic_write_seq(dsi, 0xe9, 0x03);
	dsi_generic_write_seq(dsi, 0xea, 0xd3);
	dsi_generic_write_seq(dsi, 0xff, 0x24);
	dsi_generic_write_seq(dsi, 0xfb, 0x01);
	dsi_generic_write_seq(dsi, 0x00, 0x00);
	dsi_generic_write_seq(dsi, 0x01, 0x01);
	dsi_generic_write_seq(dsi, 0x02, 0x0b);
	dsi_generic_write_seq(dsi, 0x03, 0x0c);
	dsi_generic_write_seq(dsi, 0x04, 0x00);
	dsi_generic_write_seq(dsi, 0x05, 0x03);
	dsi_generic_write_seq(dsi, 0x06, 0x00);
	dsi_generic_write_seq(dsi, 0x07, 0x04);
	dsi_generic_write_seq(dsi, 0x08, 0x00);
	dsi_generic_write_seq(dsi, 0x09, 0x00);
	dsi_generic_write_seq(dsi, 0x0a, 0x00);
	dsi_generic_write_seq(dsi, 0x0b, 0x00);
	dsi_generic_write_seq(dsi, 0x0c, 0x00);
	dsi_generic_write_seq(dsi, 0x0d, 0x17);
	dsi_generic_write_seq(dsi, 0x0e, 0x15);
	dsi_generic_write_seq(dsi, 0x0f, 0x13);
	dsi_generic_write_seq(dsi, 0x10, 0x00);
	dsi_generic_write_seq(dsi, 0x11, 0x01);
	dsi_generic_write_seq(dsi, 0x12, 0x0b);
	dsi_generic_write_seq(dsi, 0x13, 0x0c);
	dsi_generic_write_seq(dsi, 0x14, 0x00);
	dsi_generic_write_seq(dsi, 0x15, 0x03);
	dsi_generic_write_seq(dsi, 0x16, 0x00);
	dsi_generic_write_seq(dsi, 0x17, 0x04);
	dsi_generic_write_seq(dsi, 0x18, 0x00);
	dsi_generic_write_seq(dsi, 0x19, 0x00);
	dsi_generic_write_seq(dsi, 0x1a, 0x00);
	dsi_generic_write_seq(dsi, 0x1b, 0x00);
	dsi_generic_write_seq(dsi, 0x1c, 0x00);
	dsi_generic_write_seq(dsi, 0x1d, 0x17);
	dsi_generic_write_seq(dsi, 0x1e, 0x15);
	dsi_generic_write_seq(dsi, 0x1f, 0x13);
	dsi_generic_write_seq(dsi, 0x20, 0x09);
	dsi_generic_write_seq(dsi, 0x21, 0x02);
	dsi_generic_write_seq(dsi, 0x22, 0x00);
	dsi_generic_write_seq(dsi, 0x23, 0x02);
	dsi_generic_write_seq(dsi, 0x24, 0x0a);
	dsi_generic_write_seq(dsi, 0x25, 0x3d);
	dsi_generic_write_seq(dsi, 0x26, 0x02);
	dsi_generic_write_seq(dsi, 0x27, 0x0a);
	dsi_generic_write_seq(dsi, 0x28, 0x38);
	dsi_generic_write_seq(dsi, 0x29, 0x2b);
	dsi_generic_write_seq(dsi, 0x2f, 0x02);
	dsi_generic_write_seq(dsi, 0x30, 0x01);
	dsi_generic_write_seq(dsi, 0x31, 0x49);
	dsi_generic_write_seq(dsi, 0x32, 0x23);
	dsi_generic_write_seq(dsi, 0x33, 0x01);
	dsi_generic_write_seq(dsi, 0x34, 0x03);
	dsi_generic_write_seq(dsi, 0x35, 0x6d);
	dsi_generic_write_seq(dsi, 0x36, 0x00);
	dsi_generic_write_seq(dsi, 0x37, 0x2d);
	dsi_generic_write_seq(dsi, 0x38, 0x08);
	dsi_generic_write_seq(dsi, 0x39, 0x03);
	dsi_generic_write_seq(dsi, 0x3a, 0x6d);
	dsi_generic_write_seq(dsi, 0x3b, 0x23);
	dsi_generic_write_seq(dsi, 0x74, 0x04);
	dsi_generic_write_seq(dsi, 0x75, 0x1f);
	dsi_generic_write_seq(dsi, 0x76, 0x03);
	dsi_generic_write_seq(dsi, 0x77, 0x01);
	dsi_generic_write_seq(dsi, 0x78, 0x00);
	dsi_generic_write_seq(dsi, 0x79, 0x00);
	dsi_generic_write_seq(dsi, 0x7a, 0x00);
	dsi_generic_write_seq(dsi, 0x7b, 0xa2);
	dsi_generic_write_seq(dsi, 0x7c, 0xd8);
	dsi_generic_write_seq(dsi, 0x7d, 0x50);
	dsi_generic_write_seq(dsi, 0x7e, 0x04);
	dsi_generic_write_seq(dsi, 0x7f, 0x1f);
	dsi_generic_write_seq(dsi, 0x80, 0x00);
	dsi_generic_write_seq(dsi, 0x81, 0x03);
	dsi_generic_write_seq(dsi, 0x82, 0x01);
	dsi_generic_write_seq(dsi, 0x83, 0x00);
	dsi_generic_write_seq(dsi, 0x84, 0x03);
	dsi_generic_write_seq(dsi, 0x85, 0x02);
	dsi_generic_write_seq(dsi, 0x86, 0x5b);
	dsi_generic_write_seq(dsi, 0x87, 0x39);
	dsi_generic_write_seq(dsi, 0x88, 0x1b);
	dsi_generic_write_seq(dsi, 0x89, 0x39);
	dsi_generic_write_seq(dsi, 0x8a, 0xff);
	dsi_generic_write_seq(dsi, 0x8b, 0xf4);
	dsi_generic_write_seq(dsi, 0x8c, 0x01);
	dsi_generic_write_seq(dsi, 0x9b, 0xff);
	dsi_generic_write_seq(dsi, 0x9d, 0x30);
	dsi_generic_write_seq(dsi, 0x72, 0x00);
	dsi_generic_write_seq(dsi, 0x73, 0x00);
	dsi_generic_write_seq(dsi, 0x90, 0x72);
	dsi_generic_write_seq(dsi, 0x91, 0x40);
	dsi_generic_write_seq(dsi, 0x92, 0x72);
	dsi_generic_write_seq(dsi, 0x93, 0x04);
	dsi_generic_write_seq(dsi, 0x94, 0x04);
	dsi_generic_write_seq(dsi, 0x95, 0xff);
	dsi_generic_write_seq(dsi, 0x97, 0x00);
	dsi_generic_write_seq(dsi, 0xb9, 0x02);
	dsi_generic_write_seq(dsi, 0xba, 0x82);
	dsi_generic_write_seq(dsi, 0xc4, 0x24);
	dsi_generic_write_seq(dsi, 0xc5, 0x3a);
	dsi_generic_write_seq(dsi, 0xc6, 0x09);
	dsi_generic_write_seq(dsi, 0xff, 0x2e);
	dsi_generic_write_seq(dsi, 0xfb, 0x01);
	dsi_generic_write_seq(dsi, 0x00, 0x29);
	dsi_generic_write_seq(dsi, 0x01, 0x30);
	dsi_generic_write_seq(dsi, 0x02, 0x17);
	dsi_generic_write_seq(dsi, 0x03, 0x0c);
	dsi_generic_write_seq(dsi, 0x04, 0x01);
	dsi_generic_write_seq(dsi, 0x05, 0x25);
	dsi_generic_write_seq(dsi, 0x06, 0x30);
	dsi_generic_write_seq(dsi, 0x07, 0x06);
	dsi_generic_write_seq(dsi, 0x08, 0x88);
	dsi_generic_write_seq(dsi, 0x09, 0xc8);
	dsi_generic_write_seq(dsi, 0x0a, 0x00);
	dsi_generic_write_seq(dsi, 0xf3, 0x91);
	dsi_generic_write_seq(dsi, 0x0b, 0x0c);
	dsi_generic_write_seq(dsi, 0x0c, 0x6c);
	dsi_generic_write_seq(dsi, 0x0d, 0x1f);
	dsi_generic_write_seq(dsi, 0x0e, 0x1e);
	dsi_generic_write_seq(dsi, 0x0f, 0x01);
	dsi_generic_write_seq(dsi, 0x10, 0x05);
	dsi_generic_write_seq(dsi, 0x11, 0x00);
	dsi_generic_write_seq(dsi, 0x13, 0x0b);
	dsi_generic_write_seq(dsi, 0x14, 0x10);
	dsi_generic_write_seq(dsi, 0x15, 0x01);
	dsi_generic_write_seq(dsi, 0x16, 0x00);
	dsi_generic_write_seq(dsi, 0x17, 0x00);
	dsi_generic_write_seq(dsi, 0x18, 0x42);
	dsi_generic_write_seq(dsi, 0x19, 0x00);
	dsi_generic_write_seq(dsi, 0x1a, 0x21);
	dsi_generic_write_seq(dsi, 0x1b, 0x00);
	dsi_generic_write_seq(dsi, 0x1c, 0x11);
	dsi_generic_write_seq(dsi, 0x1d, 0x9b);
	dsi_generic_write_seq(dsi, 0x1e, 0x1d);
	dsi_generic_write_seq(dsi, 0x1f, 0x21);
	dsi_generic_write_seq(dsi, 0x20, 0x3e);
	dsi_generic_write_seq(dsi, 0x21, 0x00);
	dsi_generic_write_seq(dsi, 0x22, 0x00);
	dsi_generic_write_seq(dsi, 0x23, 0x00);
	dsi_generic_write_seq(dsi, 0x24, 0x00);
	dsi_generic_write_seq(dsi, 0x25, 0x00);
	dsi_generic_write_seq(dsi, 0x26, 0x00);
	dsi_generic_write_seq(dsi, 0x27, 0x00);
	dsi_generic_write_seq(dsi, 0x28, 0x00);
	dsi_generic_write_seq(dsi, 0x29, 0x00);
	dsi_generic_write_seq(dsi, 0x2a, 0x00);
	dsi_generic_write_seq(dsi, 0x2b, 0xb0);
	dsi_generic_write_seq(dsi, 0x2d, 0x3f);
	dsi_generic_write_seq(dsi, 0x2f, 0x1d);
	dsi_generic_write_seq(dsi, 0x30, 0x20);
	dsi_generic_write_seq(dsi, 0x31, 0x3b);
	dsi_generic_write_seq(dsi, 0x32, 0x30);
	dsi_generic_write_seq(dsi, 0x33, 0x85);
	dsi_generic_write_seq(dsi, 0x34, 0x01);
	dsi_generic_write_seq(dsi, 0x35, 0x00);
	dsi_generic_write_seq(dsi, 0x36, 0x00);
	dsi_generic_write_seq(dsi, 0x37, 0x0c);
	dsi_generic_write_seq(dsi, 0x38, 0x00);
	dsi_generic_write_seq(dsi, 0x39, 0x00);
	dsi_generic_write_seq(dsi, 0x3a, 0x00);
	dsi_generic_write_seq(dsi, 0x3b, 0x80);
	dsi_generic_write_seq(dsi, 0x3d, 0x03);
	dsi_generic_write_seq(dsi, 0x3f, 0x57);
	dsi_generic_write_seq(dsi, 0x40, 0x18);
	dsi_generic_write_seq(dsi, 0x41, 0x06);
	dsi_generic_write_seq(dsi, 0x42, 0x12);
	dsi_generic_write_seq(dsi, 0x43, 0x11);
	dsi_generic_write_seq(dsi, 0x44, 0x11);
	dsi_generic_write_seq(dsi, 0x45, 0x11);
	dsi_generic_write_seq(dsi, 0x46, 0x11);
	dsi_generic_write_seq(dsi, 0x47, 0x11);
	dsi_generic_write_seq(dsi, 0x48, 0x11);
	dsi_generic_write_seq(dsi, 0x4a, 0x40);
	dsi_generic_write_seq(dsi, 0x4b, 0x21);
	dsi_generic_write_seq(dsi, 0x4c, 0x00);
	dsi_generic_write_seq(dsi, 0x4d, 0x17);
	dsi_generic_write_seq(dsi, 0x4e, 0x30);
	dsi_generic_write_seq(dsi, 0x4f, 0x85);
	dsi_generic_write_seq(dsi, 0x50, 0x02);
	dsi_generic_write_seq(dsi, 0x51, 0x1d);
	dsi_generic_write_seq(dsi, 0x52, 0x00);
	dsi_generic_write_seq(dsi, 0x53, 0x00);
	dsi_generic_write_seq(dsi, 0x54, 0x03);
	dsi_generic_write_seq(dsi, 0x55, 0x00);
	dsi_generic_write_seq(dsi, 0x56, 0x00);
	dsi_generic_write_seq(dsi, 0x58, 0x00);
	dsi_generic_write_seq(dsi, 0x59, 0x00);
	dsi_generic_write_seq(dsi, 0x5a, 0x00);
	dsi_generic_write_seq(dsi, 0x5b, 0x00);
	dsi_generic_write_seq(dsi, 0x5c, 0x00);
	dsi_generic_write_seq(dsi, 0x5d, 0x00);
	dsi_generic_write_seq(dsi, 0x5e, 0x00);
	dsi_generic_write_seq(dsi, 0x5f, 0x20);
	dsi_generic_write_seq(dsi, 0x60, 0x1f);
	dsi_generic_write_seq(dsi, 0x61, 0x3a);
	dsi_generic_write_seq(dsi, 0x62, 0x40);
	dsi_generic_write_seq(dsi, 0x63, 0x3b);
	dsi_generic_write_seq(dsi, 0x64, 0x20);
	dsi_generic_write_seq(dsi, 0x65, 0x30);
	dsi_generic_write_seq(dsi, 0x66, 0x01);
	dsi_generic_write_seq(dsi, 0x67, 0x00);
	dsi_generic_write_seq(dsi, 0x68, 0x00);
	dsi_generic_write_seq(dsi, 0x69, 0x00);
	dsi_generic_write_seq(dsi, 0x6b, 0x80);
	dsi_generic_write_seq(dsi, 0x6c, 0x57);
	dsi_generic_write_seq(dsi, 0x6d, 0x18);
	dsi_generic_write_seq(dsi, 0x6e, 0x0c);
	dsi_generic_write_seq(dsi, 0x6f, 0x05);
	dsi_generic_write_seq(dsi, 0x70, 0x11);
	dsi_generic_write_seq(dsi, 0x71, 0x11);
	dsi_generic_write_seq(dsi, 0x72, 0x11);
	dsi_generic_write_seq(dsi, 0x73, 0x11);
	dsi_generic_write_seq(dsi, 0x74, 0x11);
	dsi_generic_write_seq(dsi, 0x75, 0x11);
	dsi_generic_write_seq(dsi, 0x76, 0x00);
	dsi_generic_write_seq(dsi, 0x77, 0x40);
	dsi_generic_write_seq(dsi, 0xd2, 0x00);
	dsi_generic_write_seq(dsi, 0xd3, 0x00);
	dsi_generic_write_seq(dsi, 0xd4, 0x00);
	dsi_generic_write_seq(dsi, 0xd5, 0x00);
	dsi_generic_write_seq(dsi, 0xd6, 0x30);
	dsi_generic_write_seq(dsi, 0xd7, 0x30);
	dsi_generic_write_seq(dsi, 0xd8, 0x30);
	dsi_generic_write_seq(dsi, 0xd9, 0x30);
	dsi_generic_write_seq(dsi, 0xdb, 0x00);
	dsi_generic_write_seq(dsi, 0xe3, 0x01);
	dsi_generic_write_seq(dsi, 0xe4, 0x20);
	dsi_generic_write_seq(dsi, 0xe5, 0x00);
	dsi_generic_write_seq(dsi, 0xe6, 0x06);
	dsi_generic_write_seq(dsi, 0xe7, 0x05);
	dsi_generic_write_seq(dsi, 0xe8, 0x05);
	dsi_generic_write_seq(dsi, 0xe9, 0x03);
	dsi_generic_write_seq(dsi, 0xea, 0x02);
	dsi_generic_write_seq(dsi, 0xeb, 0x05);
	dsi_generic_write_seq(dsi, 0xec, 0x00);
	dsi_generic_write_seq(dsi, 0xed, 0x5e);
	dsi_generic_write_seq(dsi, 0xee, 0x10);
	dsi_generic_write_seq(dsi, 0xef, 0x82);
	dsi_generic_write_seq(dsi, 0xf0, 0x12);
	dsi_generic_write_seq(dsi, 0xf1, 0x70);
	dsi_generic_write_seq(dsi, 0xff, 0x2f);
	dsi_generic_write_seq(dsi, 0xfb, 0x01);
	dsi_generic_write_seq(dsi, 0x00, 0x00);
	dsi_generic_write_seq(dsi, 0x01, 0x00);
	dsi_generic_write_seq(dsi, 0x02, 0x00);
	dsi_generic_write_seq(dsi, 0x03, 0x00);
	dsi_generic_write_seq(dsi, 0x06, 0x00);
	dsi_generic_write_seq(dsi, 0x08, 0x00);
	dsi_generic_write_seq(dsi, 0x0a, 0x00);
	dsi_generic_write_seq(dsi, 0x0b, 0x00);
	dsi_generic_write_seq(dsi, 0x04, 0x07);
	dsi_generic_write_seq(dsi, 0x05, 0x06);
	dsi_generic_write_seq(dsi, 0x07, 0x02);
	dsi_generic_write_seq(dsi, 0x09, 0x0b);
	dsi_generic_write_seq(dsi, 0x0d, 0x00);
	dsi_generic_write_seq(dsi, 0x0e, 0x00);
	dsi_generic_write_seq(dsi, 0x12, 0x00);
	dsi_generic_write_seq(dsi, 0x0c, 0x0b);
	dsi_generic_write_seq(dsi, 0x0f, 0x02);
	dsi_generic_write_seq(dsi, 0x10, 0x06);
	dsi_generic_write_seq(dsi, 0x11, 0x07);
	dsi_generic_write_seq(dsi, 0x13, 0x00);
	dsi_generic_write_seq(dsi, 0x14, 0x44);
	dsi_generic_write_seq(dsi, 0x15, 0x00);
	dsi_generic_write_seq(dsi, 0x16, 0x80);
	dsi_generic_write_seq(dsi, 0x17, 0x80);
	dsi_generic_write_seq(dsi, 0x18, 0x40);
	dsi_generic_write_seq(dsi, 0x19, 0x40);
	dsi_generic_write_seq(dsi, 0x1a, 0x40);
	dsi_generic_write_seq(dsi, 0x1b, 0x40);
	dsi_generic_write_seq(dsi, 0x1c, 0x40);
	dsi_generic_write_seq(dsi, 0x1d, 0x40);
	dsi_generic_write_seq(dsi, 0x1e, 0x40);
	dsi_generic_write_seq(dsi, 0x1f, 0xe1);
	dsi_generic_write_seq(dsi, 0x20, 0xe1);
	dsi_generic_write_seq(dsi, 0x21, 0x5a);
	dsi_generic_write_seq(dsi, 0x22, 0x92);
	dsi_generic_write_seq(dsi, 0x23, 0x92);
	dsi_generic_write_seq(dsi, 0x24, 0x8b);
	dsi_generic_write_seq(dsi, 0x25, 0x8b);
	dsi_generic_write_seq(dsi, 0x26, 0x0a);
	dsi_generic_write_seq(dsi, 0x31, 0x00);
	dsi_generic_write_seq(dsi, 0x32, 0x55);
	dsi_generic_write_seq(dsi, 0x43, 0x01);
	dsi_generic_write_seq(dsi, 0x7a, 0x00);
	dsi_generic_write_seq(dsi, 0x7b, 0x25);
	dsi_generic_write_seq(dsi, 0xff, 0x23);
	dsi_generic_write_seq(dsi, 0xfb, 0x01);
	dsi_generic_write_seq(dsi, 0x01, 0x84);
	dsi_generic_write_seq(dsi, 0x05, 0x22);
	dsi_generic_write_seq(dsi, 0x06, 0x06);
	dsi_generic_write_seq(dsi, 0x08, 0x06);
	dsi_generic_write_seq(dsi, 0xff, 0x22);
	dsi_generic_write_seq(dsi, 0x00, 0x00);
	dsi_generic_write_seq(dsi, 0x01, 0x00);
	dsi_generic_write_seq(dsi, 0x02, 0x00);
	dsi_generic_write_seq(dsi, 0x03, 0x00);
	dsi_generic_write_seq(dsi, 0x04, 0x00);
	dsi_generic_write_seq(dsi, 0x05, 0x00);
	dsi_generic_write_seq(dsi, 0x06, 0x00);
	dsi_generic_write_seq(dsi, 0x07, 0x00);
	dsi_generic_write_seq(dsi, 0x08, 0x00);
	dsi_generic_write_seq(dsi, 0x09, 0x00);
	dsi_generic_write_seq(dsi, 0x0a, 0x00);
	dsi_generic_write_seq(dsi, 0x0b, 0x00);
	dsi_generic_write_seq(dsi, 0x0c, 0x23);
	dsi_generic_write_seq(dsi, 0x0d, 0x46);
	dsi_generic_write_seq(dsi, 0x0e, 0x5e);
	dsi_generic_write_seq(dsi, 0x0f, 0x7c);
	dsi_generic_write_seq(dsi, 0x10, 0x7c);
	dsi_generic_write_seq(dsi, 0x11, 0x97);
	dsi_generic_write_seq(dsi, 0x12, 0x46);
	dsi_generic_write_seq(dsi, 0x13, 0x23);
	dsi_generic_write_seq(dsi, 0x1a, 0x00);
	dsi_generic_write_seq(dsi, 0x1b, 0x00);
	dsi_generic_write_seq(dsi, 0x1c, 0x00);
	dsi_generic_write_seq(dsi, 0x1d, 0x00);
	dsi_generic_write_seq(dsi, 0x1e, 0x00);
	dsi_generic_write_seq(dsi, 0x1f, 0x00);
	dsi_generic_write_seq(dsi, 0x20, 0x00);
	dsi_generic_write_seq(dsi, 0x21, 0x00);
	dsi_generic_write_seq(dsi, 0x22, 0x00);
	dsi_generic_write_seq(dsi, 0x23, 0x00);
	dsi_generic_write_seq(dsi, 0x24, 0x00);
	dsi_generic_write_seq(dsi, 0x25, 0x00);
	dsi_generic_write_seq(dsi, 0x26, 0x00);
	dsi_generic_write_seq(dsi, 0x27, 0x00);
	dsi_generic_write_seq(dsi, 0x28, 0x00);
	dsi_generic_write_seq(dsi, 0x29, 0x00);
	dsi_generic_write_seq(dsi, 0x2a, 0x00);
	dsi_generic_write_seq(dsi, 0x2b, 0x00);
	dsi_generic_write_seq(dsi, 0x2f, 0x00);
	dsi_generic_write_seq(dsi, 0x30, 0x00);
	dsi_generic_write_seq(dsi, 0x31, 0x00);
	dsi_generic_write_seq(dsi, 0x32, 0x0d);
	dsi_generic_write_seq(dsi, 0x33, 0x14);
	dsi_generic_write_seq(dsi, 0x34, 0x0d);
	dsi_generic_write_seq(dsi, 0x35, 0x07);
	dsi_generic_write_seq(dsi, 0x36, 0x00);
	dsi_generic_write_seq(dsi, 0x37, 0x00);
	dsi_generic_write_seq(dsi, 0x38, 0x00);
	dsi_generic_write_seq(dsi, 0x39, 0x00);
	dsi_generic_write_seq(dsi, 0x3a, 0x00);
	dsi_generic_write_seq(dsi, 0x3b, 0x00);
	dsi_generic_write_seq(dsi, 0x3f, 0x00);
	dsi_generic_write_seq(dsi, 0x40, 0x00);
	dsi_generic_write_seq(dsi, 0x41, 0x00);
	dsi_generic_write_seq(dsi, 0x42, 0x00);
	dsi_generic_write_seq(dsi, 0x43, 0x00);
	dsi_generic_write_seq(dsi, 0x44, 0x00);
	dsi_generic_write_seq(dsi, 0x45, 0x00);
	dsi_generic_write_seq(dsi, 0x46, 0x00);
	dsi_generic_write_seq(dsi, 0x47, 0x00);
	dsi_generic_write_seq(dsi, 0x48, 0x00);
	dsi_generic_write_seq(dsi, 0x49, 0x00);
	dsi_generic_write_seq(dsi, 0x4a, 0x00);
	dsi_generic_write_seq(dsi, 0x4b, 0x00);
	dsi_generic_write_seq(dsi, 0x4c, 0x07);
	dsi_generic_write_seq(dsi, 0x4d, 0x00);
	dsi_generic_write_seq(dsi, 0x4e, 0x00);
	dsi_generic_write_seq(dsi, 0x4f, 0x00);
	dsi_generic_write_seq(dsi, 0x50, 0x00);
	dsi_generic_write_seq(dsi, 0x51, 0x00);
	dsi_generic_write_seq(dsi, 0x52, 0x00);
	dsi_generic_write_seq(dsi, 0x53, 0x01);
	dsi_generic_write_seq(dsi, 0x54, 0x00);
	dsi_generic_write_seq(dsi, 0x55, 0x88);
	dsi_generic_write_seq(dsi, 0x56, 0x00);
	dsi_generic_write_seq(dsi, 0x58, 0x00);
	dsi_generic_write_seq(dsi, 0x68, 0x00);
	dsi_generic_write_seq(dsi, 0x84, 0x00);
	dsi_generic_write_seq(dsi, 0x85, 0x00);
	dsi_generic_write_seq(dsi, 0x86, 0x00);
	dsi_generic_write_seq(dsi, 0x87, 0x00);
	dsi_generic_write_seq(dsi, 0x88, 0x00);
	dsi_generic_write_seq(dsi, 0xa2, 0x20);
	dsi_generic_write_seq(dsi, 0xa9, 0x00);
	dsi_generic_write_seq(dsi, 0xfb, 0x01);
	dsi_generic_write_seq(dsi, 0xff, 0x23);
	dsi_generic_write_seq(dsi, 0xfb, 0x01);
	dsi_generic_write_seq(dsi, 0x00, 0x20);
	dsi_generic_write_seq(dsi, 0x07, 0x00);
	dsi_generic_write_seq(dsi, 0x08, 0x01);
	dsi_generic_write_seq(dsi, 0x46, 0x00);
	dsi_generic_write_seq(dsi, 0xff, 0x10);
	dsi_generic_write_seq(dsi, 0xfb, 0x01);
	dsi_dcs_write_seq(dsi, 0x3b, 0x03, 0x08, 0x08, 0x0a, 0x0a);
	dsi_generic_write_seq(dsi, 0x35, 0x00);
	dsi_generic_write_seq(dsi, 0xb0, 0x01);

	ret = mipi_dsi_dcs_set_display_brightness(dsi, 0x0000);
	if (ret < 0) {
		dev_err(dev, "Failed to set display brightness: %d\n", ret);
		return ret;
	}

	dsi_generic_write_seq(dsi, 0x55, 0x83);
	dsi_dcs_write_seq(dsi, 0x68, 0x04, 0x01);

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

static int boe_nt35596s_5p5boe_vdo_off(struct boe_nt35596s_5p5boe_vdo *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
	struct device *dev = &dsi->dev;
	int ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	dsi_generic_write_seq(dsi, 0xff, 0x20);
	dsi_generic_write_seq(dsi, 0xfb, 0x01);
	dsi_generic_write_seq(dsi, 0xb1, 0x03);
	dsi_generic_write_seq(dsi, 0xb2, 0xff);
	dsi_generic_write_seq(dsi, 0xed, 0x03);
	dsi_generic_write_seq(dsi, 0xee, 0xff);
	dsi_generic_write_seq(dsi, 0xff, 0x21);
	dsi_generic_write_seq(dsi, 0xfb, 0x01);
	dsi_generic_write_seq(dsi, 0x30, 0x03);
	dsi_generic_write_seq(dsi, 0x31, 0xff);
	dsi_generic_write_seq(dsi, 0x6f, 0x03);
	dsi_generic_write_seq(dsi, 0x70, 0xff);
	dsi_generic_write_seq(dsi, 0xad, 0x03);
	dsi_generic_write_seq(dsi, 0xae, 0xff);
	dsi_generic_write_seq(dsi, 0xe9, 0x03);
	dsi_generic_write_seq(dsi, 0xea, 0xff);
	dsi_generic_write_seq(dsi, 0xff, 0x10);

	ret = mipi_dsi_dcs_set_display_off(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to set display off: %d\n", ret);
		return ret;
	}
	msleep(20);

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to enter sleep mode: %d\n", ret);
		return ret;
	}
	msleep(120);

	return 0;
}

static int boe_nt35596s_5p5boe_vdo_prepare(struct drm_panel *panel)
{
	struct boe_nt35596s_5p5boe_vdo *ctx = to_boe_nt35596s_5p5boe_vdo(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	if (ctx->prepared)
		return 0;

	ret = regulator_bulk_enable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
	if (ret < 0) {
		dev_err(dev, "Failed to enable regulators: %d\n", ret);
		return ret;
	}

	boe_nt35596s_5p5boe_vdo_reset(ctx);

	ret = boe_nt35596s_5p5boe_vdo_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		regulator_bulk_disable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
		return ret;
	}

	ctx->prepared = true;
	return 0;
}

static int boe_nt35596s_5p5boe_vdo_unprepare(struct drm_panel *panel)
{
	struct boe_nt35596s_5p5boe_vdo *ctx = to_boe_nt35596s_5p5boe_vdo(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	if (!ctx->prepared)
		return 0;

	ret = boe_nt35596s_5p5boe_vdo_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	regulator_bulk_disable(ARRAY_SIZE(ctx->supplies), ctx->supplies);

	ctx->prepared = false;
	return 0;
}

static const struct drm_display_mode boe_nt35596s_5p5boe_vdo_mode = {
	.clock = (1080 + 40 + 8 + 20) * (1920 + 8 + 2 + 10) * 60 / 1000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 40,
	.hsync_end = 1080 + 40 + 8,
	.htotal = 1080 + 40 + 8 + 20,
	.vdisplay = 1920,
	.vsync_start = 1920 + 8,
	.vsync_end = 1920 + 8 + 2,
	.vtotal = 1920 + 8 + 2 + 10,
	.width_mm = 69,
	.height_mm = 122,
};

static int boe_nt35596s_5p5boe_vdo_get_modes(struct drm_panel *panel,
					     struct drm_connector *connector)
{
	struct drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &boe_nt35596s_5p5boe_vdo_mode);
	if (!mode)
		return -ENOMEM;

	drm_mode_set_name(mode);

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;
	drm_mode_probed_add(connector, mode);

	return 1;
}

static const struct drm_panel_funcs boe_nt35596s_5p5boe_vdo_panel_funcs = {
	.prepare = boe_nt35596s_5p5boe_vdo_prepare,
	.unprepare = boe_nt35596s_5p5boe_vdo_unprepare,
	.get_modes = boe_nt35596s_5p5boe_vdo_get_modes,
};

static int boe_nt35596s_5p5boe_vdo_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct boe_nt35596s_5p5boe_vdo *ctx;
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
			  MIPI_DSI_MODE_VIDEO_HSE | MIPI_DSI_MODE_NO_EOT_PACKET |
			  MIPI_DSI_CLOCK_NON_CONTINUOUS;

	drm_panel_init(&ctx->panel, dev, &boe_nt35596s_5p5boe_vdo_panel_funcs,
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

static void boe_nt35596s_5p5boe_vdo_remove(struct mipi_dsi_device *dsi)
{
	struct boe_nt35596s_5p5boe_vdo *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id boe_nt35596s_5p5boe_vdo_of_match[] = {
	{ .compatible = "boe,nt35596s-5p5boe-vdo" }, // FIXME
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, boe_nt35596s_5p5boe_vdo_of_match);

static struct mipi_dsi_driver boe_nt35596s_5p5boe_vdo_driver = {
	.probe = boe_nt35596s_5p5boe_vdo_probe,
	.remove = boe_nt35596s_5p5boe_vdo_remove,
	.driver = {
		.name = "panel-boe-nt35596s-5p5boe-vdo",
		.of_match_table = boe_nt35596s_5p5boe_vdo_of_match,
	},
};
module_mipi_dsi_driver(boe_nt35596s_5p5boe_vdo_driver);

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for boe nt35596s fhd vdo dsi panel");
MODULE_LICENSE("GPL");
