#/******************* OHT 769D configuration parameters **********************/

MachineSpecificConfig = {

#/* Weighing app configuration values */

"Front_Press_to_Wht" => 0.002528677,  # Mg/kPa
"Rear_Press_to_Wht"  => 0.003056861, # Mg/kPa 
"Rear_Axle_Payload_Ratio" => 0.7907, # none
"LoadingPassDetectWeight" => 10, # Mg
"LoadingPldStabThreshold" => 1, # Mg
"LoadingPldStabTime" => 10,  # 200ms/bit
"StabilitySpdThreshold" => 5, # Kph
"StabilityYawRateLimit" => 10, # deg/s 
"StabilityPitchLimit" => 5, # deg
"StabilityFAccLimit" => 0.5, # m/s^2
"StabilityFjerkLimit" => 0.5, # m/s^3
"RollingPldStabilityThreshold" => 1, # Mg
"RollingPldStabilityTime" => 50, # 200ms/bit
"LoadingPassDetectTime" => 10, # 200ms/bit
"ContinuousLoadingStabTime" => 10, # 200ms/bit
"TargetWeight" => 63.6, #Mg
"CalibFlag" => true,
"RollingPldStdWindowSize" => 50,
"PldStdWindowSize" => 10,
"FrontTrackWidth" => 4900, # m -Values not provided
"RearTrackWidth" => 4603.3, # m -Values not provided
"FrontStrutSeparation" => 4900, # m -Values not provided
"RearStrutSeparation" => 1.7396, # m -Values not provided
"FrontUnSprungWeight" => 14, # Mg -Values not provided
"RearUnSprungWeight" => 34.3, # Mg -Values not provided
"Ovrld_Limit" => 110, # %(percentage) -Values not provided
"Max_GMW" => 279.9, # Mg -Values not provided

#/* Cycle Segmentation app configuration values */

"Tpms2CSLoadDetectWeight" => 22.7,  # Mg
"Tpms2CSLoadDetectTime" => 10, # 200ms/bit
"Tpms2CSReadyToLoadSpd" => 1, # Kph
"Tpms2CSReadyToLoadTime" => 5, # 200ms/bit
"Tpms2CSTravelGoModeSpd" => 1.5, #Kph
"Tpms2CSTravelGoModeTime" => 10, # 200ms/bit
"Tpms2CSBodyRaiseTime" => 10, # 200ms/bit
#"Tpms2CSInitStatus" => 0, #"TPMS2_CS_INIT_UNKNOWN_ERROR"
"Tpms2InitialTotalFuelUsed" => 3.406141764,
"Tpms2InitialFuelRate" => 0.0,


#Tkph parameters in metrics
"TimeBase" => 4,  # 1 to 8hrs
"EmptyMachineWeight"  => 73.5 , # 0-65503 tonne
"EmpRearAxleWeightDist" => 54.6, # 0-100% Percentage
"FullRearAxleWeightDist" => 67.2,  # 0-100% Percentage
"TKPHFrontActValue" => 385, # 0-6550.3 tonne-kph
"TKPHRearActValue" => 385, # 0-6550.3 tonne-kph
"TKPHFrontDeactValue" => 360, # 0-6550.3 tonne-kph
"TKPHRearDeactValue" => 360, # 0-6550.3 tonne-kph
"MachineSpeedLimitingValue" => 15, # 14 -235.8108 kph 
"TkphEnableStatus" => 13, # 12-Enabled 13- Disabled

#/* BmiCdl config JSON file path */
"BMI_CDL_CONFIG_JSON_FILE_PATH" => "/opt/CPM/config/BmiCdlCfg_769D.json",

# Weigh App would receive IMUYawRate, IMUIncline and FilteredIMUAccelX from CDL, J1939, IMUProc app

"MachineStabilitySrc" => 1,  ##MachineStabilitySrc = 1; Weigh App would receive IMUYawRate, IMUIncline and FilteredIMUAccelX from IMUProcApp
							##MachineStabilitySrc = 2;  Weigh App would receive IMUYawRate, IMUIncline and FilteredIMUAccelX from BMICDL
							##MachineStabilitySrc = 3;  Weigh App would receive IMUYawRate, IMUIncline and FilteredIMUAccelX from BMIJ1939
							
"DataLinkComm" => 0, #BmiCDL =0, #BmiJ1939 =1

"EmptycalibThreshold" => 75, # Calibration Pressure Stability Threshold in KpA

# Data needed to display calibration values on ET screen 
"MinGroundSpeed" => 3.10686,# mph
"PayLoadCycleValue" => 600,# seconds
# SEA Feature Status
"SEA_OverrideEnableStatus" => 0, # SEA_OverrideEnableStatus = 0; SEA based attachement for machine
 	 	  		 # SEA_OverrideEnableStatus = 1; Standard equipment 


}
Machinetype1 = {
  "InternalMSN" => "CAT10200",
"Types" => [
               "769D",],
"Prefix" => "BBB",
"Group" => 1,#"This variable takes 1 only for 769D & 771D for calculating Transmission shift count"
}
StrutSensorConfig = {
"FrontStrutSensorSlope" => 0.0580156,
"FrontStrutSensorIntercept" => 200,
"RearStrutSensorSlope" => 0.0580156,
"ReartStrutSensorIntercept" => 200,
}

DeviceID_J1939 = {
  #Analysis  : 0x9601 0100 B001
  #Analysis  : 0x9601 0000 B001
  #Analysis  : 0x9601 0F00 0000 <<
  #Autonomous: 0x6004 2400 0000

  "MID"        => 0x0196,
  "ST_app_num" => 0x000F, 
  "ST_chg_lvl" => 0x0000,
}

NVM = { 
#   Key   BlockID         BlockSize  BlockIntegrity  File1                               
#  -----  ----------      ---------  --------------  -----------
   "00"=> ["0x00010000",  "1560",    "0",            "A6N2_Diagnostics_Events_Log.txt", ],
   "01"=> ["0x00000010",  "532",     "0",            "A6N2_Service_Clock_Primary.txt",  ],
   "02"=> ["0x00000011",  "532",     "0",            "A6N2_Service_Clock_Secondary.txt",],
   "03"=> ["0x00010001",  "25",      "0",            "A6N2_RTC_Time_Zone_Old.txt",      ],
   "09"=> ["0x00010003",  "25",      "0",            "A6N2_RTC_Time_Zone_New.txt",      ],   
   "04"=> ["0x00010002",  "13",      "0",            "A6N2_RTC_Secure.txt",             ],
   "05"=> ["0x0001000a",  "8",       "0",            "A6N2_ProductID.txt",              ],
   "06"=> ["0x00010020",  "8",       "0",            "A6N2_OHT_Productivity_SEA.txt",   ],
   "07"=> ["0x00010021",  "8",       "0",            "A6N2_LMT_RAC_SEA.txt",            ],
   "08"=> ["0x00010022",  "8",       "0",            "A6N2_SEA3.txt",                   ],
   "10"=> ["0x00010030",  "8",       "0",            "A6N2_ProductID1.txt",             ],

}

SEA = { 
#   Key   ReasonCode  PermInstallPID  PermEnablePID  SecurityLvl  EncByte  EncBit  TempCounter  TempInstallPID  TempCounterPID  
#  -----  ----------  --------------  -------------  -----------  -------  ------  ----------   --------------  --------------
   "00"=> ["149",      "0xD10DA0",      "0xD10EE7",   "1",         "1",     "1",    "1",         "0xD10EE6",     "0xD01A48", ],
  # "01"=> ["150",      "0xD10A93",      "0x000000",   "1",         "1",     "1",    "1",         "0x000000",     "0x000000", ],
   #"02"=> ["151",      "0xD10DA2",      "0xD114C5",   "2",         "1",     "3",    "1",         "0xD10EE7",     "0xD01A49", ],
   #"03"=> ["152",      "0xD10DA3",      "0xD114C6",   "0",         "1",     "4",    "0",         "0x000000",     "0x000000", ],
   #"04"=> ["153",      "0xD10DA4",      "0xD114C7",   "2",         "1",     "5",    "1",         "0xD10EE8",     "0xD01A4A", ],
   #"05"=> ["154",      "0xD10DA5",      "0xD114C8",   "0",         "1",     "6",    "0",         "0x000000",     "0x000000", ],
   #"06"=> ["155",      "0xD10DA6",      "0xD114C9",   "0",         "1",     "7",    "0",         "0x000000",     "0x000000", ],
   #"07"=> ["156",      "0xD10DA7",      "0xD114CA",   "2",         "1",     "8",    "1",         "0xD10EE9",     "0xD01A4B", ],
   #"08"=> ["157",      "0xD10DA8",      "0xD114CB",   "0",         "2",     "1",    "0",         "0x000000",     "0x000000", ],
   #"09"=> ["158",      "0xD10DA9",      "0xD114CC",   "2",         "2",     "2",    "1",         "0xD10EEA",     "0xD01A4C", ],
   #"10"=> ["159",      "0xD10DB0",      "0xD114CD",   "0",         "2",     "3",    "0",         "0x000000",     "0x000000", ],
}

