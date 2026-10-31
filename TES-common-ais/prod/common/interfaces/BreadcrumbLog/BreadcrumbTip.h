#include <interfaces/CoachingSummaryData/CoachingTipOutput.h>
#include "Breadcrumb.h"

#ifndef _BREADCRUMBTIP_H_
#define _BREADCRUMBTIP_H_

struct BreadcrumbTip : public Breadcrumb
{
    uint32_t tipNumber;
    float severity;
    float poissonValue;
    std::vector<float> stats;

    // Needed for serialization
    BreadcrumbTip() = default;

    BreadcrumbTip(GPSDataLinkParam::GpsPositionStatusType gpsStatus, float latitude, float longitude, uint32_t cycle,
                  const CoachingTipResult_t& tipResult) :
        Breadcrumb{BreadcrumbType::TIP, gpsStatus, latitude, longitude, cycle},
        tipNumber{tipResult.tipOutput.tipNumber},
        severity{tipResult.severity},
        poissonValue{tipResult.poissonValue},
        stats{tipResult.stat}
    {
    }

    template <class Archive>
    void serialize(Archive& ar, unsigned int version)
    {
        ar & boost::serialization::base_object<Breadcrumb>(*this);
        ar & tipNumber;
        ar & severity;
        ar & poissonValue;
        ar & stats;
    }

    void toJsonDerived(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const override
    {
        writer.Key("tipNumber"), writer.Uint(tipNumber);
        writer.Key("severity"), writer.Double(severity);
        writer.Key("poisson"), writer.Double(poissonValue);

        writer.Key("stats");
        writer.StartArray();
        for (auto stat : stats)
        {
            writer.Double(stat);
        }
        writer.EndArray();
    }
};

BOOST_CLASS_EXPORT_KEY(BreadcrumbTip)
BOOST_CLASS_VERSION(BreadcrumbTip, 1)

#endif
