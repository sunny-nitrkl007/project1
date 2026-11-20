#ifndef BMIETH_H
#define BMIETH_H

#include <ais/task/Task.h>
#include "interfaces/AppReg/InterfaceTypes.h"

class BmiEth: public task::Task
{
public:
	BmiEth( const std::string& taskName );
   virtual ~BmiEth( );

   virtual bool initialize( );
   virtual bool executive( );
   virtual void cleanup( );
   void UpdateRegistrations();

protected:

private:
   uint32_t pgtClientFidA6N2;
   uint32_t ClientSessionTimeout;
   BmiEthWrapper EthWrapper;

   //Regitration.
   AppRegStorage AppRegList;
   AppRegInput *AppRegInput_;
   AppRegOutput  *AppRegOutput_;

};

#endif //BMIETH_H
