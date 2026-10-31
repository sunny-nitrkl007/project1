///////////////////////////////////////////////////////////////////////////////
/// @file      Jhm2MsgHeader.h
/// @author    strubjc
/// @date      Mar 19, 2013
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2012 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JHM2MSGHEADER_H_
#define JHM2MSGHEADER_H_

struct Jhm2MsgHeader
{
    Jhm2MsgHeader() { }

    uint32_t length;
    uint32_t updateId;
    uint32_t dataLength;

    uint32_t totalLength() const
    {
        return sizeof(Jhm2MsgHeader) + dataLength;
    }

} __attribute__((packed)); // Have the compiler pack the structure to save space



#endif /* JHM2MSGHEADER_H_ */
