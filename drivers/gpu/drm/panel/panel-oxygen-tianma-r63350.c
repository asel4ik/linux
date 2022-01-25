// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2022 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/of.h>

#include <video/mipi_display.h>

#include "panel-mipi-dsi-common.h"

static void tianma_r63350_reset(struct gpio_desc *reset_gpio)
{
	gpiod_set_value_cansleep(reset_gpio, 1);
	usleep_range(5000, 6000);
	gpiod_set_value_cansleep(reset_gpio, 0);
	usleep_range(10000, 11000);
}

static int tianma_r63350_on(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	int ret;

	dsi_generic_write_seq(dsi, 0xb0, 0x00);
	dsi_generic_write_seq(dsi, 0xd6, 0x01);
	dsi_generic_write_seq(dsi, 0xc2,
			      0x31, 0xf7, 0x80, 0x17, 0x18, 0x00, 0x00, 0x08);
	dsi_generic_write_seq(dsi, 0xd3,
			      0x1b, 0x33, 0x99, 0xbb, 0xb3, 0x33, 0x33, 0x33,
			      0x11, 0x00, 0x01, 0x00, 0x00, 0xd8, 0xa0, 0x05,
			      0x3f, 0x3f, 0x33, 0x33, 0x72, 0x12, 0x8a, 0x57,
			      0x3d, 0xbc);
	dsi_generic_write_seq(dsi, 0xc7,
			      0x00, 0x12, 0x1a, 0x25, 0x33, 0x42, 0x4c, 0x5c,
			      0x42, 0x4a, 0x55, 0x5f, 0x69, 0x6f, 0x75, 0x00,
			      0x12, 0x1a, 0x25, 0x33, 0x42, 0x4c, 0x5c, 0x42,
			      0x4a, 0x55, 0x5f, 0x69, 0x6f, 0x75);
	dsi_generic_write_seq(dsi, 0xc8,
			      0x01, 0x00, 0xfe, 0x00, 0xfe, 0xc8, 0x00, 0x00,
			      0x02, 0x00, 0x00, 0xfc, 0x00, 0x04, 0xfe, 0x04,
			      0x0d, 0xed, 0x00);
	dsi_generic_write_seq(dsi, 0xb0, 0x03);

	ret = mipi_dsi_dcs_set_display_brightness(dsi, 0x00ff);
	if (ret < 0) {
		dev_err(dev, "Failed to set display brightness: %d\n", ret);
		return ret;
	}

	dsi_dcs_write_seq(dsi, MIPI_DCS_WRITE_CONTROL_DISPLAY, 0x24);
	dsi_dcs_write_seq(dsi, MIPI_DCS_WRITE_POWER_SAVE, 0x00);

	ret = mipi_dsi_dcs_set_display_on(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to set display on: %d\n", ret);
		return ret;
	}
	msleep(20);

	ret = mipi_dsi_dcs_exit_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to exit sleep mode: %d\n", ret);
		return ret;
	}
	msleep(120);

	return 0;
}

static int tianma_r63350_off(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	int ret;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to set display off: %d\n", ret);
		return ret;
	}
	msleep(20);

	dsi_generic_write_seq(dsi, 0xb0, 0x00);
	dsi_generic_write_seq(dsi, 0xd3,
			      0x13, 0x33, 0x99, 0xb3, 0xb3, 0x33, 0x33, 0x33,
			      0x11, 0x00, 0x01, 0x00, 0x00, 0xd8, 0xa0, 0x05,
			      0x3f, 0x3f, 0x33, 0x33, 0x72, 0x12, 0x8a, 0x57,
			      0x3d, 0xbc);
	msleep(50);
	dsi_generic_write_seq(dsi, 0xb0, 0x03);

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to enter sleep mode: %d\n", ret);
		return ret;
	}
	msleep(50);

	return 0;
}

static const struct panel_mipi_dsi_info tianma_r63350_info = {
	.mode = {
		.clock = (1080 + 150 + 10 + 40) * (1920 + 24 + 2 + 21) * 60 / 1000,
		.hdisplay = 1080,
		.hsync_start = 1080 + 150,
		.hsync_end = 1080 + 150 + 10,
		.htotal = 1080 + 150 + 10 + 40,
		.vdisplay = 1920,
		.vsync_start = 1920 + 24,
		.vsync_end = 1920 + 24 + 2,
		.vtotal = 1920 + 24 + 2 + 21,
		.width_mm = 80,
		.height_mm = 142,
	},

	.reset = tianma_r63350_reset,
	.power_on = tianma_r63350_on,
	.power_off = tianma_r63350_off,

	.lanes = 4,
	.format = MIPI_DSI_FMT_RGB888,
	.mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
		      MIPI_DSI_CLOCK_NON_CONTINUOUS
};

MIPI_DSI_PANEL_DRIVER(tianma_r63350, "tianma-r63350", "xiaomi,oxygen-tianma-r63350");

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for tianma r63350 1080p video mode dsi panel");
MODULE_LICENSE("GPL v2");
