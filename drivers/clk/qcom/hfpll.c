// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2018, The Linux Foundation. All rights reserved.

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/clk.h>
#include <linux/clk-provider.h>
#include <linux/regmap.h>

#include "clk-regmap.h"
#include "clk-hfpll.h"

static const struct hfpll_data hdata = {
	.mode_reg = 0x00,
	.l_reg = 0x04,
	.m_reg = 0x08,
	.n_reg = 0x0c,
	.user_reg = 0x10,
	.config_reg = 0x14,
	.config_val = 0x430405d,
	.status_reg = 0x1c,
	.lock_bit = 16,

	.user_val = 0x8,
	.user_vco_mask = 0x100000,
	.low_vco_max_rate = 1248000000,
	.min_rate = 537600000UL,
	.max_rate = 2900000000UL,
};

static const struct hfpll_data msm8976_a53_hdata = {
	.mode_reg = 0x0,
	.l_reg = 0x4,
	.m_reg = 0x8,
	.n_reg = 0xC,
	.user_reg = 0x10,
	.config_reg = 0x14,
	.status_reg = 0x1C,
	.lock_bit = 16,
	.user_vco_mask = 0x3 << 20,
	.pre_div_mask = 0x7 << 12,
	.post_div_mask = (BIT(8) | BIT(9)),
	.post_div_masked =  0x1 << 8,
	.early_output_mask =  BIT(3),
	.main_output_mask = BIT(0),
	.config_val = 0x00341600,
	.user_vco_val = 0x00141400,
	.vco_mode_masked = BIT(20),
	.min_rate = 652800000UL,
	.max_rate = 1478400000UL,
	.low_vco_max_rate = 902400000UL,
	.l_val = 0x49,
	.safe_parking_enabled = false,
	
};
static const struct hfpll_data msm8976_a72_hdata = {
	.mode_reg = 0x0,
	.l_reg = 0x4,
	.m_reg = 0x8,
	.n_reg = 0xC,
	.user_reg = 0x10,
	.config_reg = 0x14,
	.status_reg = 0x1C,
	.lock_bit = 16,
	.user_vco_mask = 0x3 << 28,
	.pre_div_mask = BIT(12),
	.pre_div_masked = 0,
	.post_div_mask = (BIT(8) | BIT(9)),
	.post_div_masked = 0x100,
	.early_output_mask =  0x8,
	.main_output_mask = BIT(0),
	.vco_mode_masked = BIT(20),
	.config_val = 0x04E0405D,
	.max_rate = 2016000000UL,
	.min_rate = 940800000UL,
	.l_val = 0x5B,
	.l_park_val = 0x35,
	.safe_parking_enabled = true,
};

static const struct hfpll_data msm8976_cci_hdata = {
	.mode_reg = 0x0,
	.l_reg = 0x4,
	.m_reg = 0x8,
	.n_reg = 0xC,
	.user_reg = 0x10,
	.config_reg = 0x14,
	.status_reg = 0x1C,
	.lock_bit = 16,
	.user_vco_mask = 0x3 << 20,
	.pre_div_mask = 0x7 << 12,
	.post_div_mask = (BIT(8) | BIT(9)),
	.early_output_mask =  BIT(3),
	.main_output_mask = BIT(0),
	.post_div_masked = 0x1 << 8,
	.vco_mode_masked = BIT(20),
	.config_val = 0x00141400,
	.min_rate = 307200000UL,
	.max_rate = 902400000UL,
	.l_val = 0x20,
	.safe_parking_enabled = false,
};

static const struct of_device_id qcom_hfpll_match_table[] = {
	{ .compatible = "qcom,hfpll", &hdata },
	{ .compatible = "qcom,hfpll2" },
	{ .compatible = "qcom,hfpll-msm8976-a53", &msm8976_a53_hdata },
	{ .compatible = "qcom,hfpll-msm8976-a72", &msm8976_a72_hdata },
	{ .compatible = "qcom,hfpll-msm8976-cci", &msm8976_cci_hdata },
	{ }
};
MODULE_DEVICE_TABLE(of, qcom_hfpll_match_table);

static const struct regmap_config hfpll_regmap_config = {
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_register	= 0x30,
	.fast_io	= true,
};

static int qcom_hfpll_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct device *dev = &pdev->dev;
	void __iomem *base;
	struct regmap *regmap;
	struct hfpll_data *pll_data;
	struct clk_hfpll *h;
	struct clk_init_data init = {
		.num_parents = 1,
		.ops = &clk_ops_hfpll,
		/*
		 * rather than marking the clock critical and forcing the clock
		 * to be always enabled, we make sure that the clock is not
		 * disabled: the firmware remains responsible of enabling this
		 * clock (for more info check the commit log)
		 */
		.flags = CLK_IGNORE_UNUSED,
	};
	pll_data = of_device_get_match_data(&pdev->dev);
	
	if (of_device_is_compatible(pdev->dev.of_node, "qcom,hfpll2")) {
	init.ops = &clk_ops_hf2_pll;
	}
	
	int ret;
	struct clk_parent_data pdata = { .index = 0 };

	h = devm_kzalloc(dev, sizeof(*h), GFP_KERNEL);
	if (!h)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(dev, res);
	if (IS_ERR(base))
		return PTR_ERR(base);

	regmap = devm_regmap_init_mmio(&pdev->dev, base, &hfpll_regmap_config);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	if (of_property_read_string_index(dev->of_node, "clock-output-names",
					  0, &init.name))
		return -ENODEV;

	init.parent_data = &pdata;


	h->d = pll_data;
	h->clkr.hw.init = &init;
	spin_lock_init(&h->lock);

	ret = devm_clk_register_regmap(dev, &h->clkr);
	if (ret) {
		dev_err(dev, "failed to register regmap clock: %d\n", ret);
		return ret;
	}

	return devm_of_clk_add_hw_provider(dev, of_clk_hw_simple_get,
					   &h->clkr.hw);
}

static struct platform_driver qcom_hfpll_driver = {
	.probe		= qcom_hfpll_probe,
	.driver		= {
		.name	= "qcom-hfpll",
		.of_match_table = qcom_hfpll_match_table,
	},
};
module_platform_driver(qcom_hfpll_driver);

MODULE_DESCRIPTION("QCOM HFPLL Clock Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:qcom-hfpll");
