require "commonLoad"
require "commonTaskParams.rb"
require "interfaces_CpmCommon.rb"
load "Robot.rb"

Interfaces = CommonTaskParams::Interfaces.dup;

AppDataBase = "/opt/appdata"
VerityDirectoryName = ENV["CAT_DIR"].split("/").last              # Last directory in the path
ThisAppName = File.basename( __FILE__, File.extname(__FILE__) )   # Script name without extension
StorageRoot = AppDataBase + "/" + VerityDirectoryName + "/" + ThisAppName
TempDataDirectory = "/tmp/appdata/" + VerityDirectoryName + "/" + ThisAppName
VideoDirectory = "/CPM/videos"    # taking out /opt and /www since this is not needed when using lighttpd server

Interfaces.update( {
  "CoachingShowHideStatusOutput" => InterfaceDefs_CpmCommon::CoachingShowHideStatusOutput, ## send status output to xcp
  "CoachingSummaryDataOutput" => InterfaceDefs_CpmCommon::CoachingSummaryDataOutput, ## send tips output to xcp
  "Coaching3x3DataOutput" => InterfaceDefs_CpmCommon::Coaching3x3DataOutput,
  "DataLinkDataInput" => InterfaceDefs_CpmCommon::DataLinkDataInput,
  "BreadcrumbLogOutput" => InterfaceDefs_CpmCommon::BreadcrumbLogOutput,
  "CoachingTipHistoryOutput" => InterfaceDefs_CpmCommon::CoachingTipHistoryOutput,
  "ShmClockInput" => InterfaceDefs::ShmClockInput,
} )

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
  "cycleRate_hz" => 8.3333333333333334,
  "loggerThreshold" => "info",  ##  All options listed in descending severity order
                                 ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug 
  "serverPort" => 55566,         ## Websocket server port
  "coachingLanguagePath" => "/CPM/languages/appSpecifc_addstring_en.json", # used in SHowHide.html response
  "coachingDataPath" => StorageRoot + "/CoachingDataRecords",
  "maxSavedOperators" => 15,                # Maximum saved operators in OperatorList, OperatorTiphistory. Defaults to 15
  "coachingTipHistoryMaxRecords" => 1000,   # Maximum records stored in CoachingTipHistory. Defaults to 1000
  "operatorExpirationDays" => 180,          # Delete any operator that has not logged in for > this many days. Defaults to 180
  "maxRequestedBreadcrumbRecords" => 100,   # Configurable from the UI
  "maxBreadcrumbRecords" => 1000,           # Absolute maximum
  "minBreadcrumbRecords" => 100,            # Absolute minimum
  "maxBreadcrumbGpsTimeSeconds" => 60,            # Given: GPS is good, how often to log GPS position, Note: GPS record automatic when status goes Good->BAD, BAD->GOOD
  "maxBreadcrumbGpsDistanceMeters" => 50,            # Given: GPS is good, how often to log GPS position, when the Machine move past this threshold.... Note: GpsTime is reset if record logged
  "videoPath" => VideoDirectory,
  "coachingShowHidePracticeSupported" => false,
  "coachingShowHideMapSupported" => false,
  "coachingShowHideStandAloneUiSupported" => false,      # UI flag to indicate if StandAlone Display is used
  "coachingTipSummaryDisplayRequiredTimeSeconds" => 30,  # When tip goes to red, number of seconds that "displayedRequired" is set to True
  "internalMsnNotSet" => "NOT00000",                     # Disable coaching when internalMsn is this value
  "coachingEnabledDefault" => false,                     # Default value of isCoachingEnabled when initialized or DSI is received 
  "coachingInstalledDefault" => false,                   # Default value of isCoachingInstalled when initialized or DSI is received
  "NVMWriteWaitTimeSeconds" => 360,                      # When New Data needing NVM is detected, wait # seconds in case of more changes before writing to NVM
  "coachingFake_SafeState" => false,                     # used for TESTing to toggle SafeState on-off periodically
  } )

Execution = {
  "executableName" => "CoachingTask",
}
