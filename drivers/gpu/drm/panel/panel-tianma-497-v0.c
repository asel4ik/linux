// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2021 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/of.h>

#include <video/mipi_display.h>

#include "panel-mipi-dsi-common.h"

static void tianma_497_v0_reset(struct gpio_desc *reset_gpio)
{
	gpiod_set_value_cansleep(reset_gpio, 0);
	usleep_range(2000, 3000);
	gpiod_set_value_cansleep(reset_gpio, 1);
	usleep_range(2000, 3000);
	gpiod_set_value_cansleep(reset_gpio, 0);
	usleep_range(2000, 3000);
	gpiod_set_value_cansleep(reset_gpio, 1);
	usleep_range(2000, 3000);
	gpiod_set_value_cansleep(reset_gpio, 0);
	msleep(20);
}

static int tianma_497_v0_on(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	int ret;

	dsi_dcs_write_seq(dsi, 0xff, 0xee);
	dsi_dcs_write_seq(dsi, 0x18, 0x40);
	usleep_range(10000, 11000);
	dsi_dcs_write_seq(dsi, 0x18, 0x00);
	usleep_range(10000, 11000);
	dsi_dcs_write_seq(dsi, 0xff, 0x00);
	dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	dsi_dcs_write_seq(dsi, 0xd3, 0x0a);
	dsi_dcs_write_seq(dsi, 0xd4, 0x0e);

	ret = mipi_dsi_dcs_exit_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to exit sleep mode: %d\n", ret);
		return ret;
	}
	msleep(120);

	ret = mipi_dsi_dcs_set_display_brightness(dsi, 0x00cc);
	if (ret < 0) {
		dev_err(dev, "Failed to set display brightness: %d\n", ret);
		return ret;
	}

	dsi_dcs_write_seq(dsi, MIPI_DCS_WRITE_CONTROL_DISPLAY, 0x2c);
	dsi_dcs_write_seq(dsi, MIPI_DCS_WRITE_POWER_SAVE, 0x01);

	ret = mipi_dsi_dcs_set_display_on(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to set display on: %d\n", ret);
		return ret;
	}

	return 0;
}

static int tianma_497_v0_off(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	int ret;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to set display off: %d\n", ret);
		return ret;
	}

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to enter sleep mode: %d\n", ret);
		return ret;
	}
	msleep(120);

	return 0;
}

static const struct panel_mipi_dsi_info tianma_497_v0_info = {
	.mode = {
		.clock = (1080 + 120 + 20 + 120) * (1920 + 14 + 2 + 8) * 60 / 1000,
		.hdisplay = 1080,
		.hsync_start = 1080 + 120,
		.hsync_end = 1080 + 120 + 20,
		.htotal = 1080 + 120 + 20 + 120,
		.vdisplay = 1920,
		.vsync_start = 1920 + 14,
		.vsync_end = 1920 + 14 + 2,
		.vtotal = 1920 + 14 + 2 + 8,
		.width_mm = 62,
		.height_mm = 110,
	},

	.reset = tianma_497_v0_reset,
	.power_on = tianma_497_v0_on,
	.power_off = tianma_497_v0_off,

	.lanes = 4,
	.format = MIPI_DSI_FMT_RGB888,
	.mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
		      MIPI_DSI_CLOCK_NON_CONTINUOUS | MIPI_DSI_MODE_LPM
};

MIPI_DSI_PANEL_DRIVER(tianma_497_v0, "tianma-497-v0", "tianma,497-v0");

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for mipi_mot_vid_tianma_1080p_497");
MODULE_LICENSE("GPL v2");
