///////////////////////////////////////////////////////////////////////////////
/// @file      Jhm2ChannelData.h
/// @author    strubjc
/// @date      Dec 15, 2015
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2015 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JHM2CHANNELDATA_H_
#define JHM2CHANNELDATA_H_

#include <jhm2/Jhm2Param/Jhm2Msg.h>
#include <jhm2/jsonCommon/JsonObjectSerializer.h>
#include <jhm2/jsonCommon/JsonSerializer.h>
#include <jhm2/jsonCommon/JsonOutStream.h>
#include <jhm2/jsonCommon/JsonIosBase.h>
#include <jhm2/JsonableInterfaceFactory/JsonableInterfaceFactory.h>


class Jhm2Channel
{
  public:
    Jhm2Channel(const std::string& name, Jsonable* channel): m_name(name), m_data( channel ) {}
    virtual ~Jhm2Channel() {}

    virtual void jsonSerialize( JsonIosAbstractBase& json )
    {
      json("Name", m_name);
      json("Data", m_data);
    }

  private:
    std::string m_name;
    Jsonable* m_data;
};

class Jhm2ChannelData: public Jhm2Msg
{
  public:
    Jhm2ChannelData (): m_jostream()
    {
      //Start the response on construction
      m_jostream.responseStart( "ChannelDataResponse" );
      m_jostream.String("ChannelList");
      m_jostream.StartArray();
    }
    Jhm2ChannelData (const Jhm2ParamMsgRequest::ReqDataT& channels, jhm2::JsonableInterfaceFactory& inputData): m_jostream()
    {
      //Start the response on construction
      m_jostream.responseStart( "ChannelDataResponse" );
      m_jostream.String("ChannelList");
      m_jostream.StartArray();
      addChannels(channels,inputData);
    }
    virtual ~Jhm2ChannelData() {}


    bool add( const std::string& channelName, Jsonable* channel)
    {
      if (channel)
      {
        Jhm2Channel channelToSend(channelName, channel);
        //Hack to get a serialized object without the key for insertion correctly into array
        jhm2::json::JsonSerializer<Jhm2Channel>::serialize(m_jostream, channelToSend);

        return true;
      }

      return false;
    }

    bool add( const std::string& channelName, jhm2::JsonableInterfaceFactory& inputData )
    {
      Jsonable* channel = inputData.getIntf(channelName);
      return add(channelName, channel);
    }

    void addChannels( const Jhm2ParamMsgRequest::ReqDataT& channels, jhm2::JsonableInterfaceFactory& inputData )
    {
      for ( Jhm2ParamMsgRequest::ReqDataT::const_iterator it = channels.begin(); it != channels.end(); ++it )
      {
        add(*it, inputData);
      }
      doneAddingDatums();
    }


    void doneAddingDatums()
    {
      //End the array
      m_jostream.EndArray();
      //End the response
      m_jostream.responseEnd();
    }

    virtual bool getJson( std::ostream& out )
    {
      out << m_jostream;
      return true;
    }

  protected:
    JsonOutStream m_jostream;
};

#endif /* JHM2CHANNELDATA_H_ */
