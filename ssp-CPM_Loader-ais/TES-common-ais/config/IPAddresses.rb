######################################################################
##
## These IP Addresses are based off of the Peoria Networking Scheme
##
######################################################################

#IP Addresses

IPAddressMap = {
    "A6N2-0"                    => "165.26.79.19",  # CPM
    "CPM"                       => "165.26.79.19",  # If LC can be ignored
    "D6CX"                      => "165.26.78.161",

    "gateway_ciscoRouter"       => "165.26.78.1", # Default gateway for all onboard devices
    "switch0"                   => "192.168.2.250", # access to network switch configuration
    "switch1"                   => "165.26.79.2", # access to network switch configuration
    "switch2"                   => "165.26.79.3", # access to network switch configuration
    "switch3"                   => "192.168.3.4", # access to network switch configuration (Velodyne only)
    "switch4"                   => "165.26.79.5", # access to network switch configuration
    "applanix"                  => "165.26.79.6", # address for Applanix

    "auto0"                     => "165.26.79.180", # default IP address for fresh install of Pathfinder system
    "auto1"                     => "165.26.79.7", # Eth0 configuration
    "auto2"                     => "165.26.79.9", # Eth0 configuration
    "auto3"                     => "165.26.79.11", # Eth0 configuration
    "auto4"                     => "165.26.79.13", # Eth0 configuration
    "auto5"                     => "165.26.79.15", # Eth0 configuration

    "broadcastAddress"          => "165.26.79.255", # Eth0 configuration
    "broadcastAddress_eth2"     => "192.168.3.255", # Eth1 configuration

    "auxiliaryApplanix_eth2"    => "192.168.3.6", # address for the auxiliary Applanix
    "auto1_eth2"                => "192.168.3.7", # Eth1 configuration (Velodyne only)
    "auto2_eth2"                => "192.168.3.9", # Eth1 configuration (Velodyne only)
    "auto3_eth2"                => "192.168.3.11", # Eth1 configuration (Velodyne only)
    "auto4_eth2"                => "192.168.3.13", # Eth1 configuration (Velodyne only)
    "auto5_eth2"                => "192.168.3.15", # Eth1 configuration (Velodyne only)

    "parTruck"                  => "192.168.2.8", # IP Address for Par Truck
    "sanityAddr"                => "192.168.2.15", # IP Address for Sanity computer
    "sanity2Addr"               => "192.168.2.16", # Sanity2 computer
    "autoTimeSyncPort"          => 2009, # Time Sync Port for Auto ECMs
    "sanityTimeSyncPort"        => 2010, # Time Sync Port for Sanity computers
    "timeSyncMasterAddress"     => "165.26.79.13", # IP address of the "master" to synchronize time with
    "benchAddr"                 => "165.26.79.7", # IP Address for bench A5N6 

    "velodyne"                  => "192.168.3.43", # address for Velodyne
    "velodynePort"              => 2368, # port for Velodyne

    "mcm"                       => "165.26.79.21", # MCM A4N4
    "mcmTxPort"                 => "9000", # Tx port for MCM (Must be enclosed in "")
    "mcmRxPort"                 => "9001", # Rx port for MCM (Must be enclosed in "")
    "diagnosticAgentPort"       => "9002", # diagnostic agent interface port to MCM (Must be enclosed in "")
    "eventAgentPort"            => "9003", # event agent interface port to MCM (Must be enclosed in "")

    "topeCMPD"                  => "165.26.79.22", # Tope ECM
    "ciodsCMPD"                 => "165.26.79.23", # CIODS ECM
    "topeTIM"                   => "165.26.79.24", # TOPETIME A4N4
    "cellModem"                 => "165.26.79.25", # used for condition monitoring Cell Modem
    "cmpd"                      => "192.168.2.150", # address for CMPD
    "cmpdPort"                  => 17000, # port for CMPD

    "leftLowerRadar"            => "165.26.1.35", # Left Lower Radar
    "rightLowerRadar"           => "165.26.1.36", # Right Lower Radar
    "leftUpperRadar"            => "165.26.1.37", # Left Upper Radar
    "rightUpperRadar"           => "165.26.1.38", # Right Upper Radar
    "midUpperRadar"             => "165.26.1.39", # Mid Upper Radar
    "midLowerRadar"             => "165.26.1.40", # Mid Lower Radar

    "vimsMain"                       => "165.26.79.218", # IP address for AMT VIMS on D and VIMSMain
    "vimsApp"                        => "165.26.79.226", # IP address for AMT VIMS on F

    "gpsBroadcastAddress"            => "165.26.79.255", # Local broadcast address for GPS positions
    "gpsBroadcastUDPPort"            => "10110", # port for GPS Broadcast UDP (Must be enclosed in "")

    "rtkUDPPort"                     => 3784, # port for RTK UDP

    "loopback"                       => "127.0.0.1", # loopback address
    "loopbackRxPort"                 => "9000", # loopback Rx port (Must be enclosed in "")
    "loopbackTxPort"                 => "9001", # loopback Tx port (Must be enclosed in "")

    # IP Addresses for legacy code...currently needed to support other Pathfinder Infrastucture 
    "leftNodder"                => "165.26.1.44", # LeftYesNodder
    "rightNodder"               => "165.26.1.45", # RightYesNodder
    "noNodder"                  => "165.26.1.46", # NoNoNodder
    "leftYesLidar"              => "165.26.1.15", # LeftYesLidar
    "rightYesLidar"             => "165.26.1.16", # RightYesLidar
    "frontLeftLidar"            => "165.26.1.17", # FrontLeftLidar
    "frontRightLidar"           => "165.26.1.18", # FrontRightLidar
    "noLidar"                   => "165.26.1.19", # NoNoLidar
    "rearLidar"                 => "165.26.1.20", # RearLidar

    "frontLeftIPCamera"              => "165.26.79.40", # Left blade tip camera IP address
    "frontRightIPCamera"             => "165.26.79.41", # Right blade tip camera IP address
    "IPCameraHTTPPort"               => "80", # HTTP port for all IP cameras (Must be enclosed in "")

    "rearRadar"                 => "165.26.1.41", # Rear Radar

    "timeTagEcm1"               => "192.168.2.51", # address for Time Tag ECM devices
    "timeTagEcm2"               => "192.168.2.52", # address for Time Tag ECM devices
    "timeTagEcm3"               => "192.168.2.53", # address for Time Tag ECM devices
    "timeTagEcm4"               => "192.168.2.54", # address for Time Tag ECM devices
    "radarPort"                 => 2000, # ECM port
    "lidarPort"                 => 2001, # ECM port
    "servicePort"               => 2002, # ECM port
    "timePort"                  => 2003, # ECM port
    "ecmStatusPort"             => 2005, # ECM port
}

# If there's an auxiliary file, load it
loadInstanceAuxFile( File.basename( __FILE__ ) )
