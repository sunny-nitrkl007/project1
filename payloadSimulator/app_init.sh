#!/bin/sh
# app_init for payloadSimulator - runs INSIDE the guest VM at every boot
# Starts two Node.js payload simulator web servers:
#   Port 8090 — gen6 dist (/tmp/payloadSimulator_gen6/dist/)
#   Port 8091 — gen7 dist (/tmp/payloadSimulator_gen7/dist/)

SCRIPT_DIR="$(realpath "$(dirname "$0")")"
NODE_BIN="${SCRIPT_DIR}/bin/node"
SERVER_JS="${SCRIPT_DIR}/server/server.js"

echo "payloadSimulator: Starting Node.js payload simulators..."

if [ ! -x "${NODE_BIN}" ]; then
    echo "payloadSimulator: ERROR - Node.js binary not found at ${NODE_BIN}" >&2
    exit 1
fi

if [ ! -f "${SERVER_JS}" ]; then
    echo "payloadSimulator: ERROR - server.js not found at ${SERVER_JS}" >&2
    exit 1
fi

# Kill any existing instances
pkill -f "node.*server.js" 2>/dev/null || true
sleep 1

# Shared writable work directory (both instances use the same value.json)
SHARED_WORK="/tmp/payloadSimulator_work"
mkdir -p "${SHARED_WORK}/NodeServerContent"
cp "${SCRIPT_DIR}/server/value.json" "${SHARED_WORK}/NodeServerContent/value.json"

# Setup function: creates a server instance directory in /tmp
# Usage: setup_instance <name> <http_port> <ws_port> <dist_source>
setup_instance() {
    NAME="$1"
    HTTP_PORT="$2"
    WS_PORT="$3"
    DIST_SRC="$4"
    INST_DIR="/tmp/payloadSimulator_${NAME}"
    LOG="/tmp/payloadSimulator_${NAME}.log"

    mkdir -p "${INST_DIR}"

    # Copy server.js and patch ports
    sed -e "s/app\.listen(8090/app.listen(${HTTP_PORT}/" \
        -e "s/websockets\.listen(55555/websockets.listen(${WS_PORT}/" \
        "${SERVER_JS}" > "${INST_DIR}/server.js"

    # Copy dist if not already present (preserves manual edits across restarts)
    if [ ! -d "${INST_DIR}/dist" ]; then
        cp -a "${DIST_SRC}" "${INST_DIR}/dist"
    fi

    # Copy simulatorUI if present
    if [ -d "${SCRIPT_DIR}/server/simulatorUI" ] && [ ! -d "${INST_DIR}/simulatorUI" ]; then
        cp -a "${SCRIPT_DIR}/server/simulatorUI" "${INST_DIR}/simulatorUI"
    fi

    # Symlink node_modules from the verity (read-only is fine)
    [ ! -e "${INST_DIR}/node_modules" ] && \
        ln -sf "${SCRIPT_DIR}/server/node_modules" "${INST_DIR}/node_modules"

    # Start server (CWD = shared work dir so both instances read/write same value.json)
    cd "${SHARED_WORK}" && \
        "${NODE_BIN}" "${INST_DIR}/server.js" > "${LOG}" 2>&1 &

    echo "payloadSimulator: ${NAME} started (PID $!, port ${HTTP_PORT}, ws ${WS_PORT}, log: ${LOG})"
    echo "  dist:  ${INST_DIR}/dist/"
}

# Gen7 dist source: use dist_gen7 if present, otherwise fall back to dist
GEN7_DIST_SRC="${SCRIPT_DIR}/server/dist_gen7"
[ ! -d "${GEN7_DIST_SRC}" ] && GEN7_DIST_SRC="${SCRIPT_DIR}/server/dist"

# Start gen6 on port 8090 (websocket 55555)
setup_instance "gen6" 8090 55555 "${SCRIPT_DIR}/server/dist"

# Start gen7 on port 8091 (websocket 55556)
setup_instance "gen7" 8091 55556 "${GEN7_DIST_SRC}"

echo ""
echo "payloadSimulator: To update dist content, SCP files to:"
echo "  gen6: /tmp/payloadSimulator_gen6/dist/"
echo "  gen7: /tmp/payloadSimulator_gen7/dist/"
