**PartNumbersPublisher Plugin**

  Works with ACD2 DatalinkManager, publishes PartNumbers SCS objects

# Installation
  Add the following to the top of Acd2Task.cpp:

  #include <plugins/DatalinkMgrToDld/PartNumbersPublisher.h>

  Add the folowing to Acd2Task::addPlugins(), in the "Application specific plugins" section 
    addPlugin<PartNumbersPublisher>(*m_pDatalinkManager);
