#ifndef _COACHINGTASKWSINTERFACE_H_
#define _COACHINGTASKWSINTERFACE_H_

#include <string>
#include <vector>

namespace coaching_task
{

enum GrpId : uint32_t
{
    GRP_ID_SUMMARY = 0,
    GRP_ID_3X3 = 1,
    GRP_ID_BREADCRUMB = 2,
    GRP_ID_SHOW_HIDE_STATUS = 3,
    GRP_ID_SIZE = 4,
    GRP_ID_NOT_FOUND = GRP_ID_SIZE
};

/*
 * Handles local caching
 */
class IWsApp
{
public:
    virtual ~IWsApp(){};

    /*
     * Force a send of data associated with grpId
     * This will block.
     */
    virtual void sendData(GrpId grpId) = 0;

    /*
     * Sets the publish rate (in millisecond) for the provided data
     */
    virtual void setPublishRate(GrpId grpId, uint32_t intervalMs) = 0;

    /*
     * Sets the Operator Id to the provided value
     */
    virtual void setOperatorId(const std::string& operatorId) = 0;

    /*
     * Sets Tip On/Off
     */
    virtual void setOpTipOnOff(bool tipOn, uint32_t tipNumber) = 0;

    /*
     * Sets Tip Show/Hide
     */
    virtual void setSysTipShowHide(bool showTip, uint32_t tipNumber) = 0;

    /*
     * Sets Tip Auto Enable Time
     */
    virtual void setTipAutoEnableTime(int64_t tipAutoEnableTimeSeconds) = 0;

    /*
     * Sets Tip Auto Enable Time
     */
    virtual void setElapsedTimeSec(int64_t elapsedTimeSec) = 0;

    /*
     * Sets Breadcrumb Records
     */
    virtual void setBreadcrumbRequestedRecords(size_t BreadcrumbRequestedRecords) = 0;

    /*
     * Sets Breadcrumb GPS-Time Seconds
     */
    virtual void setBreadcrumbGpsTimeSeconds(size_t BreadcrumbGpsTimeSeconds) = 0;

    /*
     * Sets Breadcrumb GPS-Distance Meters
     */
    virtual void setBreadcrumbGpsDistanceMeters(size_t BreadcrumbGpsDistanceMeters) = 0;

    /*
     * Notification that a tutorial was viewed for the provided tip
     */
    virtual void setTutorialViewed(uint32_t tipNumber) = 0;

    /*
     * Notification that a tip was viewed for the provided tip
     */
    virtual void setTipViewed(uint32_t tipNumber) = 0;

    /*
     * Notification that a tip is INCREMENTED  ONLY for TESTING
     *      */
    virtual void setTipIncrement(uint32_t tipNumber) = 0;

    /*
     * Notification that a tip is DECREMENTED  ONLY for TESTING
     *      */
    virtual void setTipDecrement(uint32_t tipNumber) = 0;

    /*
     * reset
     */
    virtual void resetStats() = 0;
};

} // namespace coaching_task

#endif
