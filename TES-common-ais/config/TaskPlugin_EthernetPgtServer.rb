EthernetPgtServer = {
  "enabled" => true,

  "serverFid" => 0x00160000,
  "jsonConfigFile" => "BmiEth_Server.json",

  # csf_http_server
  "httpdNumConnections" => 3,
  "httpdTaskPeriodMs" => 100,  # Set to the same rate as the OEL task
}
