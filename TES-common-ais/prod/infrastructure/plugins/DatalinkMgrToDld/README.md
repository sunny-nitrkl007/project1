**DataLinkMgrToDld Plugin**

  Works with ACD2 DataLinkManager, pulls all received Parameters out of DataLinkManager and publishes DataLinkData scs object

# Installation
  Add the following to the top of Acd2Task.cpp:

  #include <plugins/DatalinkMgrToDld/DatalinkMgrToDld.h>

  Add the folowing to Acd2Task::addPlugins(), in the "Application specific plugins" section 
    addPlugin<DatalinkMgrToDld>(*m_pDatalinkManager);
