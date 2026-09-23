#Advanced ECM (default to 982 device id)

#if the Machine Robot file does not define DeviceID_J1939, then the following default device ID will be used
if (defined?(DeviceID_J1939) == nil)   
  DeviceID_J1939 = {
    #Analysis  : 0x9601 8200 B001 
    "MID"        => 0x0196,
    "ST_app_num" => 0x01B0, 
    "ST_chg_lvl" => 0x0085,
  }
end

RTC_TZ = {
  "RTC_Security"  => 0, #0-> Non-Secure, 1->Secure
  "RTC_Type"      => 1, #0-> Standalone, 1->Distributed Client, 2-> Distributed Server, 3->PID client, 4-> PID server
  "RTC_Master"    => 0x28, #Relevant for RTC_Type 1, 3.  0x28 is secondary display
}

ECM_SUMMARY = {
#   ECM Name   		 Filename  				IP Address(optional)                               
#  ---------- 		 --------      			 	-----------------
  "Analysis Module"  => ["AnalysisModuleECMSummary.json",	""],
  "Product Link"     => ["ProductLinkServiceDashboard.xml", 	"165.26.78.1"],
}
