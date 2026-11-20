#!/bin/sh

# ------------------------------------------------------------------------------
# This file sets variables that describe this release unit.
# All variables defined in this release unit start with the "ru_" prefix.
# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Release Unit Git Prefix - ru_git_prefix
# This is used as the prefix for the Git tag for the release unit.
ru_git_prefix="SSS"

# ------------------------------------------------------------------------------
# Release Unit Ivy Path - ru_ivy_path
ru_ivy_path="cat/ess-csf"

# ------------------------------------------------------------------------------
# Release Unit Ivy Name - ru_ivy_name
# This is used as the name of the Ivy descriptor for this release unit.
ru_ivy_name="sss"

# ------------------------------------------------------------------------------
# Release Unit Integration Branch - ru_int_branch
ru_int_branch="master_int"

# ------------------------------------------------------------------------------
# Release Unit Release Branch - ru_rel_branch
ru_rel_branch="master"

# ------------------------------------------------------------------------------
# Release Unit Git URL - ru_git_url
ru_git_url="git@git1.corp.cat.com:/cat/ess-csf/sss"

# ------------------------------------------------------------------------------
# Release Unit Local Path - ru_local_path
ru_local_path="lib_sss/sss"

# ------------------------------------------------------------------------------
# Release Unit Targets - ru_tgts
ru_tgts="tgt_ar_diab_5.9.4.0_PPCVLEEF "
ru_tgts+="tgt_diab_5.8.0.0_PPCVLEEF "


ru_oel_rev="2016.4.0"
ru_scl_rev="2016.2.0"
ru_cd_rev="2016.3.0"
ru_a5m4i1_rev="2015.8.0"

# ------------------------------------------------------------------------------
# Release Unit Dependencies common to all build targets - ru_common_deps
ru_common_deps=(
    #Name                                       Version                   Org       Domain   Config
    cat/ess-csf/hal_include                     2016.10.0                com.cat.e ivy-csf "dev->rel"
    cat/ess-csf/boot_inc                        2015.2.0                 com.cat.e ivy-csf "dev->rel"
    cat/ess-csf/pclint_pkg                      2015.4.0                 com.cat.e ivy-csf "dev->rel"
    treck/cots_treck_release                    2016.1.0                 com.cat.e ivy-csf "dev->rel"
    cat/dt/bt_ectools                           COMMANDER_TOOLS_2.9      com.cat.e ivy-dt  "dev->rel"
    oss/make                                    MAKE4.1_2015.1.0         com.cat.e ivy-csf "dev->rel"
    cat/dt/hfile                                DEV_TOOLS_2005_Q1_PROD   com.cat.e ivy-dt  "dev->rel"
)

# ------------------------------------------------------------------------------
# Release Unit Dependencies specific to tgt_ar_diab_5.9.4.0_PPCVLEEF - ru_tgt_ar_diab_5_9_4_0_PPCVLEEF_deps
ru_tgt_ar_diab_5_9_4_0_PPCVLEEF_deps=(
   #Name                                                                Version                                    Org        Domain   Config
    cat/ess-csf/oel-tgt_ar_diab_5.9.4.0_PPCVLEEF-a                      $ru_oel_rev                                com.cat.e  ivy-csf  "dev->rel"
    cat/ess-csf/scl-tgt_ar_diab_5.9.4.0_PPCVLEEF-a                      $ru_scl_rev                                com.cat.e  ivy-csf  "dev->nodep"
    cat/ess-csf/cd-tgt_ar_diab_5.9.4.0_PPCVLEEF-a                       $ru_cd_rev                                 com.cat.e  ivy-csf  "dev->rel"
    #A5M4I1                                                                                                                            
    cat/ess-csf/hal_a5m4i1/a5m4i1-tgt_ar_diab_5.9.4.0_PPCVLEEF-a        $ru_a5m4i1_rev                             com.cat.e  ivy-csf  "dev->rel"
    #A6P1                                                                                                                              
    cat/ess-csf/hal_a6p1/hal_a6p1-tgt_ar_diab_5.9.4.0_PPCVLEEF_pkg      2016.1.0                                   com.cat.e  ivy-csf  "dev->rel"
    cat/ess-csf/hal_a6p1/hal_common-tgt_ar_diab_5.9.4.0_PPCVLEEF-a      HAL_COMMON_2015.9.0_FLEXCAN3_A6P1_ATEST_6  com.cat.e  ivy-csf  "dev->rel"
    #OEL_OS_CFG_CSNS_TEST                                                                                                              
    cat/ess-csf/oel_os_cfg_csns_test/oel_os_cfg_csns_test-tgt_ar_diab_5.9.4.0_PPCVLEEF_pkg   2016.1.0              com.cat.e  ivy-csf  "dev->rel"
   )

# ------------------------------------------------------------------------------
# Release Unit Dependencies specific to tgt_diab_5.8.0.0_PPCVLEEF - ru_tgt_diab_5_8_0_0_PPCVLEEF_deps
ru_tgt_diab_5_8_0_0_PPCVLEEF_deps=(
   #Name                                                               Version              Org        Domain   Config
    cat/ess-csf/oel-tgt_diab_5.8.0.0_PPCVLEEF-a                        $ru_oel_rev          com.cat.e  ivy-csf  "dev->rel"
    cat/ess-csf/scl-tgt_diab_5.8.0.0_PPCVLEEF-a                        $ru_scl_rev          com.cat.e  ivy-csf  "dev->nodep"
    cat/ess-csf/cd-tgt_diab_5.8.0.0_PPCVLEEF-a                         $ru_cd_rev           com.cat.e  ivy-csf  "dev->rel"
    #A5M4I1                                                                                                     
    cat/ess-csf/hal_a5m4i1/a5m4i1-tgt_diab_5.8.0.0_PPCVLEEF-a          $ru_a5m4i1_rev       com.cat.e  ivy-csf  "dev->rel"
  )



