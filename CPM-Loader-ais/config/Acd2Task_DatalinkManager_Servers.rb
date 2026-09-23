DatalinkServerConfig.push({
  "Engine" => {
    Datalink::Keys::J1939_SA     => 0x00,
    Datalink::Keys::CDL_MID      => 0x24,
    Datalink::Keys::COMPONENT_ID => 590,
    Datalink::Keys::GLOBAL_ID    => 0xF1,
    Datalink::Keys::ETHERNET_FID => 0x00010000,
    Datalink::Keys::IP_ADDRESS   => "165.26.79.190",
  },

  "Transmission" => {
    Datalink::Keys::J1939_SA     => 0x03,
    Datalink::Keys::CDL_MID      => 0x1B,
    Datalink::Keys::COMPONENT_ID => 296,
    Datalink::Keys::GLOBAL_ID    => 0x252,
    Datalink::Keys::ETHERNET_FID => 0x00020000,
    Datalink::Keys::IP_ADDRESS   => "165.26.79.25",
  },

  "Productivity" => {
    Datalink::Keys::J1939_SA     => 0x41,
    Datalink::Keys::CDL_MID      => 0x37,
    Datalink::Keys::COMPONENT_ID => 111,
    Datalink::Keys::GLOBAL_ID    => 0x0,
    Datalink::Keys::ETHERNET_FID => 0x00040000,
    Datalink::Keys::IP_ADDRESS   => "165.26.79.26",
  },

  "Telematics" => {
    Datalink::Keys::J1939_SA     => 0x25,
    Datalink::Keys::CDL_MID      => 0xFF,
    Datalink::Keys::COMPONENT_ID => 5806,
    Datalink::Keys::GLOBAL_ID    => 0x0,
    Datalink::Keys::ETHERNET_FID => 0x00000000,
    Datalink::Keys::IP_ADDRESS   => "0.0.0.0",
  },

  "Chassis" => {
    Datalink::Keys::J1939_SA     => 0x99,
    Datalink::Keys::CDL_MID      => 0x57,
    Datalink::Keys::COMPONENT_ID => 1273,
    Datalink::Keys::GLOBAL_ID    => 0x258,
    Datalink::Keys::ETHERNET_FID => 0x00050000,
    Datalink::Keys::IP_ADDRESS   => "165.26.79.79",
  },

  "Steering" => {
    Datalink::Keys::J1939_SA     => 0x98,
    Datalink::Keys::CDL_MID      => 0x96,
    Datalink::Keys::COMPONENT_ID => 3434,
    Datalink::Keys::GLOBAL_ID    => 0x0,
    Datalink::Keys::ETHERNET_FID => 0x00640000,
    Datalink::Keys::IP_ADDRESS   => "165.26.79.40",
  },

  "Implement" => {
    Datalink::Keys::J1939_SA     => 0x97,
    Datalink::Keys::CDL_MID      => 0x52,
    Datalink::Keys::COMPONENT_ID => 596,
    Datalink::Keys::GLOBAL_ID    => 0xF3,
    Datalink::Keys::ETHERNET_FID => 0x00650000,
    Datalink::Keys::IP_ADDRESS   => "165.26.79.19",
  },

  "Display" => {
    Datalink::Keys::J1939_SA     => 0x96,
    Datalink::Keys::CDL_MID      => 0x35,
    Datalink::Keys::COMPONENT_ID => 2448,
    Datalink::Keys::GLOBAL_ID    => 0xF6,
    Datalink::Keys::ETHERNET_FID => 0x00660000,
    Datalink::Keys::IP_ADDRESS   => "165.26.79.19",
  },

})

