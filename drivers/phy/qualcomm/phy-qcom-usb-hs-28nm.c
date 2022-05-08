// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2009-2018, Linux Foundation. All rights reserved.
 * Copyright (c) 2018-2020, Linaro Limited
 */

#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_graph.h>
#include <linux/phy/phy.h>
#include <linux/platform_device.h>
#include <linux/regulator/consumer.h>
#include <linux/reset.h>
#include <linux/slab.h>
#include <linux/regmap.h>


/* PHY register and bit definitions */

#define USB_PHY_UTMI_CTRL5		0x0074
#define PICOPHY_UTMI_CONTROL_OVERWRITE_EN	BIT(4)
#define POR					BIT(1)
#define ATERESET				BIT(0)
#define USB_PHY_HS_PHY_CTRL_COMMON0	0x0078
#define COMMONONN				BIT(7)
#define FSEL					GENMASK(6, 4)
#define RETENABLEN				BIT(3)
#define SIDDQ					BIT(2)
#define VATESTENB				GENMASK(1, 0)
#define USB_PHY_HS_PHY_CTRL_COMMON1	0x007c
#define PLLBTUNE				BIT(7)
#define USE_CLKCORE				BIT(6)
#define ACAENB0					BIT(5)
#define VBUSVLDEXTSEL0				BIT(4)
#define OTGDISABLE0				BIT(3)
#define OTGTUNE0				GENMASK(2, 0)
#define USB_PHY_HS_PHY_CTRL1		0x008c
#define VBUSVLDEXT0				BIT(5)
#define ULPIPOR					BIT(2)
#define ID_HV_CLAMP_EN_N			BIT(1)
#define ULPI_CLK_EN				BIT(0)
#define USB_PHY_HS_PHY_CTRL2		0x0090
#define USB2_SUSPEND_N_SEL			BIT(7)
#define USB2_SUSPEND_N				BIT(6)
#define USB2_UTMI_CLK_EN			BIT(5)
#define AUTORESUME_LEGACY			BIT(4)
#define AUTORESUME				BIT(3)
#define USB_PHY_PARAMETER_OVERRIDE_X0	0x0098
#define SQRXTUNE0				GENMASK(7, 5)
#define COMPDISTUNE0				GENMASK(2, 0)
#define USB_PHY_PARAMETER_OVERRIDE_X1	0x009c
#define TXPREEMPAMPTUNE0			GENMASK(7, 6)
#define TXPREEMPPULSETUNE0			BIT(5)
#define TXVREFTUNE0				GENMASK(3, 0)
#define USB_PHY_PARAMETER_OVERRIDE_X2		0x00A0
#define TXRESTUNE0				GENMASK(5, 4)
#define TXHSXVTUNE0				GENMASK(3, 2)
#define TXRISETUNE0				GENMASK(1, 0)
#define USB_PHY_PARAMETER_OVERRIDE_X3	0x00a4
#define TXFSLSTUNE0				GENMASK(3, 0)
#define USB_PHY_TCSR_CTRL		0x00c0
#define SNPS_CTRL_USB2_PHY			BIT(0)
#define USB_PHY_IRQ_CMD			0x0d0
#define IRQ_GLOBAL_CLEAR			BIT(0)
#define PHY_INTR_MASK0			0x0d4
#define PHY_INTR_CLEAR0			0x0dc
#define DP_1_0					BIT(4)
#define DP_0_1					BIT(3)
#define DM_1_0					BIT(2)
#define DM_0_1					BIT(1)
#define USB_PHY_REFCLK_CTRL		0x00e8
#define REFCLK_SEL				GENMASK(3, 1)
#define REFCLK_RXTAP_EN				BIT(0)

enum hsphy_voltage {
	VOL_NONE,
	VOL_MIN,
	VOL_MAX,
	VOL_NUM,
};

enum hsphy_vreg {
	VDD,
	VDDA_1P8,
	VDDA_3P3,
	VREG_NUM,
};

struct hsphy_init_seq {
	int offset;
	int val;
	int delay;
};

struct hsphy_data {
	const struct hsphy_init_seq *init_seq;
	unsigned int init_seq_num;
};

/* struct override_param - structure holding one femtophy overriding param
 * set override true if the  device tree property exists and read and assign
 * to value
 */
struct override_param {
	bool override;
	u8 value;
};

/* struct override_params - structure holding overriding params
 * for femtophy strap signals exposed in registers
 *
 * currently only straps overriden during the qcs405 init sequence are present
 *
 * @snps_ctrl_usb2_phy: not actually a femtophy strap signal, but is set as
 *  part of the qcs405 init sequence; meaning unknown
 * @commononn: Common Block Power-Down Control, set low to prevent CLK48MOHCI,
 *  CLK12MOHCI, and CLK480M from powering down in suspend/sleep.
 * @otgtune0: set lower or higher than 0x3 to adjust VBUS Valid Threshold
 * @usb2_utmi_clk_en: not a name of a femtophy strap signal, why qcom why...
 */
struct override_params {
	struct override_param snps_ctrl_usb2_phy;
	struct override_param commononn;
	struct override_param otgtune0;
	struct override_param usb2_utmi_clk_en;
	bool overrides_present;
};

struct hsphy_priv {
	void __iomem *base;
	struct clk_bulk_data *clks;
	int num_clks;
	struct reset_control *phy_reset;
	struct reset_control *por_reset;
	struct regulator_bulk_data vregs[VREG_NUM];
	const struct hsphy_data *data;
	enum phy_mode mode;
	struct regmap *map;
	struct override_params overrides;
};

static const struct regmap_config phy_regmap_cfg = {
	.reg_bits = 32,
	.val_bits = 8,	/* the register is 32 bits long, but really contains four copies */
			/* of the actually implemented lower 8 bits                      */
	.reg_stride = 4,
	.max_register = 0x200,
};

static int qcom_snps_hsphy_set_mode(struct phy *phy, enum phy_mode mode,
				    int submode)
{
	struct hsphy_priv *priv = phy_get_drvdata(phy);

	priv->mode = PHY_MODE_INVALID;

	if (mode > 0)
		priv->mode = mode;

	return 0;
}

static inline void qcom_snps_hsphy_clear_pending_interrupts(struct hsphy_priv *priv)
{
	regmap_set_bits(priv->map, PHY_INTR_CLEAR0, DP_1_0 | DP_0_1 | DM_1_0 | DM_0_1);

	regmap_clear_bits(priv->map, USB_PHY_IRQ_CMD, IRQ_GLOBAL_CLEAR);
	usleep_range(200, 220);
	regmap_set_bits(priv->map, USB_PHY_IRQ_CMD, IRQ_GLOBAL_CLEAR);

	/* Make sure the interrupts are cleared */
	usleep_range(200, 220);
}

static void qcom_snps_hsphy_enable_hv_interrupts(struct hsphy_priv *priv)
{
	/* Clear any existing interrupts before enabling the interrupts */
	qcom_snps_hsphy_clear_pending_interrupts(priv);

	switch (priv->mode) {
	case PHY_MODE_USB_HOST_HS:
	case PHY_MODE_USB_HOST_FS:
	case PHY_MODE_USB_DEVICE_HS:
	case PHY_MODE_USB_DEVICE_FS:
		regmap_set_bits(priv->map, PHY_INTR_MASK0, DP_1_0 | DM_0_1);
		break;
	case PHY_MODE_USB_HOST_LS:
	case PHY_MODE_USB_DEVICE_LS:
		regmap_set_bits(priv->map, PHY_INTR_MASK0, DP_0_1 | DM_1_0);
		break;
	default:
		/* No device connected */
		regmap_set_bits(priv->map, PHY_INTR_MASK0, DP_0_1 | DM_0_1);
		break;
	}
}

static inline void qcom_snps_hsphy_disable_hv_interrupts(struct hsphy_priv *priv)
{
	regmap_clear_bits(priv->map, PHY_INTR_MASK0, DP_1_0 | DP_0_1 | DM_1_0 | DM_0_1);

	/* Clear any pending interrupts */
	qcom_snps_hsphy_clear_pending_interrupts(priv);
}

static inline void qcom_snps_hsphy_enter_retention(struct hsphy_priv *priv)
{
	regmap_set_bits(priv->map, USB_PHY_HS_PHY_CTRL_COMMON0, SIDDQ);
}

static inline void qcom_snps_hsphy_exit_retention(struct hsphy_priv *priv)
{
	regmap_clear_bits(priv->map, USB_PHY_HS_PHY_CTRL_COMMON0, SIDDQ);
}

static int qcom_snps_hsphy_power_on(struct phy *phy)
{
	struct hsphy_priv *priv = phy_get_drvdata(phy);
	int ret;

	ret = regulator_bulk_enable(VREG_NUM, priv->vregs);
	if (ret)
		return ret;

	qcom_snps_hsphy_disable_hv_interrupts(priv);
	qcom_snps_hsphy_exit_retention(priv);

	return 0;
}

static int qcom_snps_hsphy_power_off(struct phy *phy)
{
	struct hsphy_priv *priv = phy_get_drvdata(phy);

	qcom_snps_hsphy_enter_retention(priv);
	qcom_snps_hsphy_enable_hv_interrupts(priv);
	regulator_bulk_disable(VREG_NUM, priv->vregs);

	return 0;
}

static int qcom_snps_hsphy_reset(struct hsphy_priv *priv)
{
	int ret;

	ret = reset_control_assert(priv->phy_reset);
	if (ret)
		return ret;

	usleep_range(10, 15);

	ret = reset_control_deassert(priv->phy_reset);
	if (ret)
		return ret;

	usleep_range(80, 100);

	return 0;
}

static void qcom_snps_hsphy_set_overrides(struct hsphy_priv *priv)
{
	struct override_params *or = &priv->overrides;

	// don't needlessly reset if we're not applying overrides
	if(!or->overrides_present)
		return;

	/* the reason for why some overrides are applied before asserting POR is not known */
	if(or->snps_ctrl_usb2_phy.override)
		regmap_update_bits(priv->map, USB_PHY_TCSR_CTRL, SNPS_CTRL_USB2_PHY, or->snps_ctrl_usb2_phy.value);

	/* assert POR (relation to the GCC-controller POR signal unknown) */
	regmap_set_bits(priv->map, USB_PHY_UTMI_CTRL5, POR);

	if(or->commononn.override)
		regmap_update_bits(priv->map, USB_PHY_HS_PHY_CTRL_COMMON0, COMMONONN, or->commononn.value);

	if(or->otgtune0.override)
		regmap_update_bits(priv->map, USB_PHY_HS_PHY_CTRL_COMMON1, OTGTUNE0, or->otgtune0.value);

	if(or->usb2_utmi_clk_en.override)
		regmap_update_bits(priv->map, USB_PHY_HS_PHY_CTRL2, USB2_UTMI_CLK_EN, or->usb2_utmi_clk_en.value);

	/* de-assert POR */
	regmap_set_bits(priv->map, USB_PHY_HS_PHY_CTRL2, USB2_SUSPEND_N_SEL);
	regmap_clear_bits(priv->map, USB_PHY_UTMI_CTRL5, POR);
	regmap_clear_bits(priv->map, USB_PHY_HS_PHY_CTRL2, USB2_SUSPEND_N_SEL);

}

static int qcom_snps_hsphy_por_reset(struct hsphy_priv *priv)
{
	int ret;

	ret = reset_control_assert(priv->por_reset);
	if (ret)
		return ret;

	/*
	 * The Femto PHY is POR reset in the following scenarios.
	 *
	 * 1. After overriding the parameter registers.
	 * 2. Low power mode exit from PHY retention.
	 *
	 * Ensure that SIDDQ is cleared before bringing the PHY
	 * out of reset.
	 */
	qcom_snps_hsphy_exit_retention(priv);

	/*
	 * As per databook, 10 usec delay is required between
	 * PHY POR assert and de-assert.
	 */
	usleep_range(10, 20);
	ret = reset_control_deassert(priv->por_reset);
	if (ret)
		return ret;

	/*
	 * As per databook, it takes 75 usec for PHY to stabilize
	 * after the reset.
	 */
	usleep_range(80, 100);

	return 0;
}

static int qcom_snps_hsphy_init(struct phy *phy)
{
	struct hsphy_priv *priv = phy_get_drvdata(phy);
	int ret;

	ret = clk_bulk_prepare_enable(priv->num_clks, priv->clks);
	if (ret)
		return ret;

	ret = qcom_snps_hsphy_reset(priv);
	if (ret)
		goto disable_clocks;

	qcom_snps_hsphy_set_overrides(priv);

	ret = qcom_snps_hsphy_por_reset(priv);
	if (ret)
		goto disable_clocks;

	return 0;

disable_clocks:
	clk_bulk_disable_unprepare(priv->num_clks, priv->clks);
	return ret;
}

static int qcom_snps_hsphy_exit(struct phy *phy)
{
	struct hsphy_priv *priv = phy_get_drvdata(phy);

	clk_bulk_disable_unprepare(priv->num_clks, priv->clks);

	return 0;
}

static const struct phy_ops qcom_snps_hsphy_ops = {
	.init = qcom_snps_hsphy_init,
	.exit = qcom_snps_hsphy_exit,
	.power_on = qcom_snps_hsphy_power_on,
	.power_off = qcom_snps_hsphy_power_off,
	.set_mode = qcom_snps_hsphy_set_mode,
	.owner = THIS_MODULE,
};

static const char * const qcom_snps_hsphy_clks[] = {
	"ref",
	"ahb",
	"sleep",
};

static int qcom_snps_hsphy_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct phy_provider *provider;
	struct hsphy_priv *priv;
	struct phy *phy;
	int ret;
	int i;
	u32 value;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);

	priv->map  = devm_regmap_init_mmio(dev, priv->base , &phy_regmap_cfg);

	priv->num_clks = ARRAY_SIZE(qcom_snps_hsphy_clks);
	priv->clks = devm_kcalloc(dev, priv->num_clks, sizeof(*priv->clks),
				  GFP_KERNEL);
	if (!priv->clks)
		return -ENOMEM;

	for (i = 0; i < priv->num_clks; i++)
		priv->clks[i].id = qcom_snps_hsphy_clks[i];

	ret = devm_clk_bulk_get(dev, priv->num_clks, priv->clks);
	if (ret)
		return ret;

	priv->phy_reset = devm_reset_control_get_exclusive(dev, "phy");
	if (IS_ERR(priv->phy_reset))
		return PTR_ERR(priv->phy_reset);

	priv->por_reset = devm_reset_control_get_exclusive(dev, "por");
	if (IS_ERR(priv->por_reset))
		return PTR_ERR(priv->por_reset);

	priv->vregs[VDD].supply = "vdd";
	priv->vregs[VDDA_1P8].supply = "vdda1p8";
	priv->vregs[VDDA_3P3].supply = "vdda3p3";

	ret = devm_regulator_bulk_get(dev, VREG_NUM, priv->vregs);
	if (ret)
		return ret;

	/* Get device match data */
	priv->data = device_get_match_data(dev);

	/* Overwrite settings */

 	if (!of_property_read_u32(dev->of_node, "qcom,snps_ctrl_usb2_phy-value", &value)) {
		priv->overrides.snps_ctrl_usb2_phy.value = (u8)value;
		priv->overrides.snps_ctrl_usb2_phy.override = true;
		priv->overrides.overrides_present = true;
	}

	if (!of_property_read_u32(dev->of_node, "qcom,commononn-value", &value)) {
		priv->overrides.commononn.value = (u8)value;
		priv->overrides.commononn.override = true;
		priv->overrides.overrides_present = true;
	}

	if (!of_property_read_u32(dev->of_node, "qcom,otgtune0-value", &value)) {
		priv->overrides.otgtune0.value = (u8)value;
		priv->overrides.otgtune0.override = true;
		priv->overrides.overrides_present = true;
	}

	if (!of_property_read_u32(dev->of_node, "qcom,usb2_utmi_clk_en-value", &value)) {
		priv->overrides.usb2_utmi_clk_en.value = (u8)value;
		priv->overrides.usb2_utmi_clk_en.override = true;
		priv->overrides.overrides_present = true;
	}

	phy = devm_phy_create(dev, dev->of_node, &qcom_snps_hsphy_ops);
	if (IS_ERR(phy))
		return PTR_ERR(phy);

	phy_set_drvdata(phy, priv);

	provider = devm_of_phy_provider_register(dev, of_phy_simple_xlate);
	if (IS_ERR(provider))
		return PTR_ERR(provider);

	ret = regulator_set_load(priv->vregs[VDDA_1P8].consumer, 19000);
	if (ret < 0)
		return ret;

	ret = regulator_set_load(priv->vregs[VDDA_3P3].consumer, 16000);
	if (ret < 0)
		goto unset_1p8_load;

	return 0;

unset_1p8_load:
	regulator_set_load(priv->vregs[VDDA_1P8].consumer, 0);

	return ret;
}

static const struct of_device_id qcom_snps_hsphy_match[] = {
	{ .compatible = "qcom,usb-hs-28nm-femtophy" },
	{ },
};
MODULE_DEVICE_TABLE(of, qcom_snps_hsphy_match);

static struct platform_driver qcom_snps_hsphy_driver = {
	.probe = qcom_snps_hsphy_probe,
	.driver	= {
		.name = "qcom,usb-hs-28nm-phy",
		.of_match_table = qcom_snps_hsphy_match,
	},
};
module_platform_driver(qcom_snps_hsphy_driver);

MODULE_DESCRIPTION("Qualcomm 28nm Hi-Speed USB PHY driver");
MODULE_LICENSE("GPL v2");

