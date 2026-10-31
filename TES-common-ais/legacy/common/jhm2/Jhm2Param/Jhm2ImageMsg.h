///////////////////////////////////////////////////////////////////////////////
/// @file      Jhm2ImageMsg.h
/// @author    strubjc
/// @date      Mar 18, 2013
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2013 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JHM2IMAGEMSG_H_
#define JHM2IMAGEMSG_H_

#include <std_types.h>
#include <string.h> //for memcpy
#include <interfaces/CameraImage/CameraImage.h>
#include "Jhm2Msg.h"


class Jhm2ImageMsg: public Jhm2Msg
{
  public:
    Jhm2ImageMsg(): cameraId( 0 ), dataSize( 0 ), dataP( NULL ), dataBufferSize( 0 )  {}
    ~Jhm2ImageMsg() { clear(); }

    Jhm2ImageMsg& operator=(const Jhm2ImageMsg& rhs )
    {
      if ( this != &rhs )
      {
        allocate_buffer( rhs.dataSize );
        memcpy( dataP, rhs.dataP, rhs.dataSize );
        cameraId = rhs.cameraId;
        dataSize = rhs.dataSize;
      }
      return *this;
    }

    void update(const CameraImageStorage& camImage )
    {
      allocate_buffer( camImage.dataSize );
      memcpy( dataP, camImage.getImageData(), camImage.dataSize );
      cameraId = camImage.cameraId;
      dataSize = camImage.dataSize;
    }

    void clear()
    {
      //clear out memory
      if(dataP != NULL)
      {
        delete[] dataP;
        dataP = NULL;
      }
    }

    virtual bool getJpg( std::ostream& out ) const
    {
      out.write( (char*)( dataP ), dataSize );
      return true;
    }

  private:
    unsigned int cameraId;
    unsigned int dataSize;

    unsigned char *dataP;
    unsigned int  dataBufferSize;

    void allocate_buffer(unsigned int newDataSize)
    {
      if(newDataSize > dataBufferSize)
      {
        if(dataP != NULL)
        {
          delete[] dataP;
        }

        // allocate a bit more then needed for next time
        dataP = new unsigned char[newDataSize*3/2];
        dataBufferSize = newDataSize*3/2;
      }
    }

};

#endif /* JHM2IMAGEMSG_H_ */
