// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2021 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/of.h>

#include "panel-mipi-dsi-common.h"

static void nt35596_ebbg_reset(struct gpio_desc *reset_gpio)
{
	gpiod_set_value_cansleep(reset_gpio, 0);
	msleep(20);
	gpiod_set_value_cansleep(reset_gpio, 1);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(reset_gpio, 0);
	msleep(20);
	gpiod_set_value_cansleep(reset_gpio, 1);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(reset_gpio, 0);
	msleep(20);
}

static int nt35596_ebbg_on(struct mipi_dsi_device *dsi)
{

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	dsi_generic_write_seq(dsi, 0xff, 0xee);
	dsi_generic_write_seq(dsi, 0x18, 0x40);
	usleep_range(10000, 11000);
	dsi_generic_write_seq(dsi, 0x18, 0x00);
	usleep_range(10000, 11000);
	dsi_generic_write_seq(dsi, 0xff, 0x00);
	dsi_generic_write_seq(dsi, 0x35, 0x00);
	dsi_generic_write_seq(dsi, 0xd3, 0x14);
	dsi_generic_write_seq(dsi, 0xd4, 0x08);
	dsi_generic_write_seq(dsi, 0x11, 0x00);
	msleep(120);
	dsi_generic_write_seq(dsi, 0x29, 0x00);
	usleep_range(10000, 11000);

	return 0;
}

static int nt35596_ebbg_off(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	int ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to set display off: %d\n", ret);
		return ret;
	}
	msleep(50);

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to enter sleep mode: %d\n", ret);
		return ret;
	}
	msleep(120);

	return 0;
}

static const struct panel_mipi_dsi_info nt35596_ebbg_info = {
	.mode = {
		.clock = (1080 + 124 + 4 + 120) * (1920 + 8 + 5 + 15) * 60 / 1000,
		.hdisplay = 1080,
		.hsync_start = 1080 + 124,
		.hsync_end = 1080 + 124 + 4,
		.htotal = 1080 + 124 + 4 + 120,
		.vdisplay = 1920,
		.vsync_start = 1920 + 8,
		.vsync_end = 1920 + 8 + 5,
		.vtotal = 1920 + 8 + 5 + 15,
		.width_mm = 62,
		.height_mm = 110,
	},

	.reset = nt35596_ebbg_reset,
	.power_on = nt35596_ebbg_on,
	.power_off = nt35596_ebbg_off,

	.lanes = 4,
	.format = MIPI_DSI_FMT_RGB888,
	.mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
		      MIPI_DSI_MODE_VIDEO_HSE | MIPI_DSI_MODE_EOT_PACKET |
		      MIPI_DSI_CLOCK_NON_CONTINUOUS
};

MIPI_DSI_PANEL_DRIVER(nt35596_ebbg, "nt35596-ebbg", "xiaomi,nt35596-ebbg");

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for nt35596_1080p_video_EBBG");
MODULE_LICENSE("GPL v2");
