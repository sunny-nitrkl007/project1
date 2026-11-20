#/******************* Default configuration parameters **********************/

MachineSpecificConfig = {

#/* BmiJ1939 config JSON file paths */  
"BMI_J1939_PGN_CONFIG_JSON_FILE_PATH" => "/opt/CPM/config/BmiJ1939PGNCfg_Default.json",
"BMI_J1939_CDL_PID_CONFIG_JSON_FILE_PATH" => "/opt/CPM/config/BmiJ1939PIDCfg_Default.json",

}
Machinetype1 = {
  "InternalMSN" => "CAT00000",
"Types" => [
               "Default",],
"Group" => 1,#"This variable takes 1 only for 769D & 771D for calculating Transmission shift count"
"Prefix" => "CAT",
}
StrutSensorConfig = {

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
   "06"=> ["0x00010022",  "8",       "0",            "A6N2_SEA3.txt",                   ],
   "07"=> ["0x00010021",  "8",       "0",            "A6N2_LMT_RAC_SEA.txt",            ],
   "08"=> ["0x00010020",  "8",       "0",            "A6N2_OHT_Productivity_SEA.txt",   ],
   "10"=> ["0x00010030",  "8",       "0",            "A6N2_ProductID1.txt",             ],

}

SEA = { 
#   Key   ReasonCode  PermInstallPID  PermEnablePID  SecurityLvl  EncByte  EncBit  TempCounter  TempInstallPID  TempCounterPID  
#  -----  ----------  --------------  -------------  -----------  -------  ------  ----------   --------------  --------------
   #"00"=> ["149",      "0xD10DA0",      "0xD10EE7",   "1",         "1",     "1",    "1",         "0xD10EE6",     "0xD01A48", ],
   #"01"=> ["150",      "0xD10A93",      "0x000000",   "1",         "1",     "1",    "1",         "0x000000",     "0x000000", ],
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

