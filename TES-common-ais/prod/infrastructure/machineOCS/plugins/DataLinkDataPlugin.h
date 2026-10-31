#ifndef _DataLinkDataPlugin_h_
#define _DataLinkDataPlugin_h_

#include <unordered_map>

#include <FL/Fl_Group.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Tabs.H>

#include <interfaces/DataLinkData/InterfaceTypes.h>
#include <taskPlugins/interfaces/DatalinkParameterDataInterface.h>

#include <plugins/Executable.h>
#include <machineOCS/MachineOCS.h>
#include <plugins/Widget.h>

#include "DataLinkDataWidget.h"


namespace OCS
{
  class DataLinkDataPlugin : public Fl_Group, public Widget, public Executable
  {
  public:
    DataLinkDataPlugin();
    ~DataLinkDataPlugin();

    virtual bool initializeWidget(const ConfigSection &cs);
    virtual bool executive();

  protected:
    Fl_Tabs* tabs;
    Fl_Pack* pack;
    Fl_Group* group;

    struct DataLinkDataDisplayType
    {
      Fl_Widget* gui;
      TimeStamp lastUpdate;
    };

    typedef std::unordered_map<datalink::RxParameterKey, DataLinkDataDisplayType, datalink::RxParameterKeyHash> WidgetsDataLinkDataMap;
    typedef WidgetsDataLinkDataMap::iterator WidgetsDataLinkDataMapIterator;
    typedef std::pair<datalink::RxParameterKey, DataLinkDataDisplayType> WidgetsDataLinkDataMapEntry;
    WidgetsDataLinkDataMap m_widgetsMap;

    DataLinkDataInput* m_pDataLinkDataInput;

    void processDataLinkData();
    WidgetsDataLinkDataMapIterator createNewDataLinkDataWidget(const std::string& name, const datalink::RxParameterKey& key);

    std::string vec2hexStr(const std::vector<uint8_t> &vec, bool msbFirst);

    pthread_mutex_t dataLinkDataLock;
  };
}

#endif




