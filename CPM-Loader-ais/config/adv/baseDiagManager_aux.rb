
Parameters.update( {
  "EDDT_Servers"=>[
  "ACD",
  "IMPLEMENT"],
} )

ACD = 
{
  "Data_Link"               => 0, #0=> J1939, 1=> CDL
  "ID_By"                   => 0, #0=> J1939Address, 1=> J1939Name 
  "Address"                 => 0x41,
  "Industry_Group"          => 3,
  "Vehicle_System"          => 0,
  "Vehicle_System_Instance" => 0,
  "Function"                => 145,
  "Function_Instance"       => 0,
  "ECU_Instance"            => 0,
  "Manufacturer_Code"       => 8,
}

IMPLEMENT = 
{
  "Data_Link"               => 0, #0=> J1939, 1=> CDL
  "ID_By"                   => 0, #0=> J1939Address, 1=> J1939Name 
  "Address"                 => 0x2E,
  "Industry_Group"          => 3,
  "Vehicle_System"          => 0,
  "Vehicle_System_Instance" => 0,
  "Function"                => 145,
  "Function_Instance"       => 0,
  "ECU_Instance"            => 0,
  "Manufacturer_Code"       => 8,
}

