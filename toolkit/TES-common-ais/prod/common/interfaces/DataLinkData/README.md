**DataLinkData SCS Channel**

    This SCS Channel contains Parameter data received over the Datalink (CDL, J1939, Ethernet, CAN over UDP). It is published by BmiCdl, BmiEthernet, BmiJ1939, and Acd2Task

# Iterating over all parameters

    DataLinkData dlData;

    while (pDataLinkDataInput->get(dlData)) {
        auto& dlDataMap = dlData.GetDataLinkDataMap();
        for (const auto& kv : dlDataMap) {
            for (const DataLinkParam& dlParam : kv.second) {
                
                switch (param.GetParamIdentifierType()) {

                    // CDL PIDs
                    case (DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID): {
                        switch (param.GetParamId()) {

                        // Ground Speed
                        case (0xF4FD): {
                            auto dsi = dlParam.GetLastValueDsi();                   // Check DSI
                            auto valueEng = dlParam.GetLastGoodValueEng();          // Get Engineering (scaled) value
                            auto valueRaw = dlParam.GetLastGoodValue<uint32_t>();   // Get unscaled value (endian will always match architecture, does not depend on PID encoding)

# Read a specific parameter

    while (pDataLinkDataInput->get(dlData)) {
        AIS_LOG_DEBUG("DataLinkData received");
        dlData.PrintDataLinkParamMap();
        DataLinkParam* pParam{nullptr};
        if (dlData.GetParam(pParam, BOOM_CYLINDER_HEAD_END_PRESSURE, DataLinkParam::DATA_LINK_PARAM_IDENTIFIER_PID))
        {
            auto dsi = pParam->GetLastValueDsi();
            auto valueEng = pParam->GetLastGoodValueEng();
            auto valueRaw = pParam->GetLastGoodValue<uint32_t>();

# Producing parameter data

    It may be that an internal task/application needs to publish DataLinkData. As an example:

    initialize():
        dlData.AddDataLinkParam(tireRevParam);

        digTimeParam.SetDataLinkType(DataLinkParamInfo::DATA_LINK_PARAM_INT);                       // Internalyl produced data
        digTimeParam.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID);
        digTimeParam.SetParamId(PAYLOAD_CYCLE_CURRENT_DIG_TIME_PID);
        digTimeParam.SetParameterType(CDL2_U16_DSI);
        digTimeParam.SetSid(0xFF);

        /*
        * This does not match the actual datalink parameter encoding.
        * This application pre-scales the data to 0.01 sec/bit
        */
        digTimeParam.SetScaling(1.0);
        digTimeParam.SetOffset(0);

        dlData.AddDataLinkParam(digTimeParam);

    update():
        // Sets the value as a vector of bytes in the native byte order
        value.assign(reinterpret_cast<unsigned_8*>( &digTimeCurrent ),
                reinterpret_cast<unsigned_8*>( &digTimeCurrent ) + sizeof ( decltype( digTimeCurrent )));
        digTimeParam.SetLastValue(value, (digTimeCurrent == 0) ? CDL2_DSI_CONDITIONS_NOT_MET : BMI_CDL_DATA_STATUS_OK);
        dlData.UpdateDataLinkParam(digTimeParam);

        pDataLinkDataInput->publish(dlData);

