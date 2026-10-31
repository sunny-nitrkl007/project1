#ifndef JHM2KEYS_H
#define JHM2KEYS_H

#include <unordered_map>

#include <jhm2/Jhm2Param/Jhm2Msg.h>
#include <jhm2/Jhm2Param/Jhm2ParamMsgRequest.h>
#include <jhm2/Jhm2WebSockets/Jhm2WebSocketRequest.h>

namespace jhm2 {
    // Common
    static constexpr auto PARAMSREQUESTED_KEY = "paramsRequested";
    static constexpr auto COMMANDREQUESTED_KEY = "commandRequested";
    static constexpr auto FILEREQUESTED_KEY = "fileRequested";

    // Request
    static constexpr auto QUERY_STRINGS_KEY = "queryStrings";
    static constexpr auto REQUEST_TYPE_KEY = "requestType";
    static constexpr auto WS_REQUEST_TYPE_KEY = "wsRequestType";
    static constexpr auto RATE_SEC_KEY = "rateSec";

    // Response
    static constexpr uint32_t HTTP_STATUS_CODE_OK = 200;
    static constexpr uint32_t HTTP_STATUS_CODE_NO_CONTENT = 204;
    static constexpr uint32_t HTTP_STATUS_CODE_BAD_REQUEST = 400;
    static constexpr uint32_t HTTP_STATUS_CODE_INTERNAL_SERVER_ERROR = 500;

    static constexpr auto RESPONSE_TYPE_KEY = "responseType";
    static constexpr auto HTTP_STATUS_CODE_KEY = "httpStatusCode";
    static constexpr auto BODY_KEY = "body";

    inline Jhm2WebSocketRequest::Jhm2WsRequestType getWsRequestType(const std::string& requestType)
    {
        const std::unordered_map<std::string, Jhm2WebSocketRequest::Jhm2WsRequestType> EnumLookup {
            { "Unknown", Jhm2WebSocketRequest::WS_REQUEST_UNKNOWN },
            { "Add", Jhm2WebSocketRequest::WS_REQUEST_ADD },
            { "Remove", Jhm2WebSocketRequest::WS_REQUEST_REMOVE },
            { "Cancel", Jhm2WebSocketRequest::WS_REQUEST_CANCEL }
        };

    auto   it  = EnumLookup.find(requestType);
    return it == EnumLookup.end() ? Jhm2WebSocketRequest::WS_REQUEST_UNKNOWN : it->second;
    }

    inline Jhm2ParamMsgRequest::eRequestType getJhm2RequestType(const std::string& requestType)
    {
        const std::unordered_map<std::string, Jhm2ParamMsgRequest::eRequestType> EnumLookup {
            { "Invalid", Jhm2ParamMsgRequest::INVALID_REQUEST },
            { "ParameterRequest", Jhm2ParamMsgRequest::PARAMETER_MSG_REQUEST },
            { "ImageRequest", Jhm2ParamMsgRequest::IMAGE_MSG_REQUEST },
            { "CommandRequest", Jhm2ParamMsgRequest::COMMAND_MSG_REQUEST },
            { "ResetRequest", Jhm2ParamMsgRequest::RESET_MSG_REQUEST },
            { "ChannelUpdate", Jhm2ParamMsgRequest::CHANNEL_UPDATE_REQUEST },
            { "HardwareClockUpdate", Jhm2ParamMsgRequest::HARDWARE_CLOCK_UPDATE_REQUEST },
            { "FileRequest", Jhm2ParamMsgRequest::FILE_MSG_REQUEST },
            { "ParameterRequest2", Jhm2ParamMsgRequest::PARAMETER_MSG_REQUEST_2 },
            { "CommandRequest2", Jhm2ParamMsgRequest::COMMAND_MSG_REQUEST_2 }
        };

    auto   it  = EnumLookup.find(requestType);
    return it == EnumLookup.end() ? Jhm2ParamMsgRequest::INVALID_REQUEST : it->second;
    }

    inline const char* jhm2RequestTypeToCstr(Jhm2ParamMsgRequest::eRequestType requestType)
    {
        const std::unordered_map<uint8_t, const char*> EnumLookup {
            { Jhm2ParamMsgRequest::INVALID_REQUEST, "Invalid" },
            { Jhm2ParamMsgRequest::PARAMETER_MSG_REQUEST, "ParameterRequest" },
            { Jhm2ParamMsgRequest::IMAGE_MSG_REQUEST, "ImageRequest" },
            { Jhm2ParamMsgRequest::COMMAND_MSG_REQUEST, "CommandRequest" },
            { Jhm2ParamMsgRequest::RESET_MSG_REQUEST, "ResetRequest" },
            { Jhm2ParamMsgRequest::CHANNEL_UPDATE_REQUEST, "ChannelUpdate" },
            { Jhm2ParamMsgRequest::HARDWARE_CLOCK_UPDATE_REQUEST, "HardwareClockUpdate" },
            { Jhm2ParamMsgRequest::FILE_MSG_REQUEST, "FileRequest" },
            { Jhm2ParamMsgRequest::PARAMETER_MSG_REQUEST_2, "ParameterRequest2" },
            { Jhm2ParamMsgRequest::COMMAND_MSG_REQUEST_2, "CommandRequest2" }
        };

    auto   it  = EnumLookup.find(requestType);
    return it == EnumLookup.end() ? EnumLookup.at(Jhm2ParamMsgRequest::INVALID_REQUEST) : it->second;
    }
}

#endif
