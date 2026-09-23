/* stub for oel_timestamp.h */

#ifndef OEL_TIMESTAMP_H_
#define OEL_TIMESTAMP_H_

#include <time.h>
#include <stdint.h>
#include <stdio.h>

/* primary OEL timestamp data type */
typedef uint64_t oel_timestamp64_t;

oel_timestamp64_t oel_timestamp_get64();
uint32_t oel_timestamp_get_freq();

#endif /*OEL_TIMESTAMP_H_*/

