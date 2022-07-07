// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2022 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/of.h>

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>

struct nt36672a_truly_v2 {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct gpio_desc *reset_gpio;
	bool prepared;
};

static inline
struct nt36672a_truly_v2 *to_nt36672a_truly_v2(struct drm_panel *panel)
{
	return container_of(panel, struct nt36672a_truly_v2, panel);
}

#define dsi_dcs_write_seq(dsi, seq...) do {				\
		static const u8 d[] = { seq };				\
		int ret;						\
		ret = mipi_dsi_dcs_write_buffer(dsi, d, ARRAY_SIZE(d));	\
		if (ret < 0)						\
			return ret;					\
	} while (0)

static void nt36672a_truly_v2_reset(struct nt36672a_truly_v2 *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	msleep(20);
}

static int nt36672a_truly_v2_on(struct nt36672a_truly_v2 *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
	struct device *dev = &dsi->dev;
	int ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	dsi_dcs_write_seq(dsi, 0xff, 0x23);
	dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	dsi_dcs_write_seq(dsi, 0x00, 0x80);
	dsi_dcs_write_seq(dsi, 0x07, 0x00);
	dsi_dcs_write_seq(dsi, 0x08, 0x01);
	dsi_dcs_write_seq(dsi, 0x09, 0x00);
	dsi_dcs_write_seq(dsi, 0xff, 0xf0);
	dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	dsi_dcs_write_seq(dsi, 0xa2, 0x00);
	dsi_dcs_write_seq(dsi, 0xff, 0x10);

	ret = mipi_dsi_dcs_exit_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to exit sleep mode: %d\n", ret);
		return ret;
	}
	msleep(120);

	dsi_dcs_write_seq(dsi, 0x35, 0x00);
	dsi_dcs_write_seq(dsi, 0x51, 0x0f, 0xff);
	dsi_dcs_write_seq(dsi, 0x53, 0x2c);
	dsi_dcs_write_seq(dsi, 0x55, 0x01);
	dsi_dcs_write_seq(dsi, 0xff, 0x23);
	dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	dsi_dcs_write_seq(dsi, 0x10, 0x50);
	dsi_dcs_write_seq(dsi, 0x11, 0x01);
	dsi_dcs_write_seq(dsi, 0x12, 0x8a);
	dsi_dcs_write_seq(dsi, 0x15, 0x6a);
	dsi_dcs_write_seq(dsi, 0x16, 0x0b);
	dsi_dcs_write_seq(dsi, 0x29, 0x80);
	dsi_dcs_write_seq(dsi, 0x30, 0xfd);
	dsi_dcs_write_seq(dsi, 0x31, 0xfc);
	dsi_dcs_write_seq(dsi, 0x32, 0xf8);
	dsi_dcs_write_seq(dsi, 0x33, 0xf6);
	dsi_dcs_write_seq(dsi, 0x34, 0xf5);
	dsi_dcs_write_seq(dsi, 0x35, 0xf4);
	dsi_dcs_write_seq(dsi, 0x36, 0xf3);
	dsi_dcs_write_seq(dsi, 0x37, 0xf3);
	dsi_dcs_write_seq(dsi, 0x38, 0xf2);
	dsi_dcs_write_seq(dsi, 0x39, 0xf0);
	dsi_dcs_write_seq(dsi, 0x3a, 0xee);
	dsi_dcs_write_seq(dsi, 0x3b, 0xec);
	dsi_dcs_write_seq(dsi, 0x3d, 0xea);
	dsi_dcs_write_seq(dsi, 0x3f, 0xe8);
	dsi_dcs_write_seq(dsi, 0x40, 0xe6);
	dsi_dcs_write_seq(dsi, 0x41, 0xe5);
	dsi_dcs_write_seq(dsi, 0x45, 0xe4);
	dsi_dcs_write_seq(dsi, 0x46, 0xe4);
	dsi_dcs_write_seq(dsi, 0x47, 0xe4);
	dsi_dcs_write_seq(dsi, 0x48, 0xe4);
	dsi_dcs_write_seq(dsi, 0x49, 0xe4);
	dsi_dcs_write_seq(dsi, 0x4a, 0xe4);
	dsi_dcs_write_seq(dsi, 0x4b, 0xd0);
	dsi_dcs_write_seq(dsi, 0x4c, 0xb2);
	dsi_dcs_write_seq(dsi, 0x4d, 0xaf);
	dsi_dcs_write_seq(dsi, 0x4e, 0xaa);
	dsi_dcs_write_seq(dsi, 0x4f, 0xa4);
	dsi_dcs_write_seq(dsi, 0x50, 0x9a);
	dsi_dcs_write_seq(dsi, 0x51, 0x90);
	dsi_dcs_write_seq(dsi, 0x52, 0x85);
	dsi_dcs_write_seq(dsi, 0x53, 0x7a);
	dsi_dcs_write_seq(dsi, 0x54, 0x66);
	dsi_dcs_write_seq(dsi, 0x2b, 0x87);
	dsi_dcs_write_seq(dsi, 0x58, 0xe4);
	dsi_dcs_write_seq(dsi, 0x59, 0xe4);
	dsi_dcs_write_seq(dsi, 0x5a, 0xe4);
	dsi_dcs_write_seq(dsi, 0x5b, 0xe4);
	dsi_dcs_write_seq(dsi, 0x5c, 0xe4);
	dsi_dcs_write_seq(dsi, 0x5d, 0xe4);
	dsi_dcs_write_seq(dsi, 0x5e, 0xdf);
	dsi_dcs_write_seq(dsi, 0x5f, 0xda);
	dsi_dcs_write_seq(dsi, 0x60, 0xd7);
	dsi_dcs_write_seq(dsi, 0x61, 0xd0);
	dsi_dcs_write_seq(dsi, 0x62, 0xcd);
	dsi_dcs_write_seq(dsi, 0x63, 0xca);
	dsi_dcs_write_seq(dsi, 0x64, 0xc8);
	dsi_dcs_write_seq(dsi, 0x65, 0xc1);
	dsi_dcs_write_seq(dsi, 0x66, 0xbb);
	dsi_dcs_write_seq(dsi, 0x67, 0xb3);
	dsi_dcs_write_seq(dsi, 0xff, 0x10);

	ret = mipi_dsi_dcs_set_display_on(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to set display on: %d\n", ret);
		return ret;
	}
	msleep(20);

	return 0;
}

static int nt36672a_truly_v2_off(struct nt36672a_truly_v2 *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
	struct device *dev = &dsi->dev;
	int ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

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
	msleep(140);

	dsi_dcs_write_seq(dsi, 0x00, 0x00);
	dsi_dcs_write_seq(dsi, 0xf7, 0x5a, 0xa5, 0x95, 0x27);

	return 0;
}

static int nt36672a_truly_v2_prepare(struct drm_panel *panel)
{
	struct nt36672a_truly_v2 *ctx = to_nt36672a_truly_v2(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	if (ctx->prepared)
		return 0;

	nt36672a_truly_v2_reset(ctx);

	ret = nt36672a_truly_v2_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		return ret;
	}

	ctx->prepared = true;
	return 0;
}

static int nt36672a_truly_v2_unprepare(struct drm_panel *panel)
{
	struct nt36672a_truly_v2 *ctx = to_nt36672a_truly_v2(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	if (!ctx->prepared)
		return 0;

	ret = nt36672a_truly_v2_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);

	ctx->prepared = false;
	return 0;
}

static const struct drm_display_mode nt36672a_truly_v2_mode = {
	.clock = (1080 + 76 + 12 + 56) * (2340 + 32 + 2 + 15) * 60 / 1000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 76,
	.hsync_end = 1080 + 76 + 12,
	.htotal = 1080 + 76 + 12 + 56,
	.vdisplay = 2340,
	.vsync_start = 2340 + 32,
	.vsync_end = 2340 + 32 + 2,
	.vtotal = 2340 + 32 + 2 + 15,
	.width_mm = 65,
	.height_mm = 129,
};

static int nt36672a_truly_v2_get_modes(struct drm_panel *panel,
				       struct drm_connector *connector)
{
	struct drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &nt36672a_truly_v2_mode);
	if (!mode)
		return -ENOMEM;

	drm_mode_set_name(mode);

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;
	drm_mode_probed_add(connector, mode);

	return 1;
}

static const struct drm_panel_funcs nt36672a_truly_v2_panel_funcs = {
	.prepare = nt36672a_truly_v2_prepare,
	.unprepare = nt36672a_truly_v2_unprepare,
	.get_modes = nt36672a_truly_v2_get_modes,
};

static int nt36672a_truly_v2_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct nt36672a_truly_v2 *ctx;
	int ret;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ctx->reset_gpio))
		return dev_err_probe(dev, PTR_ERR(ctx->reset_gpio),
				     "Failed to get reset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_CLOCK_NON_CONTINUOUS;

	drm_panel_init(&ctx->panel, dev, &nt36672a_truly_v2_panel_funcs,
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

static void nt36672a_truly_v2_remove(struct mipi_dsi_device *dsi)
{
	struct nt36672a_truly_v2 *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id nt36672a_truly_v2_of_match[] = {
	{ .compatible = "mdss,nt36672a-truly-v2" }, // FIXME
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, nt36672a_truly_v2_of_match);

static struct mipi_dsi_driver nt36672a_truly_v2_driver = {
	.probe = nt36672a_truly_v2_probe,
	.remove = nt36672a_truly_v2_remove,
	.driver = {
		.name = "panel-nt36672a-truly-v2",
		.of_match_table = nt36672a_truly_v2_of_match,
	},
};
module_mipi_dsi_driver(nt36672a_truly_v2_driver);

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for nt36672a truly video mode dsi truly panel");
MODULE_LICENSE("GPL v2");
