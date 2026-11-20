**CPM TES-Common-ais repo**

     This repository uses SCons as its build system.  A top level makefile provides easy to use 
     targets for building.

     This repo needs to be built with the 14.04-64 AIS development environment.  You
     will need the 5.1 VirtualBox VM (or equivalent) to build this project for the native target.

# Setup

     [CPM Super Project (SSP) Setup](doc/ssp_setup/README.md)

     [AIS Template App documentation](../eta-ais/README.md)

     [Building the SSP](doc/build_commands.md)

# Applications

     [CoachingTask](apps/CoachingTask/README)

     [XCP Server](apps/xcp_server/README)

# Interfaces

     [DataLinkData SCS Channel](prod/common/interfaces/DataLinkData/README.md)

# Components

     [Jhm2WsServer](prod/common/jhm2WsServer/README.md)

# TaskPlugins

     [DatalinkMgrToDld](prod/infrastructure/plugins/DatalinkMgrToDld/README.md)

     [DataLinkDataPublisher](prod/infrastructure/plugins/DataLinkDataPublisher/README.md) NOTE: For ACD2, DatalinkMgrToDld should be used instead

     [DataLinkDataReceiver](prod/infrastructure/plugins/DataLinkDataReceiver/README.md)

     [EthernetPgtServer](prod/infrastructure/plugins/EthernetPgtServer/README.md) NOTE: This functionality is included by default in ACD2

     [EthernetPortStatics](prod/infrastructure/plugins/EthernetPortStatistics/README.md) NOTE: This functionality is included by default in ACD2

