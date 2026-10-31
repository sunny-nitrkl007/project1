#ifndef BMIETHUTIL_H
#define BMIETHUTIL_H

#include <ifaddrs.h>

namespace tes_common_ais
{

namespace bmi_ethernet_util {

constexpr uint32_t BMI_ETH_INVALID_IP = 0;

uint32_t GetIpAddressInt(std::string ifaName= "eth0.20");
std::string GetIpAddressString(std::string ifaName = "eth0.20", int32_t saFamily = AF_INET);
uint32_t IpAddressToInt (const char * ip);

}
}

#endif //BMIETHUTIL_H
