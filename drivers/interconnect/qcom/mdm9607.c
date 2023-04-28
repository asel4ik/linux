// SPDX-License-Identifier: GPL-2.0

#include <linux/clk.h>
#include <linux/device.h>
#include <linux/interconnect-provider.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include <linux/regmap.h>
#include <linux/slab.h>

#include <dt-bindings/interconnect/qcom,mdm9607.h>

#include "icc-rpm.h"
#include "smd-rpm.h"


enum {
	QNOC_MASTER_AMPSS_M0 = 1,
	QNOC_MASTER_PCNOC_BIMC_1,
	QNOC_MASTER_TCU_0,
	QNOC_MASTER_QDSS_BAM,
	QNOC_MASTER_BIMC_PCNOC,
	QNOC_MASTER_QDSS_ETR,
	QNOC_MASTER_AUDIO,
	QNOC_MASTER_QPIC,
	QNOC_MASTER_USB_HSIC,
	QNOC_MASTER_BLSP_1,
	QNOC_MASTER_USB_HS,
	QNOC_MASTER_CRYPTO,
	QNOC_MASTER_SDCC_1,
	QNOC_MASTER_SDCC_2,
	QNOC_MASTER_XM_USB_HS1,
	QNOC_MASTER_XI_USB_HSIC,
	QNOC_MASTER_SGMII,
	QNOC_PNOC_M_0,
	QNOC_PNOC_M_1,
	QNOC_SNOC_QDSS_INT,
	QNOC_PNOC_INT_0,
	QNOC_PNOC_INT_2,
	QNOC_PNOC_INT_3,
	QNOC_PNOC_SLV_0,
	QNOC_PNOC_SLV_1,
	QNOC_PNOC_SLV_2,
	QNOC_PNOC_SLV_3,
	QNOC_PNOC_SLV_4,
	QNOC_PNOC_SLV_5,
	QNOC_SLAVE_EBI_CH0,
	QNOC_SLAVE_BIMC_PCNOC,
	QNOC_SLAVE_PCNOC_BIMC_1,
	QNOC_SLAVE_QDSS_STM,
	QNOC_SLAVE_CATS_128,
	QNOC_SLAVE_SYSTEM_IMEM,
	QNOC_SLAVE_TCSR,
	QNOC_SLAVE_SDCC_1,
	QNOC_SLAVE_BLSP_1,
	QNOC_SLAVE_SGMII,
	QNOC_SLAVE_CRYPTO_0_CFG,
	QNOC_SLAVE_MESSAGE_RAM,
	QNOC_SLAVE_PDM,
	QNOC_SLAVE_PRNG,
	QNOC_SLAVE_USB_HS,
	QNOC_SLAVE_SDCC_2,
	QNOC_SLAVE_AUDIO,
	QNOC_SLAVE_USB_HSIC,
	QNOC_SLAVE_USB_PHYS_CFG,
	QNOC_SLAVE_TLMM,
	QNOC_SLAVE_IMEM_CFG,
	QNOC_SLAVE_PMIC_ARB,
	QNOC_SLAVE_TCU,
	QNOC_SLAVE_QPIC,
};

static const u16 mas_apps_proc_links[] = {
	QNOC_SLAVE_BIMC_PCNOC,
	QNOC_SLAVE_EBI_CH0
};

static struct qcom_icc_node mas_apps_proc = {
	.name = "mas_apps_proc",
	.id = QNOC_MASTER_AMPSS_M0,
	.buswidth = 8,
	.mas_rpm_id = 0,
	.slv_rpm_id = -1,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.areq_prio = 0,
	.qos.prio_level = 0,
	.qos.qos_port = 0,
	.num_links = ARRAY_SIZE(mas_apps_proc_links),
	.links = mas_apps_proc_links,
};

static const u16 mas_pcnoc_bimc_1_links[] = {
	QNOC_SLAVE_EBI_CH0
};

static struct qcom_icc_node mas_pcnoc_bimc_1 = {
	.name = "mas_pcnoc_bimc_1",
	.id = QNOC_MASTER_PCNOC_BIMC_1,
	.buswidth = 8,
	.mas_rpm_id = 139,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_pcnoc_bimc_1_links),
	.links = mas_pcnoc_bimc_1_links,
};

static const u16 mas_tcu_0_links[] = {
	QNOC_SLAVE_EBI_CH0
};

static struct qcom_icc_node mas_tcu_0 = {
	.name = "mas_tcu_0",
	.id = QNOC_MASTER_TCU_0,
	.buswidth = 8,
	.mas_rpm_id = 102,
	.slv_rpm_id = -1,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.areq_prio = 0,
	.qos.prio_level = 2,
	.qos.qos_port = 5,
	.num_links = ARRAY_SIZE(mas_tcu_0_links),
	.links = mas_tcu_0_links,
};

static const u16 mas_qdss_bam_links[] = {
	QNOC_SNOC_QDSS_INT
};

static struct qcom_icc_node mas_qdss_bam = {
	.name = "mas_qdss_bam",
	.id = QNOC_MASTER_QDSS_BAM,
	.buswidth = 4,
	.mas_rpm_id = 19,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_qdss_bam_links),
	.links = mas_qdss_bam_links,
};

static const u16 mas_bimc_pcnoc_links[] = {
	QNOC_PNOC_INT_0,
	QNOC_PNOC_INT_2,
	QNOC_SLAVE_CATS_128
};

static struct qcom_icc_node mas_bimc_pcnoc = {
	.name = "mas_bimc_pcnoc",
	.id = QNOC_MASTER_BIMC_PCNOC,
	.buswidth = 8,
	.mas_rpm_id = 140,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_bimc_pcnoc_links),
	.links = mas_bimc_pcnoc_links,
};

static const u16 mas_qdss_etr_links[] = {
	QNOC_SNOC_QDSS_INT
};

static struct qcom_icc_node mas_qdss_etr = {
	.name = "mas_qdss_etr",
	.id = QNOC_MASTER_QDSS_ETR,
	.buswidth = 8,
	.mas_rpm_id = 31,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_qdss_etr_links),
	.links = mas_qdss_etr_links,
};

static const u16 mas_audio_links[] = {
	QNOC_PNOC_M_0
};

static struct qcom_icc_node mas_audio = {
	.name = "mas_audio",
	.id = QNOC_MASTER_AUDIO,
	.buswidth = 4,
	.mas_rpm_id = 78,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_audio_links),
	.links = mas_audio_links,
};

static const u16 mas_qpic_links[] = {
	QNOC_PNOC_M_0
};

static struct qcom_icc_node mas_qpic = {
	.name = "mas_qpic",
	.id = QNOC_MASTER_QPIC,
	.buswidth = 4,
	.mas_rpm_id = 58,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_qpic_links),
	.links = mas_qpic_links,
};

static const u16 mas_hsic_links[] = {
	QNOC_PNOC_M_0
};

static struct qcom_icc_node mas_hsic = {
	.name = "mas_hsic",
	.id = QNOC_MASTER_USB_HSIC,
	.buswidth = 4,
	.mas_rpm_id = 40,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_hsic_links),
	.links = mas_hsic_links,
};

static const u16 mas_blsp_1_links[] = {
	QNOC_PNOC_M_1
};

static struct qcom_icc_node mas_blsp_1 = {
	.name = "mas_blsp_1",
	.id = QNOC_MASTER_BLSP_1,
	.buswidth = 4,
	.mas_rpm_id = 41,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_blsp_1_links),
	.links = mas_blsp_1_links,
};

static const u16 mas_usb_hs1_links[] = {
	QNOC_PNOC_M_1
};

static struct qcom_icc_node mas_usb_hs1 = {
	.name = "mas_usb_hs1",
	.id = QNOC_MASTER_USB_HS,
	.buswidth = 4,
	.mas_rpm_id = 42,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_usb_hs1_links),
	.links = mas_usb_hs1_links,
};

static const u16 mas_crypto_links[] = {
	QNOC_PNOC_INT_3
};

static struct qcom_icc_node mas_crypto = {
	.name = "mas_crypto",
	.id = QNOC_MASTER_CRYPTO,
	.buswidth = 8,
	.mas_rpm_id = 23,
	.slv_rpm_id = -1,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.areq_prio = 2,
	.qos.prio_level = 2,
	.qos.qos_port = 0,
	.num_links = ARRAY_SIZE(mas_crypto_links),
	.links = mas_crypto_links,
};

static const u16 mas_sdcc_1_links[] = {
	QNOC_PNOC_INT_3
};

static struct qcom_icc_node mas_sdcc_1 = {
	.name = "mas_sdcc_1",
	.id = QNOC_MASTER_SDCC_1,
	.buswidth = 8,
	.mas_rpm_id = 33,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_sdcc_1_links),
	.links = mas_sdcc_1_links,
};

static const u16 mas_sdcc_2_links[] = {
	QNOC_PNOC_INT_3
};

static struct qcom_icc_node mas_sdcc_2 = {
	.name = "mas_sdcc_2",
	.id = QNOC_MASTER_SDCC_2,
	.buswidth = 8,
	.mas_rpm_id = 35,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_sdcc_2_links),
	.links = mas_sdcc_2_links,
};

static const u16 mas_xi_usb_hs1_links[] = {
	QNOC_SLAVE_PCNOC_BIMC_1,
	QNOC_PNOC_INT_2
};

static struct qcom_icc_node mas_xi_usb_hs1 = {
	.name = "mas_xi_usb_hs1",
	.id = QNOC_MASTER_XM_USB_HS1,
	.buswidth = 8,
	.mas_rpm_id = 138,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_xi_usb_hs1_links),
	.links = mas_xi_usb_hs1_links,
};

static const u16 mas_xi_hsic_links[] = {
	QNOC_SLAVE_PCNOC_BIMC_1,
	QNOC_PNOC_INT_2
};

static struct qcom_icc_node mas_xi_hsic = {
	.name = "mas_xi_hsic",
	.id = QNOC_MASTER_XI_USB_HSIC,
	.buswidth = 8,
	.mas_rpm_id = 141,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_xi_hsic_links),
	.links = mas_xi_hsic_links,
};

static const u16 mas_sgmii_links[] = {
	QNOC_SLAVE_PCNOC_BIMC_1,
	QNOC_PNOC_INT_2
};

static struct qcom_icc_node mas_sgmii = {
	.name = "mas_sgmii",
	.id = QNOC_MASTER_SGMII,
	.buswidth = 8,
	.mas_rpm_id = 142,
	.slv_rpm_id = -1,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.areq_prio = 1,
	.qos.prio_level = 1,
	.qos.qos_port = 10,
	.num_links = ARRAY_SIZE(mas_sgmii_links),
	.links = mas_sgmii_links,
};

static const u16 pcnoc_m_0_links[] = {
	QNOC_SLAVE_PCNOC_BIMC_1,
	QNOC_PNOC_INT_2
};

static struct qcom_icc_node pcnoc_m_0 = {
	.name = "pcnoc_m_0",
	.id = QNOC_PNOC_M_0,
	.buswidth = 4,
	.mas_rpm_id = 87,
	.slv_rpm_id = 116,
	.num_links = ARRAY_SIZE(pcnoc_m_0_links),
	.links = pcnoc_m_0_links,
};

static const u16 pcnoc_m_1_links[] = {
	QNOC_SLAVE_PCNOC_BIMC_1,
	QNOC_PNOC_INT_2
};

static struct qcom_icc_node pcnoc_m_1 = {
	.name = "pcnoc_m_1",
	.id = QNOC_PNOC_M_1,
	.buswidth = 4,
	.mas_rpm_id = 88,
	.slv_rpm_id = 117,
	.num_links = ARRAY_SIZE(pcnoc_m_1_links),
	.links = pcnoc_m_1_links,
};

static const u16 qdss_int_links[] = {
	QNOC_PNOC_INT_0,
	QNOC_SLAVE_PCNOC_BIMC_1
};

static struct qcom_icc_node qdss_int = {
	.name = "qdss_int",
	.id = QNOC_SNOC_QDSS_INT,
	.buswidth = 8,
	.mas_rpm_id = 98,
	.slv_rpm_id = 128,
	.num_links = ARRAY_SIZE(qdss_int_links),
	.links = qdss_int_links,
};

static const u16 pcnoc_int_0_links[] = {
	QNOC_SLAVE_SYSTEM_IMEM,
	QNOC_SLAVE_QDSS_STM
};

static struct qcom_icc_node pcnoc_int_0 = {
	.name = "pcnoc_int_0",
	.id = QNOC_PNOC_INT_0,
	.buswidth = 8,
	.mas_rpm_id = 85,
	.slv_rpm_id = 114,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.num_links = ARRAY_SIZE(pcnoc_int_0_links),
	.links = pcnoc_int_0_links,
};

static const u16 pcnoc_int_2_links[] = {
	QNOC_PNOC_SLV_1,
	QNOC_PNOC_SLV_2,
	QNOC_PNOC_SLV_0,
	QNOC_PNOC_SLV_4,
	QNOC_PNOC_SLV_5,
	QNOC_PNOC_SLV_3,
	QNOC_SLAVE_TCU
};

static struct qcom_icc_node pcnoc_int_2 = {
	.name = "pcnoc_int_2",
	.id = QNOC_PNOC_INT_2,
	.buswidth = 8,
	.mas_rpm_id = 124,
	.slv_rpm_id = 184,
	.num_links = ARRAY_SIZE(pcnoc_int_2_links),
	.links = pcnoc_int_2_links,
};

static const u16 pcnoc_int_3_links[] = {
	QNOC_SLAVE_PCNOC_BIMC_1,
	QNOC_PNOC_INT_2
};

static struct qcom_icc_node pcnoc_int_3 = {
	.name = "pcnoc_int_3",
	.id = QNOC_PNOC_INT_3,
	.buswidth = 8,
	.mas_rpm_id = 125,
	.slv_rpm_id = 185,
	.num_links = ARRAY_SIZE(pcnoc_int_3_links),
	.links = pcnoc_int_3_links,
};

static const u16 pcnoc_s_0_links[] = {
	QNOC_SLAVE_TCSR,
	QNOC_SLAVE_SDCC_1,
	QNOC_SLAVE_BLSP_1,
	QNOC_SLAVE_SGMII
};

static struct qcom_icc_node pcnoc_s_0 = {
	.name = "pcnoc_s_0",
	.id = QNOC_PNOC_SLV_0,
	.buswidth = 4,
	.mas_rpm_id = 89,
	.slv_rpm_id = 118,
	.num_links = ARRAY_SIZE(pcnoc_s_0_links),
	.links = pcnoc_s_0_links,
};

static const u16 pcnoc_s_1_links[] = {
	QNOC_SLAVE_USB_HS,
	QNOC_SLAVE_CRYPTO_0_CFG,
	QNOC_SLAVE_PRNG,
	QNOC_SLAVE_PDM,
	QNOC_SLAVE_MESSAGE_RAM
};

static struct qcom_icc_node pcnoc_s_1 = {
	.name = "pcnoc_s_1",
	.id = QNOC_PNOC_SLV_1,
	.buswidth = 4,
	.mas_rpm_id = 90,
	.slv_rpm_id = 119,
	.num_links = ARRAY_SIZE(pcnoc_s_1_links),
	.links = pcnoc_s_1_links,
};

static const u16 pcnoc_s_2_links[] = {
	QNOC_SLAVE_USB_HSIC,
	QNOC_SLAVE_SDCC_2,
	QNOC_SLAVE_AUDIO
};

static struct qcom_icc_node pcnoc_s_2 = {
	.name = "pcnoc_s_2",
	.id = QNOC_PNOC_SLV_2,
	.buswidth = 4,
	.mas_rpm_id = 91,
	.slv_rpm_id = 120,
	.num_links = ARRAY_SIZE(pcnoc_s_2_links),
	.links = pcnoc_s_2_links,
};

static const u16 pcnoc_s_3_links[] = {
	QNOC_SLAVE_USB_PHYS_CFG
};

static struct qcom_icc_node pcnoc_s_3 = {
	.name = "pcnoc_s_3",
	.id = QNOC_PNOC_SLV_3,
	.buswidth = 4,
	.mas_rpm_id = 92,
	.slv_rpm_id = 121,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.num_links = ARRAY_SIZE(pcnoc_s_3_links),
	.links = pcnoc_s_3_links,
};

static const u16 pcnoc_s_4_links[] = {
	QNOC_SLAVE_IMEM_CFG,
	QNOC_SLAVE_PMIC_ARB
};

static struct qcom_icc_node pcnoc_s_4 = {
	.name = "pcnoc_s_4",
	.id = QNOC_PNOC_SLV_4,
	.buswidth = 4,
	.mas_rpm_id = 93,
	.slv_rpm_id = 122,
	.num_links = ARRAY_SIZE(pcnoc_s_4_links),
	.links = pcnoc_s_4_links,
};

static const u16 pcnoc_s_5_links[] = {
	QNOC_SLAVE_TLMM
};

static struct qcom_icc_node pcnoc_s_5 = {
	.name = "pcnoc_s_5",
	.id = QNOC_PNOC_SLV_5,
	.buswidth = 4,
	.mas_rpm_id = 129,
	.slv_rpm_id = 189,
	.num_links = ARRAY_SIZE(pcnoc_s_5_links),
	.links = pcnoc_s_5_links,
};

static struct qcom_icc_node slv_ebi = {
	.name = "slv_ebi",
	.id = QNOC_SLAVE_EBI_CH0,
	.buswidth = 8,
	.mas_rpm_id = -1,
	.slv_rpm_id = 0,
};

static const u16 slv_bimc_pcnoc_links[] = {
	QNOC_MASTER_BIMC_PCNOC
};

static struct qcom_icc_node slv_bimc_pcnoc = {
	.name = "slv_bimc_pcnoc",
	.id = QNOC_SLAVE_BIMC_PCNOC,
	.buswidth = 8,
	.mas_rpm_id = -1,
	.slv_rpm_id = 202,
	.num_links = ARRAY_SIZE(slv_bimc_pcnoc_links),
	.links = slv_bimc_pcnoc_links,
};

static const u16 slv_pcnoc_bimc_1_links[] = {
	QNOC_MASTER_PCNOC_BIMC_1
};

static struct qcom_icc_node slv_pcnoc_bimc_1 = {
	.name = "slv_pcnoc_bimc_1",
	.id = QNOC_SLAVE_PCNOC_BIMC_1,
	.buswidth = 8,
	.mas_rpm_id = -1,
	.slv_rpm_id = 203,
	.num_links = ARRAY_SIZE(slv_pcnoc_bimc_1_links),
	.links = slv_pcnoc_bimc_1_links,
};

static struct qcom_icc_node slv_qdss_stm = {
	.name = "slv_qdss_stm",
	.id = QNOC_SLAVE_QDSS_STM,
	.buswidth = 4,
	.mas_rpm_id = -1,
	.slv_rpm_id = 30,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
};

static struct qcom_icc_node slv_cats_0 = {
	.name = "slv_cats_0",
	.id = QNOC_SLAVE_CATS_128,
	.buswidth = 8,
	.mas_rpm_id = -1,
	.slv_rpm_id = 106,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
};

static struct qcom_icc_node slv_imem = {
	.name = "slv_imem",
	.id = QNOC_SLAVE_SYSTEM_IMEM,
	.buswidth = 8,
	.mas_rpm_id = -1,
	.slv_rpm_id = 26,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
};

static struct qcom_icc_node slv_tcsr = {
	.name = "slv_tcsr",
	.id = QNOC_SLAVE_TCSR,
	.buswidth = 4,
	.mas_rpm_id = -1,
	.slv_rpm_id = 50,
};

static struct qcom_icc_node slv_sdcc_1 = {
	.name = "slv_sdcc_1",
	.id = QNOC_SLAVE_SDCC_1,
	.buswidth = 4,
	.mas_rpm_id = -1,
	.slv_rpm_id = 31,
};

static struct qcom_icc_node slv_blsp_1 = {
	.name = "slv_blsp_1",
	.id = QNOC_SLAVE_BLSP_1,
	.buswidth = 4,
	.mas_rpm_id = -1,
	.slv_rpm_id = 39,
};

static struct qcom_icc_node slv_sgmii = {
	.name = "slv_sgmii",
	.id = QNOC_SLAVE_SGMII,
	.buswidth = 4,
	.mas_rpm_id = -1,
	.slv_rpm_id = 200,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
};

static struct qcom_icc_node slv_crypto_0_cfg = {
	.name = "slv_crypto_0_cfg",
	.id = QNOC_SLAVE_CRYPTO_0_CFG,
	.buswidth = 4,
	.mas_rpm_id = -1,
	.slv_rpm_id = 52,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
};

static struct qcom_icc_node slv_message_ram = {
	.name = "slv_message_ram",
	.id = QNOC_SLAVE_MESSAGE_RAM,
	.buswidth = 4,
	.mas_rpm_id = -1,
	.slv_rpm_id = 55,
};

static struct qcom_icc_node slv_pdm = {
	.name = "slv_pdm",
	.id = QNOC_SLAVE_PDM,
	.buswidth = 4,
	.mas_rpm_id = -1,
	.slv_rpm_id = 41,
};

static struct qcom_icc_node slv_prng = {
	.name = "slv_prng",
	.id = QNOC_SLAVE_PRNG,
	.buswidth = 4,
	.mas_rpm_id = -1,
	.slv_rpm_id = 44,
};

static struct qcom_icc_node slv_usb2 = {
	.name = "slv_usb2",
	.id = QNOC_SLAVE_USB_HS,
	.buswidth = 4,
	.mas_rpm_id = -1,
	.slv_rpm_id = 40,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
};

static struct qcom_icc_node slv_sdcc_2 = {
	.name = "slv_sdcc_2",
	.id = QNOC_SLAVE_SDCC_2,
	.buswidth = 4,
	.mas_rpm_id = -1,
	.slv_rpm_id = 33,
};

static struct qcom_icc_node slv_audio = {
	.name = "slv_audio",
	.id = QNOC_SLAVE_AUDIO,
	.buswidth = 4,
	.mas_rpm_id = -1,
	.slv_rpm_id = 105,
};

static struct qcom_icc_node slv_hsic = {
	.name = "slv_hsic",
	.id = QNOC_SLAVE_USB_HSIC,
	.buswidth = 4,
	.mas_rpm_id = -1,
	.slv_rpm_id = 38,
};

static struct qcom_icc_node slv_usb_phy = {
	.name = "slv_usb_phy",
	.id = QNOC_SLAVE_USB_PHYS_CFG,
	.buswidth = 4,
	.mas_rpm_id = -1,
	.slv_rpm_id = 95,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
};

static struct qcom_icc_node slv_tlmm = {
	.name = "slv_tlmm",
	.id = QNOC_SLAVE_TLMM,
	.buswidth = 4,
	.mas_rpm_id = -1,
	.slv_rpm_id = 51,
};

static struct qcom_icc_node slv_imem_cfg = {
	.name = "slv_imem_cfg",
	.id = QNOC_SLAVE_IMEM_CFG,
	.buswidth = 4,
	.mas_rpm_id = -1,
	.slv_rpm_id = 54,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
};

static struct qcom_icc_node slv_pmic_arb = {
	.name = "slv_pmic_arb",
	.id = QNOC_SLAVE_PMIC_ARB,
	.buswidth = 4,
	.mas_rpm_id = -1,
	.slv_rpm_id = 59,
};

static struct qcom_icc_node slv_tcu = {
	.name = "slv_tcu",
	.id = QNOC_SLAVE_TCU,
	.buswidth = 8,
	.mas_rpm_id = -1,
	.slv_rpm_id = 133,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
};

static struct qcom_icc_node slv_qipc = {
	.name = "slv_qipc",
	.id = QNOC_SLAVE_QPIC,
	.buswidth = 4,
	.mas_rpm_id = -1,
	.slv_rpm_id = 80,
};

static struct qcom_icc_node *mdm9607_bimc_nodes[] = {
	[MAS_APPS_PROC] = &mas_apps_proc,
	[MAS_PCNOC_BIMC_1] = &mas_pcnoc_bimc_1,
	[MAS_TCU_0] = &mas_tcu_0,
	[SLV_EBI] = &slv_ebi,
	[SLV_BIMC_PCNOC] = &slv_bimc_pcnoc,
};

static const struct regmap_config mdm9607_bimc_regmap_config = {
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_register = 0x58000,
	.fast_io = true,
};

static const struct qcom_icc_desc mdm9607_bimc = {
	.type = QCOM_ICC_BIMC,
	.nodes = mdm9607_bimc_nodes,
	.num_nodes = ARRAY_SIZE(mdm9607_bimc_nodes),
	.regmap_cfg = &mdm9607_bimc_regmap_config
};

static struct qcom_icc_node *mdm9607_pcnoc_nodes[] = {
	[MAS_QDSS_BAM] = &mas_qdss_bam,
	[MAS_BIMC_PCNOC] = &mas_bimc_pcnoc,
	[MAS_QDSS_ETR] = &mas_qdss_etr,
	[MAS_AUDIO] = &mas_audio,
	[MAS_QPIC] = &mas_qpic,
	[MAS_HSIC] = &mas_hsic,
	[MAS_BLSP_1] = &mas_blsp_1,
	[MAS_USB_HS1] = &mas_usb_hs1,
	[MAS_CRYPTO] = &mas_crypto,
	[MAS_SDCC_1] = &mas_sdcc_1,
	[MAS_SDCC_2] = &mas_sdcc_2,
	[MAS_XI_USB_HS1] = &mas_xi_usb_hs1,
	[MAS_XI_HSIC] = &mas_xi_hsic,
	[MAS_SGMII] = &mas_sgmii,
	[PCNOC_M_0] = &pcnoc_m_0,
	[PCNOC_M_1] = &pcnoc_m_1,
	[QDSS_INT] = &qdss_int,
	[PCNOC_INT_0] = &pcnoc_int_0,
	[PCNOC_INT_2] = &pcnoc_int_2,
	[PCNOC_INT_3] = &pcnoc_int_3,
	[PCNOC_S_0] = &pcnoc_s_0,
	[PCNOC_S_1] = &pcnoc_s_1,
	[PCNOC_S_2] = &pcnoc_s_2,
	[PCNOC_S_3] = &pcnoc_s_3,
	[PCNOC_S_4] = &pcnoc_s_4,
	[PCNOC_S_5] = &pcnoc_s_5,
	[SLV_PCNOC_BIMC_1] = &slv_pcnoc_bimc_1,
	[SLV_QDSS_STM] = &slv_qdss_stm,
	[SLV_CATS_0] = &slv_cats_0,
	[SLV_IMEM] = &slv_imem,
	[SLV_TCSR] = &slv_tcsr,
	[SLV_SDCC_1] = &slv_sdcc_1,
	[SLV_BLSP_1] = &slv_blsp_1,
	[SLV_SGMII] = &slv_sgmii,
	[SLV_CRYPTO_0_CFG] = &slv_crypto_0_cfg,
	[SLV_MESSAGE_RAM] = &slv_message_ram,
	[SLV_PDM] = &slv_pdm,
	[SLV_PRNG] = &slv_prng,
	[SLV_USB2] = &slv_usb2,
	[SLV_SDCC_2] = &slv_sdcc_2,
	[SLV_AUDIO] = &slv_audio,
	[SLV_HSIC] = &slv_hsic,
	[SLV_USB_PHY] = &slv_usb_phy,
	[SLV_TLMM] = &slv_tlmm,
	[SLV_IMEM_CFG] = &slv_imem_cfg,
	[SLV_PMIC_ARB] = &slv_pmic_arb,
	[SLV_TCU] = &slv_tcu,
	[SLV_QIPC] = &slv_qipc,
};

static const struct regmap_config mdm9607_pcnoc_regmap_config = {
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_register = 0x15080,
	.fast_io = true,
};

static const struct qcom_icc_desc mdm9607_pcnoc = {
	.type = QCOM_ICC_NOC,
	.nodes = mdm9607_pcnoc_nodes,
	.num_nodes = ARRAY_SIZE(mdm9607_pcnoc_nodes),
	.qos_offset = 0x7000,
	.regmap_cfg = &mdm9607_pcnoc_regmap_config,
};

static const struct of_device_id mdm9607_noc_of_match[] = {
	{ .compatible = "qcom,mdm9607-bimc", .data = &mdm9607_bimc },
	{ .compatible = "qcom,mdm9607-pcnoc", .data = &mdm9607_pcnoc },
	{ }
};
MODULE_DEVICE_TABLE(of, mdm9607_noc_of_match);

static struct platform_driver mdm9607_noc_driver = {
	.probe = qnoc_probe,
	.remove = qnoc_remove,
	.driver = {
		.name = "qnoc-mdm9607",
		.of_match_table = mdm9607_noc_of_match,
		.sync_state = icc_sync_state,
	},
};

module_platform_driver(mdm9607_noc_driver);
MODULE_DESCRIPTION("Qualcomm mdm9607 NoC driver");
MODULE_LICENSE("GPL");
