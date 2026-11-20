///////////////////////////////////////////////////////////////////////////////
// @attention COPYRIGHT (C) 2011-2011 CATERPILLAR INC. ALL RIGHTS RESERVED.
//
// @file    EthernetPgtServerTest.h
//
// @brief   This is the definition include file for the module.
///////////////////////////////////////////////////////////////////////////////
#ifndef EthernetPgtServerTest_H_
#define EthernetPgtServerTest_H_

///////////////////////////////////////////////////////////////////////////////
// -- #Include's --
///////////////////////////////////////////////////////////////////////////////
#include <memory>
#include <vector>

#include <ais/task/Task.h>

#include <commTask/commTask.h>

#include <taskPlugins/base/TaskPluginMgr.h>

///////////////////////////////////////////////////////////////////////////////
// -- #Define, Struct's, Typedef's, Enum's --
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// -- Class Definition
///////////////////////////////////////////////////////////////////////////////
class EthernetPgtServerTest: public task::Task, public commTask, public TaskPluginMgr
{
   public:
      explicit EthernetPgtServerTest( const std::string& taskName );
      virtual ~EthernetPgtServerTest( );

      bool initialize(void) override;
      bool executive(void) override;
      void cleanup(void) override;

   protected:
      static void oelUpdate();
      static EthernetPgtServerTest& getInstance();

      // TaskPluginMgr
      bool addPlugins() override;
      static bool m_initDone;

      std::vector<void*> oelInitFunctions;
      std::vector<void*> oelUpdateFunctions;
};

#endif
