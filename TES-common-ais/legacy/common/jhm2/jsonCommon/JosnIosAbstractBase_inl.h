///////////////////////////////////////////////////////////////////////////////
/// @file      JosnIosAbstractBase_inl.h
/// @author    strubjc
/// @date      Apr 15, 2016
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////


template<class T>
void JsonIosAbstractBase::operator()(const std::string& key, T& val )
{
    switch ( m_type )
    {
      case INPUT:
        dynamic_cast<JsonInStream*>(this)->jsonImpl(key,val);
        break;
      case OUTPUT:
        dynamic_cast<JsonOutStream*>(this)->jsonImpl(key,val);
        break;
    }

}

template<class T>
void JsonIosAbstractBase::operator()(const std::string& key, T& val, FlagContainer& fc )
{
    switch ( m_type )
    {
      case INPUT:
        //Note the dropped flagContainer for input types
        dynamic_cast<JsonInStream*>(this)->jsonImpl(key,val,fc);
        break;
      case OUTPUT:
        dynamic_cast<JsonOutStream*>(this)->jsonImpl(key,val,fc);
        break;
    }
}
