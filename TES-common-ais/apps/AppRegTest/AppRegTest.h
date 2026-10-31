#ifndef APPREGTEST_H
#define APPREGTEST_H

#ifndef Task_h
#include <ais/task/Task.h>
#endif

#include <interfaces/AppReg/InterfaceTypes.h>

typedef enum
{
	RET_SUCCESS = 0,
	RET_ERROR
}Ret_t;


class AppRegTest: public task::Task
{
public:
    AppRegTest( const std::string& taskName );
    virtual ~AppRegTest( );

    virtual bool initialize( );
    virtual bool executive( );
    virtual void cleanup( );
protected:
private:

	AppRegInput  *AppRegInput_;
	AppRegOutput *AppRegOutput_;

	std::string AppName;
    std::string DestAppName;
    bool AppRegistered;
    unsigned int keyOffTimeOutMSec;
    bool ShutdownRequested;

    //This line probably defined as non-pointer object.
    AppRegStorage *RegInst;

    void PrintAppRegistrations(void);
    void UpdateRegistrations(void);
};

#endif //APPREGTEST_H
