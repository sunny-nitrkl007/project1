#ifndef _JSONABLE_H_
#define _JSONABLE_H_

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

class jsonable
{
public:
    virtual ~jsonable() {}
    virtual void toJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const = 0;
};
#endif
