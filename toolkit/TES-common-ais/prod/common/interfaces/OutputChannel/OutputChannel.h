#include <ais/serialization/Datum.h> // For Boost serialization
#include <vector>
#include <boost/serialization/vector.hpp>

#ifndef _OutputChannel_h_
#define _OutputChannel_h_

class OutputChannelStorage : public csvable
{
public:

   enum Port
   {
      OUTPUT_SINK_1, // OUTPUT_APP_PORT_SINK1_PIN31_GPIO86
      OUTPUT_SINK_2, // OUTPUT_APP_PORT_SINK2_PIN30_GPIO87
      OUTPUT_SINK_3, // OUTPUT_APP_PORT_SINK3_PIN29_GPIO88
      /*If any ports added,add above this comment*/
      OUTPUT_SINK_COUNT,
   };

   enum State
   {
      PORT_OFF = 0,
      PORT_ON = 1,
   };

   enum ChangeDuration
   {
      NO_FLASH = 0,//no flash
      ONE = 1, //250 ms
      TWO = 2, //500 ms
      FOUR = 4,//1 s
   };

   static const uint32_t DurationInfinite = 0;// If duration is Infinite only Initial State is used.

   struct OutputCmd
   {
      Port OutputPort;
      State InitialState;
      ChangeDuration StateChangeDuration;
      uint32_t TotalDuration;  //250 ms/bit (ex: duration 0, 1, 2, 3, etc. - INFINIT, 250 ms, 500 ms, 750 ms)
      State FinalState;

      template <class Archive>
      void serialize(Archive &ar, unsigned int version)
      {
         /* Archive Fields Here */
         ar & OutputPort;
         ar & InitialState;
         ar & StateChangeDuration;
         ar & TotalDuration;
         ar & FinalState;
      }
   };

   OutputChannelStorage() { }

   void toCsv( CsvOutStream& out ) const
   {
      for( auto command : OutputAppCmdVector )
      {
         std::string index = std::to_string( command.OutputPort + 1 );
         out( ( "PortNumber" + index ), command.OutputPort );
         out( ( "InitialState" + index ), command.InitialState );
         out( ( "FlashingHz" + index ), command.StateChangeDuration );
         out( ( "Duration" + index ), command.TotalDuration );
         out( ( "FinalState" + index ), command.FinalState );
      }
   }

   template <class Archive>
   void serialize(Archive &ar, unsigned int version)
   {
      /* Archive Fields Here */
      ar & OutputAppCmdVector;
   }

   void AddOutputAppCmd( OutputCmd outputAppCmd )
   {
      OutputAppCmdVector.push_back( outputAppCmd );
   }

   void ClearOutputAppCmds( )
   {
      OutputAppCmdVector.clear();
      OutputAppCmdVector.shrink_to_fit();
   }

   std::vector<OutputCmd> GetOutputAppCmds( )
   {
      return OutputAppCmdVector;
   }

private:
   /* Add Fields Here */
   std::vector<OutputCmd> OutputAppCmdVector;

};

typedef Datum<OutputChannelStorage> OutputChannel;

BOOST_CLASS_VERSION(OutputChannelStorage, 1);
#endif

