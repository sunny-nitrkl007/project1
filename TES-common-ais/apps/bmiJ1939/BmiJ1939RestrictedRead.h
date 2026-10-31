////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Caterpillar Inc.  All Rights Reserved.
//
//
//
//  Abstract: Handle incoming restricted read parameters.
//
////////////////////////////////////////////////////////
#ifndef BMIJ1939RESTRICTEDREAD_H
#define BMIJ1939RESTRICTEDREAD_H

#include <unordered_map>

#include <interfaces/DataLinkData/InterfaceTypes.h>

#include "BmiJ1939Config.h"


class BmiJ1939RestrictedRead
{
public:
	BmiJ1939RestrictedRead() = delete;
	
	static void RestrictedParamDataUpdate(const DataLinkParam& dlParm);

protected:

private:
	static std::unordered_map<DataLinkParamInfo::PidKey_t, DataLinkParam> m_restParamDataTable;

};

#endif // BMIJ1939RESTRICTEDREAD_H
