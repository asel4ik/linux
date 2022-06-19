// SPDX-License-Identifier: GPL-2.0
/*
 * Qualcomm SM6115 Network-on-Chip (NoC) QoS driver
 *
 * Copyright (c) 2021, Linaro Ltd.
 *
 */

#include <dt-bindings/interconnect/qcom,sm6115.h>
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

#include "icc-rpm.h"
#include "smd-rpm.h"

enum {
	SM6115_MASTER_APPSS_PROC = 1,
	SM6115_MASTER_SNOC_BIMC_RT,
	SM6115_MASTER_SNOC_BIMC_NRT,
	SM6115_MASTER_SNOC_BIMC,
	SM6115_MASTER_GPU_CDSP_BIMC, //NEW
	SM6115_MASTER_TCU_0,
	SM6115_MASTER_GFX3D,
	SM6115_MASTER_SNOC_CNOC,
	SM6115_MASTER_QDSS_DAP,
	SM6115_MASTER_CRYPTO_CORE0,
	SM6115_MASTER_SNOC_CFG,
	SM6115_MASTER_TIC,
	SM6115_MASTER_ANOC_SNOC,
	SM6115_MASTER_BIMC_SNOC,
	SM6115_MASTER_PIMEM,
	SM6115_MASTER_QDSS_BAM,
	SM6115_MASTER_QUP_0,
	SM6115_MASTER_IPA,
	SM6115_MASTER_QDSS_ETR,
	SM6115_MASTER_SDCC_1,
	SM6115_MASTER_SDCC_2,
	SM6115_MASTER_XM_UFS_MEM,
	//SM6115_MASTER_QPIC,
	SM6115_MASTER_USB3_0,
	SM6115_MASTER_QNM_GPU_QOS,
	SM6115_MASTER_QUP_CORE_0,
	
	SM6115_MASTER_CAMNOC_SF,
	SM6115_MASTER_VIDEO_P0,
	SM6115_MASTER_VIDEO_PROC,
	SM6115_MASTER_CAMNOC_HF,
	SM6115_MASTER_MDP0,

	SM6115_SLAVE_EBI1,
	SM6115_SLAVE_BIMC_SNOC,
	SM6115_SLAVE_BIMC_CFG,
	SM6115_SLAVE_CAMERA_NRT_THROTTLE_CFG,
	SM6115_SLAVE_CAMERA_RT_THROTTLE_CFG,
	SM6115_SLAVE_CAMERA_CFG,
	SM6115_SLAVE_CLK_CTL,
	SM6115_SLAVE_CRYPTO_0_CFG,
	SM6115_SLAVE_DISPLAY_CFG,
	SM6115_SLAVE_DISPLAY_THROTTLE_CFG,
	SM6115_SLAVE_GPU_CFG,
	SM6115_SLAVE_HWKM,
	SM6115_SLAVE_IMEM_CFG,
	SM6115_SLAVE_IPA_CFG,
	SM6115_SLAVE_LPASS,
	SM6115_SLAVE_MESSAGE_RAM,
	SM6115_SLAVE_PDM,
	SM6115_SLAVE_PIMEM_CFG,
	//SM6115_SLAVE_PKA_WRAPPER,
	SM6115_SLAVE_PMIC_ARB,
	SM6115_SLAVE_PRNG,
	SM6115_SLAVE_QDSS_CFG,
	SM6115_SLAVE_QM_CFG,
	SM6115_SLAVE_QM_MPU_CFG,
	SM6115_SLAVE_QPIC,
	SM6115_SLAVE_QUP_0,
	SM6115_SLAVE_SDCC_1,
	SM6115_SLAVE_SDCC_2,
	SM6115_SLAVE_SNOC_CFG,
	SM6115_SLAVE_TCSR,
	SM6115_SLAVE_USB3,
	SM6115_SLAVE_VENUS_CFG,
	SM6115_SLAVE_VENUS_THROTTLE_CFG,
	SM6115_SLAVE_VSENSE_CTRL_CFG,
	SM6115_SLAVE_SERVICE_CNOC,
	SM6115_SLAVE_APPSS,
	SM6115_SLAVE_SNOC_CNOC,
	SM6115_SLAVE_IMEM,
	SM6115_SLAVE_PIMEM,
	SM6115_SLAVE_SNOC_BIMC,
	SM6115_SLAVE_SERVICE_SNOC,
	SM6115_SLAVE_QDSS_STM,
	SM6115_SLAVE_TCU,
	SM6115_SLAVE_ANOC_SNOC,
	SM6115_SLAVE_QUP_CORE_0,
	SM6115_SLAVE_SNOC_BIMC_NRT,
	SM6115_SLAVE_SNOC_BIMC_RT,
};

/* Master nodes */
static const u16 mas_appss_proc_links[] = {
	SM6115_SLAVE_EBI1,
	SM6115_SLAVE_BIMC_SNOC,
};

static struct qcom_icc_node mas_appss_proc = {
	.id = SM6115_MASTER_APPSS_PROC,
	.name = "mas_apps_proc",
	.buswidth = 16,
	.qos.ap_owned = true,
	.qos.qos_port = 0,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.prio_level = 0,
	.qos.areq_prio = 0,
	.mas_rpm_id = 0,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_appss_proc_links),
	.links = mas_appss_proc_links,
};

static const u16 mas_snoc_bimc_rt_links[] = {
	SM6115_SLAVE_EBI1,
};

static struct qcom_icc_node mas_snoc_bimc_rt = {
	.id = SM6115_MASTER_SNOC_BIMC_RT,
	.name = "mas_snoc_bimc_rt",
	.buswidth = 16,
	.qos.ap_owned = true,
	.qos.qos_port = 2,
	.qos.qos_mode = NOC_QOS_MODE_BYPASS,
	.mas_rpm_id = 163,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_snoc_bimc_rt_links),
	.links = mas_snoc_bimc_rt_links,
};

static const u16 mas_snoc_bimc_nrt_links[] = {
	SM6115_SLAVE_EBI1,
};

static struct qcom_icc_node mas_snoc_bimc_nrt = {
	.id = SM6115_MASTER_SNOC_BIMC_NRT,
	.name = "mas_snoc_bimc_nrt",
	.buswidth = 16,
	.qos.ap_owned = true,
	.qos.qos_port = 2,
	.qos.qos_mode = NOC_QOS_MODE_BYPASS,
	.mas_rpm_id = 163,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_snoc_bimc_nrt_links),
	.links = mas_snoc_bimc_nrt_links,
};

static const u16 mas_snoc_bimc_links[] = {
	SM6115_SLAVE_EBI1,
};

static struct qcom_icc_node mas_snoc_bimc = {
	.id = SM6115_MASTER_SNOC_BIMC,
	.name = "mas_snoc_bimc",
	.buswidth = 16,
	.qos.ap_owned = true,
	.qos.qos_port = 2,
	.qos.qos_mode = NOC_QOS_MODE_BYPASS,
	.mas_rpm_id = 164,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_snoc_bimc_links),
	.links = mas_snoc_bimc_links,
};

//New

static const u16 mas_gpu_cdsp_bimc_links[] = {
	SM6115_SLAVE_EBI1,
	SM6115_SLAVE_BIMC_SNOC,
};

static struct qcom_icc_node mas-gpu-cdsp-bimc = {
	.id = SM6115_MASTER_GPU_CDSP_BIMC,
	.name = "mas_snoc_bimc",
	.buswidth = 32,
	.qos.ap_owned = true,
	.qos.qos_port = 1,
	.qos.qos_mode = NOC_QOS_MODE_BYPASS,
	.mas_rpm_id = 165,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_gpu_cdsp_bimc_links),
	.links = mas_gpu_cdsp_bimc_links,
};

static const u16 mas_tcu_0_links[] = {
	SM6115_SLAVE_EBI1,
	SM6115_SLAVE_BIMC_SNOC,
};

static struct qcom_icc_node mas_tcu_0 = {
	.id = SM6115_MASTER_TCU_0,
	.name = "mas_tcu_0",
	.buswidth = 8,
	.qos.ap_owned = true,
	.qos.qos_port = 4,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.prio_level = 6,
	.qos.areq_prio = 6,
	.mas_rpm_id = 102,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_tcu_0_links),
	.links = mas_tcu_0_links,
};

static const u16 mas_snoc_cnoc_links[] = {
	SM6115_SLAVE_CAMERA_RT_THROTTLE_CFG,
	SM6115_SLAVE_SDCC_2,
	SM6115_SLAVE_SDCC_1,
	SM6115_SLAVE_QM_CFG,
	SM6115_SLAVE_BIMC_CFG,
	SM6115_SLAVE_USB3,
	SM6115_SLAVE_QM_MPU_CFG,
	SM6115_SLAVE_CAMERA_NRT_THROTTLE_CFG,
	SM6115_SLAVE_QDSS_CFG,
	SM6115_SLAVE_PDM,
	SM6115_SLAVE_IPA_CFG,
	SM6115_SLAVE_DISPLAY_THROTTLE_CFG,
	SM6115_SLAVE_TCSR,
	SM6115_SLAVE_MESSAGE_RAM,
	SM6115_SLAVE_PMIC_ARB,
	SM6115_SLAVE_LPASS,
	SM6115_SLAVE_DISPLAY_CFG,
	SM6115_SLAVE_VENUS_CFG,
	SM6115_SLAVE_GPU_CFG,
	SM6115_SLAVE_IMEM_CFG,
	SM6115_SLAVE_SNOC_CFG,
	SM6115_SLAVE_SERVICE_CNOC,
	SM6115_SLAVE_VENUS_THROTTLE_CFG,
	//SM6115_SLAVE_PKA_WRAPPER,
	//SM6115_SLAVE_HWKM,
	SM6115_SLAVE_PRNG,
	SM6115_SLAVE_VSENSE_CTRL_CFG,
	SM6115_SLAVE_CRYPTO_0_CFG,
	SM6115_SLAVE_PIMEM_CFG,
	SM6115_SLAVE_QUP_0,
	SM6115_SLAVE_CAMERA_CFG,
	SM6115_SLAVE_CLK_CTL,
	SM6115_SLAVE_QPIC,
};

static struct qcom_icc_node mas_snoc_cnoc = {
	.id = SM6115_MASTER_SNOC_CNOC,
	.name = "mas_snoc_cnoc",
	.buswidth = 8,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = 52,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_snoc_cnoc_links),
	.links = mas_snoc_cnoc_links,
};

static const u16 mas_qdss_dap_links[] = {
	SM6115_SLAVE_CAMERA_RT_THROTTLE_CFG,
	SM6115_SLAVE_SDCC_2,
	SM6115_SLAVE_SDCC_1,
	SM6115_SLAVE_QM_CFG,
	SM6115_SLAVE_BIMC_CFG,
	SM6115_SLAVE_USB3,
	SM6115_SLAVE_QM_MPU_CFG,
	SM6115_SLAVE_CAMERA_NRT_THROTTLE_CFG,
	SM6115_SLAVE_QDSS_CFG,
	SM6115_SLAVE_PDM,
	SM6115_SLAVE_IPA_CFG,
	SM6115_SLAVE_DISPLAY_THROTTLE_CFG,
	SM6115_SLAVE_TCSR,
	SM6115_SLAVE_MESSAGE_RAM,
	SM6115_SLAVE_PMIC_ARB,
	SM6115_SLAVE_LPASS,
	SM6115_SLAVE_DISPLAY_CFG,
	SM6115_SLAVE_VENUS_CFG,
	SM6115_SLAVE_GPU_CFG,
	SM6115_SLAVE_IMEM_CFG,
	SM6115_SLAVE_SNOC_CFG,
	SM6115_SLAVE_SERVICE_CNOC,
	SM6115_SLAVE_VENUS_THROTTLE_CFG,
	//SM6115_SLAVE_PKA_WRAPPER,
	//SM6115_SLAVE_HWKM,
	SM6115_SLAVE_PRNG,
	SM6115_SLAVE_VSENSE_CTRL_CFG,
	SM6115_SLAVE_CRYPTO_0_CFG,
	SM6115_SLAVE_PIMEM_CFG,
	SM6115_SLAVE_QUP_0,
	SM6115_SLAVE_CAMERA_CFG,
	SM6115_SLAVE_CLK_CTL,
//	SM6115_SLAVE_QPIC,
};

static struct qcom_icc_node mas_qdss_dap = {
	.id = SM6115_MASTER_QDSS_DAP,
	.name = "mas_qdss_dap",
	.buswidth = 8,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = 49,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_qdss_dap_links),
	.links = mas_qdss_dap_links,
};

static const u16 mas_crypto_core0_links[] = {
	SM6115_SLAVE_ANOC_SNOC
};

static struct qcom_icc_node mas_crypto_core0 = {
	.id = SM6115_MASTER_CRYPTO_CORE0,
	.name = "mas_crypto_core0",
	.buswidth = 8,
	.qos.ap_owned = true,
	.qos.qos_port = 22,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.areq_prio = 2,
	.mas_rpm_id = 23,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_crypto_core0_links),
	.links = mas_crypto_core0_links,
};

static const u16 mas_qup_core_0_links[] = {
	SM6115_SLAVE_QUP_CORE_0,
};

static struct qcom_icc_node mas_qup_core_0 = {
	.id = SM6115_MASTER_QUP_CORE_0,
	.name = "mas_qup_core_0",
	.buswidth = 4,
	.mas_rpm_id = 170,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_qup_core_0_links),
	.links = mas_qup_core_0_links,
};

static const u16 mas_camnoc_sf_links[] = {
	SM6115_SLAVE_SNOC_BIMC_NRT,
};

static struct qcom_icc_node mas_camnoc_sf = {
	.id = SM6115_MASTER_CAMNOC_SF,
	.name = "mas_camnoc_sf",
	.buswidth = 32,
	.qos.ap_owned = true,
	.qos.qos_port = 4,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.areq_prio = 3,
	.mas_rpm_id = 172,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_camnoc_sf_links),
	.links = mas_camnoc_sf_links,
};

static const u16 mas_camnoc_hf_links[] = {
	SM6115_SLAVE_SNOC_BIMC_RT,
};

static struct qcom_icc_node mas_camnoc_hf = {
	.id = SM6115_MASTER_CAMNOC_HF,
	.name = "mas_camnoc_hf",
	.buswidth = 32,
	.qos.ap_owned = true,
	.qos.qos_port = 10,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.areq_prio = 3,
	.qos.urg_fwd_en = true,
	.mas_rpm_id = 173,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_camnoc_hf_links),
	.links = mas_camnoc_hf_links,
};

static const u16 mas_mdp0_links[] = {
	SM6115_SLAVE_SNOC_BIMC_RT,
};

static struct qcom_icc_node mas_mdp0 = {
	.id = SM6115_MASTER_MDP0,
	.name = "mas_mdp0",
	.buswidth = 16,
	.qos.ap_owned = true,
	.qos.qos_port = 5,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.areq_prio = 3,
	.qos.urg_fwd_en = true,
	.mas_rpm_id = 8,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_mdp0_links),
	.links = mas_mdp0_links,
};

static const u16 mas_video_p0_links[] = {
	SM6115_SLAVE_SNOC_BIMC_NRT,
};

static struct qcom_icc_node mas_video_p0 = {
	.id = SM6115_MASTER_VIDEO_P0,
	.name = "mas_video_p0",
	.buswidth = 16,
	.qos.ap_owned = true,
	.qos.qos_port = 9,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.areq_prio = 3,
	.qos.urg_fwd_en = true,
	.mas_rpm_id = 9,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_video_p0_links),
	.links = mas_video_p0_links,
};

static const u16 mas_video_proc_links[] = {
	SM6115_SLAVE_SNOC_BIMC_NRT,
};

static struct qcom_icc_node mas_video_proc = {
	.id = SM6115_MASTER_VIDEO_PROC,
	.name = "mas_video_proc",
	.buswidth = 8,
	.qos.ap_owned = true,
	.qos.qos_port = 13,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.areq_prio = 4,
	.mas_rpm_id = 168,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_video_proc_links),
	.links = mas_video_proc_links,
};

static const u16 mas_snoc_cfg_links[] = {
	SM6115_SLAVE_SERVICE_SNOC,
};

static struct qcom_icc_node mas_snoc_cfg = {
	.id = SM6115_MASTER_SNOC_CFG,
	.name = "mas_snoc_cfg",
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = 20,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_snoc_cfg_links),
	.links = mas_snoc_cfg_links,
};

static const u16 mas_tic_links[] = {
	SM6115_SLAVE_PIMEM,
	SM6115_SLAVE_IMEM,
	SM6115_SLAVE_APPSS,
	SM6115_SLAVE_SNOC_BIMC,
	SM6115_SLAVE_SNOC_CNOC,
	SM6115_SLAVE_TCU,
	SM6115_SLAVE_QDSS_STM,
};

static struct qcom_icc_node mas_tic = {
	.id = SM6115_MASTER_TIC,
	.name = "mas_tic",
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_port = 8,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.areq_prio = 2,
	.mas_rpm_id = 51,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_tic_links),
	.links = mas_tic_links,
};

static const u16 mas_anoc_snoc_links[] = {
	SM6115_SLAVE_PIMEM,
	SM6115_SLAVE_IMEM,
	SM6115_SLAVE_APPSS,
	SM6115_SLAVE_SNOC_BIMC,
	SM6115_SLAVE_SNOC_CNOC,
	SM6115_SLAVE_TCU,
	SM6115_SLAVE_QDSS_STM,
};

static struct qcom_icc_node mas_anoc_snoc = {
	.id = SM6115_MASTER_ANOC_SNOC,
	.name = "mas_anoc_snoc",
	.buswidth = 16,
	.mas_rpm_id = 110,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_anoc_snoc_links),
	.links = mas_anoc_snoc_links,
};

static const u16 mas_bimc_snoc_links[] = {
	SM6115_SLAVE_PIMEM,
	SM6115_SLAVE_IMEM,
	SM6115_SLAVE_APPSS,
	SM6115_SLAVE_SNOC_CNOC,
	SM6115_SLAVE_TCU,
	SM6115_SLAVE_QDSS_STM,
};

static struct qcom_icc_node mas_bimc_snoc = {
	.id = SM6115_MASTER_BIMC_SNOC,
	.name = "mas_bimc_snoc",
	.buswidth = 8,
	.mas_rpm_id = 21,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_bimc_snoc_links),
	.links = mas_bimc_snoc_links,
};

static const u16 mas_pimem_links[] = {
	SM6115_SLAVE_IMEM,
	SM6115_SLAVE_SNOC_BIMC,
};

static struct qcom_icc_node mas_pimem = {
	.id = SM6115_MASTER_PIMEM,
	.name = "mas_pimem",
	.buswidth = 8,
	.qos.ap_owned = true,
	.qos.qos_port = 20,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.areq_prio = 2,
	.mas_rpm_id = 113,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_pimem_links),
	.links = mas_pimem_links,
};

static const u16 mas_qdss_bam_links[] = {
	SM6115_SLAVE_ANOC_SNOC,
};

static struct qcom_icc_node mas_qdss_bam = {
	.id = SM6115_MASTER_QDSS_BAM,
	.name = "mas_qdss_bam",
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_port = 2,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.areq_prio = 2,
	.mas_rpm_id = 19,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_qdss_bam_links),
	.links = mas_qdss_bam_links,
};

static const u16 mas_qup_0_links[] = {
	SM6115_SLAVE_ANOC_SNOC,
};

static struct qcom_icc_node mas_qup_0 = {
	.id = SM6115_MASTER_QUP_0,
	.name = "mas_qup_0",
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_port = 0,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.areq_prio = 2,
	.mas_rpm_id = 166,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_qup_0_links),
	.links = mas_qup_0_links,
};

static const u16 mas_ipa_links[] = {
	SM6115_SLAVE_ANOC_SNOC,
};

static struct qcom_icc_node mas_ipa = {
	.id = SM6115_MASTER_IPA,
	.name = "mas_ipa",
	.buswidth = 8,
	.qos.ap_owned = true,
	.qos.qos_port = 3,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.areq_prio = 2,
	.mas_rpm_id = 59,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_ipa_links),
	.links = mas_ipa_links,
};

static const u16 mas_qdss_etr_links[] = {
	SM6115_SLAVE_ANOC_SNOC,
};

static struct qcom_icc_node mas_qdss_etr = {
	.id = SM6115_MASTER_QDSS_ETR,
	.name = "mas_qdss_etr",
	.buswidth = 8,
	.qos.ap_owned = true,
	.qos.qos_port = 12,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.areq_prio = 2,
	.mas_rpm_id = 31,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_qdss_etr_links),
	.links = mas_qdss_etr_links,
};

static const u16 mas_sdcc_1_links[] = {
	SM6115_SLAVE_ANOC_SNOC,
};

static struct qcom_icc_node mas_sdcc_1 = {
	.id = SM6115_MASTER_SDCC_1,
	.name = "mas_sdcc_1",
	.buswidth = 8,
	.qos.ap_owned = true,
	.qos.qos_port = 17,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.areq_prio = 2,
	.mas_rpm_id = 33,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_sdcc_1_links),
	.links = mas_sdcc_1_links,
};

static const u16 mas_sdcc_2_links[] = {
	SM6115_SLAVE_ANOC_SNOC,
};

static struct qcom_icc_node mas_sdcc_2 = {
	.id = SM6115_MASTER_SDCC_2,
	.name = "mas_sdcc_2",
	.buswidth = 8,
	.qos.ap_owned = true,
	.qos.qos_port = 23,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.areq_prio = 2,
	.mas_rpm_id = 35,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_sdcc_2_links),
	.links = mas_sdcc_2_links,
};

static const u16 mas_xm_ufs_mem_links[] = {
	SM6115_SLAVE_ANOC_SNOC,
};

static struct qcom_icc_node mas_xm_ufs_mem = {
	.id = SM6115_MASTER_XM_UFS_MEM,
	.name = "mas_xm_ufs_mem",
	.buswidth = 8,
	.qos.ap_owned = true,
	.qos.qos_port = 25,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.areq_prio = 2,
	.mas_rpm_id = 167,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_xm_ufs_mem_links),
	.links = mas_xm_ufs_mem_links,
};

/*
static const u16 mas_qpic_links[] = {
	SM6115_SLAVE_ANOC_SNOC,
};

static struct qcom_icc_node mas_qpic = { //TO_REMOVE_GPU_CDSP_BIMC
	.id = SM6115_MASTER_QPIC,
	.name = "mas_qpic",
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_port = 1,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.areq_prio = 2,
	.mas_rpm_id = 58,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_qpic_links),
	.links = mas_qpic_links,
};
*/
static const u16 mas_usb3_0_links[] = {
	SM6115_SLAVE_ANOC_SNOC,
};

static struct qcom_icc_node mas_usb3_0 = {
	.id = SM6115_MASTER_USB3_0,
	.name = "mas_usb3_0",
	.buswidth = 8,
	.qos.ap_owned = true,
	.qos.qos_port = 24,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.areq_prio = 2,
	.mas_rpm_id = 32,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_usb3_0_links),
	.links = mas_usb3_0_links,
};
//NEW
static const u16 mas_qnm_gpu_qos_links[] = {
	 SM6115_SLAVE_ANOC_SNOC,
};

//FIX ONCE SLAVE IS READY GPU
static struct qcom_icc_node mas_qnm_gpu_qos = {
	.id = SM6115_MASTER_QNM_GPU_QOS,
	.name = "mas_qnm_gpu_qos",
	.buswidth = 32,
	.qos.ap_owned = true,
	.qos.qos_port = 16,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.areq_prio = 0,
	.mas_rpm_id = 6,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_qnm_gpu_qos_links),
	.links = mas_qnm_gpu_qos_links,
};

static const u16 mas_gfx3d_links[] = {
	SM6115_SLAVE_EBI1,
	slv_gpu_cdsp_bimc
};

static struct qcom_icc_node mas_gfx3d = {
	.id = SM6115_MASTER_GFX3D,
	.name = "mas_gfx3d",
	.buswidth = 32,
	.qos.ap_owned = true,

	.mas_rpm_id = 6,
	.slv_rpm_id = -1,
	.num_links = ARRAY_SIZE(mas_gfx3d_links),
	.links = mas_gfx3d_links,
};

/* Slave nodes */
static struct qcom_icc_node slv_ebi1 = {
	.name = "slv_ebi1",
	.id = SM6115_SLAVE_EBI1,
	.buswidth = 8,
	.mas_rpm_id = -1,
	.slv_rpm_id = 0,
};

static const u16 slv_bimc_snoc_links[] = {
	SM6115_MASTER_BIMC_SNOC,
};

static struct qcom_icc_node slv_bimc_snoc = {
	.name = "slv_bimc_snoc",
	.id = SM6115_SLAVE_BIMC_SNOC,
	.buswidth = 8,
	.mas_rpm_id = -1,
	.slv_rpm_id = 2,
	.num_links = ARRAY_SIZE(slv_bimc_snoc_links),
	.links = slv_bimc_snoc_links,
};

static struct qcom_icc_node slv_bimc_cfg = {
	.name = "slv_bimc_cfg",
	.id = SM6115_SLAVE_BIMC_CFG,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 56,
};

static struct qcom_icc_node slv_camera_nrt_throttle_cfg = {
	.name = "slv_camera_nrt_throttle_cfg",
	.id = SM6115_SLAVE_CAMERA_NRT_THROTTLE_CFG,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 271,
};

static struct qcom_icc_node slv_camera_rt_throttle_cfg = {
	.name = "slv_camera_rt_throttle_cfg",
	.id = SM6115_SLAVE_CAMERA_RT_THROTTLE_CFG,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 279,
};

static struct qcom_icc_node slv_camera_cfg = {
	.name = "slv_camera_cfg",
	.id = SM6115_SLAVE_CAMERA_CFG,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 3,
};

static struct qcom_icc_node slv_cdsp_throttle_cfg = {
	.name = "slv_cdsp_throttle_cfg",
	.id = SM6115_SLAVE_CDSP_THROTTLE_CFG,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 272,
};

272
static struct qcom_icc_node slv_clk_ctl = {
	.name = "slv_clk_ctl",
	.id = SM6115_SLAVE_CLK_CTL,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 47,
};

static struct qcom_icc_node slv_crypto_0_cfg = {
	.name = "slv_crypto_0_cfg",
	.id = SM6115_SLAVE_CRYPTO_0_CFG,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 52,
};

static struct qcom_icc_node slv_display_cfg = {
	.name = "slv_display_cfg",
	.id = SM6115_SLAVE_DISPLAY_CFG,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 4,
};

static struct qcom_icc_node slv_display_throttle_cfg = {
	.name = "slv_display_throttle_cfg",
	.id = SM6115_SLAVE_DISPLAY_THROTTLE_CFG,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 156,
};

static struct qcom_icc_node slv_gpu_cfg = {
	.name = "slv_gpu_cfg",
	.id = SM6115_SLAVE_GPU_CFG,
	.buswidth = 8,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 275,
};
/*
static struct qcom_icc_node slv_hwkm = {
	.name = "slv_hwkm",
	.id = SM6115_SLAVE_HWKM,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 280,
};
*/
static struct qcom_icc_node slv_imem_cfg = {
	.name = "slv_imem_cfg",
	.id = SM6115_SLAVE_IMEM_CFG,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 54,
};

static struct qcom_icc_node slv_ipa_cfg = {
	.name = "slv_ipa_cfg",
	.id = SM6115_SLAVE_IPA_CFG,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 183,
};

static struct qcom_icc_node slv_lpass = {
	.name = "slv_lpass",
	.id = SM6115_SLAVE_LPASS,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 21,
};

static struct qcom_icc_node slv_message_ram = {
	.name = "slv_message_ram",
	.id = SM6115_SLAVE_MESSAGE_RAM,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 55,
};

static struct qcom_icc_node slv_pdm = {
	.name = "slv_pdm",
	.id = SM6115_SLAVE_PDM,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 41,
};

static struct qcom_icc_node slv_pimem_cfg = {
	.name = "slv_pimem_cfg",
	.id = SM6115_SLAVE_PIMEM_CFG,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 167,
};
/*
static struct qcom_icc_node slv_pka_wrapper = {
	.name = "slv_pka_wrapper",
	.id = SM6115_SLAVE_PKA_WRAPPER,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 281,
};
*/
static struct qcom_icc_node slv_pmic_arb = {
	.name = "slv_pmic_arb",
	.id = SM6115_SLAVE_PMIC_ARB,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 59,
};

static struct qcom_icc_node slv_prng = {
	.name = "slv_prng",
	.id = SM6115_SLAVE_PRNG,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 44,
};

static struct qcom_icc_node slv_qdss_cfg = {
	.name = "slv_qdss_cfg",
	.id = SM6115_SLAVE_QDSS_CFG,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 63,
};

static struct qcom_icc_node slv_qm_cfg = {
	.name = "slv_qm_cfg",
	.id = SM6115_SLAVE_QM_CFG,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 212,
};

static struct qcom_icc_node slv_qm_mpu_cfg = {
	.name = "slv_qm_mpu_cfg",
	.id = SM6115_SLAVE_QM_MPU_CFG,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 231,
};

static struct qcom_icc_node slv_qpic = {
	.name = "slv_qpic",
	.id = SM6115_SLAVE_QPIC,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 80,
};

static struct qcom_icc_node slv_qup_0 = {
	.name = "slv_qup_0",
	.id = SM6115_SLAVE_QUP_0,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 261,
};

static struct qcom_icc_node slv_sdcc_1 = {
	.name = "slv_sdcc_1",
	.id = SM6115_SLAVE_SDCC_1,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 31,
};

static struct qcom_icc_node slv_sdcc_2 = {
	.name = "slv_sdcc_2",
	.id = SM6115_SLAVE_SDCC_2,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 33,
};

static const u16 slv_snoc_cfg_links[] = {
	SM6115_MASTER_SNOC_CFG,
};

static struct qcom_icc_node slv_snoc_cfg = {
	.name = "slv_snoc_cfg",
	.id = SM6115_SLAVE_SNOC_CFG,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 70,
	.num_links = ARRAY_SIZE(slv_snoc_cfg_links),
	.links = slv_snoc_cfg_links,
};

static struct qcom_icc_node slv_tcsr = {
	.name = "slv_tcsr",
	.id = SM6115_SLAVE_TCSR,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 50,
};

static struct qcom_icc_node slv_tlmm_east = {
	.name = "slv_tlmm_east",
	.id = SM6115_SLAVE_TLMM_EAST,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 213,
};

static struct qcom_icc_node slv_tlmm_south = {
	.name = "slv_tlmm_south",
	.id = SM6115_SLAVE_TLMM_SOUTH	,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 217,
};

static struct qcom_icc_node slv_tlmm_west = {
	.name = "slv_tlmm_west",
	.id = SM6115_SLAVE_TLMM_WEST,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 215,
};

static struct qcom_icc_node slv_ufs_mem_cfg = {
	.name = "slv_ufs_mem_cfg",
	.id = SM6115_SLAVE_UFS_MEM_CFG,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 262,
};

static struct qcom_icc_node slv_tlmm_east = {
	.name = "slv_tlmm_east",
	.id = SM6115_SLAVE_TLMM_EAST,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 213,
};

static struct qcom_icc_node slv_usb3 = {
	.name = "slv_usb3",
	.id = SM6115_SLAVE_USB3,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 22,
};

static struct qcom_icc_node slv_venus_cfg = {
	.name = "slv_venus_cfg",
	.id = SM6115_SLAVE_VENUS_CFG,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 10,
};

static struct qcom_icc_node slv_venus_throttle_cfg = {
	.name = "slv_venus_throttle_cfg",
	.id = SM6115_SLAVE_VENUS_THROTTLE_CFG,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 178,
};

static struct qcom_icc_node slv_vsense_ctrl_cfg = {
	.name = "slv_vsense_ctrl_cfg",
	.id = SM6115_SLAVE_VSENSE_CTRL_CFG,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 263,
};

static struct qcom_icc_node slv_service_cnoc = {
	.name = "slv_service_cnoc",
	.id = SM6115_SLAVE_SERVICE_CNOC,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 76,
};

static struct qcom_icc_node slv_qup_core_0 = {
	.name = "slv_qup_core_0",
	.id = SM6115_SLAVE_QUP_CORE_0,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 264,
};

static const u16 slv_snoc_bimc_nrt_links[] = {
	SM6115_MASTER_SNOC_BIMC_NRT,
};

static struct qcom_icc_node slv_snoc_bimc_nrt = {
	.name = "slv_snoc_bimc_nrt",
	.id = SM6115_SLAVE_SNOC_BIMC_NRT,
	.buswidth = 16,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 259,
	.num_links = ARRAY_SIZE(slv_snoc_bimc_nrt_links),
	.links = slv_snoc_bimc_nrt_links,
};

static const u16 slv_snoc_bimc_rt_links[] = {
	SM6115_MASTER_SNOC_BIMC_RT,
};

static struct qcom_icc_node slv_snoc_bimc_rt = {
	.name = "slv_snoc_bimc_rt",
	.id = SM6115_SLAVE_SNOC_BIMC_RT,
	.buswidth = 16,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 260,
	.num_links = ARRAY_SIZE(slv_snoc_bimc_rt_links),
	.links = slv_snoc_bimc_rt_links,
};

static struct qcom_icc_node slv_appss = {
	.name = "slv_appss",
	.id = SM6115_SLAVE_APPSS,
	.buswidth = 8,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 20,
};

static const u16 slv_snoc_cnoc_links[] = {
	SM6115_MASTER_SNOC_CNOC,
};

static struct qcom_icc_node slv_snoc_cnoc = {
	.name = "slv_snoc_cnoc",
	.id = SM6115_SLAVE_SNOC_CNOC,
	.buswidth = 8,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.mas_rpm_id = -1,
	.slv_rpm_id = 25,
	.num_links = ARRAY_SIZE(slv_snoc_cnoc_links),
	.links = slv_snoc_cnoc_links,
};

static struct qcom_icc_node slv_imem = {
	.name = "slv_imem",
	.id = SM6115_SLAVE_IMEM,
	.buswidth = 8,
	.mas_rpm_id = -1,
	.slv_rpm_id = 26,
};

static struct qcom_icc_node slv_pimem = {
	.name = "slv_pimem",
	.id = SM6115_SLAVE_PIMEM,
	.buswidth = 8,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 166,
};

static const u16 slv_snoc_bimc_links[] = {
	SM6115_MASTER_SNOC_BIMC,
};

static struct qcom_icc_node slv_snoc_bimc = {
	.name = "slv_snoc_bimc",
	.id = SM6115_SLAVE_SNOC_BIMC,
	.buswidth = 16,
	.mas_rpm_id = -1,
	.slv_rpm_id = 24,
	.num_links = ARRAY_SIZE(slv_snoc_bimc_links),
	.links = slv_snoc_bimc_links,
};

static struct qcom_icc_node slv_service_snoc = {
	.name = "slv_service_snoc",
	.id = SM6115_SLAVE_SERVICE_SNOC,
	.buswidth = 4,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 29,
};

static struct qcom_icc_node slv_qdss_stm = {
	.name = "slv_qdss_stm",
	.id = SM6115_SLAVE_QDSS_STM,
	.buswidth = 4,
	.mas_rpm_id = -1,
	.slv_rpm_id = 30,
};

static struct qcom_icc_node slv_tcu = {
	.name = "slv_tcu",
	.id = SM6115_SLAVE_TCU,
	.buswidth = 8,
	.qos.ap_owned = true,
	.qos.qos_mode = NOC_QOS_MODE_INVALID,
	.mas_rpm_id = -1,
	.slv_rpm_id = 133,
};

static const u16 slv_anoc_snoc_links[] = {
	SM6115_MASTER_ANOC_SNOC,
};

static struct qcom_icc_node slv_anoc_snoc = {
	.name = "slv_anoc_snoc",
	.id = SM6115_SLAVE_ANOC_SNOC,
	.buswidth = 16,
	.mas_rpm_id = -1,
	.slv_rpm_id = 141,
	.num_links = ARRAY_SIZE(slv_anoc_snoc_links),
	.links = slv_anoc_snoc_links,
};

/* NoC descriptors */
static struct qcom_icc_node * const sm6115_bimc_nodes[] = {
	[MASTER_APPSS_PROC] = &mas_appss_proc,
	[MASTER_SNOC_BIMC_RT] = &mas_snoc_bimc_rt,
	[MASTER_SNOC_BIMC_NRT] = &mas_snoc_bimc_nrt,
	[MASTER_SNOC_BIMC] = &mas_snoc_bimc,
	[MASTER_TCU_0] = &mas_tcu_0,
	[MASTER_GFX3D] = &mas_gfx3d,
	[SLAVE_EBI1] = &slv_ebi1,
	[SLAVE_BIMC_SNOC] = &slv_bimc_snoc,
};

static const struct regmap_config sm6115_bimc_regmap_config = {
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_register	= 0x80000,
	.fast_io	= true,
};

static const struct qcom_icc_desc sm6115_bimc = {
	.type = QCOM_ICC_BIMC,
	.nodes = sm6115_bimc_nodes,
	.num_nodes = ARRAY_SIZE(sm6115_bimc_nodes),
	.regmap_cfg = &sm6115_bimc_regmap_config,
	/* M_REG_BASE() in vendor msm_bus_bimc_adhoc driver */
	.qos_offset = 0x8000,
};

static struct qcom_icc_node * const sm6115_cnoc_nodes[] = {
	[MASTER_SNOC_CNOC] = &mas_snoc_cnoc,
	[MASTER_QDSS_DAP] = &mas_qdss_dap,
	[SLAVE_BIMC_CFG] = &slv_bimc_cfg,
	[SLAVE_CAMERA_NRT_THROTTLE_CFG] = &slv_camera_nrt_throttle_cfg,
	[SLAVE_CAMERA_RT_THROTTLE_CFG] = &slv_camera_rt_throttle_cfg,
	[SLAVE_CAMERA_CFG] = &slv_camera_cfg,
	[SLAVE_CDSP_THROTTLE_CFG]= &slv_cdsp_throttle_cfg,
	[SLAVE_CLK_CTL] = &slv_clk_ctl,
	[SLAVE_CRYPTO_0_CFG] = &slv_crypto_0_cfg,
	[SLAVE_DISPLAY_CFG] = &slv_display_cfg,
	[SLAVE_DISPLAY_THROTTLE_CFG] = &slv_display_throttle_cfg,
	[SLAVE_GPU_CFG] = &slv_gpu_cfg,
	[SLAVE_HWKM] = &slv_hwkm,
	[SLAVE_IMEM_CFG] = &slv_imem_cfg,
	[SLAVE_IPA_CFG] = &slv_ipa_cfg,
	[SLAVE_LPASS] = &slv_lpass,
	[SLAVE_MESSAGE_RAM] = &slv_message_ram,
	[SLAVE_PDM] = &slv_pdm,
	[SLAVE_PIMEM_CFG] = &slv_pimem_cfg,
	//[SLAVE_PKA_WRAPPER] = &slv_pka_wrapper,
	[SLAVE_PMIC_ARB] = &slv_pmic_arb,
	[SLAVE_PRNG] = &slv_prng,
	[SLAVE_QDSS_CFG] = &slv_qdss_cfg,
	[SLAVE_QM_CFG] = &slv_qm_cfg,
	[SLAVE_QM_MPU_CFG] = &slv_qm_mpu_cfg,
	[SLAVE_QPIC] = &slv_qpic,
	[SLAVE_QUP_0] = &slv_qup_0,
	[SLAVE_SDCC_1] = &slv_sdcc_1,
	[SLAVE_SDCC_2] = &slv_sdcc_2,
	[SLAVE_SNOC_CFG] = &slv_snoc_cfg,
	[SLAVE_TCSR] = &slv_tcsr,
	[SLAVE_TLMM_EAST] = &slv_tlmm_east,
	[SLAVE_TLMM_SOUTH] = &slv_tlmm_south,
	[SLAVE_TLMM_WEST] = &slv_tlmm_west,
	[SLAVE_UFS_MEM_CFG] = &slv_ufs_mem_cfg,
	[SLAVE_USB3] = &slv_usb3,
	[SLAVE_VENUS_CFG] = &slv_venus_cfg,
	[SLAVE_VENUS_THROTTLE_CFG] = &slv_venus_throttle_cfg,
	[SLAVE_VSENSE_CTRL_CFG] = &slv_vsense_ctrl_cfg,
	[SLAVE_SERVICE_CNOC] = &slv_service_cnoc,
};

static const struct regmap_config sm6115_cnoc_regmap_config = {
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_register	= 0x8200,
	.fast_io	= true,
};

static const struct qcom_icc_desc sm6115_cnoc = {
	.type = QCOM_ICC_NOC,
	.nodes = sm6115_cnoc_nodes,
	.num_nodes = ARRAY_SIZE(sm6115_cnoc_nodes),
	.regmap_cfg = &sm6115_cnoc_regmap_config,
};

static struct qcom_icc_node * const sm6115_snoc_nodes[] = {
	[MASTER_CRYPTO_CORE0] = &mas_crypto_core0,
	[MASTER_SNOC_CFG] = &mas_snoc_cfg,
	[MASTER_TIC] = &mas_tic,
	[MASTER_ANOC_SNOC] = &mas_anoc_snoc,
	[MASTER_BIMC_SNOC] = &mas_bimc_snoc,
	[MASTER_PIMEM] = &mas_pimem,
	[MASTER_QDSS_BAM] = &mas_qdss_bam,
	[MASTER_QUP_0] = &mas_qup_0,
	[MASTER_IPA] = &mas_ipa,
	[MASTER_QDSS_ETR] = &mas_qdss_etr,
	[MASTER_SDCC_1] = &mas_sdcc_1,
	[MASTER_SDCC_2] = &mas_sdcc_2,
	//[MASTER_QPIC] = &mas_qpic,
	[MASTER_USB3_0] = &mas_usb3_0,
	[SLAVE_APPSS] = &slv_appss,
	[SLAVE_SNOC_CNOC] = &slv_snoc_cnoc,
	[SLAVE_IMEM] = &slv_imem,
	[SLAVE_PIMEM] = &slv_pimem,
	[SLAVE_SNOC_BIMC] = &slv_snoc_bimc,
	[SLAVE_SERVICE_SNOC] = &slv_service_snoc,
	[SLAVE_QDSS_STM] = &slv_qdss_stm,
	[SLAVE_TCU] = &slv_tcu,
	[SLAVE_ANOC_SNOC] = &slv_anoc_snoc,
};

static const struct regmap_config sm6115_snoc_regmap_config = {
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_register	= 0x60200,
	.fast_io	= true,
};

static const struct qcom_icc_desc sm6115_snoc = {
	.type = QCOM_ICC_QNOC,
	.nodes = sm6115_snoc_nodes,
	.num_nodes = ARRAY_SIZE(sm6115_snoc_nodes),
	.regmap_cfg = &sm6115_snoc_regmap_config,
	/* Vendor DT node fab-sys_noc property 'qcom,base-offset' */
	.qos_offset = 0x15000,
};

static struct qcom_icc_node * const sm6115_qup_virt_nodes[] = {
	[MASTER_QUP_CORE_0] = &mas_qup_core_0,
	[SLAVE_QUP_CORE_0] = &slv_qup_core_0
};

static const struct qcom_icc_desc sm6115_qup_virt = {
	.type = QCOM_ICC_QNOC,
	.nodes = sm6115_qup_virt_nodes,
	.num_nodes = ARRAY_SIZE(sm6115_qup_virt_nodes),
};
//FABV_GPU_VERT_BASE
static struct qcom_icc_node * const sm6115_gpu_vert_nodes[] = {

};

static const struct qcom_icc_desc sm6115_gpu_vert = {
	.type = QCOM_ICC_QNOC,
	.nodes = sm6115_gpu_vert_nodes,
	.num_nodes = ARRAY_SIZE(sm6115_gpu_vert_nodes),
};

static struct qcom_icc_node * const sm6115_mmnrt_virt_nodes[] = {
	[MASTER_CAMNOC_SF] = &mas_camnoc_sf,
	[MASTER_VIDEO_P0] = &mas_video_p0,
	[MASTER_VIDEO_PROC] = &mas_video_proc,
	[SLAVE_SNOC_BIMC_NRT] = &slv_snoc_bimc_nrt,
};

static const struct qcom_icc_desc sm6115_mmnrt_virt = {
	.type = QCOM_ICC_QNOC,
	.nodes = sm6115_mmnrt_virt_nodes,
	.num_nodes = ARRAY_SIZE(sm6115_mmnrt_virt_nodes),
	.regmap_cfg = &sm6115_snoc_regmap_config,
	.qos_offset = 0x15000,
};

static struct qcom_icc_node * const sm6115_mmrt_virt_nodes[] = {
	[MASTER_CAMNOC_HF] = &mas_camnoc_hf,
	[MASTER_MDP0] = &mas_mdp0,
	[SLAVE_SNOC_BIMC_RT] = &slv_snoc_bimc_rt,
};

static const struct qcom_icc_desc sm6115_mmrt_virt = {
	.type = QCOM_ICC_QNOC,
	.nodes = sm6115_mmrt_virt_nodes,
	.num_nodes = ARRAY_SIZE(sm6115_mmrt_virt_nodes),
	.regmap_cfg = &sm6115_snoc_regmap_config,
	.qos_offset = 0x15000,
};

static const struct of_device_id sm6115_noc_of_match[] = {
	{ .compatible = "qcom,sm6115-bimc", .data = &sm6115_bimc },
	{ .compatible = "qcom,sm6115-cnoc", .data = &sm6115_cnoc },
	{ .compatible = "qcom,sm6115-snoc", .data = &sm6115_snoc },
	{ .compatible = "qcom,sm6115-qup-virt", .data = &sm6115_qup_virt },
	{ .compatible = "qcom,sm6115-gpu-vert", .data = &sm6115_gpu_vert },
	{ .compatible = "qcom,sm6115-mmrt-virt", .data = &sm6115_mmrt_virt },
	{ .compatible = "qcom,sm6115-mmnrt-virt", .data = &sm6115_mmnrt_virt },
	{ },
};
MODULE_DEVICE_TABLE(of, sm6115_noc_of_match);

static struct platform_driver sm6115_noc_driver = {
	.probe = qnoc_probe,
	.remove = qnoc_remove,
	.driver = {
		.name = "qnoc-sm6115",
		.of_match_table = sm6115_noc_of_match,
	},
};
module_platform_driver(sm6115_noc_driver);

MODULE_DESCRIPTION("Qualcomm SM6115 NoC driver");
MODULE_LICENSE("GPL v2");
