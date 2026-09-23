#ifndef DATALINKDATAPUBLISH_H_
#define DATALINKDATAPUBLISH_H_

#include <ais/task/Task.h>
#include <commTask/commTask.h>

#include <interfaces/DataLinkData/InterfaceTypes.h>
#include <interfaces/DemoAppTxChannel/InterfaceTypes.h>
#include <interfaces/DemoAppReqstChannel/InterfaceTypes.h>

class  DemoApp: public task::Task
{
public:
    DemoApp( const std::string& taskName );
    virtual ~ DemoApp( );

    virtual bool initialize( );
    virtual bool executive( );
    virtual void cleanup( );

protected:
    DataLinkData dlData_;
    DataLinkDataOutput* dataLinkDataOutput_;

private:
    DemoAppTxChannelInput  *DemoAppScsTxIn;
    DemoAppTxChannelOutput *DemoAppScsTxout;
    DemoAppReqstChannelInput *DemoAppScsReqstIn;

    DataLinkParam hydtempparam;
    DataLinkParam seainstallparam;
    DataLinkParam linkageparam;
    DataLinkParam toolparam;
    DataLinkParam prodparam;
    DataLinkParam engineSpeedParam;
    DataLinkParam serviceModeParam;
    DataLinkParam totalFuelUsedHrParam;
    DataLinkParam totalFuelUsedLrParam;

    uint32_t hyd_temp_value = 60;
    uint32_t tool_config = 371;
    uint32_t linkage_config = 52;
    uint32_t sea_level_2 = 16;
    uint32_t production_measurement = 12;
    uint32_t total_fuel_used_ = 80000;
    uint32_t fuelPeriodCount_ = 12;



    float liftposition_;
    float liftposition_rate_;
    float tiltposition_;
    float tiltposition_rate_;
    float payload_;
    float payload_rate_;

    void InitDataLinkData();
    void PublishDataLinkData();
    void ReadDemoAppScsIn();
    void ReadPWM_API();

    void updateTotalFuel() {
        ++fuelPeriodCount_;
        if (fuelPeriodCount_ >= 12) {
            fuelPeriodCount_ = 0;
            total_fuel_used_ = total_fuel_used_ + 1;
        }
    }
};



#endif
