#Standalone ECM

#if the Machine Robot file does not define DeviceID_J1939, then the following default device ID will be used
if (defined?(DeviceID_J1939) == nil)   
  DeviceID_J1939 = {
    #Analysis  : 0x9601 0100 B001
    #Analysis  : 0x9601 0000 B001
    #Analysis  : 0x9601 0F00 0000
    #Autonomous: 0x6004 2400 0000
    #TTL       : 0x9601 0100 BC00

    "MID"        => 0x0196,
    "ST_app_num" => 0x01B0, 
    "ST_chg_lvl" => 0x0012,
  }
end

RTC_TZ = {
  "RTC_Security"  => 0, #0-> Non-Secure, 1->Secure
  "RTC_Type"      => 3, #0-> Standalone, 1->Distributed Client, 2-> Distributed Server, 3->PID client, 4-> PID server
  "RTC_Master"    => 0x25, #Relevant for RTC_Type 1, 3.  0x25 is Telematics ECM for CPM 2.0 SA
}

ECM_SUMMARY = {
#   ECM Name   		 Filename  				IP Address(optional)                               
#  ---------- 		 --------      			 	-----------------
  "Analysis Module"  => ["AnalysisModuleECMSummary.json",	""],
  "Product Link"     => ["ProductLinkServiceDashboard.xml", 	"165.26.78.1"],
  "Analysis Display" => ["AnalysisDisplayServiceDashboard.xml", "165.26.79.43"],
}
