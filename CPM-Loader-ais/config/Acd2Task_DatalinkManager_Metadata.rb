DatalinkParameterMetadata.push({
  "Application Specific Message # 1" => {
    Datalink::Keys::ID              => 0x0,
    Datalink::Keys::PARAMETER_TYPE  => Datalink::ParameterType::CAT_EXT_ID,
    Datalink::Keys::DATA_TYPE       => Datalink::DataType::VAR_NO_DSI,
    Datalink::Keys::DATA_BYTE_ORDER => Datalink::ByteOrder::NA,
    Datalink::Keys::SCALING         => "NA",
    Datalink::Keys::OFFSET          => "NA",
    Datalink::Keys::UNITS           => Datalink::Units::NA,
    Datalink::Keys::BYTE_LENGTH     => 6,
  },

  "Total Tattletale" => {
    Datalink::Keys::ID              => 0x59,
    Datalink::Keys::PARAMETER_TYPE  => Datalink::ParameterType::PID,
    Datalink::Keys::DATA_TYPE       => Datalink::DataType::U16_DSI,
    Datalink::Keys::DATA_BYTE_ORDER => Datalink::ByteOrder::LSB_FIRST,
    Datalink::Keys::SCALING         => 1,
    Datalink::Keys::OFFSET          => 1,
    Datalink::Keys::UNITS           => Datalink::Units::NA,
    Datalink::Keys::BYTE_LENGTH     => "NA",
  },

  "Security Access Level" => {
    Datalink::Keys::ID              => 0xF012,
    Datalink::Keys::PARAMETER_TYPE  => Datalink::ParameterType::PID,
    Datalink::Keys::DATA_TYPE       => Datalink::DataType::U8_DSI,
    Datalink::Keys::DATA_BYTE_ORDER => Datalink::ByteOrder::LSB_FIRST,
    Datalink::Keys::SCALING         => 1,
    Datalink::Keys::OFFSET          => 1,
    Datalink::Keys::UNITS           => Datalink::Units::NA,
    Datalink::Keys::BYTE_LENGTH     => "NA",
  },

  "Engine Serial Number" => {
    Datalink::Keys::ID              => 0xF810,
    Datalink::Keys::PARAMETER_TYPE  => Datalink::ParameterType::PID,
    Datalink::Keys::DATA_TYPE       => Datalink::DataType::VAR_NO_DSI,
    Datalink::Keys::DATA_BYTE_ORDER => Datalink::ByteOrder::NA,
    Datalink::Keys::SCALING         => 1,
    Datalink::Keys::OFFSET          => 1,
    Datalink::Keys::UNITS           => Datalink::Units::NA,
    Datalink::Keys::BYTE_LENGTH     => 9,
  },

  "Equipment ID" => {
    Datalink::Keys::ID              => 0xF81A,
    Datalink::Keys::PARAMETER_TYPE  => Datalink::ParameterType::PID,
    Datalink::Keys::DATA_TYPE       => Datalink::DataType::VAR_NO_DSI,
    Datalink::Keys::DATA_BYTE_ORDER => Datalink::ByteOrder::NA,
    Datalink::Keys::SCALING         => 1,
    Datalink::Keys::OFFSET          => 1,
    Datalink::Keys::UNITS           => Datalink::Units::NA,
    Datalink::Keys::BYTE_LENGTH     => 18,
  },

  "Product Link Module GPS Position Status" => {
    Datalink::Keys::ID              => 0xF84D,
    Datalink::Keys::PARAMETER_TYPE  => Datalink::ParameterType::PID,
    Datalink::Keys::DATA_TYPE       => Datalink::DataType::VAR_NO_DSI,
    Datalink::Keys::DATA_BYTE_ORDER => Datalink::ByteOrder::NA,
    Datalink::Keys::SCALING         => 1,
    Datalink::Keys::OFFSET          => 0,
    Datalink::Keys::UNITS           => Datalink::Units::NA,
    Datalink::Keys::BYTE_LENGTH     => 15,
  },

  "Time Zone Information" => {
    Datalink::Keys::ID              => 0xFA27,
    Datalink::Keys::PARAMETER_TYPE  => Datalink::ParameterType::PID,
    Datalink::Keys::DATA_TYPE       => Datalink::DataType::VAR_NO_DSI,
    Datalink::Keys::DATA_BYTE_ORDER => Datalink::ByteOrder::NA,
    Datalink::Keys::SCALING         => 1,
    Datalink::Keys::OFFSET          => 0,
    Datalink::Keys::UNITS           => Datalink::Units::NA,
    Datalink::Keys::BYTE_LENGTH     => 20,
  },

  # Gen7 Middleware parameter metadata.
  # - ID is derived from GEN7_MIDDLEWARE_ID automatically; do not specify ID.
  # - DATA_BYTE_ORDER and SCALING/OFFSET are optional.
  # - Use DATA_TYPE::BINARY for serialized Protobuf payloads.
  "Machine State Protobuf" => {
    Datalink::Keys::GEN7_MIDDLEWARE_ID => "Engine.machine_state",  # Format: "Server.parameter_name"
    Datalink::Keys::PARAMETER_TYPE     => Datalink::ParameterType::GEN7_MIDDLEWARE,
    Datalink::Keys::DATA_TYPE          => Datalink::DataType::BINARY,
    Datalink::Keys::UNITS              => Datalink::Units::NA,
  },

  "Engine Speed (Gen7 Double)" => {
    Datalink::Keys::GEN7_MIDDLEWARE_ID => "Engine.engine_speed",
    Datalink::Keys::PARAMETER_TYPE     => Datalink::ParameterType::GEN7_MIDDLEWARE,
    Datalink::Keys::DATA_TYPE          => Datalink::DataType::DOUBLE,
    Datalink::Keys::UNITS              => Datalink::Units::RPM,
  },

  "Vehicle Name (Gen7 String)" => {
    Datalink::Keys::GEN7_MIDDLEWARE_ID => "Engine.vehicle_name",
    Datalink::Keys::PARAMETER_TYPE     => Datalink::ParameterType::GEN7_MIDDLEWARE,
    Datalink::Keys::DATA_TYPE          => Datalink::DataType::VAR_NO_DSI,
    Datalink::Keys::UNITS              => Datalink::Units::NA,
    Datalink::Keys::BYTE_LENGTH        => 32,
  },

  "Actual Engine RPM" => {
    Datalink::Keys::ID              => 0x40,
    Datalink::Keys::PARAMETER_TYPE  => Datalink::ParameterType::PID,
    Datalink::Keys::DATA_TYPE       => Datalink::DataType::I16_DSI,
    Datalink::Keys::DATA_BYTE_ORDER => Datalink::ByteOrder::LSB_FIRST,
    Datalink::Keys::SCALING         => 0.5,
    Datalink::Keys::OFFSET          => 0,
    Datalink::Keys::UNITS           => Datalink::Units::RPM,
    Datalink::Keys::BYTE_LENGTH     => "NA",
  },

  "Production Measurement Feature Enable Status" => {
    Datalink::Keys::ID              => 0xD10EE7,
    Datalink::Keys::PARAMETER_TYPE  => Datalink::ParameterType::PID,
    Datalink::Keys::DATA_TYPE       => Datalink::DataType::U16_DSI,
    Datalink::Keys::DATA_BYTE_ORDER => Datalink::ByteOrder::MSB_FIRST,
    Datalink::Keys::SCALING         => 1,
    Datalink::Keys::OFFSET          => 0,
    Datalink::Keys::UNITS           => Datalink::Units::NA,
    Datalink::Keys::BYTE_LENGTH     => "NA",
  },

  "<SEA> Production Measurement Level 2 Feature Installation Status" => {
    Datalink::Keys::ID              => 0xD11884,
    Datalink::Keys::PARAMETER_TYPE  => Datalink::ParameterType::PID,
    Datalink::Keys::DATA_TYPE       => Datalink::DataType::U16_DSI,
    Datalink::Keys::DATA_BYTE_ORDER => Datalink::ByteOrder::MSB_FIRST,
    Datalink::Keys::SCALING         => 1,
    Datalink::Keys::OFFSET          => 0,
    Datalink::Keys::UNITS           => Datalink::Units::NA,
    Datalink::Keys::BYTE_LENGTH     => "NA",
  },

  "<SEA> Guidance Assisted Steering System Installation Status" => {
    Datalink::Keys::ID              => 0xD1182A,
    Datalink::Keys::PARAMETER_TYPE  => Datalink::ParameterType::PID,
    Datalink::Keys::DATA_TYPE       => Datalink::DataType::U16_DSI,
    Datalink::Keys::DATA_BYTE_ORDER => Datalink::ByteOrder::MSB_FIRST,
    Datalink::Keys::SCALING         => 1,
    Datalink::Keys::OFFSET          => 0,
    Datalink::Keys::UNITS           => Datalink::Units::NA,
    Datalink::Keys::BYTE_LENGTH     => "NA",
  },

  "<SEA> Co-Pilot System Installation Status" => {
    Datalink::Keys::ID              => 0xD1182D,
    Datalink::Keys::PARAMETER_TYPE  => Datalink::ParameterType::PID,
    Datalink::Keys::DATA_TYPE       => Datalink::DataType::U16_DSI,
    Datalink::Keys::DATA_BYTE_ORDER => Datalink::ByteOrder::MSB_FIRST,
    Datalink::Keys::SCALING         => 1,
    Datalink::Keys::OFFSET          => 0,
    Datalink::Keys::UNITS           => Datalink::Units::NA,
    Datalink::Keys::BYTE_LENGTH     => "NA",
  },

  "<SEA> Tire Monitoring System Installation Status" => {
    Datalink::Keys::ID              => 0xD10DBD,
    Datalink::Keys::PARAMETER_TYPE  => Datalink::ParameterType::PID,
    Datalink::Keys::DATA_TYPE       => Datalink::DataType::U16_DSI,
    Datalink::Keys::DATA_BYTE_ORDER => Datalink::ByteOrder::MSB_FIRST,
    Datalink::Keys::SCALING         => 1,
    Datalink::Keys::OFFSET          => 0,
    Datalink::Keys::UNITS           => Datalink::Units::NA,
    Datalink::Keys::BYTE_LENGTH     => "NA",
  },

})

