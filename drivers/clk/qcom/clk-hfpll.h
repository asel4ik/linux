/* SPDX-License-Identifier: GPL-2.0 */

#ifndef __QCOM_CLK_HFPLL_H__
#define __QCOM_CLK_HFPLL_H__

#include <linux/clk-provider.h>
#include <linux/spinlock.h>
#include "clk-regmap.h"


struct pll_vco {
	unsigned long min_freq;
	unsigned long max_freq;
	u32 val;
};

#define VCO(a, b, c) { \
	.val = a,\
	.min_freq = b,\
	.max_freq = c,\
}

struct hfpll_config {
	u16 l;
	u32 m;
	u32 n;
	u32 vco_val;
	u32 vco_mask;
	u32 pre_div_val;
	u32 pre_div_mask;
	u32 post_div_val;
	u32 post_div_mask;
	u32 mn_ena_mask;
	u32 early_output_mask;
	u32 main_output_mask;
	u32 aux_output_mask;
};

struct hfpll_data {
        const struct pll_vco *vco_table;
	size_t num_vco;
	u32 mode_reg;
	u32 l_reg;
	u32 m_reg;
	u32 n_reg;
	u32 user_reg;
	u32 droop_reg;
	u32 config_reg;
	u32 status_reg;
	u8  lock_bit;

	u32 droop_val;
	u32 config_val;
	u32 user_val;
	u32 user_vco_mask;
	unsigned long low_vco_max_rate;
	
	unsigned long min_rate;
	unsigned long max_rate;
	struct hfpll_config const c;
};

struct clk_hfpll {
	struct hfpll_data const *d;
	int init_done;

	struct clk_regmap clkr;
	spinlock_t lock;
};

#define to_clk_hfpll(_hw) \
	container_of(to_clk_regmap(_hw), struct clk_hfpll, clkr)

extern const struct clk_ops clk_ops_hfpll;

#endif
