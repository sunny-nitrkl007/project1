///////////////////////////////////////////////////////////////////////////////
/// @file      Jhm2Msg.h
/// @author    strubjc
/// @date      Oct 20, 2015
/// @brief     Base type for Jhm2 Response message
///
///
/// @attention COPYRIGHT (C) 2015 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JHM2MSG_H_
#define JHM2MSG_H_

#include "Jhm2ParamMsgRequest.h" //For eOutputFormat

class Jhm2Msg {
public:
    Jhm2Msg() {}
    virtual ~Jhm2Msg() {}

    virtual bool getResponse(const Jhm2ParamMsgRequest::eFormat& format, std::ostream& out) {
        switch ( format )
        {
        case Jhm2ParamMsgRequest::XML_FORMAT: return getXml( out );
        case Jhm2ParamMsgRequest::JPG_FORMAT: return getJpg( out );
        case Jhm2ParamMsgRequest::JSON_FORMAT: return getJson( out );
        case Jhm2ParamMsgRequest::JSON_FORMAT_2: return getJson2(out);
        default: break;
        }
        return false;
    }

protected:
    virtual bool getXml(std::ostream& out) const {
        return false;
    }

    virtual bool getJpg(std::ostream& out) const {
        return false;
    }

    virtual bool getJson(std::ostream& out) const {
        return false;
    }

    virtual bool getJson2(std::ostream& out) const {
        return false;
    }
};



#endif /* JHM2MSG_H_ */
