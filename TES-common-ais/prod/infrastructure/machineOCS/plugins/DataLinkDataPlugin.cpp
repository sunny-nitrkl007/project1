#include <ais/PluginProcessor/PluginDefine.h>

#include "DataLinkDataPlugin.h"
#include "ais/util/stringUtils.h"
#include <sstream>

using namespace std;
using namespace OCS;
using namespace task;

///////////////////////////////////////////////////////////////////////////////
/// @brief Constructor.  Set up member vars and init mutex lock
///
/// @param cs 
/// 
/// 
///////////////////////////////////////////////////////////////////////////////
DataLinkDataPlugin::DataLinkDataPlugin() : Fl_Group(0, 0, 400, 3000), Widget(),
  tabs(nullptr), pack(nullptr), group(nullptr), 
  m_widgetsMap(), m_pDataLinkDataInput(nullptr)
{
  pthread_mutex_init(&dataLinkDataLock, nullptr);
}

///////////////////////////////////////////////////////////////////////////////
/// @brief destroy mutex
///
/// 
///////////////////////////////////////////////////////////////////////////////
DataLinkDataPlugin::~DataLinkDataPlugin()
{
  pthread_mutex_destroy(&dataLinkDataLock);
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Create FLTK gui elements, set up input interface to 
/// receive DataLinkDataMessagse
///
/// @return  true if successful in setting up input interface
///////////////////////////////////////////////////////////////////////////////
bool DataLinkDataPlugin::initializeWidget(const ConfigSection &cs)
{
  m_pDataLinkDataInput = dynamic_cast<DataLinkDataInput*>( InterfaceDb::fetch("DataLinkDataInput"));
  if (!m_pDataLinkDataInput) 
  {
    AIS_LOG_ERROR("Failed to create DataLinkDataInput");
    return false;
  }
  // Set up GUI here
  tabs = new Fl_Tabs(0, 0, 400, 3000);  // create this tab
  pack = new Fl_Pack(5, 20, 350, 50);  // create a pack to hold the m_widgetsMap
  group = new Fl_Group(5, 20, 350, 3000, "     DataLinkData Monitor    ");
  add(tabs);
  // End of GUI work

  return true;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Update GUI
///
/// @return  always true
///////////////////////////////////////////////////////////////////////////////
bool DataLinkDataPlugin::executive()
{
  Fl::lock();
  processDataLinkData();
  Fl::unlock();

  return true;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Update the gui based in the current list of messages to process
///////////////////////////////////////////////////////////////////////////////
void DataLinkDataPlugin::processDataLinkData()
{
  PThreadLocker lock(&dataLinkDataLock);
  DataLinkData dlData;
  while (m_pDataLinkDataInput->get(dlData))
  {
    const auto& dlMap = dlData.GetDataLinkDataMap();
    for (const auto& dlParamPair : dlMap)
    {
      for (const auto& dlParam : dlParamPair.second)
      {
        // search for DataLinkData key in our map
        auto sourceId = dlParam.GetSid();
        auto paramId = dlParam.GetParamId();

        using namespace datalink;

        auto paramIdType = dlParam.GetParamIdentifierType();
        auto parameterType = (paramIdType == DataLinkParam::DATA_LINK_PARAM_IDENTIFIER_PID) ? ParameterType::PID :
                             (paramIdType == DataLinkParam::DATA_LINK_PARAM_IDENTIFIER_PUBLIC_PGN) ? ParameterType::PGN :
                             (paramIdType == DataLinkParam::DATA_LINK_PARAM_IDENTIFIER_CAT_EXT) ? ParameterType::CAT_EXT_ID :
                             (paramIdType == DataLinkParam::DATA_LINK_PARAM_IDENTIFIER_SPN) ? ParameterType::SPN :
                             (paramIdType == DataLinkParam::DATA_LINK_PARAM_IDENTIFIER_CDA) ? ParameterType::CDA :
                             ParameterType::NA;

        auto datalinkType = dlParam.GetDataLinkType();
        auto datalinkProtocol = (datalinkType == DataLinkParam::DATA_LINK_PARAM_CDL) ? DatalinkProtocol::CDL : 
                                (datalinkType == DataLinkParam::DATA_LINK_PARAM_CAN1_1939) ? DatalinkProtocol::J1939 : 
                                (datalinkType == DataLinkParam::DATA_LINK_PARAM_CAN2_1939) ? DatalinkProtocol::J1939 :
                                (datalinkType == DataLinkParam::DATA_LINK_PARAM_ETH) ? DatalinkProtocol::ETHERNET_PGT :
                                (datalinkType == DataLinkParam::DATA_LINK_PARAM_CDA) ? DatalinkProtocol::CDA :
                                DatalinkProtocol::NA;
        datalink::RxParameterKey key{datalink::ParameterKey{paramId, parameterType}, datalinkProtocol, sourceId};

        WidgetsDataLinkDataMapIterator ctr;

        //look for key
        bool gotIt = false;
        for (ctr = m_widgetsMap.begin(); ctr != m_widgetsMap.end(); ++ctr ) 
        {
          if ( (*ctr).first == key )
          {
            gotIt = true;
            break;
          }
        }

        // Name widget base on PID # & Source ID (since key contains more info)
        DataLinkDataWidget* widget {nullptr};
        stringstream ssName;
        ssName << c_str(parameterType) << " 0x" << std::uppercase << std::hex << paramId << " (SID 0x" << std::uppercase << std::hex << sourceId << ")";
        if (!gotIt) 
        {
          // Name widget based on Name if it is not blank, otherwise use PID
          auto& paramName = dlParam.GetParamName();
          std::string widgetName;
          if (paramName.size() > 0)
          {
            widgetName = paramName;
          }
          else
          {
            widgetName = ssName.str();
          }
          // NEED TO ADD NEW Widget
          WidgetsDataLinkDataMapIterator newEntry = createNewDataLinkDataWidget(widgetName, key);
          (*newEntry).second.lastUpdate = dlData.getTransmissionTime();
          widget = dynamic_cast<DataLinkDataWidget*>((*newEntry).second.gui);
        }
        else
        {
          // Update diagnostics on this widget
          (*ctr).second.lastUpdate = dlData.getTransmissionTime();
          widget = dynamic_cast<DataLinkDataWidget*>((*ctr).second.gui);
        }
      
        if(widget != nullptr)
        {
          // Update dlParam data
          widget->color(FL_BACKGROUND_COLOR);
          widget->paramId->value(ssName.str().c_str());
          widget->dlType->value(dlParam.GetDataLinkTypeCstr());
          if (dlParam.GetParameterType() == DataLinkParamInfo::CDL2_DOUBLE)
          {
            widget->lastValueEng->value(dlParam.GetLastValueDouble());
          }
          else
          {
            widget->lastValueEng->value(dlParam.GetLastValueEng());
          }
          widget->dsi->value(dlParam.GetLastValueDsi());
          stringstream ssSid;
          ssSid << "0x" << std::setfill ('0') << std::setw(2) << std::uppercase << std::hex << dlParam.GetSid();
          widget->sid->value(ssSid.str().c_str());
          widget->paramIdType->value(dlParam.GetParamIdTypeCstr());
          widget->paramType->value(dlParam.GetParameterTypeCstr());
          widget->units->value(dlParam.GetUnitsCstr());
          widget->varLengthParamType->value(VarLengthDataLinkParamFactory::GetVarLengthParamTypeString(dlParam.GetVarLengthParamType()).c_str());
          // Fixed length PIDs are stored LSB first, variable length are in byte order (MSB first)
          bool msbFirst = dlParam.GetParameterType() == CDL2_VAR_NO_DSI ? true : false;
          widget->lastValueRaw->value(vec2hexStr(dlParam.GetLastValueVector(), msbFirst).c_str());
        }
        else
        {
          AIS_LOG_ERROR("widget '%s' is NULL", ssName.str().c_str());
        }
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Create a new DataLinkDataWidget for the message
///
/// @param [in] name - name for the widget
/// @param [in] key - RxParameterKey&
///////////////////////////////////////////////////////////////////////////////
DataLinkDataPlugin::WidgetsDataLinkDataMapIterator DataLinkDataPlugin::createNewDataLinkDataWidget(const std::string& name, const datalink::RxParameterKey& key)
{

  AIS_LOG_INFO(" ---> Making widget for '%s'\n", name.c_str());

  Fl_Widget* widget;
  // Add DataLinkDataWidget, manually tweak height value
  DataLinkDataWidget* w1 = new DataLinkDataWidget(0, 0, 335, 286, name.c_str());
  w1->resizable(NULL); // don't resize the widgets when collapsed
  w1->open(false); // start collapsed

  widget = dynamic_cast<Fl_Widget*>(w1);
  std::string *widgetString = new std::string(name);
  std::transform(widgetString->begin(), widgetString->end(), widgetString->begin(), ::tolower);
  widget->label(widgetString->c_str());
  DataLinkDataDisplayType dlDataType;
  dlDataType.gui = widget;

  auto entered = m_widgetsMap.insert(WidgetsDataLinkDataMapEntry(key, dlDataType));

  if (entered.second == false)
  {
    AIS_LOG_WARN("Element '%s' was already added  - do not add again\n", name.c_str());
    delete w1; 
  }
  else 
  {
    bool added=false;
    //do an insertion sort
    for(int idx=0;idx<pack->children();idx++)
    {
      Fl_Widget* aWidget = pack->child(idx);
      if(*widgetString < string(aWidget->label()))
      {
        pack->insert(*widget,idx);
        group->add(pack);

        tabs->add(group);
        // remove the tab and then add it again
        remove(tabs);
        add(tabs);
        added=true;
        break;
      }
    }
    if(!added)
    {
      pack->add(widget);
      group->add(pack);

      tabs->add(group);
      // remove the tab and then add it again
      remove(tabs);
      add(tabs);
    }
  }

  return entered.first;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Convert uint8_t vector to a hex string
///
/// @param [in] vec
/// @param [in] msbFirst
///
/// @return string
///////////////////////////////////////////////////////////////////////////////
std::string DataLinkDataPlugin::vec2hexStr(const std::vector<uint8_t> &vec, bool msbFirst)
{
  static const char *digits = "0123456789ABCDEF";
  size_t hex_len = vec.size() << 1;
  std::string rc(hex_len, '0');
  if (msbFirst)
  {
    for (size_t i = 0, j = 0; i < hex_len; i += 2, j++)
    {
      rc[i] = digits[(vec[j] >> 4) & 0x0F];
      rc[i + 1] = digits[(vec[j]) & 0x0F];
    }
  }
  else
  {
    for (size_t i = 0, j = vec.size() - 1; i < hex_len; i += 2, j--)
    {
      rc[i] = digits[(vec[j] >> 4) & 0x0F];
      rc[i + 1] = digits[(vec[j]) & 0x0F];
    }
  }
  
  return "0x" + rc;
}

RegisterPlugin(DataLinkDataPlugin, interfaces::Interface, DataLinkDataPlugin);