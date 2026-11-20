/*
 * xcpServerDb_private.h
 *
 *  Created on: Mar 1, 2017
 *      Author: pf
 */

#ifndef XCPSERVERDBPRIVATE_H_
#define XCPSERVERDBPRIVATE_H_

#include "xcp_server/db/XCPServerDb.hpp"

bool xcpServerDbInit(xcp_server::ParameterDb& db);
bool xcpServerDbUpdate();
void xcpServerDbCleanup();

#endif /* XCPSERVERDBPRIVATE_H_ */
