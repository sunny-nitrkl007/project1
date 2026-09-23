/*
 * legal_for_trade_identifiers.h
 */

#ifndef LEGAL_FOR_TRADE_IDENTIFIERS_H_
#define LEGAL_FOR_TRADE_IDENTIFIERS_H_

#include <string>

/*
 * Payload Legal For Trade (LFT) Measurement Software Identifier
 * ----------------------------------------------------------------------------
 * Used to read the identifier inextricably linked to the legally relevant
 * payload measurement software. The Payload Legal For Trade Measurement
 * Software Identifier only represents the legally relevant portion of
 * software. For example, this software identification could be altered for
 * every software change that may affect the metrological functions of the
 * instrument. This identifier is application specific.
 */
extern const std::string legal_for_trade_software_id_version;
extern const std::string legal_for_trade_software_id_build;

/*
 * The legal for trade system is certified and issued a type approval number.
 * This type approval number could be specific to the regional authority.
 * For example, the EU could have one that is different than the UK which could
 * be still different from Australia, New Zealand or Canada.
 *
 * The type approval will be specific to the software id or range of ids.
 * For example, it could cover "4.0.x" and "4.1.x".
 */
#define LEGAL_FOR_TRADE_TYPE_APPROVAL_NUMBER "T12670, T12670-UK, NMI 6/20A/15"

#endif /* LEGAL_FOR_TRADE_IDENTIFIERS_H_ */
