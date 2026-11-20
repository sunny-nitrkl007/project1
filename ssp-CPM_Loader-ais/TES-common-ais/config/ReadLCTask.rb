require "ReadLCTask_Base.rb"

Parameters.update( {
  # "loggerThreshold" => "error", # "fatal", "error", "warn", "notice", "info", "debug",
  # "cycleRate_hz" => 2,
  # "requireGPSTimeSynchronizationOnStart" => false, # ALLOW this process to start without synchronization
  # "OverrideHostName" => true, # Override hostname based on platform and location code, defaults to true
  # "OverrideIPAddress" => true, # Replace the current conn_mgr xml_file based on the platform and location code, defaults to true
  # "ForceXmlOverwrite" => false, # Overwrite conn-mgr xml_file even if the contents of the existing file are identical, defaults to false
  # "OverrideLocationCode" => false, # Get location code from LocationCodeOverrideFile, defaults to false
  # "LocationCodeOverrideFile" => getEtcDir() + '/locationCodeOverride', # if OverrideLocationCode is set but this file is not present, LC override will be disabled (i.e. default behavior)
  # "xmlConfigPath" =>  getCatDir() + '/config/conn_mgr_xml_configs/', # path where the xml_files are stored, defaults to /opt/appSoftware/config/conn_mgr_xml_configs/
  # "ExitOnCompletion" => true, # Exit task after reading location code. This reduces the CPU burden of the OEL task for cases where the LC will not be changed when machine is powered on, defaults to false
} )

# Overwrite existing A6NX IP mappings
A6N2 = {
#  loc code      xml_file,                  hostname        
#  -----         -----                    -----                                                                                    # 23 | 24 | 25
   "1" => [ "conn_mgr_rw_a6n2_79_19.xml", "A6N2"],       # for location code 1, IP address/hostname sets to 165.26.79.19/A6N2         0 |  0 | 1   
   "2" => [ "conn_mgr_rw_a6n2_79_19.xml", "A6N2"],       # for location code 2, IP address/hostname sets to 165.26.79.19/A6N2         0 |  1 | 0
   "3" => [ "conn_mgr_rw_a6n2_79_19.xml", "A6N2"],       # for location code 3, IP address/hostname sets to 165.26.79.19/A6N2         0 |  1 | 1
   "4" => [ "conn_mgr_rw_a6n2_79_19.xml", "A6N2"],       # for location code 4, IP address/hostname sets to 165.26.79.14/A6N2         1 |  0 | 0
   "5" => [ "conn_mgr_rw_a6n2_79_19.xml", "A6N2"],       # for location code 5, IP address/hostname sets to 165.26.79.19/A6N2         1 |  0 | 1
   "6" => [ "conn_mgr_rw_a6n2_79_19.xml", "A6N2"],       # for location code 6, IP address/hostname sets to 165.26.79.19/A6N2         1 |  1 | 0
   "7" => [ "conn_mgr_rw_a6n2_79_19.xml", "A6N2"],       # for location code 7, IP address/hostname sets to 165.26.79.19/A6N2         1 |  1 | 1
   "0" => [ "conn_mgr_rw_a6n2_79_19.xml", "A6N2"],       # default, IP address/hostname sets to 165.26.79.19/A6N2
}

A6N1 = {
  #  loc code      xml_file,                 hostname        
  #  -----         -----                    -----                                                                                    # 23 | 24 | 25
     "1" => [ "conn_mgr_rw_a6n1_79_19.xml", "A6N1"],       # for location code 1, IP address/hostname sets to 165.26.79.19/A6N1         0 |  0 | 1   
     "2" => [ "conn_mgr_rw_a6n1_79_19.xml", "A6N1"],       # for location code 2, IP address/hostname sets to 165.26.79.19/A6N1         0 |  1 | 0
     "3" => [ "conn_mgr_rw_a6n1_79_19.xml", "A6N1"],       # for location code 3, IP address/hostname sets to 165.26.79.19/A6N1         0 |  1 | 1
     "4" => [ "conn_mgr_rw_a6n1_79_19.xml", "A6N1"],       # for location code 4, IP address/hostname sets to 165.26.79.14/A6N1         1 |  0 | 0
     "5" => [ "conn_mgr_rw_a6n1_79_19.xml", "A6N1"],       # for location code 5, IP address/hostname sets to 165.26.79.19/A6N1         1 |  0 | 1
     "6" => [ "conn_mgr_rw_a6n1_79_19.xml", "A6N1"],       # for location code 6, IP address/hostname sets to 165.26.79.19/A6N1         1 |  1 | 0
     "7" => [ "conn_mgr_rw_a6n1_79_19.xml", "A6N1"],       # for location code 7, IP address/hostname sets to 165.26.79.19/A6N1         1 |  1 | 1
     "0" => [ "conn_mgr_rw_a6n1_79_19.xml", "A6N1"],       # default, IP address/hostname sets to 165.26.79.19/A6N1
}
