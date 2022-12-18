/*
static void get_speed_bin(struct platform_device *pdev, int *bin)
{
	struct resource *res;
	void __iomem *base;
	u32 config_efuse;

	*bin = 0;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "gpu-bin");
	if (!res) {
		dev_info(&pdev->dev,
			"No GPU speed binning available. Defaulting to 0.\n");
		return;
	}

	base = ioremap(res->start, resource_size(res));
	if (!base) {
		dev_warn(&pdev->dev,
			"Unable to ioremap efuse reg address. Defaulting to 0.\n");
		return;
	}

	config_efuse = readl_relaxed(base);
	iounmap(base);
	*bin = (config_efuse >> 31) & 0x1;

	dev_info(&pdev->dev, "GPU speed bin: %d\n", *bin);
}
*/
static struct clk_init_data vcodec0_clk_src_init = {
	.name = "vcodec0_clk_src",
	.parent_data = gcc_parent_data_7,
	.num_parents = 5,
	.ops = &clk_rcg2_ops,	
};


static void fixup_for_qm215(struct platform_device *pdev,
	struct regmap *regmap, int speed_bin)
	
	
	{
	gpll3_config.l = 0x30;
	gpll3_config.alpha_hi = 0x70;
	
	
	vfe0_clk_src.freq_tbl = ftbl_vfe0_clk_src_qm215;
	vfe1_clk_src.freq_tbl = ftbl_vfe0_clk_src_qm215;
	vcodec0_clk_src.freq_tbl = ftbl_vcodec0_clk_src_qm215;
	vcodec0_clk_src.parent_map = gcc_parent_map_7;
	vcodec0_clk_src.clkr.hw.init = &vcodec0_clk_src_init;
	cpp_clk_src.freq_tbl = ftbl_cpp_clk_src_qm215;
	gfx3d_clk_src.parent_map = gcc_parent_map_14_gfx3d;
	gfx3d_clk_src.freq_tbl = ftbl_oxili_gfx3d_clk_src_qm215;
	csi0phytimer_clk_src.freq_tbl = ftbl_csi0phytimer_clk_src_qm215;
	csi1phytimer_clk_src.freq_tbl = ftbl_csi0phytimer_clk_src_qm215;
	usb_hs_system_clk_src.freq_tbl = ftbl_usb_hs_system_clk_src_qm215;
	
	};

/*
static void fixup_for_qm215(struct platform_device *pdev,
	struct regmap *regmap, int speed_bin)
{
	gpll3_config.l = 0x30;
	gpll3_config.alpha_hi = 0x70;

	vfe0_clk_src.clkr.hw.init->rate_max
	vfe0_clk_src.clkr.hw.init->rate_max
	vfe0_clk_src.clkr.hw.init->rate_max
	vfe0_clk_src.clkr.hw.init->rate_max
	vfe0_clk_src.clkr.hw.init->rate_max
	vfe0_clk_src.freq_tbl = ftbl_vfe0_clk_src_qm215;

	vfe1_clk_src.clkr.hw.init->rate_max
	vfe1_clk_src.clkr.hw.init->rate_max
	vfe1_clk_src.clkr.hw.init->rate_max
	vfe1_clk_src.clkr.hw.init->rate_max
	vfe1_clk_src.clkr.hw.init->rate_max
	vfe1_clk_src.freq_tbl = ftbl_vfe0_clk_src_qm215;

	cpp_clk_src.clkr.hw.init->rate_max
	cpp_clk_src.clkr.hw.init->rate_max
	cpp_clk_src.clkr.hw.init->rate_max
	cpp_clk_src.clkr.hw.init->rate_max
	cpp_clk_src.clkr.hw.init->rate_max
	cpp_clk_src.freq_tbl = ftbl_cpp_clk_src_qm215;

	vcodec0_clk_src.freq_tbl = ftbl_vcodec0_clk_src_qm215;
	vcodec0_clk_src.parent_map = gcc_parent_map_7;
	vcodec0_clk_src.clkr.hw.init = &vcodec0_clk_src_init;

	gfx3d_clk_src.parent_map = gcc_parent_map_14_gfx3d;
	gfx3d_clk_src.freq_tbl = ftbl_oxili_gfx3d_clk_src_qm215;
	gcc_msm8937_desc.clks[BLSP1_QUP1_I2C_APPS_CLK_SRC] = NULL;
	gcc_msm8937_desc.clks[BLSP1_QUP1_SPI_APPS_CLK_SRC] = NULL;
	gcc_msm8937_desc.clks[BLSP2_QUP4_I2C_APPS_CLK_SRC] = NULL;
	gcc_msm8937_desc.clks[BLSP2_QUP4_SPI_APPS_CLK_SRC] = NULL;
	gcc_msm8937_desc.clks[GCC_BLSP1_QUP1_I2C_APPS_CLK] = NULL;
	gcc_msm8937_desc.clks[GCC_BLSP1_QUP1_SPI_APPS_CLK] = NULL;
	gcc_msm8937_desc.clks[GCC_BLSP2_QUP4_I2C_APPS_CLK] = NULL;
	gcc_msm8937_desc.clks[GCC_BLSP2_QUP4_SPI_APPS_CLK] = NULL;
	gcc_msm8937_desc.clks[GCC_OXILI_AON_CLK] = NULL;
	gcc_msm8937_desc.clks[GCC_OXILI_TIMER_CLK] = NULL;
	gcc_msm8937_desc.clks[ESC1_CLK_SRC] = NULL;
	gcc_msm8937_desc.clks[GCC_MDSS_ESC1_CLK] = NULL;
	
	
	
	if (speed_bin) {
		gcc_oxili_gfx3d_clk.clkr.hw.init->rate_max
			270000000;
		gcc_oxili_gfx3d_clk.clkr.hw.init->rate_max
			400000000;
		gcc_oxili_gfx3d_clk.clkr.hw.init->rate_max
			484800000;
		gcc_oxili_gfx3d_clk.clkr.hw.init->rate_max
			523200000;
		gcc_oxili_gfx3d_clk.clkr.hw.init->rate_max
			650000000;
	} else {
		gcc_oxili_gfx3d_clk.clkr.hw.init->rate_max
			270000000;
		gcc_oxili_gfx3d_clk.clkr.hw.init->rate_max
			400000000;
		gcc_oxili_gfx3d_clk.clkr.hw.init->rate_max
			484800000;
		gcc_oxili_gfx3d_clk.clkr.hw.init->rate_max
			523200000;
		gcc_oxili_gfx3d_clk.clkr.hw.init->rate_max
			598000000;
	}


}

static void fixup_for_sdm439_429(void)
{
	
	gcc_msm8937_desc.clks[GCC_GFX_TCU_CLK] = NULL;
	gcc_msm8937_desc.clks[GCC_GFX_TBU_CLK] = NULL;
	gcc_msm8937_desc.clks[GCC_GTCU_AHB_CLK] = NULL;
}
*/

static const struct of_device_id gcc_msm8937_match_table[] = {
	{ .compatible = "qcom,gcc-msm8937" },
	{ .compatible = "qcom,gcc-qm215" },
	{ .compatible = "qcom,gcc-sdm439" },
	{ }
};
MODULE_DEVICE_TABLE(of, gcc_msm8937_match_table);

static int gcc_msm8937_probe(struct platform_device *pdev)
{
	struct regmap *regmap;
	struct clk *clk;
		/* Configure Sleep and Wakeup cycles for GMEM clock */
		regmap_update_bits(regmap, gcc_oxili_gmem_clk.clkr.enable_reg,
				0xff0, 0xff0);
	}

	clk_alpha_pll_configure(&gpll3_out_main, regmap, &gpll3_config);

	ret = devm_clk_hw_register(&pdev->dev, &gpll3_out_main_div.hw);
	if (ret) {
		dev_err(&pdev->dev, "Failed to register hardware clock\n");
		return ret;
	}

	ret = qcom_cc_really_probe(pdev, &gcc_msm8937_desc, regmap);
	if (ret) {
		dev_err(&pdev->dev, "Failed to register GCC clocks\n");
		return ret;
	}

	clk_set_rate(apss_ahb_clk_src.clkr.hw.clk, 19200000);
	clk_prepare_enable(apss_ahb_clk_src.clkr.hw.clk);
	clk_prepare_enable(gpll0_ao_out_main.clkr.hw.clk);

	dev_info(&pdev->dev, "Registered GCC clocks\n");

	return 0;
}

static struct platform_driver gcc_msm8937_driver = {
	.probe = gcc_msm8937_probe,
	.driver = {
		.name = "gcc-msm8937",
		.of_match_table = gcc_msm8937_match_table,
	},
};

static int __init gcc_msm8937_init(void)
{
	return platform_driver_register(&gcc_msm8937_driver);
}
subsys_initcall(gcc_msm8937_init);

static void __exit gcc_msm8937_exit(void)
{
	platform_driver_unregister(&gcc_msm8937_driver);
}
module_exit(gcc_msm8937_exit);

struct clk_hw *mdss_msm8937_hws[] = {
	[MDSS_MDP_VOTE_CLK] = &mdss_mdp_vote_clk.hw,
	[MDSS_ROTATOR_VOTE_CLK] = &mdss_rotator_vote_clk.hw,
};

static struct clk_regmap *mdss_msm8937_clocks[] = {
	[GCC_MDSS_BYTE0_CLK] = &gcc_mdss_byte0_clk.clkr,
	[GCC_MDSS_BYTE1_CLK] = &gcc_mdss_byte1_clk.clkr,
	[GCC_MDSS_PCLK0_CLK] = &gcc_mdss_pclk0_clk.clkr,
	[GCC_MDSS_PCLK1_CLK] = &gcc_mdss_pclk1_clk.clkr,
	[BYTE0_CLK_SRC] = &byte0_clk_src.clkr,
	[BYTE1_CLK_SRC] = &byte1_clk_src.clkr,
	[PCLK0_CLK_SRC] = &pclk0_clk_src.clkr,
	[PCLK1_CLK_SRC] = &pclk1_clk_src.clkr,
};

static const struct qcom_cc_desc mdss_msm8937_desc = {
	.config = &gcc_msm8937_regmap_config,
	.clks = mdss_msm8937_clocks,
	.num_clks = ARRAY_SIZE(mdss_msm8937_clocks),
	.hwclks = mdss_msm8937_hws,
	.num_hwclks = ARRAY_SIZE(mdss_msm8937_hws),
};

static void fixup_for_qm215_gcc_mdss(void)
{
	/*
	 * Below clocks are not available on QM215, thus mark them NULL.
	 */

	mdss_msm8937_desc.clks[BYTE1_CLK_SRC] = NULL;
	mdss_msm8937_desc.clks[PCLK1_CLK_SRC] = NULL;
	mdss_msm8937_desc.clks[GCC_MDSS_BYTE1_CLK] = NULL;
	mdss_msm8937_desc.clks[GCC_MDSS_PCLK1_CLK] = NULL;
}

static const struct of_device_id mdss_msm8937_match_table[] = {
	{ .compatible = "qcom,gcc-mdss-msm8937" },
	{ .compatible = "qcom,gcc-mdss-qm215" },
	{ .compatible = "qcom,gcc-mdss-sdm439" },
	{}
};
MODULE_DEVICE_TABLE(of, mdss_msm8937_match_table);

static int mdss_msm8937_probe(struct platform_device *pdev)
{
	struct clk *clk;
	struct regmap *regmap;
	struct resource *res;
	void __iomem *base;
	int ret;
	bool is_qm215;

	is_qm215 = of_device_is_compatible(pdev->dev.of_node,
			"qcom,gcc-mdss-qm215");

	clk = clk_get(&pdev->dev, "pclk0_src");
	if (IS_ERR(clk)) {
		if (PTR_ERR(clk) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Unable to get pclk0_src clock\n");
		return PTR_ERR(clk);
	}
	clk_put(clk);

	clk = clk_get(&pdev->dev, "byte0_src");
	if (IS_ERR(clk)) {
		if (PTR_ERR(clk) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Unable to get byte0_src clock\n");
		return PTR_ERR(clk);
	}
	clk_put(clk);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res == NULL) {
		dev_err(&pdev->dev, "Failed to get resources\n");
		return -EINVAL;
	}

	base = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	if (IS_ERR(base))
		return PTR_ERR(base);

	regmap = devm_regmap_init_mmio(&pdev->dev, base,
					mdss_msm8937_desc.config);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	if (is_qm215)
		fixup_for_qm215_gcc_mdss();

	ret = qcom_cc_really_probe(pdev, &mdss_msm8937_desc, regmap);
	if (ret) {
		dev_err(&pdev->dev, "Failed to register MDSS clocks\n");
		return ret;
	}

	dev_info(&pdev->dev, "Registered GCC MDSS Clocks\n");

	return ret;
}

static struct platform_driver mdss_msm8937_driver = {
	.probe = mdss_msm8937_probe,
	.driver = {
		.name = "gcc-mdss-msm8937",
		.of_match_table = mdss_msm8937_match_table,
	},
};

static int __init mdss_msm8937_init(void)
{
	return platform_driver_register(&mdss_msm8937_driver);
}
subsys_initcall(mdss_msm8937_init);

static void __exit mdss_msm8937_exit(void)
{
	platform_driver_unregister(&mdss_msm8937_driver);
}
module_exit(mdss_msm8937_exit);

MODULE_DESCRIPTION("QTI GCC msm8937 Driver");
MODULE_LICENSE("GPL v2");

