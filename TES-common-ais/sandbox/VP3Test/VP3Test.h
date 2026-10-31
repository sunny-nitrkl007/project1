#ifndef _VP3Test_H_
#define _VP3Test_H_
#include "../VP3Test/VP3Test.h"

#include <ais/task/Task.h>
#include <interfaces/ShmClock/InterfaceTypes.h>

class VP3Test : public task :: Task
{
public:
   VP3Test(const std::string& taskName );
   virtual ~VP3Test();
   virtual bool initialize( );
   virtual bool executive( );
   virtual void cleanup( );


protected:
private:
   ShmClockOutput* outShm;
};

#endif /* _RIPPERTEST_H_ */
