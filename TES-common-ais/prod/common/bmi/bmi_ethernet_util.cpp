
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/if_link.h>
#include <string.h>
#include <ais/task/Task.h>

#include "bmi_ethernet_util.h"

using namespace std;

namespace tes_common_ais
{
namespace bmi_ethernet_util {

uint32_t GetIpAddressInt(string ifaName)
{
    string ipStr = GetIpAddressString(ifaName);
    uint32_t ipInt = IpAddressToInt(&ipStr[0]);
    if (ipInt == BMI_ETH_INVALID_IP)
    {
        AIS_LOG_ERROR("Failed to read IP Address from local target.");
    }
    else
    {
        AIS_LOG_NOTICE("%s is 0x%08x\n", ipStr.c_str(), ipInt);
    }

    return ipInt;
}

string GetIpAddressString(string ifaName, int32_t saFamily)
{
    string retIpString = "0";
    struct ifaddrs * ifAddrStruct = NULL;
    struct ifaddrs * ifa = NULL;
    void * tmpAddrPtr = NULL;
    int32_t family;

    if (getifaddrs(&ifAddrStruct) == -1)
    {
        AIS_LOG_ERROR("Failed to get address from local target.");
        return retIpString;
    }

    bool ethNameAndFamilyFound = false;

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (!ifa->ifa_addr)
        {
            continue;
        }

        family = ifa->ifa_addr->sa_family;

        AIS_LOG_NOTICE("%-8s %s (%d)\n", ifa->ifa_name,
                (family == AF_PACKET) ? "AF_PACKET" :
                (family == AF_INET) ? "AF_INET" :
                (family == AF_INET6) ? "AF_INET6" : "???",
                family);
        AIS_LOG_NOTICE("%-8s %s (%d)\n", ifa->ifa_name,
                (family == AF_PACKET) ? "AF_PACKET" :
                (family == AF_INET) ? "AF_INET" :
                (family == AF_INET6) ? "AF_INET6" : "???",
                family);

        if (strcmp(ifa->ifa_name, &ifaName[0]) == 0  && family == saFamily)
        {
            ethNameAndFamilyFound = true;

            if (saFamily == AF_INET)
            {
                tmpAddrPtr = &((struct sockaddr_in *) ifa->ifa_addr)->sin_addr;
                char addressBuffer[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
                AIS_LOG_NOTICE("%s AF_INET-IP Address %s\n", ifa->ifa_name, addressBuffer);
                AIS_LOG_NOTICE("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
                retIpString = addressBuffer;
            }
            else if (saFamily == AF_INET6)
            {
                tmpAddrPtr = &((struct sockaddr_in6 *) ifa->ifa_addr)->sin6_addr;
                char addressBuffer[INET6_ADDRSTRLEN];
                inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
                AIS_LOG_NOTICE("%s AF_INET6-IP Address %s\n", ifa->ifa_name, addressBuffer);
                AIS_LOG_NOTICE("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
                retIpString = addressBuffer;
            }
            else
            {
                AIS_LOG_ERROR("Ethernet IP Family not matched.");
            }
        }
    }

    if(false == ethNameAndFamilyFound)
    {
        AIS_LOG_ERROR("Ethernet IP Name/Family not found.");
    }

    freeifaddrs(ifa);

    return retIpString;
}

uint32_t IpAddressToInt (const char * ip)
{
    /* The return value. */
    uint32_t v = 0;
    /* The count of the number of bytes processed. */
    int32_t i;
    /* A pointer to the next digit to process. */
    const char * start;

    start = ip;
    for (i = 0; i < 4; i++) {
        /* The value of this byte. */
        int32_t n = 0;
        while (1) {
            /* The digit being processed. */
            char c = * start;
            start++;
            if (c >= '0' && c <= '9') {
                n *= 10;
                n += c - '0';
            }
            /* We insist on stopping at "." if we are still parsing
               the first, second, or third numbers. If we have reached
               the end of the numbers, we will allow any character. */
            else if ((i < 3 && c == '.') || i == 3) {
                break;
            }
            else {
                return BMI_ETH_INVALID_IP;
            }
        }
        if (n >= 256) {
            return BMI_ETH_INVALID_IP;
        }
        v *= 256;
        v += n;
    }
    return v;
}

}
}