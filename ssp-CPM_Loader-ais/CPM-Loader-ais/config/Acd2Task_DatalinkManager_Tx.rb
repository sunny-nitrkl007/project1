DatalinkParameterTxConfig.push({
  # Gen7 Middleware Tx publisher example.
  # - GEN7_MIDDLEWARE_ID must match the middleware topic name exactly.
  # - No ID, SERVER_NAME, PROTOCOL_TYPE, or PORT fields are needed.
  # - Publish rate defaults to 1000ms. To configure, add TRANSMIT_RATE_MS parsing to the Tx parser (future work).
  "Machine State Protobuf" => {
    Datalink::Keys::PARAMETER_TYPE       => Datalink::ParameterType::GEN7_MIDDLEWARE,
    Datalink::Keys::GEN7_MIDDLEWARE_ID   => "Engine.machine_state",
    Datalink::Keys::WRITEABLE            => false,
    Datalink::Keys::QUALIFIED_DATA_TYPE  => Datalink::NA,
  },

  "Total Tattletale" => {
    Datalink::Keys::ID                   => 0x59,
    Datalink::Keys::PARAMETER_TYPE       => Datalink::ParameterType::PID,
    Datalink::Keys::WRITEABLE            => Datalink::Writeable::NO,
    Datalink::Keys::QUALIFIED_DATA_TYPE  => "NA",
    Datalink::Keys::PRIORITY             => "NA",
    Datalink::Keys::MAP_SUPPORTED        => Datalink::Supported::YES,
    Datalink::Keys::CAN_ID               => "NA",
    Datalink::Keys::START_BIT            => "NA",
  },

  "Engine Serial Number" => {
    Datalink::Keys::ID                   => 0xF810,
    Datalink::Keys::PARAMETER_TYPE       => Datalink::ParameterType::PID,
    Datalink::Keys::WRITEABLE            => Datalink::Writeable::NO,
    Datalink::Keys::QUALIFIED_DATA_TYPE  => "NA",
    Datalink::Keys::PRIORITY             => "NA",
    Datalink::Keys::MAP_SUPPORTED        => Datalink::Supported::YES,
    Datalink::Keys::CAN_ID               => "NA",
    Datalink::Keys::START_BIT            => "NA",
  },

})

