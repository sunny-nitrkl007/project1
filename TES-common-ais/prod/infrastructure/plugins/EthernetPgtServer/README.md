**EthernetPgtServer TaskPlugin**

    The libraries in libs-list need to be included in the Sconscript for the application that uses the EthernetPgtServer plugin.  Use the EthernetPgtServerTest SConscript as a guid:

        tesPluginDir = localEnv[ 'TES_COMMON_DIR' ] + '/prod/infrastructure/plugins/'
        ethernetPgtServerLibList = localEnv.getLibsListFromPath(tesPluginDir + 'EthernetPgtServer')

        # Build for ECM target only
        if ( localEnv[ 'PLATFORM' ] in [ 'D6XX', 'A6N1', 'A6N2' ] ):
            libList = [
                'ais_task',
                'ais_log',
                'ais_config',
                'commTask',
                ethernetPgtServerLibList,

    A plugin needs to be created to produce the data for the EthernetPgtServer (the data could come from a combination of TES common and project specific SCS channels)  The producer should take a EthernetPgtServerApplicationInterface reference in the constructor (see sandbox/EthernetPgtServerTest/EthernetPgtServerTestdataProducer.hpp for an example)

    Testing PGT server using bmiEthernet:
        1. create new .rb (see below BmiEth_ACD_Client.rb)
        2. create BmiEth_Server.json with the parameters to be requested (see below)
        3. in a new putty window after setting the environment,  ./bmiEthernet --instanceName=BmiEth_ACD_Client


    BmiEth_ACD_Client.rb ***********************

    require "commonLoad.rb"
    require "interfaces_CpmCommon.rb"
    require "Robot.rb"
    load "commonTaskParams.rb"

    Interfaces = CommonTaskParams::Interfaces.dup;
    Interfaces.update( {
        "DataLinkDataOutput" => InterfaceDefs_CpmCommon::DataLinkDataOutput,
        "AppRegInput" => InterfaceDefs_CpmCommon::AppRegInput,
        "AppRegOutput" => InterfaceDefs_CpmCommon::AppRegOutput,
    } )

    Parameters = CommonTaskParams::Parameters.dup;
    Parameters.update( {
    "loggerThreshold" => "debug",  ##  All options listed in descending severity order
                                    ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug
    "cycleRate_hz" => 0.5,       ## going slow since it publishes DLD, which may cause Coaching App to log into breadcrumb
    "PgtClientFid" => 0x00160000,
    "ClientSessionTimeOut" => 300000,
    } )

    MachineSpecificConfig = {
    # bmiEthernet config file path, parameter and ecm configurations are given in this JSON file
    # Correct.rb file should have this path
    # ./bmiEthernet --instanceName=BmiEth_ACD_Client
    "BMI_ETH_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/BmiEth_Server.json",
    }

    Execution = {
    "executableName" => "bmiEth_ACD_Client",
    }


    BmiEth_Server.json ***********************************

    {

    "Ethernet_ECM_Source_Config":
    {
        "ecm_0": {
            "ecm_name"      : "CPM_LWL_ANALYSIS_MODULE",
            "ecm_fid"       : "0x00160000",
            "ip_address"    : "0xA51A4F13",
            "cid"           : "0"
        }
    },

    "CDL_PID":
    {
        "Operator Coaching Tip Progress Indicator Percentage": {
            "CDL PID"                : "0xD027DC",
            "Data Size(bytes)"       : "2",
            "Data Byte Order"        : "LSB",
            "Request Period(mu)"     : "120000",
            "Source FID"             : "0x00160000",
            "Data Type"              : "unsigned_16",
            "VarLengthDataType"      : "0",
            "Dsi Support"            : "Enable",
            "Diag Support"           : "Enable",
            "Scaling"                : "1",
            "Offset"                 : "0",
            "Units"                  : "8"
        },

        "Operator Coaching Tip Summary Display Requirement Status": {
            "CDL PID"                : "0xD1199D",
            "Data Size(bytes)"       : "2",
            "Data Byte Order"        : "MSB",
            "Request Period(mu)"     : "120000",
            "Source FID"             : "0x00160000",
            "Data Type"              : "unsigned_16",
            "VarLengthDataType"      : "0",
            "Dsi Support"            : "Enable",
            "Diag Support"           : "Enable",
            "Scaling"                : "1",
            "Offset"                 : "0",
            "Units"                  : "0"
        },

        "Operator Coaching Tip Snooze Timer": {
            "CDL PID"                : "0xD027DB",
            "Data Size(bytes)"       : "2",
            "Data Byte Order"        : "LSB",
            "Request Period(mu)"     : "120000",
            "Source FID"             : "0x00160000",
            "Data Type"              : "unsigned_16",
            "VarLengthDataType"      : "0",
            "Dsi Support"            : "Enable",
            "Diag Support"           : "Enable",
            "Scaling"                : "1",
            "Offset"                 : "0",
            "Units"                  : "15"
        }
    }
    }
