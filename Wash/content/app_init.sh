#!/bin/sh

#---------------------------------------------------------
# app_init.sh: this script is called by OS on the boot.
#---------------------------------------------------------
logger -p user.info "Wash: Begin app_init.sh"

sleep 10;

logger -p user.info "Wash: /opt/etc/*"
rm -rf /opt/etc/*

logger -p user.info "Wash: /opt/tmp/*"
rm -rf /opt/tmp/*

logger -p user.info "Wash: /opt/appdata/CoreInfrastructure"
rm -rf /opt/appdata/CoreInfrastructure

logger -p user.info "Wash: /opt/appdata/ServiceDashboard"
rm -rf /opt/appdata/ServiceDashboard

logger -p user.info "Wash: /opt/appdata/CDA"
rm -rf /opt/appdata/CDA

logger -p user.info "Wash: /opt/appdata/CPM"
rm -rf /opt/appdata/CPM

logger -p user.info "Wash: /opt/appdata/zzDevTools"
rm -rf /opt/appdata/zzDevTools

logger -p user.info "Wash: /opt/appdata/DeveloperToken"
rm -rf /opt/appdata/DeveloperToken

logger -p user.info "Wash: /opt/appdata/zzzAutostart"
rm -rf /opt/appdata/zzzAutostart

logger -p user.info "Wash: /opt/appdata/ossSoftware"
rm -rf /opt/appdata/ossSoftware

logger -p user.info "Wash: /opt/appdata/DefaultConfig"
rm -rf /opt/appdata/DefaultConfig

logger -p user.info "Wash: /opt/appdata/zzAutostart"
rm -rf /opt/appdata/zzAutostart

logger -p user.info "Wash: /opt/appdata/Wash"
rm -rf /opt/appdata/Wash

logger -p user.info "Wash: /tmp/appdata/*"
rm -rf /tmp/appdata/*

logger -p user.info "Wash: End app_init.sh"
