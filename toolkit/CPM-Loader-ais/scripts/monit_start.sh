#!/bin/sh

APP_DIR=/opt/CPM
CONFIG_DIR=${APP_DIR}/config

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

[ -f "${CONFIG_DIR}/LpsSaJobMgrApp.yaml" ] || exit 1
[ -f "${CONFIG_DIR}/LpsSaWeighApp.yaml" ] || exit 1
[ -f "${CONFIG_DIR}/${ROBOT_YAML}" ] || exit 1
[ -f "${CONFIG_DIR}/OutputApp.yaml" ] || exit 1

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
    --instanceName=OutputApp \
    --ros-args \
    --params-file "${CONFIG_DIR}/OutputApp.yaml" \
    -p logger_threshold:=error
