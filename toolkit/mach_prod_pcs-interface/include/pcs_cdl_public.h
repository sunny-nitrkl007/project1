/*******************************************************************************
***
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%                                                                        %%
*** %%  COPYRIGHT (C) 1997 - 2016 CATERPILLAR INC.   ALL RIGHTS RESERVED.     %%
*** %%      This work contains proprietary information which may              %%
*** %%      constitute a trade secret and/or be confidential.                 %%
*** %%                                                                        %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
***
*** DESCRIPTION :
***    cdl public defines and prototypes
***
*** REQUIRED HEADER :
***
*** LANGUAGE :
***    ANSI C
***
*** COMPILE FLAGS :
***
*** METHOD:
***
*** NOTES:
***
*** GLOBALS USED:
***
***
*** FUNCTIONS:
***
***
*******************************************************************************/

/*******************************************************************************
***
***    Referenced Functions, Data, & Symbols
***    -- #Include's --
***
*******************************************************************************/
#include <cat_std_types.h>
#include <cdl2_proto.h>
#include <com_proto.h>
#include <clock_proto.h>
#include <cdl2_mod_proto.h>
#include <pcs_public.h>

/* ========================================================================== */
/* ===== P R O T O T Y P E S ================================================ */
/* ========================================================================== */


extern Cdl_wr_m_1_pie_t cdl_pcs_features_config_2_wr_pie ;
extern Cdl_wr_m_1_pie_t cdl_pcs_calibration_wt_wr_pie;
extern Cdl_wr_m_1_pie_t cdl_trk_payload_trgt_wt_wr_pie;
extern Cdl_wr_m_1_pie_t cdl_loader_bkt_trgt_wt_wr_pie;
extern Cdl_wr_m_1_pie_t cdl_payload_indicator_config_wr_pie ;
extern Cdl_wr_m_1_pie_t cdl_max_lift_vel_wr_pie;
extern Cdl_wr_m_1_pie_t cdl_oil_temp_comp_wr_pie;
extern Cdl_wr_m_1_pie_t cdl_skew_limit_wr_pie ;
extern Cdl_wr_m_1_pie_t cdl_material_id_wr_pie ;
extern Cdl_wr_m_1_pie_t cdl_truck_payload_id_wr_pie ;
extern Cdl_wr_m_1_pie_t cdl_operator_id_wr_pie;
extern Cdl_wr_m_1_pie_t cdl_loader_machine_id_wr_pie ;
extern Cdl_wr_m_1_pie_t cdl_pcs_password_wr_pie ;
extern Cdl_wr_m_1_pie_t cdl_total_reweigh_rqst_count_wr_pie ;
extern Cdl_wr_m_1_pie_t cdl_pcs_mode_wr_pie ;
extern Cdl_wr_m_1_pie_t cdl_last_store_weight_wr_pie;
extern Cdl_wr_m_1_pie_t cdl_total_payload_wt_wr_pie ;
extern Cdl_wr_m_1_pie_t cdl_total_load_count_wr_pie ;
extern Cdl_wr_m_1_pie_t cdl_resettable_load_count_wr_pie ;
extern Cdl_wr_m_1_pie_t cdl_lifetime_loaded_travel_hours_wr_pie ;
extern Cdl_wr_m_1_pie_t cdl_weigh_range_start_wr_pie ;
extern Cdl_wr_m_1_pie_t cdl_weigh_range_end_wr_pie ;
extern Cdl_wr_m_1_pie_t cdl_printer_setting_wr_pie;
extern Cdl_wr_m_1_pie_t cdl_printer_tot_wr_pie;
extern Cdl_wr_m_1_pie_t cdl_oil_type_wr_pie ;
extern Cdl_wr_m_1_pie_t cdl_material_reset_index_wr_pie ;
extern Cdl_wr_m_1_pie_t cdl_payload_control_system_status_wr_pie;
extern Cdl_wr_m_1_pie_t cdl_blast_number_wr_pie;
extern Cdl_wr_m_1_pie_t cdl_payload_horn_status_wr_pie;
extern Cdl_wr_m_1_pie_t cdl_payload_overload_limit_enable_wr_pie;
extern Cdl_wr_m_1_pie_t cdl_loadsite_id_wr_pie;
extern Cdl_wr_m_1_pie_t cdl_payload_control_statcode_wr_pie; /* Support for delay code*/
extern Cdl_wr_m_1_pie_t cdl_truck_string_wr_pie;
extern Cdl_wr_m_1_pie_t cdl_excess_mat_ready_wr_pie;
extern Cdl_wr_m_1_pie_t cdl_excess_mat_location_wr_pie;
extern Cdl_wr_m_1_pie_t cdl_tip_off_mode_wr_pie;
extern Cdl_wr_m_1_pie_t cdl_tip_off_trigger_wr_pie;
extern Cdl_wr_m_1_pie_t cdl_autoid_list_ack_wr_pie;
extern Cdl_wr_m_1_pie_t cdl_tip_off_trigger_type_wr_pie;
extern Cdl_wr_m_1_pie_t cdl_payload_display_mode_wr_pie;
extern Cdl_wr_m_1_pie_t cdl_history_list_index_wr_pie;
extern Cdl_wr_m_1_pie_t cdl_history_list_weight_wr_pie;
extern Cdl_wr_m_1_pie_t cdl_total_pass_count_wr_pie;


extern Cdl_gen_tx_pie_t cdl_bucket_payload_data_st_tx_pie;
extern Cdl_gen_tx_pie_t cdl_pcs_features_config_2_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_bucket_payload_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_trk_payload_trgt_wt_tx_pie;
extern Cdl_gen_tx_pie_t cdl_truck_payload_trgt_wt_tx_pie;
extern Cdl_gen_tx_pie_t cdl_total_load_count_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_resettable_load_count_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_total_truck_payload_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_truck_payload_id_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_loader_machine_id_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_pcs_password_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_machine_loaded_travel_hrs_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_payload_mem_remain_st_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_loader_bkt_trgt_wt_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_number_of_passes_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_total_pass_count_tx_pie;
extern Cdl_gen_tx_pie_t cdl_total_reweigh_rqst_count_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_total_payload_wt_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_max_lift_vel_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_oil_temp_comp_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_cal_type_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_skew_limit_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_operator_id_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_material_id_tx_pie;
extern Cdl_gen_tx_pie_t cdl_pcs_calibration_wt_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_remain_payload_to_load_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_payload_indicator_config_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_last_store_weight_tx_pie;
extern Cdl_gen_tx_pie_t cdl_pcs_mode_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_load_cycle_start_time_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_load_cycle_end_time_tx_pie;
extern Cdl_gen_tx_pie_t cdl_weigh_range_start_tx_pie;
extern Cdl_gen_tx_pie_t cdl_weigh_range_end_tx_pie;
extern Cdl_gen_tx_pie_t cdl_printer_setting_tx_pie;
extern Cdl_gen_tx_pie_t cdl_printer_tot_tx_pie  ;
extern Cdl_gen_tx_pie_t cdl_oil_type_tx_pie;
extern Cdl_gen_tx_pie_t cdl_cal_adjust_status_tx_pie   ;
extern Cdl_gen_tx_pie_t cdl_reweigh_warning_status_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_zero_accepted_status_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_zero_needed_status_tx_pie  ;
extern Cdl_gen_tx_pie_t cdl_enter_cal_weight_tx_pie;
extern Cdl_gen_tx_pie_t cdl_payload_control_system_status_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_blast_number_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_payload_horn_status_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_statcode_id_tx_pie;
extern Cdl_gen_tx_pie_t cdl_loader_bkt_trgt_wt_percentage_tx_pie;
extern Cdl_gen_tx_pie_t cdl_truck_string_tx_pie ;
extern Cdl_gen_tx_pie_t cdl_excess_mat_ready_tx_pie;
extern Cdl_gen_tx_pie_t cdl_excess_mat_location_tx_pie;
extern Cdl_gen_tx_pie_t cdl_weight_remain_extended_tx_pie;
extern Cdl_gen_tx_pie_t cdl_payload_accuracy_tx_pie;
extern Cdl_gen_tx_pie_t cdl_pcs_clear_button_disp_stat_tx_pie;
extern Cdl_gen_tx_pie_t cdl_pcs_minus_one_button_disp_stat_tx_pie;
extern Cdl_gen_tx_pie_t cdl_pcs_payload_stat_code_index_tx_pie;
extern Cdl_gen_tx_pie_t cdl_tip_off_mode_tx_pie;
extern Cdl_gen_tx_pie_t cdl_tip_off_trigger_tx_pie; /* Dev PID - to be removed later */
extern Cdl_gen_tx_pie_t cdl_tip_off_trigger_type_tx_pie;
extern Cdl_gen_tx_pie_t cdl_autoid_list_display_tx_pie;
extern Cdl_gen_tx_pie_t cdl_payload_overload_limit_enable_tx_pie;
extern Cdl_gen_tx_pie_t cdl_loadsite_id_tx_pie;
extern Cdl_gen_tx_pie_t cdl_weigh_range_indicator_tx_pie;
extern Cdl_gen_tx_pie_t cdl_pcs_last_payload_wt_tx_pie;
extern Cdl_gen_tx_pie_t cdl_payload_display_mode_tx_pie;
extern Cdl_gen_tx_pie_t cdl_history_list_index_tx_pie;
extern Cdl_gen_tx_pie_t cdl_history_list_weight_tx_pie;
extern unsigned_8 mt_reset_mat(unsigned_16 list_index);




void pcs_cdl_init(void);
void pcs_cdl_update(void);
