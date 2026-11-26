#!/bin/sh

export AMENT_PREFIX_PATH=/opt/CPM
APP_DIR=/opt/CPM
CONFIG_DIR=${APP_DIR}/config

CONFIG_DIR=${APP_DIR}/config
VERITY_DIRECTORY=${APP_DIR%/}
VERITY_DIRECTORY=${VERITY_DIRECTORY##*/}
DAEMON=${START_STOP_DAEMON:-/sbin/start-stop-daemon}
PIDFILE=${VP3_PIDFILE:-/run/lps_vp3.pid}

# Debug
{
    echo "========================================"
    echo "$(date)"
    echo "Searching robot file..."
    find /opt -type f -name robot 2>/dev/null
} >> /tmp/lps_start.log 2>&1

# Temporary fallback
ROBOT_YAML="Robot_NOT_SET.yaml"

# If a robot file exists, calculate machine name
ROBOT_FILE=$(find /opt -type f -name robot 2>/dev/null | head -1)

if [ -n "${ROBOT_FILE}" ] && [ -s "${ROBOT_FILE}" ]; then

    ROBOT_TYPE=$(head -n 1 "${ROBOT_FILE}" | tr -d '\r\n')

    MACHINE_NAME=$(
        ${APP_DIR}/bin/convertMsnToMachName \
            --msn "${ROBOT_TYPE}" \
            --subsys "${APP_DIR}" \
            --terse 2>/dev/null | tr -d '\r\n'
    )

    case "${MACHINE_NAME}" in
        ""|MSNINVALID|MSNUNSUPPORTED|MSNNOTAVAIL)
            ROBOT_YAML="Robot_NOT_SET.yaml"
            ;;
        *)
            ROBOT_YAML="Robot_${MACHINE_NAME}.yaml"
            ;;
    esac
fi

{
    echo "ROBOT_FILE=${ROBOT_FILE}"
    echo "ROBOT_TYPE=${ROBOT_TYPE}"
    echo "MACHINE_NAME=${MACHINE_NAME}"
    echo "ROBOT_YAML=${ROBOT_YAML}"
} >> /tmp/lps_start.log 2>&1

[ -f "${CONFIG_DIR}/XcpServerTask.yaml" ] || exit 1
[ -f "${CONFIG_DIR}/LpsSaJobMgrApp.yaml" ] || exit 1
[ -f "${CONFIG_DIR}/LpsSaWeighApp.yaml" ] || exit 1
[ -f "${CONFIG_DIR}/${ROBOT_YAML}" ] || exit 1
[ -f "${CONFIG_DIR}/OutputApp.yaml" ] || exit 1
[ -f "${CONFIG_DIR}/SerialPrinterApp.yaml" ] || exit 1
[ -f "${CONFIG_DIR}/VP3FileCreationApp.yaml" ] || exit 1

# Start XcpServerTask (aisXcpServer) first, as in AIS. The NVM calibration snapshot
# (lps_sa_nvm_cal_data_channel) is transient_local, so a later start still receives it.
# No Robot YAML: the app reads no machine-specific keys.
/sbin/start-stop-daemon \
    --start \
    --background \
    --make-pidfile \
    --pidfile /run/xcp_server_task.pid \
    --exec "${APP_DIR}/bin/aisXcpServer" \
    -- \
    --instance XcpServerTask \
    --ros-args \
    --params-file "${CONFIG_DIR}/XcpServerTask.yaml"

# Start JobMgr
/sbin/start-stop-daemon \
    --start \
    --background \
    --make-pidfile \
    --pidfile /run/lps_job_mgr.pid \
    --exec "${APP_DIR}/bin/LpsSaJobMgrApp" \
    -- \
    --instance LpsSaJobMgrApp \
    --ros-args \
    --params-file "${CONFIG_DIR}/LpsSaJobMgrApp.yaml" \
    --params-file "${CONFIG_DIR}/${ROBOT_YAML}" \
    ${UI_SHOW_FEATURE_CONFIG_JSON_FILE_PATH:+--param ui_show_feature_config_json_file_path:=${UI_SHOW_FEATURE_CONFIG_JSON_FILE_PATH}}

# Start WeighApp
/sbin/start-stop-daemon \
    --start \
    --background \
    --make-pidfile \
    --pidfile /run/lps_weigh.pid \
    --exec "${APP_DIR}/bin/LpsSaWeighApp" \
    -- \
    --instance LpsSaWeighApp \
    --ros-args \
    --params-file "${CONFIG_DIR}/LpsSaWeighApp.yaml" \
    --params-file "${CONFIG_DIR}/${ROBOT_YAML}"

# Start OutputApp
/sbin/start-stop-daemon \
    --start \
    --background \
    --make-pidfile \
    --pidfile /run/output_app.pid \
    --exec "${APP_DIR}/bin/OutputApp" \
    -- \
    --instance OutputApp \
    --ros-args \
    --params-file "${CONFIG_DIR}/OutputApp.yaml" 

# Start VP3FileCreationApp
/sbin/start-stop-daemon \
    --start \
    --background \
    --make-pidfile \
    --pidfile /run/lps_vp3.pid \
    --exec "${APP_DIR}/bin/VP3FileCreationApp" \
    -- \
    --instance VP3FileCreationApp \
    --ros-args \
    --params-file "${CONFIG_DIR}/VP3FileCreationApp.yaml" \
    --param "storageRoot:=/opt/appdata/${VERITY_DIRECTORY}/VP3FileCreationApp/nvm/" \
    --param "tempRoot:=/tmp/appdata/${VERITY_DIRECTORY}/VP3FileCreationApp" \
    --param "VP3TxPath:=/opt/appdata/${VERITY_DIRECTORY}/FileTransferBridgeApp/TxFiles/"

# Start SerialPrinterApp
/sbin/start-stop-daemon \
    --start \
    --background \
    --make-pidfile \
    --pidfile /run/serial_printer.pid \
    --exec "${APP_DIR}/bin/SerialPrinterApp" \
    -- \
    --instance SerialPrinterApp \
    --ros-args \
    --params-file "${CONFIG_DIR}/SerialPrinterApp.yaml"
