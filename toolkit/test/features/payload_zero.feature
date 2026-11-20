Feature: Payload Zero Adjustment
  The payload zero function adjusts the tare weight of the implement (bucket).
  It compensates for material buildup, temperature-related hydraulic changes,
  and other drift in the empty-bucket weight reading. All interactions are
  exercised through the AIS JHM2 CPM Loader HTTP/CGI API.

  Requirements Index:
    REQ-ZERO-AVAIL       — Zero button visibility and availability
    REQ-ZERO-EXEC        — Executing zero adjustment (ZeroEnable command)
    REQ-ZERO-LFT         — Zero behaviour under Legal For Trade
    REQ-ZERO-WARMUP      — Zero notification suppressed during warmup lifts
    REQ-ZERO-AUTO-NOTIFY — Auto zero notification triggers (timer, temperature)
    REQ-ZERO-SNOOZE      — Zero notification snooze during active weighing/standby
    REQ-ZERO-PASSCOUNT   — Zero notification suppressed during active loading pass
    REQ-ZERO-POST-SUCCESS— Payload state after successful zero
    REQ-ZERO-MULTI-CMD   — Zero combined with other commands
    REQ-ZERO-SERVICE     — Zero-related service parameters
    REQ-ZERO-BUCKET-ICON — Bucket status during zero operations
    REQ-ZERO-STANDBY     — Zero interaction with standby mode
    REQ-ZERO-HEARTBEAT   — API liveness during zero operations

  API surface used:
    GET  /CPM/cgi-bin/jhm2CgiApp.cgi?requestType=ParameterRequest2&paramsRequested=PayloadInfo
    GET  /CPM/cgi-bin/jhm2CgiApp.cgi?requestType=ParameterRequest2&paramsRequested=ServiceParameters
    GET  /CPM/cgi-bin/jhm2CgiApp.cgi?requestType=ParameterRequest2&paramsRequested=CalibrationData
    GET  /CPM/cgi-bin/jhm2CgiApp.cgi?requestType=ParameterRequest2&paramsRequested=LFTSealed
    GET  /CPM/cgi-bin/jhm2CgiApp.cgi?requestType=ParameterRequest2&paramsRequested=PayloadSettings
    GET  /CPM/cgi-bin/jhm2CgiApp.cgi?requestType=ParameterRequest2&paramsRequested=ActiveInfo_Rd
    POST /CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2  body: {"ZeroEnable": true}

  Key API field semantics:
    PayloadInfo.tipOffState.value:
      "0" = pile tip-off button highlighted (active during dump-to-pile)
      "1" = truck tip-off button highlighted (active during dump-to-truck)
      "2" = tip-off buttons unavailable; Zero button shown (default idle state)
    PayloadInfo.zeroAvailable.value (BoolParam, INVERTED logic):
      false = zero CAN be performed (button enabled)
      true  = zero CANNOT be performed (button disabled)
    ActiveInfo_Rd.value (bitfield, decimal string):
      bit 20 = PAYLOAD_TOO_HEAVY_TO_ZERO
      bit 21 = PAYLOAD_NOT_ZEROED (zero adjustment is needed/overdue)
      bit 23 = PAYLOAD_ZERO_ACCEPTED (zero was just accepted)

  Background:
    Given the CPM loader display is reachable at "{host}:{port}"
    And the API base URL is "/CPM/cgi-bin/jhm2CgiApp.cgi"

  # ===========================================================================
  # REQ-ZERO-AVAIL: Zero Button Visibility and Availability
  # ===========================================================================

  @api @read @PayloadInfo
  Scenario: Zero button is shown in the UI when system is idle (not in tip-off)
    When I GET parameter "PayloadInfo"
    Then the response field "PayloadInfo.tipOffState.value" should be "2"
    # tipOffState "2" is the default idle state — Zero button replaces tip-off buttons

  @api @read @PayloadInfo
  Scenario: Tip-off buttons replace zero button during active loading cycle
    Given the system is actively loading (tip-off is active)
    When I GET parameter "PayloadInfo"
    Then the response field "PayloadInfo.tipOffState.value" should be one of "0" or "1"
    # "0" = pile tip-off highlighted, "1" = truck tip-off highlighted

  @api @read @PayloadInfo
  Scenario: Zero is available when the system is calibrated and bucket weight is valid
    Given the system is calibrated
    And the bucket is in a valid weigh position
    When I GET parameter "PayloadInfo"
    Then the response field "PayloadInfo.zeroAvailable.value" should be false
    # API value false = zero IS available in the UI (inverted logic)

  @api @read @PayloadInfo
  Scenario: Zero is unavailable when calibration is incomplete
    Given the system is not calibrated
    When I GET parameter "PayloadInfo"
    Then the response field "PayloadInfo.zeroAvailable.value" should be true
    # API value true = zero is NOT available in the UI

  @api @read @PayloadInfo
  Scenario: Zero is unavailable when bucket weight accuracy is insufficient
    Given the bucket is not in a valid weigh position
    When I GET parameter "PayloadInfo"
    Then the response field "PayloadInfo.zeroAvailable.value" should be true

  @api @read @PayloadInfo
  Scenario: Zero is unavailable when bucket icon indicates excessive pitch
    When I GET parameter "PayloadInfo"
    And the response field "PayloadInfo.bucketIcon.value" is 2
    Then the response field "PayloadInfo.zeroAvailable.value" should be true

  @api @read @PayloadInfo
  Scenario: Zero is unavailable when bucket is not racked
    When I GET parameter "PayloadInfo"
    And the response field "PayloadInfo.bucketIcon.value" is 3
    Then the response field "PayloadInfo.zeroAvailable.value" should be true

  # ===========================================================================
  # REQ-ZERO-EXEC: Executing Zero Adjustment (ZeroEnable command)
  # ===========================================================================

  @api @command @ZeroEnable
  Scenario: Successful zero adjustment via ZeroEnable command
    Given the system is calibrated
    And the bucket weight is valid and within zero range
    When I POST command {"ZeroEnable": true}
    Then the response should not contain "CommandStatus"
    And the response should not contain "CommandFailDetails"

  @api @command @ZeroEnable @read @ActiveInfo_Rd
  Scenario: Zero command succeeds and sets PAYLOAD_ZERO_ACCEPTED info bit
    Given the system is calibrated
    And the bucket weight is valid and within zero range
    When I POST command {"ZeroEnable": true}
    And I wait 500ms for the next poll cycle
    And I GET parameter "ActiveInfo_Rd"
    Then bit 23 (PAYLOAD_ZERO_ACCEPTED) of "ActiveInfo_Rd.value" should be set

  @api @command @ZeroEnable @read @ActiveInfo_Rd
  Scenario: Zero command succeeds and clears PAYLOAD_NOT_ZEROED info bit
    Given the system is calibrated
    And the bucket weight is valid and within zero range
    And I GET parameter "ActiveInfo_Rd" and bit 21 (PAYLOAD_NOT_ZEROED) is set
    When I POST command {"ZeroEnable": true}
    And I wait 500ms for the next poll cycle
    And I GET parameter "ActiveInfo_Rd"
    Then bit 21 (PAYLOAD_NOT_ZEROED) of "ActiveInfo_Rd.value" should be cleared

  @api @command @ZeroEnable
  Scenario: Zero command fails when system is not calibrated
    Given the system is not calibrated
    When I GET parameter "CalibrationData"
    Then the response field "CalibrationData.CALSTATUS_Rd.value" should indicate uncalibrated
    When I POST command {"ZeroEnable": true}
    Then the zero adjustment should be rejected

  @api @command @ZeroEnable
  Scenario: Zero command fails when bucket weight is not accurate
    Given the system is calibrated
    And the bucket is not in a valid weigh position
    When I POST command {"ZeroEnable": true}
    Then the zero adjustment should be rejected

  @api @command @ZeroEnable @read @ActiveInfo_Rd
  Scenario: Zero command fails when bucket weight exceeds zero range limits
    Given the system is calibrated
    And the bucket contains material that exceeds the zero range
    When I POST command {"ZeroEnable": true}
    Then the zero adjustment should be rejected
    When I GET parameter "ActiveInfo_Rd"
    Then bit 20 (PAYLOAD_TOO_HEAVY_TO_ZERO) of "ActiveInfo_Rd.value" should be set

  # ===========================================================================
  # REQ-ZERO-LFT: Zero Behaviour Under Legal For Trade
  # ===========================================================================

  @api @read @LFT
  Scenario: Legal For Trade sealed state is readable via LFTSealed parameter
    When I GET parameter "LFTSealed"
    Then the response field "LFTSealed.value" should be a boolean

  @api @command @ZeroEnable @LFT @read @ActiveInfo_Rd
  Scenario: Initial zero is required on power-up when Legal For Trade is installed
    Given Legal For Trade is installed and sealed
    And the system has just powered on
    When I GET parameter "ActiveInfo_Rd"
    Then bit 21 (PAYLOAD_NOT_ZEROED) of "ActiveInfo_Rd.value" should be set
    When I GET parameter "PayloadInfo"
    Then the response field "PayloadInfo.zeroAvailable.value" should be false

  @api @command @ZeroEnable @LFT
  Scenario: Initial zero accepts weight within +/-10% of weight capacity
    Given Legal For Trade is installed
    And the system has just powered on (initial zero required)
    And the bucket weight is within 10 percent of weight capacity
    When I POST command {"ZeroEnable": true}
    Then the response should not contain "CommandStatus"

  @api @command @ZeroEnable @LFT
  Scenario: Subsequent zero accepts weight within +/-2% of weight capacity for Legal For Trade
    Given Legal For Trade is installed
    And initial zero has already been completed
    And the bucket weight is within 2 percent of weight capacity from previous zero weight
    When I POST command {"ZeroEnable": true}
    Then the response should not contain "CommandStatus"

  @api @command @ZeroEnable @LFT
  Scenario: Subsequent zero rejects weight outside +/-2% of weight capacity for Legal For Trade
    Given Legal For Trade is installed
    And initial zero has already been completed
    And the bucket weight exceeds 2 percent of weight capacity from previous zero weight
    When I POST command {"ZeroEnable": true}
    Then the zero adjustment should be rejected

  @api @command @ZeroEnable
  Scenario: Standard mode zero range is based on calibration weight and configured limit factor
    Given Legal For Trade is NOT installed
    And the system is calibrated
    And the bucket weight is within the configured zero range limit
    When I POST command {"ZeroEnable": true}
    Then the response should not contain "CommandStatus"

  @api @command @ZeroEnable
  Scenario: Standard mode zero rejects weight outside configured range
    Given Legal For Trade is NOT installed
    And the system is calibrated
    And the bucket weight exceeds the configured zero range limit
    When I POST command {"ZeroEnable": true}
    Then the zero adjustment should be rejected

  # ===========================================================================
  # REQ-ZERO-WARMUP: Zero Notification Suppressed During Warmup Lifts
  # ===========================================================================

  @api @read @PayloadInfo @ActiveInfo_Rd
  Scenario: PAYLOAD_NOT_ZEROED info is suppressed while warmup lifts are required
    Given the system has just powered on
    And warmup lifts are still required
    When I GET parameter "PayloadInfo"
    Then the response field "PayloadInfo.warmupLiftsRequired.value" should be greater than 0
    When I GET parameter "ActiveInfo_Rd"
    Then bit 21 (PAYLOAD_NOT_ZEROED) of "ActiveInfo_Rd.value" should be cleared
    # The zero-needed notification is suppressed until warmup lifts are completed

  @api @read @PayloadInfo @ActiveInfo_Rd
  Scenario: PAYLOAD_NOT_ZEROED info appears after warmup lifts are completed
    Given all warmup lifts have been completed
    And the configured zero time interval has elapsed
    When I GET parameter "PayloadInfo"
    Then the response field "PayloadInfo.warmupLiftsRequired.value" should be 0
    When I GET parameter "ActiveInfo_Rd"
    Then bit 21 (PAYLOAD_NOT_ZEROED) of "ActiveInfo_Rd.value" should be set

  # ===========================================================================
  # REQ-ZERO-AUTO-NOTIFY: Auto Zero Notification Triggers
  # ===========================================================================

  @api @read @ActiveInfo_Rd
  Scenario: Zero-needed notification triggered by timer expiry
    Given the system is calibrated
    And no zero adjustment has been performed since power-on
    And the configured zero time interval has elapsed
    And the pass count is 0
    When I GET parameter "ActiveInfo_Rd"
    Then bit 21 (PAYLOAD_NOT_ZEROED) of "ActiveInfo_Rd.value" should be set

  @api @read @ActiveInfo_Rd @ServiceParameters
  Scenario: Zero-needed notification triggered by hydraulic oil temperature change
    Given the system is calibrated
    And a zero adjustment was last performed at a significantly different oil temperature
    And the pass count is 0
    When I GET parameter "ServiceParameters"
    Then the response field "ServiceParameters.hydOilTemp.value" should be a number
    When I GET parameter "ActiveInfo_Rd"
    Then bit 21 (PAYLOAD_NOT_ZEROED) of "ActiveInfo_Rd.value" should be set

  @api @read @ActiveInfo_Rd @LFT
  Scenario: Zero-needed notification triggered immediately on power-up for Legal For Trade
    Given Legal For Trade is installed
    And the system has just powered on
    And warmup lifts have been completed
    And the pass count is 0
    When I GET parameter "ActiveInfo_Rd"
    Then bit 21 (PAYLOAD_NOT_ZEROED) of "ActiveInfo_Rd.value" should be set

  @api @read @ActiveInfo_Rd
  Scenario: Zero-needed notification uses fast time interval when oil temp sensor is disabled
    Given the system is calibrated
    And hydraulic oil temperature monitoring is disabled
    And the fast zero time interval has elapsed
    And the pass count is 0
    When I GET parameter "ActiveInfo_Rd"
    Then bit 21 (PAYLOAD_NOT_ZEROED) of "ActiveInfo_Rd.value" should be set

  @api @read @PayloadSettings
  Scenario: Hydraulic oil temperature enabled state is readable
    When I GET parameter "PayloadSettings"
    Then the response should contain field "PayloadSettings.hydOilTempEnabled"

  # ===========================================================================
  # REQ-ZERO-SNOOZE: Zero Notification Snooze During Active Weighing/Standby
  #
  # The zero-needed notification (PAYLOAD_NOT_ZEROED) is suppressed ("snoozed")
  # when the system is actively weighing or in standby mode. The tipOffState
  # field independently changes during these states (to "0"/"1" during tip-off),
  # but that reflects the tip-off workflow, NOT the snooze mechanism.
  # The snooze is observable via the ActiveInfo_Rd bitfield.
  # ===========================================================================

  @api @read @ActiveInfo_Rd @PayloadInfo
  Scenario: Zero-needed notification is snoozed while actively weighing
    Given a zero adjustment is needed (PAYLOAD_NOT_ZEROED bit 21 is set)
    And the system begins a weighing cycle (passCount increments)
    When I GET parameter "ActiveInfo_Rd"
    Then bit 21 (PAYLOAD_NOT_ZEROED) of "ActiveInfo_Rd.value" should be cleared
    # The notification is snoozed during active weighing

  @api @read @ActiveInfo_Rd @PayloadInfo
  Scenario: Zero-needed notification is snoozed while in standby
    Given a zero adjustment is needed (PAYLOAD_NOT_ZEROED bit 21 is set)
    When I POST command {"StandByEnable": true}
    And I wait 500ms for the next poll cycle
    And I GET parameter "PayloadInfo"
    Then the response field "PayloadInfo.standbyState.value" should be "0"
    When I GET parameter "ActiveInfo_Rd"
    Then bit 21 (PAYLOAD_NOT_ZEROED) of "ActiveInfo_Rd.value" should be cleared

  @api @read @ActiveInfo_Rd @PayloadInfo
  Scenario: Snoozed zero notification restored after snooze interval (standard mode)
    Given a zero notification was snoozed during weighing
    And the weighing cycle has ended
    And the pass count has returned to 0
    And at least 600 seconds have elapsed since the snooze
    When I GET parameter "PayloadInfo"
    Then the response field "PayloadInfo.passCount.value" should be "0"
    When I GET parameter "ActiveInfo_Rd"
    Then bit 21 (PAYLOAD_NOT_ZEROED) of "ActiveInfo_Rd.value" should be set

  @api @read @ActiveInfo_Rd @PayloadInfo @LFT
  Scenario: Snoozed zero notification restored immediately for Legal For Trade
    Given Legal For Trade is installed
    And a zero notification was snoozed during weighing
    And the weighing cycle has ended
    And the pass count has returned to 0
    When I GET parameter "ActiveInfo_Rd"
    Then bit 21 (PAYLOAD_NOT_ZEROED) of "ActiveInfo_Rd.value" should be set
    # LFT does not wait for the 600-second snooze interval

  @api @read @ActiveInfo_Rd @PayloadInfo
  Scenario: Snoozed zero notification NOT restored while pass count is non-zero
    Given a zero notification was snoozed during weighing
    And the pass count is greater than 0
    When I GET parameter "PayloadInfo"
    Then the response field "PayloadInfo.passCount.value" should not be "0"
    When I GET parameter "ActiveInfo_Rd"
    Then bit 21 (PAYLOAD_NOT_ZEROED) of "ActiveInfo_Rd.value" should be cleared
    # Un-snooze requires pass count to return to 0

  @api @read @ActiveInfo_Rd @PayloadInfo
  Scenario: Snoozed zero notification NOT restored before 600-second interval (standard)
    Given Legal For Trade is NOT installed
    And a zero notification was snoozed during weighing
    And the weighing cycle has ended
    And the pass count has returned to 0
    And less than 600 seconds have elapsed since the snooze
    When I GET parameter "ActiveInfo_Rd"
    Then bit 21 (PAYLOAD_NOT_ZEROED) of "ActiveInfo_Rd.value" should be cleared

  # ===========================================================================
  # REQ-ZERO-PASSCOUNT: Zero Notification Suppressed During Active Loading Pass
  # ===========================================================================

  @api @read @ActiveInfo_Rd @PayloadInfo
  Scenario: No new zero notification triggered while pass count is non-zero
    Given the system is calibrated
    And the pass count is greater than 0
    When I GET parameter "PayloadInfo"
    Then the response field "PayloadInfo.passCount.value" should not be "0"
    When I GET parameter "ActiveInfo_Rd"
    Then bit 21 (PAYLOAD_NOT_ZEROED) of "ActiveInfo_Rd.value" should be cleared

  # ===========================================================================
  # REQ-ZERO-POST-SUCCESS: Payload State After Successful Zero
  # ===========================================================================

  @api @command @ZeroEnable @read @PayloadInfo
  Scenario: Bucket weight resets to near-zero after successful zero adjustment
    Given the system is calibrated
    And the bucket is empty and in the weigh range
    When I POST command {"ZeroEnable": true}
    And I wait 500ms for the next PayloadInfo poll cycle
    And I GET parameter "PayloadInfo"
    Then the response field "PayloadInfo.bucketWeight.value" should be approximately 0.0

  @api @command @ZeroEnable @read @ActiveInfo_Rd
  Scenario: Zero adjustment clears PAYLOAD_NOT_ZEROED and resets auto-zero timer
    Given a zero adjustment is needed (PAYLOAD_NOT_ZEROED bit 21 is set)
    And the bucket is in a valid position for zeroing
    When I POST command {"ZeroEnable": true}
    And I wait 500ms for the next poll cycle
    And I GET parameter "ActiveInfo_Rd"
    Then bit 21 (PAYLOAD_NOT_ZEROED) of "ActiveInfo_Rd.value" should be cleared
    And bit 23 (PAYLOAD_ZERO_ACCEPTED) of "ActiveInfo_Rd.value" should be set
    # The auto-zero timer is reset; no new notification for at least the configured interval

  @api @command @ZeroEnable @read @ServiceParameters
  Scenario: Zero adjustment records current hydraulic oil temperature
    Given the system is calibrated
    And hydraulic oil temperature monitoring is enabled
    And the bucket is in a valid position for zeroing
    When I GET parameter "ServiceParameters"
    And I note the current "ServiceParameters.hydOilTemp.value"
    And I POST command {"ZeroEnable": true}
    Then the zero should use the noted hydraulic oil temperature as baseline for future temperature-change detection

  # ===========================================================================
  # REQ-ZERO-MULTI-CMD: Zero Combined With Other Commands
  # ===========================================================================

  @api @command
  Scenario: ZeroEnable can be sent alongside other commands in a single request body
    Given the system is calibrated
    And the bucket is in a valid position for zeroing
    When I POST command {"ZeroEnable": true, "DisplayBrightness_Wr": 80}
    Then the response should not contain "CommandStatus"

  # ===========================================================================
  # REQ-ZERO-SERVICE: Zero-Related Service Parameters
  # ===========================================================================

  @api @read @ServiceParameters
  Scenario: Hydraulic oil temperature is readable via ServiceParameters
    When I GET parameter "ServiceParameters"
    Then the response field "ServiceParameters.hydOilTemp.value" should be a number
    Or the response field "ServiceParameters.hydOilTemp" should have a "status" DSI code if unavailable

  @api @read @CalibrationData
  Scenario: Calibration status is readable via CalibrationData
    When I GET parameter "CalibrationData"
    Then the response should contain field "CalibrationData.CALSTATUS_Rd"
    And the response field "CalibrationData.CALSTATUS_Rd.value" should be a string

  @api @read @CalibrationData
  Scenario: Hydraulic oil temperature in Celsius is readable via CalibrationData
    When I GET parameter "CalibrationData"
    Then the response should contain field "CalibrationData.HydOilTempC_Rd"
    And the response field "CalibrationData.HydOilTempC_Rd.value" should be a string representing a float

  # ===========================================================================
  # REQ-ZERO-BUCKET-ICON: Bucket Status During Zero Operations
  # ===========================================================================

  @api @read @PayloadInfo
  Scenario Outline: Bucket icon reflects weigh position suitability for zero
    When I GET parameter "PayloadInfo"
    Then the response field "PayloadInfo.bucketIcon.value" should be <iconValue>
    And the bucket status should indicate "<meaning>"

    Examples:
      | iconValue | meaning            |
      | 0         | no icon            |
      | 1         | in weigh range     |
      | 2         | excessive pitch    |
      | 3         | bucket not racked  |

  @api @read @PayloadInfo
  Scenario: Zero is only available when bucket icon is 0 (no icon) or 1 (in weigh range)
    When I GET parameter "PayloadInfo"
    And the response field "PayloadInfo.bucketIcon.value" is 1
    Then the response field "PayloadInfo.zeroAvailable.value" should be false

  # ===========================================================================
  # REQ-ZERO-STANDBY: Zero Interaction With Standby Mode
  # ===========================================================================

  @api @command @read @ActiveInfo_Rd @PayloadInfo
  Scenario: Entering standby suppresses zero-needed notification
    Given a zero adjustment is needed (PAYLOAD_NOT_ZEROED bit 21 is set)
    When I POST command {"StandByEnable": true}
    And I wait 500ms for the next poll cycle
    And I GET parameter "PayloadInfo"
    Then the response field "PayloadInfo.standbyState.value" should be "0"
    When I GET parameter "ActiveInfo_Rd"
    Then bit 21 (PAYLOAD_NOT_ZEROED) of "ActiveInfo_Rd.value" should be cleared

  @api @command @read @ActiveInfo_Rd @PayloadInfo
  Scenario: Exiting standby with pass count 0 can restore zero-needed notification
    Given a zero notification was snoozed during standby
    When I POST command {"StandByDisable": true}
    And I wait for the snooze interval to elapse (600 seconds for standard mode)
    And I GET parameter "PayloadInfo"
    Then the response field "PayloadInfo.standbyState.value" should be "1"
    And the response field "PayloadInfo.passCount.value" should be "0"
    When I GET parameter "ActiveInfo_Rd"
    Then bit 21 (PAYLOAD_NOT_ZEROED) of "ActiveInfo_Rd.value" should be set

  # ===========================================================================
  # REQ-ZERO-HEARTBEAT: API Liveness During Zero Operations
  # ===========================================================================

  @api @read @Heartbeat
  Scenario: API remains responsive during and after zero adjustment
    When I GET parameter "Heartbeat"
    Then the response should contain field "Heartbeat.SoftwareVersion"
    When I POST command {"ZeroEnable": true}
    And I GET parameter "Heartbeat"
    Then the response should contain field "Heartbeat.SoftwareVersion"
