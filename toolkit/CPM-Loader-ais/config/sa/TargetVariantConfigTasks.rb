#######################################################################
# Contains target variant specific configurations for Tasks for example;
# 	standalone(sa) vs advanced(adv)
#
#######################################################################
AuxiliaryProcesses.update(

  "bmiJ1939_CANA" => {
      "machines" => [
                      Machines::MachineMap.default,
                    ],
      "arguments" => ["--instanceName=BmiJ1939_CANA"],
      "executableName" => ENV['CAT_DIR'] + "/bin/bmiJ1939",
      "autoRestart" => true,
      "timeBetweenRestarts_s" => 2,
      "alwaysOn" => false,
  },

  "bmiJ1939_CANB" => {
      "machines" => [
                      Machines::MachineMap.default,
                    ],
      "arguments" => ["--instanceName=BmiJ1939_CANB"],
      "executableName" => ENV['CAT_DIR'] + "/bin/bmiJ1939",
      "autoRestart" => true,
      "timeBetweenRestarts_s" => 2,
      "alwaysOn" => false,
  },

  "bmiCdl" => {
    "machines" => [
                    Machines::MachineMap.default,
                  ],
    "executableName" => ENV['CAT_DIR'] + "/bin/bmiCdl",
      "autoRestart" => true,
      "timeBetweenRestarts_s" => 2,
      "alwaysOn" => false,
  },

  "SwitchInput" => {
    "machines" => [
                    Machines::MachineMap.default,
                  ],
    "executableName" => ENV['CAT_DIR'] + "/bin/SwitchInputApp",
    "autoRestart" => true,
    "timeBetweenRestarts_s" => 2,
    "alwaysOn" => false,
  },

  "CycleSeg" => {
      "machines" => [
                      Machines::MachineMap.default,
                    ],
      "executableName" => ENV['CAT_DIR'] + "/bin/CycleSeg",
      "autoRestart" => true,
      "timeBetweenRestarts_s" => 2,
      "alwaysOn" => false,
  }
)
