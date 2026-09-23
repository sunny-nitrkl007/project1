#include "oel_timestamp.h"

oel_timestamp64_t oel_timestamp_get64()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    uint64_t ret = ts.tv_sec*1000+(ts.tv_nsec /1000000);

    //printf("sec: %ld , nsec: %ld\n", ts.tv_sec, ts.tv_nsec);

    return ret;
}

uint32_t oel_timestamp_get_freq()
{
    return 1000;
}

