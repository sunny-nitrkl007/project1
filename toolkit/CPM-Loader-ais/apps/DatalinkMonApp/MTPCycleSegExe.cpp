#include <interfaces/DataLinkData/SecuritySystemCurrentSecurityIDParam.h>

#include "MTPCycleSegExe.h"
#include "MTP_BMI_CDL_PID.h"
#include "MTP_BMI_J1939_PGN.h"

#include <pthread.h>

using namespace task;

AbstractTaskCore* task::getTaskImplementation(void)
{
    static MTPCycleSegApp thisTask("MTPCycleSegApp"); 
    return dynamic_cast<Task *>(&thisTask);
}

MTPCycleSegApp::MTPCycleSegApp(const std::string& taskName):
	    Task(taskName),
    dataLinkDataInput(nullptr)
{
}

MTPCycleSegApp::~MTPCycleSegApp()
{
}

bool MTPCycleSegApp::initialize()
{
    // Bind all scs channels, return false if any failures occur
    if (!InterfaceDb::bind("DataLinkDataInput", dataLinkDataInput))
    {
        return false;
    }

    // Store task config
    rubyCfg = getTaskConfig();

    return true;
}

bool MTPCycleSegApp::ReadDataLinkData()
{
    DataLinkData dlData;
    //pthread_mutex_t count_mutex;

    // Process all DataLinkData objects
    while (dataLinkDataInput->get(dlData))
    {
        typedef struct{
        	float    valEng = 0.0f;
        	uint16_t val = 0;
            uint16_t stat = DataLinkParam::DATA_LINK_PARAM_CDL_STATUS_FAULT;
        }DLParamFloat;
        typedef struct{
        	float    valEng = 0.0f;
        	uint32_t val = 0;
            uint16_t stat = DataLinkParam::DATA_LINK_PARAM_CDL_STATUS_FAULT;
        }DLParamFuel;
        typedef struct{
        	uint8_t  valEng = 0;
        	uint8_t  val = 0;
            uint16_t stat = DataLinkParam::DATA_LINK_PARAM_CDL_STATUS_FAULT;
        }DLParamUInt8;
        typedef struct{
        	uint16_t  valEng = 0;
        	uint16_t  val = 0;
            uint16_t stat = DataLinkParam::DATA_LINK_PARAM_CDL_STATUS_FAULT;
        }DLParamUInt16;
        DLParamFloat tiltLevPos, extForce, machIdleStat, implOpStat;
        DLParamUInt8 storeSwitch, unitsStat;
        DLParamFuel totalFuel;
        DLParamUInt16 OpReqGear;
        
        // Iterate through the DataLinkData map
        for (auto& dlParam : dlData.GetParams())
        {
            auto paramId = dlParam.GetParamId();

            AIS_LOG_ERROR("------------------------------------");
            AIS_LOG_ERROR("paramId = %X, val = %f, dsi = %d, source = %d", paramId, dlParam.GetLastGoodValueEng(),dlParam.GetLastValueDsi(),dlParam.GetSid() );            
            AIS_LOG_ERROR("------------------------------------");

            uint16_t stat = (dlParam.GetLastValueDsi() == 0) ? DataLinkParam::DATA_LINK_PARAM_CDL_STATUS_OK : DataLinkParam::DATA_LINK_PARAM_CDL_STATUS_FAULT;
            bool noDsi = (stat == DataLinkParam::DATA_LINK_PARAM_CDL_STATUS_OK);

            switch (paramId) {

            case SecuritySystemCurrentSecurityIDParam::CatExtId: {
                if (DataLinkParam::DlpParamIdentifierType_t::DATA_LINK_PARAM_IDENTIFIER_CAT_EXT != dlParam.GetParamIdentifierType()) {
                    AIS_LOG_WARN("%X not cat ext id.", paramId);
                }
                else if (VarLengthDataLinkParamPool::CAT_EXT != dlParam.GetVarLengthParamType()) {
                    AIS_LOG_WARN("%X var length param type wrong: %d", paramId, dlParam.GetVarLengthParamType());
                }
                else if (0 != dlParam.GetVarLengthParamDsi()) {
                    AIS_LOG_WARN("%X var length param dsi not 0: %d", paramId, dlParam.GetVarLengthParamDsi());
                }
                else if (dlParam.GetVarParamBlockLength() < SecuritySystemCurrentSecurityIDParam::m_DataLengthMinSize) {
                    AIS_LOG_WARN("%X var param block length too short: %d", paramId, dlParam.GetVarParamBlockLength());
                }
                else if (!dlParam.IsPIDDataReceived()) {
                    AIS_LOG_WARN("%X not received.", paramId);
                }
                else {
                    const SecuritySystemCurrentSecurityIDParam idParam(dlParam);
                    std::vector<uint8_t> id;
                    std::string description;
                    if (!idParam.getID(id)) {
                        AIS_LOG_WARN("%X could not get ID", paramId);
                    }
                    else if (!idParam.getIDDescription(description)) {
                        AIS_LOG_WARN("%X could not get description", paramId);
                    }
                    else {
                        AIS_LOG_INFO("%X got it! '%s'", paramId, description.c_str());
                    }
                }
                break;
            }


                case BMI_CDL_PID_OP_REQUESTED_GEAR:
                	OpReqGear.valEng = dlParam.GetLastGoodValueEng();
                	OpReqGear.val = noDsi ? dlParam.GetLastGoodValue<uint16_t>() : 0;
                	OpReqGear.stat = stat;
                    AIS_LOG_INFO("Op Requested Gear (PID $%X), val: %f (0x%X) | stat: %d", paramId, OpReqGear.valEng, OpReqGear.val, OpReqGear.stat);
                break;



                case BMI_CDL_PID_STORE_SWITCH:
                	storeSwitch.valEng = dlParam.GetLastGoodValueEng();
                	storeSwitch.val = noDsi ? dlParam.GetLastGoodValue<int8_t>() : 0;
                	storeSwitch.stat = stat;
                    AIS_LOG_INFO("Store Switch (PID $%X), val: %d (0x%X) | stat: %d", paramId, storeSwitch.valEng, storeSwitch.val, storeSwitch.stat);
                break;

                case BMI_CDL_PID_TILT_LEVER_POSITION:
                	tiltLevPos.valEng = dlParam.GetLastGoodValueEng();
                	tiltLevPos.val = noDsi ? dlParam.GetLastGoodValue<int16_t>() : 0;
                	tiltLevPos.stat = stat;
                    AIS_LOG_INFO("Tilt Lever Position (PID $%X), val: %f (0x%X) | stat: %d", paramId, tiltLevPos.valEng, tiltLevPos.val, tiltLevPos.stat);
                    break;

                case BMI_CDL_PID_EXT_FORCE:
                	extForce.valEng = dlParam.GetLastGoodValueEng();
                	extForce.val = noDsi ? dlParam.GetLastGoodValue<int16_t>() : 0;
                	extForce.stat = stat;
                    AIS_LOG_INFO("External Force (PID $%X), val: %f (0x%X) | stat: %d", paramId, extForce.valEng, extForce.val, extForce.stat);
                break;

                case BMI_CDL_PID_MACHINE_IDLE_STATUS:
                	machIdleStat.valEng = dlParam.GetLastGoodValueEng();
                	machIdleStat.val = noDsi ? dlParam.GetLastGoodValue<uint16_t>() : 0;
                	machIdleStat.stat = stat;
                    AIS_LOG_INFO("Mach Idle Status (PID $%X), val: %d (0x%X) | stat: %d", paramId, machIdleStat.valEng, machIdleStat.val, machIdleStat.stat);
                	break;

                case BMI_CDL_PID_TOTAL_FUEL:
                	totalFuel.valEng = dlParam.GetLastGoodValueEng();
                	totalFuel.val = noDsi ? dlParam.GetLastGoodValue<uint32_t>() : 0;
                	totalFuel.stat = stat;
                    AIS_LOG_INFO("Total Fuel (PID $%X), val: %f (0x%X) | stat: %d", paramId, totalFuel.valEng, totalFuel.val, totalFuel.stat);
                    break;

                case BMI_CDL_PID_UNITS_STATUS:
                	unitsStat.valEng = dlParam.GetLastGoodValueEng();
                	unitsStat.val = noDsi ? dlParam.GetLastGoodValue<uint8_t>() : 0;
                	unitsStat.stat = stat;
            		AIS_LOG_INFO("Units Status (PID $%X), val: %d (0x%X) | stat: %d", paramId, unitsStat.valEng, unitsStat.val, unitsStat.stat);
                break;

                case BMI_CDL_PID_IMPLEMENT_OPERATION_STATUS:
                	implOpStat.valEng = dlParam.GetLastGoodValueEng();
                	implOpStat.val = noDsi ? dlParam.GetLastGoodValue<uint16_t>() : 0;
                	implOpStat.stat = stat;
                    AIS_LOG_INFO("Implement Op Status (PID $%X), val: %d (0x%X) | stat: %d", paramId, implOpStat.valEng, implOpStat.val, implOpStat.stat);
                break;
                case BMI_J1939_PGN_ELEC_STEERING_CONTROL:
           		    AIS_LOG_INFO(" Steering Control PGN Received");
           		    AIS_LOG_INFO("GetVarLengthParamDsi = %d",dlParam.GetVarLengthParamDsi());
                    dlParam.SetVarLengthParamType(VarLengthDataLinkParamPool::PGN);
					if( BMI_DATA_STATUS_OK == dlParam.GetVarLengthParamDsi())
					{
					   if((dlParam.GetVarLengthParamType() == VarLengthDataLinkParamPool::PGN) )
					   {
							const boost::shared_ptr<VarLengthDataLinkParam> varLengthParam = dlParam.GetVarLengthParam();
							const unsigned_8* varParamBlock = dlParam.GetVarParamBlock();
							const unsigned_8 varParamBlockSize = dlParam.GetVarParamBlockLength();
							AIS_LOG_INFO("varParamBlockSize %d", varParamBlockSize);
							for (int i = 0; i < varParamBlockSize; i++)
							  {
								  AIS_LOG_INFO("pidData[%2d]    %x", i, varParamBlock[i]);
							  }
					   }
					   else
					   {
						   if (dlParam.GetVarLengthParamType() != VarLengthDataLinkParamPool::PGN)
							{
								AIS_LOG_WARN("Expected VarLengthParamType to equal %d, but equals %d instead.", VarLengthDataLinkParamPool::PGN, dlParam.GetVarLengthParamType());
							}
					   }
					}
                	break;

                case BMI_J1939_PGN_ACCELERATION_SENSOR:
           		    AIS_LOG_INFO(" Acceleration Sensor PGN Received");
           		    AIS_LOG_INFO("GetVarLengthParamDsi = %d",dlParam.GetVarLengthParamDsi());
                    dlParam.SetVarLengthParamType(VarLengthDataLinkParamPool::PGN);
					if( BMI_DATA_STATUS_OK == dlParam.GetVarLengthParamDsi())
					{
					   if((dlParam.GetVarLengthParamType() == VarLengthDataLinkParamPool::PGN) )
					   {
							const boost::shared_ptr<VarLengthDataLinkParam> varLengthParam = dlParam.GetVarLengthParam();
							const unsigned_8* varParamBlock = dlParam.GetVarParamBlock();
							const unsigned_8 varParamBlockSize = dlParam.GetVarParamBlockLength();
							AIS_LOG_INFO("varParamBlockSize %d", varParamBlockSize);
							for (int i = 0; i < varParamBlockSize; i++)
							  {
								  AIS_LOG_INFO("pidData[%2d]    %x", i, varParamBlock[i]);
							  }
					   }
					   else
					   {
						   if (dlParam.GetVarLengthParamType() != VarLengthDataLinkParamPool::PGN)
							{
								AIS_LOG_WARN("Expected VarLengthParamType to equal %d, but equals %d instead.", VarLengthDataLinkParamPool::PGN, dlParam.GetVarLengthParamType());
							}
					   }
					}
                	break;

                case BMI_J1939_PGN_EEC1:
           		    AIS_LOG_INFO(" EEC1 PGN Received");
           		    AIS_LOG_INFO("GetVarLengthParamDsi = %d",dlParam.GetVarLengthParamDsi());
                    dlParam.SetVarLengthParamType(VarLengthDataLinkParamPool::PGN);
					if( BMI_DATA_STATUS_OK == dlParam.GetVarLengthParamDsi())
					{
					   if((dlParam.GetVarLengthParamType() == VarLengthDataLinkParamPool::PGN) )
					   {
							const boost::shared_ptr<VarLengthDataLinkParam> varLengthParam = dlParam.GetVarLengthParam();
							const unsigned_8* varParamBlock = dlParam.GetVarParamBlock();
							const unsigned_8 varParamBlockSize = dlParam.GetVarParamBlockLength();
							AIS_LOG_INFO("varParamBlockSize %d", varParamBlockSize);
							for (int i = 0; i < varParamBlockSize; i++)
							  {
								  AIS_LOG_INFO("pidData[%2d]    %x", i, varParamBlock[i]);
							  }
					   }
					   else
					   {
						   if (dlParam.GetVarLengthParamType() != VarLengthDataLinkParamPool::PGN)
							{
								AIS_LOG_WARN("Expected VarLengthParamType to equal %d, but equals %d instead.", VarLengthDataLinkParamPool::PGN, dlParam.GetVarLengthParamType());
							}
					   }
					}
                	break;

                case BMI_J1939_PGN_FUEL_ECONOMY:
           		    AIS_LOG_INFO(" Fuel Economy PGN Received");
           		    AIS_LOG_INFO("GetVarLengthParamDsi = %d",dlParam.GetVarLengthParamDsi());
                    dlParam.SetVarLengthParamType(VarLengthDataLinkParamPool::PGN);
					if( BMI_DATA_STATUS_OK == dlParam.GetVarLengthParamDsi())
					{
					   if((dlParam.GetVarLengthParamType() == VarLengthDataLinkParamPool::PGN) )
					   {
							const boost::shared_ptr<VarLengthDataLinkParam> varLengthParam = dlParam.GetVarLengthParam();
							const unsigned_8* varParamBlock = dlParam.GetVarParamBlock();
							const unsigned_8 varParamBlockSize = dlParam.GetVarParamBlockLength();
							AIS_LOG_INFO("varParamBlockSize %d", varParamBlockSize);
							for (int i = 0; i < varParamBlockSize; i++)
							  {
								  AIS_LOG_INFO("pidData[%2d]    %x", i, varParamBlock[i]);
							  }
					   }
					   else
					   {
						   if (dlParam.GetVarLengthParamType() != VarLengthDataLinkParamPool::PGN)
							{
								AIS_LOG_WARN("Expected VarLengthParamType to equal %d, but equals %d instead.", VarLengthDataLinkParamPool::PGN, dlParam.GetVarLengthParamType());
							}
					   }
					}
                	break;

                case BMI_CDL_PID_PRODUCT_ID:
           		    AIS_LOG_INFO(" Product ID PID Received");
           		    AIS_LOG_INFO("GetVarLengthParamDsi = %d",dlParam.GetVarLengthParamDsi());
                    dlParam.SetVarLengthParamType(VarLengthDataLinkParamPool::PRODUCT_ID);
					if( BMI_DATA_STATUS_OK == dlParam.GetVarLengthParamDsi())
					{
					   if((dlParam.GetVarLengthParamType() == VarLengthDataLinkParamPool::PRODUCT_ID) )
					   {
							const boost::shared_ptr<VarLengthDataLinkParam> varLengthParam = dlParam.GetVarLengthParam();
							const unsigned_8* varParamBlock = dlParam.GetVarParamBlock();
							const unsigned_8 varParamBlockSize = dlParam.GetVarParamBlockLength();
							AIS_LOG_INFO("varParamBlockSize %d", varParamBlockSize);
							for (int i = 0; i < varParamBlockSize; i++)
							  {
								  AIS_LOG_INFO("pidData[%2d]    %x", i, varParamBlock[i]);
							  }
					   }
					   else
					   {
						   if (dlParam.GetVarLengthParamType() != VarLengthDataLinkParamPool::PRODUCT_ID)
							{
								AIS_LOG_WARN("Expected VarLengthParamType to equal %d, but equals %d instead.", VarLengthDataLinkParamPool::PRODUCT_ID, dlParam.GetVarLengthParamType());
							}
					   }
					}
                	break;
                }
            }
        }
    return true;
}

bool MTPCycleSegApp::executive()
{
    // Register CycleSeg with any dependent apps
    //RegisterApps();

    // Read scs input channels
    //ReadShmClock();
    ReadDataLinkData();
    //ReadPartNumbers();

    // Update cycle segmentation model based on scs inputs
    //UpdateModel();

    // Publish any VP3 records handled by VP3RecMgr
    //VP3RecMgr::getInstance()->VP3RecMgrUpdate();

    // Write cycle/segment VP3 records
    //WriteVp3Records();

    // Publish scs output channels
    //PublishScsOutputs();

    return true;
}

void MTPCycleSegApp::cleanup()
{
    // Force all VP3 records to be written
    //WriteVp3Records(true);

    // Unregister from all dependent apps
    //UnregisterApps();

    // Peform model cleanup
    //CleanupModel();
}
