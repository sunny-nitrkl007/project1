///////////////////////////////////////////////////////////////////////////////
/// @file      JsonableInterfaceFactory.h
/// @author    strubjc
/// @date      Nov 23, 2016
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JSONABLEINTERFACEFACTORY_H_
#define JSONABLEINTERFACEFACTORY_H_

#include <map>
#include <string>
#include <interfaces/traits/Jsonable.h>

namespace jhm2
{
  
  class JsonableInterfaceFactory
  {
    public:
      JsonableInterfaceFactory () {}
      ~JsonableInterfaceFactory () {}

      bool interfaceExists(const std::string& intfName)
      {
        return ( m_registeredInterfaces.count(intfName) > 0 );
      }

      Jsonable* getIntf(const std::string& intfName)
      {
        JsonMapT::iterator it = m_registeredInterfaces.find( intfName );
        if ( it == m_registeredInterfaces.end() )
        {
          return NULL;
        }

        return it->second;
      }

    protected:
      template< class T >
      void registerInterface(const std::string& intfName, T& interface)
      {
          Jsonable* json = &interface;
          m_registeredInterfaces.insert(std::pair<std::string, Jsonable*>(intfName, json ) );
      }

    private:
      typedef std::map<std::string, Jsonable*> JsonMapT;
      JsonMapT m_registeredInterfaces;
  };

} /* namespace jhm2 */

#endif /* JSONABLEINTERFACEFACTORY_H_ */
