**Overview**
 Reads all CSV files in "Input CSV Directory". Publishes to DataLinkData at a rate of "Output Rate (ms) SCS CDL"

 Currently does not support scaling/offset in DataLinkData. This means that the format of data in the csv must be the same format that the consumer reads:
 
  * Engineering (scaled) values in the csv must be read with GetLastValueEng() or GetLastGoodValueEng()
  * Raw (unscaled) values in the csv must be read with GetLastValue() or GetLastGoodValue()

**CSV Format**

 * Multiple CSVs in the same path are supported as long as they have unique Parameters
 * First row is the name of the Parameter (for debugging)
 * Second row is the Parameter Type and ID in hexidecimal. The first byte is the DataLinkParamInfo::DlpParamIdentifierType_t, the last 3 bytes are the ID. Since DATA_LINK_PARAM_IDENTIFIER_PID = 0, for CDL PID this entry will be exactly the same as the PID