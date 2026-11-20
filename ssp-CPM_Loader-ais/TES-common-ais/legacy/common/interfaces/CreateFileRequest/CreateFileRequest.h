#ifndef _CreateFileRequest_h_
#define _CreateFileRequest_h_

#include <ais/serialization/csvable.h>
#include <ais/serialization/Datum.h> // For Boost serialization

class CreateFileRequestStorage: public csvable
{  
public:  
   CreateFileRequestStorage() :
       fileNumber(0),
       Requester(),
       Command(CREATE_RESET) {}

   short int fileNumber;
   std::string Requester;
   enum
   {
      CREATE = 0,
      CREATE_RESET = 1,
      RESET = 2
   } Command;

   void toCsv(CsvOutStream& out) const
   {
      out("fileNumber",fileNumber);
      out("Requester",Requester);
      out("Command",static_cast<int>( Command ));
   }

   template <class Archive>
   void serialize(Archive &ar, unsigned int version)
   {
      ar & fileNumber & Requester & Command;
   }

private:
   // Nothing here yet
};  

typedef Datum<CreateFileRequestStorage> CreateFileRequest;

BOOST_CLASS_VERSION(CreateFileRequestStorage, 1);
#endif

