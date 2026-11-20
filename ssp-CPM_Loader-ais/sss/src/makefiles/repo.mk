########################################################################
# src/makefiles/repo.mk                                 clearmake -C gnu
########################################################################

REPO1 := ssp-afsw\lib_sss\sss
REPO2 := ssp-afsw\lib_sss\sss-a

# Content for the 'sss' git repository. 
REPO1_LIST := 

$(REPO1): REPO_NAME=$(REPO1)
$(REPO1): REPO_LIST=$(REPO1_LIST)


# Content for the 'sss-a' git repository. 
REPO2_LIST := \
   tgt_cc32r_4.30_M32Rx\
   tgt_cxs12x_4.7.9_MC9S12XEST\
   tgt_diab_4.2b_PPC555EHST\
   tgt_diab_4.4a_PPC555EH\
   tgt_rvct_2.1_ARM7TDMI\
   tgt_rvct_4.0_CORTEX-M3\
   tgt_gcc_4.4.3_ubuntu

$(REPO2): REPO_NAME=$(REPO2)
$(REPO2): REPO_LIST=$(REPO2_LIST)

# List of the git repos to be populated with 'clearmake mirror'.
MIRROR_REPOS = $(REPO1) $(REPO2)



