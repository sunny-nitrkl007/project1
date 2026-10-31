**Building the CPM Super Project (ssp)**

From the super project (ssp) base directory:

* Build for A6N2 / A6N1 / OCS(Native)
  make project_a6n2 / make project_a6n1 / make project_ocs

* Build all targets/platforms
  make project_all

* Make release for A6N2 / A6N1 (also builds)
  make release_a6n2 / make release_a6n1

* Make release for A6N2 without rebuilding (applies to A6N1 as well)
  make release_only_a6n2

* Make all verities for A6N2 (applies to A6N1 as well) (NOTE: CDA not included)
  make verity_all_a6n2

* Make individual verities for A6N2 (applies to A6N1 as well)
  make verity_app_a6n2
  make verity_autostart_a6n2
  make verity_defaultconfig_a6n2
  make verity_oss_a6n2

* Sync software to A6N2
  export BLUEKEY=165.26.79.19; cd eta-ais; . changeCatEnvToHere.sh; scripts/syncSoftware -i /home/pf/.ssh/a6n2-id_rsa -c $BLUEKEY -t A6N2
