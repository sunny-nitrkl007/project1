#!/bin/sh

#---------------------------------------------------------
# app_init.sh: this script is called by OS on the boot.
#---------------------------------------------------------
# changes made to /etc/profile by other verities are not seen in following verities,
# so we need to manually do that
. /etc/profile 
# common source for CAT_DIR and $HOME on the ECM
. vehDataDir

SERVICE_DASH_WAIT_IN_SECONDS=5

IsServiceDashboardVerityPresent=false
IsCoreInfrastructureVerityPresent=false
IsMachineHealthVerityPresent=false

if ls ${vehDataHome}/ServiceDashboard*.verity 1> /dev/null 2>&1; then
   IsServiceDashboardVerityPresent=true
fi

if ls ${vehDataHome}/CoreInfrastructure*.verity 1> /dev/null 2>&1; then
   IsCoreInfrastructureVerityPresent=true
fi

if ls ${vehDataHome}/MachineHealth*.verity 1> /dev/null 2>&1; then
   IsMachineHealthVerityPresent=true
fi

#sleep till appSoftware verity is mounted.
while true
do
   if [ -d ${vehDataDir} ]
   then
      logger -s -p kern.info "Found appSoftware verity."
      break;
   fi
   sleep 1;
done

#wait upto 5 seconds. for ServiceDashboard to be mounted
if [ "$IsServiceDashboardVerityPresent" = true ] ; then
  COUNT1=0
  until mountpoint -q ${vehDataHome}/ServiceDashboard
  do
    if [ "$COUNT1" -ge "$SERVICE_DASH_WAIT_IN_SECONDS" ]
    then
        logger -s -p kern.info "timeout. waiting for service dashboard mount."
        break
    fi
    sleep 1
    let "COUNT1++"
  done
fi

#sleep till network is up
if [ "$IsCoreInfrastructureVerityPresent" = true ] ; then
	while true
	do
	   if [ -f "/tmp/net_up" ]
	   then
	      logger -s -p kern.info "Found net up. Proceeding to start..."
	      break;
	   fi
	   sleep 1;
	done
fi

# Fixing exec bit for /opt/ if this is DEV tokened ECM
if [ -f /opt/appdata/DeveloperToken/ct_token ]; then
    # remount /opt partition with exec bit set on
    mount -o remount,exec /opt
fi

# Fixing keyswitch
if [ "$IsMachineHealthVerityPresent" = false ] ; then
if [[ -f "/sys/class/rtc/rtc0/wakealarm_st" ]]; then
    if cat "/sys/class/rtc/rtc0/wakealarm_st" | grep -xqFe "1"; then
        echo 0 > /sys/class/rtc/rtc0/wakealarm_st
    fi
fi
fi


# 
# The following fix is needed because CAN performancy of the IMU 
# task is not acceptable unless this is set to low latency.
# 
# Set serial port to low_latency if ttyS1 is a character device
if [ -c "/dev/ttyS1" ]; then
    setserial /dev/ttyS1 low_latency
fi

# 
# The following fix is needed because switch to grounds do
# not work with certain versions of the A6N2 OS (ie 2019_1.0).
# This means location codes do not work unless this is set to 
# low latency.
# 
# Set serial port to low_latency if ttyS2 is a character device
if [ -c "/dev/ttyS2" ]; then
    setserial /dev/ttyS2 low_latency
fi


# Make sure all of our binaries, libraries and scripts are executable
if [ -w "${vehDataDir}" ]; then
   chmod -R 777 "${vehDataDir}"
fi

# Modifying HostName
if [ -f "/opt/appdata/DefaultConfig/config/hostname" ]
then
    new_host_name=$( cat /opt/appdata/DefaultConfig/config/hostname )
    host_name=$(cat /etc/hostname)
    hostname $new_host_name
    sed -i "s/$host_name/$new_host_name/g" /etc/hosts
    sed -i "s/$host_name/$new_host_name/g" /etc/hostname
fi

#write to debug log for system watch (with limit to number of lines)
#AUTOSTART_DEBUG_FILE="/opt/appdata/CPM/debug/autostart.txt"
#SYSLOG_DEBUG_FILE="/opt/appdata/CPM/debug/syslog.txt"
#TEMP_FILE="/opt/cpm_tmp.txt"
#if [ ! -d /opt/appdata/CPM/debug ]; then	
#	mkdir -p /opt/appdata/CPM/debug
#fi

#if [ ! -f $AUTOSTART_DEBUG_FILE ]; then
#	echo "File created" > $AUTOSTART_DEBUG_FILE
#fi

#if [ ! -f $SYSLOG_DEBUG_FILE ]; then
#	echo "File created" > $SYSLOG_DEBUG_FILE
#fi

#tail -n 100 $AUTOSTART_DEBUG_FILE > $TEMP_FILE && mv $TEMP_FILE $AUTOSTART_DEBUG_FILE
#echo $(date) "app_inits started" >> $AUTOSTART_DEBUG_FILE

#tail -n 50000 $SYSLOG_DEBUG_FILE > $TEMP_FILE && mv $TEMP_FILE $SYSLOG_DEBUG_FILE
#tail -F -n +1 /var/log/messages >> $SYSLOG_DEBUG_FILE &




# Set env variables for current script and child scripts
export CAT_DIR=${vehDataDir}
export CAT_CONFIG_DIR=${CAT_DIR}/config
if [[ "$LD_LIBRARY_PATH" == "" ]]; then
  export LD_LIBRARY_PATH=${CAT_DIR}/lib:${vehDataHome}/ossSoftware/usr/lib
else
  export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${CAT_DIR}/lib:${vehDataHome}/ossSoftware/usr/lib
fi
export HOME=${vehDataHome}

# Set env variables for all ssh sessions
echo "" >> /etc/profile
echo "# Set AIS env variables for all ssh sessions" >> /etc/profile
echo "export CAT_DIR=${vehDataDir}" >> /etc/profile
echo "export CAT_CONFIG_DIR=${CAT_DIR}/config" >> /etc/profile
echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH" >> /etc/profile
echo "export HOME=${vehDataHome}" >> /etc/profile

# We have to have /bin/bash, since it is hardcoded in out bash scripts. copy only when not present in /bin/folder. 
if [ ! -f /bin/bash ]; then
if [ -f ${HOME}/ossSoftware/usr/bin/bash ]; then
  cp ${HOME}/ossSoftware/usr/bin/bash /bin/
else
  echo "*** ${HOME}/ossSoftware/usr/bin/bash is missing, exiting."
  exit 1
fi
fi

# We have to have /bin/rsync. copy only when not present in /bin/ folder.
if [ ! -f /bin/rsync ]; then
if [ -f ${HOME}/ossSoftware/usr/bin/rsync ]; then
  cp ${HOME}/ossSoftware/usr/bin/rsync /bin/
fi
fi

# We have to have /lib/libpopt.so.0. copy only when not present in /lib/ folder.
if [ ! -f /lib/libpopt.so.0 ]; then
if [ -f ${HOME}/ossSoftware/usr/lib/libpopt.so.0 ]; then
  cp ${HOME}/ossSoftware/usr/lib/libpopt.so.0 /lib/
fi
fi

# Non-empty robot file is required for pcm start
if ! [ -f ${HOME}/etc/robot ]; then
  if ! [ -d ${HOME}/etc ]; then
    mkdir -p ${HOME}/etc/
  fi

  
  echo "NOT00000" > ${HOME}/etc/robot         #NOT00000 is default config
fi

# Create a new udev rule to mount the log disk whenever a new usb hard drive is connected
###
cat <<EOF >/etc/udev/rules.d/91-mount_log_disk.rules
# If kernel detects a usb hard drive device 
KERNEL!="sd[a-z][0-9]", GOTO="mount_log_disk_end"

# Import FS infos for device information
IMPORT{program}="/sbin/blkid -o udev -p %N"

# Mount the connected device to /opt/log when the kernel detects a hard drive has been connected
ACTION=="add", ENV{ID_FS_LABEL}=="logs", RUN+="/usr/bin/logger 'Mounting Log Disk.'"
ACTION=="add", ENV{ID_FS_LABEL}=="logs", RUN+="/bin/mount -o relatime /dev/%k /opt/log"

# Clean up after removal
ACTION=="remove", ENV{ID_FS_LABEL}=="logs", RUN+="/bin/umount -l /opt/log"

# Exit
LABEL="mount_log_disk_end"
EOF
###

# Load any rules created since startup
udevadm control --reload-rules
# Trigger the "add" ACTION to mount any hard drive connected at startup
udevadm trigger --action=add 

# Launch the RPA Client application only when MachineHealth is not present
if [ "$IsMachineHealthVerityPresent" = false ] ; then
if [ -f ${CAT_DIR}/bin/rpa_client ]; then
 screen -h 1000 -d -m -S rpa_client ${CAT_DIR}/bin/rpa_client 
fi
if [ -f ${CAT_DIR}/bin/rpaClientTask ]; then
  screen -h 1000 -d -m -S rpaClientTask ${CAT_DIR}/bin/rpaClientTask
fi
fi

# Make sure our appdata exists, if not, create it
if [ ! -d /opt/appdata/CPM ]
then
	mkdir -p /opt/appdata/CPM
fi

# Launch the portForwardingMgr to enable port forwarding
# config for portForwarding can be found in $CAT_CONFIG_DIR/port_forwarding_cfg.xml
if [ -f "${CAT_DIR}/bin/portForwardingMgr" ]; then
 screen -h 1000 -d -m -S portForwardingMgr "${CAT_DIR}/bin/portForwardingMgr"
fi

# Attempt to determine the IP address and start another instance of FTP server
BINDIP=$(ifconfig eth0.20 | grep "inet addr" | cut -d : -f 2 | cut -d " " -f 1)
# setup two FTP servers for hlogs & nvm
#BINDIP=165.26.79.19
if [ -n "$BINDIP" ]; then
  FTPCFG="${CAT_CONFIG_DIR}/vsftpd_logger.conf"
  if [ -f "${FTPCFG}" ]; then
    vsftpd "${FTPCFG}" -olisten_address="${BINDIP}"
    echo "Found IP: ${BINDIP}"
  else
    echo "Unable to locate ${FTPCFG}"
  fi
else
  echo "Could not obtain IP to bind for eth0"
fi

if [ -n "$BINDIP" ]; then
  FTPCFG="${CAT_CONFIG_DIR}/vsftpd_nvm.conf"
  if [ -f "${FTPCFG}" ]; then
    vsftpd "${FTPCFG}" -olisten_address="${BINDIP}"
    echo "Found IP: ${BINDIP}"
  else
    echo "Unable to locate ${FTPCFG}"
  fi
else
  echo "Could not obtain IP to bind for eth0"
fi


#Lighttpd restart logic - only when servicedashboard verity and app_lighttpd.conf is present..
if [ "$IsServiceDashboardVerityPresent" = true ] ; then
  pid_lighttpd=''
  SLEEP_TIMEOUT=60
  SLEEP_TIME1=0
  SLEEP_TIME2=0
  lighttpd_killed=false

  while true
  do
    pid_lighttpd=$(pidof lighttpd)
    while [ "$pid_lighttpd" != '' ] && [ "$SLEEP_TIME2" -lt "$SLEEP_TIMEOUT" ]
    do
      killall -s SIGTERM lighttpd
      pid_lighttpd=$(pidof lighttpd)

      if [ "$pid_lighttpd" = '' ]; then
        lighttpd_killed=true
      fi
      sleep 1;
      SLEEP_TIME2=$((SLEEP_TIME2+1));
    done

    # Update lighttpd configuration for Ethernet PGT without reverse proxy
    if [ "$lighttpd_killed" = true ]; then
      echo -e "\n# Load csf_httpd_server cgi path config\ninclude \"/opt/CPM/config/csf_lighttpd.conf\"" >> /tmp/lighttpd.conf
      sed -i "s/api/api-DISABLE/g" /tmp/app_lighttpd.conf
      /opt/ServiceDashboard/bin/lighttpd -f /tmp/lighttpd.conf -m /opt/ServiceDashboard/lib/
      break;
    fi
    if [ "$SLEEP_TIMEOUT" -lt "$((SLEEP_TIME1+1))" ] || [ "$SLEEP_TIMEOUT" -lt "$((SLEEP_TIME2+1))" ]; then
      break;
    fi
    sleep 1;
    SLEEP_TIME1=$((SLEEP_TIME1+1));
  done
fi

# Launch system restart task
if [ -f ${CAT_DIR}/bin/systemRestart ]; then
 screen -h 1000 -d -m -S systemRestart ${CAT_DIR}/bin/systemRestart 
fi

# Launch the restart_mon.sh
#if [ -f /opt/zzzAutostart/restart_mon.sh ]; then
## command="restart_mon.sh"
# running=`ps ax | grep -v grep | grep $command | wc -l`
# if [ $running -gt 0 ]; then
#     echo "restart_mon is running"
# else
#     echo "restart_mon is not running"
#     screen -h 1000 -d -m -S restart_mon.sh /opt/zzzAutostart/restart_mon.sh
# fi
#fi

# Start AIS app
${CAT_DIR}/scripts/autostart

