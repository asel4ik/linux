// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2018, The Linux Foundation. All rights reserved.

#include <linux/kernel.h>
#include <linux/export.h>
#include <linux/regmap.h>
#include <linux/delay.h>
#include <linux/err.h>
#include <linux/clk-provider.h>
#include <linux/spinlock.h>

#include "clk-regmap.h"
#include "clk-hfpll.h"

#define PLL_OUTCTRL	BIT(0)
#define PLL_BYPASSNL	BIT(1)
#define PLL_RESET_N	BIT(2)

/* Layout of PLL_USER_CTL register */
#define MN_EN_MASK BIT(24)
#define VCO_SEL_BIT BIT(20)
#define PLL_VCO_MASK 0x1
#define PRE_DIV_BIT BIT(12)
#define POST_DIV_MASK GENMASK(9,8) 
#define OUTPUT_INV_BIT BIT(7)
#define PLLOUT_EARLY_BIT BIT(3)
#define PLLOUT_AUX2_BIT BIT(2)
#define PLLOUT_AUX_BIT BIT(1)
#define PLLOUT_MAIN_BIT BIT(0)

static const struct pll_vco *
hf_pll_find_vco(const struct hfpll_data *pll_data, unsigned long rate)
{

	const struct pll_vco *v = pll_data->vco_table;
	const struct pll_vco *end = v + pll_data->num_vco;

	for (; v < end; v++)
		if (rate >= v->min_freq && rate <= v->max_freq)
			return v;

	return NULL;
}

static void clk_pll_configure(const struct hfpll_data *pll_data, struct regmap *regmap,
	const struct hfpll_config *config)
{
	u32 val;
	u32 mask;

	regmap_write(regmap, pll_data->l_reg, config->l);

	val = config->vco_val;
	val |= config->pre_div_val;
	val |= config->post_div_val;
	val |= config->mn_ena_mask;
	val |= config->main_output_mask;
	val |= config->aux_output_mask;

	mask = config->vco_mask;
	mask |= config->pre_div_mask;
	mask |= config->post_div_mask;
	mask |= config->mn_ena_mask;
	mask |= config->main_output_mask;
	mask |= config->aux_output_mask;

	regmap_update_bits(regmap, pll_data->config_reg, mask, val);
}

/* Initialize a HFPLL at a given rate and enable it. */
static void __clk_hfpll_init_once(struct clk_hw *hw)
{
	struct clk_hfpll *h = to_clk_hfpll(hw);
	struct hfpll_data const *hd = h->d;
	struct hfpll_config const *hc = &hd->c;
	struct regmap *regmap = h->clkr.regmap;
        const struct pll_vco *vco;
        unsigned long rate;
	if (likely(h->init_done))
		return;

	/* Configure PLL parameters for integer mode. */
	if (hd->config_val)
		regmap_write(regmap, hd->config_reg, hd->config_val);
		
	/* Write M and N only if MN_EN is enabled. */
	if (hc->mn_ena_mask) {
		regmap_write(regmap, hd->m_reg, 0);
		regmap_write(regmap, hd->n_reg, 1);
	}

        /* Configure user_ctl register */
	if (hd->user_val || hc)
          {
           if (hd->user_reg)
            regmap_write(regmap, hd->user_reg, hd->user_val);
           if(hc)
            clk_pll_configure(hd, regmap, hc);
          }
	  else
	 pr_err("user_reg configuration not specified\n");
	 rate = 19200000*hc->l;
      /* Pick the right VCO. */
        vco = hf_pll_find_vco(hd, rate);
	if (hd->vco_table && !vco) {
		pr_err("%s: alpha pll not in a valid vco range\n",
		       clk_hw_get_name(hw));
	}

	if (vco) {
		regmap_update_bits(regmap, hd->user_reg,
				   VCO_SEL_BIT,
				   vco->val  ? VCO_SEL_BIT : 0);
	};
  
	if (hd->droop_reg)
		regmap_write(regmap, hd->droop_reg, hd->droop_val);

	h->init_done = true;
}

static void __clk_hfpll_enable(struct clk_hw *hw)
{
	struct clk_hfpll *h = to_clk_hfpll(hw);
	struct hfpll_data const *hd = h->d;
	struct regmap *regmap = h->clkr.regmap;
	u32 val;

	__clk_hfpll_init_once(hw);

	/* Disable PLL bypass mode. */
	regmap_update_bits(regmap, hd->mode_reg, PLL_BYPASSNL, PLL_BYPASSNL);

	/*
	 * H/W requires a 5us delay between disabling the bypass and
	 * de-asserting the reset. Delay 10us just to be safe.
	 */
	udelay(10);

	/* De-assert active-low PLL reset. */
	regmap_update_bits(regmap, hd->mode_reg, PLL_RESET_N, PLL_RESET_N);

	/* Wait for PLL to lock. */
	if (hd->status_reg)
		/*
		 * Busy wait. Should never timeout, we add a timeout to
		 * prevent any sort of stall.
		 */
		regmap_read_poll_timeout(regmap, hd->status_reg, val,
					 !(val & BIT(hd->lock_bit)), 0,
					 100 * USEC_PER_MSEC);
	else
		udelay(60);

	/* Enable PLL output. */
	regmap_update_bits(regmap, hd->mode_reg, PLL_OUTCTRL, PLL_OUTCTRL);
}

/* Enable an already-configured HFPLL. */
static int clk_hfpll_enable(struct clk_hw *hw)
{
	unsigned long flags;
	struct clk_hfpll *h = to_clk_hfpll(hw);
	struct hfpll_data const *hd = h->d;
	struct regmap *regmap = h->clkr.regmap;
	u32 mode;

	spin_lock_irqsave(&h->lock, flags);
	regmap_read(regmap, hd->mode_reg, &mode);
	if (!(mode & (PLL_BYPASSNL | PLL_RESET_N | PLL_OUTCTRL)))
		__clk_hfpll_enable(hw);
	spin_unlock_irqrestore(&h->lock, flags);

	return 0;
}

static void __clk_hfpll_disable(struct clk_hfpll *h)
{
	struct hfpll_data const *hd = h->d;
	struct regmap *regmap = h->clkr.regmap;

	/*
	 * Disable the PLL output, disable test mode, enable the bypass mode,
	 * and assert the reset.
	 */
	regmap_update_bits(regmap, hd->mode_reg,
			   PLL_BYPASSNL | PLL_RESET_N | PLL_OUTCTRL, 0);
}

static void clk_hfpll_disable(struct clk_hw *hw)
{
	struct clk_hfpll *h = to_clk_hfpll(hw);
	unsigned long flags;

	spin_lock_irqsave(&h->lock, flags);
	__clk_hfpll_disable(h);
	spin_unlock_irqrestore(&h->lock, flags);
}



static long clk_hfpll_round_rate(struct clk_hw *hw, unsigned long rate,
				 unsigned long *parent_rate)
{
	struct clk_hfpll *h = to_clk_hfpll(hw);
	struct hfpll_data const *hd = h->d;
	unsigned long rrate;

	rate = clamp(rate, hd->min_rate, hd->max_rate);

	rrate = DIV_ROUND_UP(rate, *parent_rate) * *parent_rate;
	if (rrate > hd->max_rate)
		rrate -= *parent_rate;

	return rrate;
}

/*
 * For optimization reasons, assumes no downstream clocks are actively using
 * it.
 */
static int clk_hfpll_set_rate(struct clk_hw *hw, unsigned long rate,
			      unsigned long parent_rate)
{
	struct clk_hfpll *h = to_clk_hfpll(hw);
	struct hfpll_data const *hd = h->d;
	struct regmap *regmap = h->clkr.regmap;
	unsigned long flags;
	u32 l_val;
	const struct pll_vco *vco;
	bool enabled;

	l_val = rate / parent_rate;

	spin_lock_irqsave(&h->lock, flags);

	enabled = __clk_is_enabled(hw->clk);
	if (enabled)
		__clk_hfpll_disable(h);

      /* Pick the right VCO. */
        vco = hf_pll_find_vco(hd, rate);
	if (hd->vco_table && !vco) {
		pr_err("%s: alpha pll not in a valid vco range\n",
		       clk_hw_get_name(hw));
		return -EINVAL;
	}

	if (vco) {
		regmap_update_bits(regmap, hd->user_reg,
				   VCO_SEL_BIT,
				   vco->val  ? VCO_SEL_BIT : 0);
	};

	regmap_write(regmap, hd->l_reg, l_val);

	if (enabled)
		__clk_hfpll_enable(hw);

	spin_unlock_irqrestore(&h->lock, flags);

	return 0;
}

static unsigned long clk_hfpll_recalc_rate(struct clk_hw *hw,
					   unsigned long parent_rate)
{
	struct clk_hfpll *h = to_clk_hfpll(hw);
	struct hfpll_data const *hd = h->d;
	struct regmap *regmap = h->clkr.regmap;
	u32 l_val;

	regmap_read(regmap, hd->l_reg, &l_val);

	return l_val * parent_rate;
}

static int clk_hfpll_init(struct clk_hw *hw)
{
	struct clk_hfpll *h = to_clk_hfpll(hw);
	struct hfpll_data const *hd = h->d;
	struct regmap *regmap = h->clkr.regmap;
	u32 mode, status;

	regmap_read(regmap, hd->mode_reg, &mode);
	if (mode != (PLL_BYPASSNL | PLL_RESET_N | PLL_OUTCTRL)) {
		__clk_hfpll_init_once(hw);
		return 0;
	}

	if (hd->status_reg) {
		regmap_read(regmap, hd->status_reg, &status);
		if (!(status & BIT(hd->lock_bit))) {
			WARN(1, "HFPLL %s is ON, but not locked!\n",
			     __clk_get_name(hw->clk));
			clk_hfpll_disable(hw);
			__clk_hfpll_init_once(hw);
		}
	}

	return 0;
}

static int hfpll_is_enabled(struct clk_hw *hw)
{
	struct clk_hfpll *h = to_clk_hfpll(hw);
	struct hfpll_data const *hd = h->d;
	struct regmap *regmap = h->clkr.regmap;
	u32 mode;

	regmap_read(regmap, hd->mode_reg, &mode);
	mode &= 0x7;
	return mode == (PLL_BYPASSNL | PLL_RESET_N | PLL_OUTCTRL);
}

const struct clk_ops clk_ops_hfpll = {
	.enable = clk_hfpll_enable,
	.disable = clk_hfpll_disable,
	.is_enabled = hfpll_is_enabled,
	.round_rate = clk_hfpll_round_rate,
	.set_rate = clk_hfpll_set_rate,
	.recalc_rate = clk_hfpll_recalc_rate,
	.init = clk_hfpll_init,
};
EXPORT_SYMBOL_GPL(clk_ops_hfpll);
