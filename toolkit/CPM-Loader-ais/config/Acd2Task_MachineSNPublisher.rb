load "Acd2Task_MachineSNPublisher_Base.rb"

# TaskPlugin configuration
MachineSNPublisher = {
  # Flag for enabling/disabling the plugin
  "enabled" => true,

  # Publish rate of MachineSNOutput
  "cycleRate_hz" => 1,

  # Flag for enabling/disabling publishing to the MachineSNOutput SCS channel. Note that if either productIdEnabled or equipIdEnabled is not set,
  # the value of the corresponding entry with be invalid. Defaults to true.
  "publishEnabled" => true,

  # Flag for enabling/disabling subscription to the MachineSNOutput SCS channel for setting Product ID and/or Equipment ID. 
  # Mutually exclusive with publishEnabled. Defaults to false.
  "subscribeEnabled" => false,

##-- Product ID PID 0xF82D
  # Enabled/Disable handling of Product ID. Received values are converted to uppercase and published to SCS and written to the Tx ParameterData in DatalinkManager
  # Defaults to true.
  "productIdEnabled" => true,

  # Flag to enable/disable raising of ProductIDNotReceived diagnostic. Defaults to false.
  "productIdDiagnosticEnabled" => false,

  # Inactive to Active Debounce time for Product ID SCLBlkSig in MachineSNOutput. Defaults to 5.0 seconds
  "productIdApplyTimeSeconds" => 5.0,

  # Active to Inactive Debounce time for Product ID SCLBlkSig in MachineSNOutput. Defaults to 0.0 seconds
  "productIdClearTimeSeconds" => 0.0,

##-- Equipment ID PID 0xF81A
  # Enabled/Disable handling of Equipment ID. Received values are published to SCS and written to the Tx ParameterData in DatalinkManager
  # Defaults to true.
  "equipIdEnabled" => true,

  # Inactive to Active Debounce time for Equipment ID SCLBlkSig in MachineSNOutput. Defaults to 5.0 seconds
  "equipIdApplyTimeSeconds" => 5.0,

  # Active to Inactive Debounce time for Equipment ID SCLBlkSig in MachineSNOutput. Defaults to 0.0 seconds
  "equipIdClearTimeSeconds" => 0.0,
}
