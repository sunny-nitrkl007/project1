###################################################################
# Mapping of Ruby config file to executable name
# This was formerly stored in Execution of each task's Ruby config file
###################################################################

if defined?(ExecutionTable_CPM_rb)
  puts __FILE__ + ' already loaded, skipping'
else
  ExecutionTable_CPM_rb = true

  ExecutionTable.update({
    "AisJhm2DataServer" => { "executableName" => "aisJhm2DataServer", },
    "AutonomyConditionDiagnostics" => { "executableName" => "autonomyConditionDiagnostics", },
    "baseDiagManager" => { "executableName" => "baseDiagManager", },
    "BmiJ1939_CANA" => { "executableName" => "bmiJ1939_CANA", },
    "BmiJ1939_CANB" => { "executableName" => "bmiJ1939_CANB", },
    "CANTestApp" => { "executableName" => "CANTestApp", },
    "CycleSeg" => { "executableName" => "CycleSeg", },
    "DemoApp" => { "executableName" => "DemoApp", },
    "DigTimerTestApp" => { "executableName" => "DigTimerTestApp", },
    "hornOnStoreTest" => { "executableName" => "hornOnStoreTest", },
    "ScsToRos2Bridge" => { "executableName" => "ScsToRos2Bridge", },
    "LpsSaJobMgrApp" => { "executableName" => "LpsSaJobMgrApp", },
    "LpsSaListMgrApp" => { "executableName" => "LpsSaListMgrApp", },
    "LpsSaListMgrTestApp" => { "executableName" => "LpsSaListMgrTestApp", },
    "LpsSaTotalsApp" => { "executableName" => "LpsSaTotalsApp", },
    "LpsSaTotalsMakeTotalsTest" => { "executableName" => "LpsSaTotalsMakeTotalsTest", },
    "LpsSaTotalsTelemetryTest" => { "executableName" => "LpsSaTotalsTelemetryTest", },
    "LpsSaTotalsTestApp" => { "executableName" => "LpsSaTotalsTestApp", },
    "LpsSaWeighApp" => { "executableName" => "LpsSaWeighApp", },
    "MTPCycleSegApp" => { "executableName" => "DatalinkTestApp", },
    "OperatorIdTest" => { "executableName" => "OperatorIdTest", },
    "TireRevTestApp" => { "executableName" => "TireRevTestApp", },
    "WidgetApp" => { "executableName" => "WidgetApp", },
    "WorkOrderAssist" => { "executableName" => "WorkOrderAssist", },
    "XcpServerTask" => { "executableName" => "aisXcpServer", },
    #"Acd2Task" => { "executableName" => "acd2Task", },

  })
end

