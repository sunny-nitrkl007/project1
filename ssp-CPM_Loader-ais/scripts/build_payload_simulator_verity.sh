#!/bin/bash
#########
# build_payload_simulator_verity.sh
#
# Builds the payloadSimulator verity for the A7H4 target.
# Entirely self-contained — assembles content from the ssp directory,
# downloads Node.js ARM64, installs npm deps, and produces the .verity file.
#
# Usage:
#   ./scripts/build_payload_simulator_verity.sh [BUILD_DIR]
#
# BUILD_DIR defaults to eta-ais/build-A7H4-adv (must already exist from a prior build)
#########

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TOP_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

BUILD_DIR="${1:-${TOP_DIR}/eta-ais/build-A7H4-adv}"
AIS_BUILD_TOOLS="${BUILD_DIR}/prod/ais_build_tools/content"

# Node.js version to use (LTS)
NODE_VERSION="${NODE_VERSION:-20.18.1}"
NODE_ARCH="linux-arm64"
NODE_TARBALL="node-v${NODE_VERSION}-${NODE_ARCH}.tar.xz"
NODE_URL="https://nodejs.org/dist/v${NODE_VERSION}/${NODE_TARBALL}"
NODE_EXTRACT_DIR="${BUILD_DIR}/ext/nodejs-arm64"

# Paths to source content (all in ssp directory, nothing in eta-ais)
PAYLOAD_SIM_DIR="${TOP_DIR}/payloadSimulator"
PAYLOAD_UI_DIR="${TOP_DIR}/ldpayloadui-a/Web_App_Release_Content"
PAYLOAD_UI_GEN7_DIR="${TOP_DIR}/ldpayloadui-a/Gen7 Dist/browser"
PAYLOAD_UI_SERVER_DIR="${PAYLOAD_UI_SERVER_DIR:-$(readlink -m "${TOP_DIR}/../../cpm/ldrpayloadui/NodeServerContent")}"
SIMULATOR_APP_DIR="${TOP_DIR}/ldpayloadui-a/Simulator_app/Simulator_Release_app"
NODE_MODULES_DIR="${BUILD_DIR}/ext/payload_sim_node_modules"

APPNAME="payloadSimulator"

echo "=== Building ${APPNAME} verity ==="
echo "  TOP_DIR:    ${TOP_DIR}"
echo "  BUILD_DIR:  ${BUILD_DIR}"
echo "  NODE_VER:   ${NODE_VERSION}"

# Verify build dir exists
if [ ! -d "${BUILD_DIR}" ]; then
    echo "ERROR: BUILD_DIR does not exist: ${BUILD_DIR}"
    echo "  Run a full build first (e.g. make project_a7h4_adv)"
    exit 1
fi

#######
# Step 1: Download Node.js ARM64
#######
if [ ! -f "${NODE_EXTRACT_DIR}/bin/node" ]; then
    echo "--- Downloading Node.js v${NODE_VERSION} for ARM64..."
    mkdir -p "${BUILD_DIR}/ext"

    if [ ! -f "${BUILD_DIR}/ext/${NODE_TARBALL}" ]; then
        wget -q --show-progress -O "${BUILD_DIR}/ext/${NODE_TARBALL}" "${NODE_URL}" || \
            { echo "ERROR: Failed to download Node.js from ${NODE_URL}"; exit 1; }
    fi

    echo "--- Extracting Node.js..."
    mkdir -p "${NODE_EXTRACT_DIR}"
    tar -xf "${BUILD_DIR}/ext/${NODE_TARBALL}" -C "${NODE_EXTRACT_DIR}" --strip-components=1

    echo "--- Node.js ARM64 binary ready at ${NODE_EXTRACT_DIR}/bin/node"
else
    echo "--- Node.js ARM64 binary already present"
fi

#######
# Step 2: Get a host-native node/npm for installing dependencies
#######
HOST_NODE_DIR="${BUILD_DIR}/ext/nodejs-host"
if ! command -v npm &>/dev/null; then
    if [ ! -f "${HOST_NODE_DIR}/bin/node" ]; then
        echo "--- npm not found on host, downloading host-native Node.js..."
        HOST_NODE_TARBALL="node-v${NODE_VERSION}-linux-x64.tar.xz"
        HOST_NODE_URL="https://nodejs.org/dist/v${NODE_VERSION}/${HOST_NODE_TARBALL}"
        mkdir -p "${HOST_NODE_DIR}"
        if [ ! -f "${BUILD_DIR}/ext/${HOST_NODE_TARBALL}" ]; then
            wget -q --show-progress -O "${BUILD_DIR}/ext/${HOST_NODE_TARBALL}" "${HOST_NODE_URL}" || \
                { echo "ERROR: Failed to download host Node.js"; exit 1; }
        fi
        tar -xf "${BUILD_DIR}/ext/${HOST_NODE_TARBALL}" -C "${HOST_NODE_DIR}" --strip-components=1
    fi
    export PATH="${HOST_NODE_DIR}/bin:${PATH}"
    echo "--- Using host Node.js: $(node --version), npm: $(npm --version)"
fi

#######
# Step 3: Install npm dependencies for the simulator server
#######
if [ ! -d "${NODE_MODULES_DIR}/express" ]; then
    echo "--- Installing npm dependencies for payload simulator..."
    mkdir -p "${NODE_MODULES_DIR}"

    # Create a temporary package.json for npm install
    TEMP_PKG_DIR=$(mktemp -d)
    cat > "${TEMP_PKG_DIR}/package.json" <<'EOF'
{
  "name": "payload-simulator-deps",
  "version": "1.0.0",
  "private": true,
  "dependencies": {
    "express": "^4.18.0",
    "body-parser": "^1.20.0",
    "cors": "^2.8.5",
    "decimal.js": "^10.4.0",
    "websocket": "^1.0.34"
  }
}
EOF

    # Install dependencies (pure JS packages work cross-platform on ARM64)
    cd "${TEMP_PKG_DIR}"
    npm install --production --no-optional 2>&1 | tail -5

    # Copy node_modules to our staging area
    rsync -rmptl "${TEMP_PKG_DIR}/node_modules/" "${NODE_MODULES_DIR}/"
    rm -rf "${TEMP_PKG_DIR}"

    echo "--- npm dependencies installed"
else
    echo "--- npm dependencies already present"
fi

#######
# Step 4: Assemble verity content
#######
echo "--- Assembling ${APPNAME} content..."

STAGING="${BUILD_DIR}/${APPNAME}"
rm -rf "${STAGING}"
mkdir -p "${STAGING}/bin" "${STAGING}/server/dist" "${STAGING}/server/node_modules"

# Copy app_init.sh from ssp payloadSimulator directory
cp "${PAYLOAD_SIM_DIR}/app_init.sh" "${STAGING}/"
chmod +x "${STAGING}/app_init.sh"

# Copy Node.js ARM64 binary
cp "${NODE_EXTRACT_DIR}/bin/node" "${STAGING}/bin/node"
chmod +x "${STAGING}/bin/node"

# Copy server.js
if [ -f "${PAYLOAD_UI_SERVER_DIR}/server.js" ]; then
    cp "${PAYLOAD_UI_SERVER_DIR}/server.js" "${STAGING}/server/"
else
    echo "ERROR: server.js not found at ${PAYLOAD_UI_SERVER_DIR}/server.js"
    exit 1
fi

# Copy value.json (prefer the Simulator_Release_app copy)
if [ -f "${SIMULATOR_APP_DIR}/value.json" ]; then
    cp "${SIMULATOR_APP_DIR}/value.json" "${STAGING}/server/"
elif [ -f "${PAYLOAD_UI_SERVER_DIR}/value.json" ]; then
    cp "${PAYLOAD_UI_SERVER_DIR}/value.json" "${STAGING}/server/"
else
    echo "WARNING: value.json not found, server may not function correctly"
fi

# Copy simulatorUI content if present
if [ -d "${PAYLOAD_UI_SERVER_DIR}/simulatorUI" ]; then
    rsync -rmptl "${PAYLOAD_UI_SERVER_DIR}/simulatorUI" "${STAGING}/server/"
fi

# Copy the compiled Angular web app (gen6) into dist/
if [ -d "${PAYLOAD_UI_DIR}" ]; then
    rsync -rmptl "${PAYLOAD_UI_DIR}/" "${STAGING}/server/dist/"
else
    echo "ERROR: Web_App_Release_Content (gen6) not found at ${PAYLOAD_UI_DIR}"
    exit 1
fi

# Copy the gen7 Angular web app into dist_gen7/
if [ -d "${PAYLOAD_UI_GEN7_DIR}" ]; then
    mkdir -p "${STAGING}/server/dist_gen7"
    rsync -rmptl "${PAYLOAD_UI_GEN7_DIR}/" "${STAGING}/server/dist_gen7/"
else
    echo "WARNING: Gen7 dist not found at ${PAYLOAD_UI_GEN7_DIR}, gen7 instance will use gen6 dist"
fi

# Copy node_modules
rsync -rmptl "${NODE_MODULES_DIR}/" "${STAGING}/server/node_modules/"

echo "--- Content assembled ($(du -sh "${STAGING}" | cut -f1))"

#######
# Step 5: Create zip and build verity
#######
echo "--- Creating verity..."

mkdir -p "${BUILD_DIR}/verity"
ZIPNAME="${BUILD_DIR}/verity/${APPNAME}.zip"
rm -f "${ZIPNAME}"

( cd "${STAGING}" && zip -qr "${ZIPNAME}" . )
echo "--- Zip created: ${ZIPNAME} ($(du -sh "${ZIPNAME}" | cut -f1))"

# Clean up staging
rm -rf "${STAGING}"

# Build verity directly on host — root operations delegated to Docker via docker exec.
# build-verity.sh uses runtime-build.sh for Docker delegation, which needs many Make env vars.
# Instead, we replicate the verity creation steps here with explicit docker exec for root ops.

DOCKER_CONTAINER="${DOCKER_CONTAINER:-bogtrotter-user-build-instance}"
VERITY_DIR="${BUILD_DIR}/verity"
SIGNING_BASEPATH="${AIS_BUILD_TOOLS}/verity-setup"
DEVMODE_CERT="${SIGNING_BASEPATH}/signing-cert.pem"
DEVMODE_KEY="${SIGNING_BASEPATH}/signing-key.pem"
VERITY_TOOL="${VERITY_DIR}/veritysetup"

# Source build settings for part number defaults
SOFTWARE_BUILD_ID="${SOFTWARE_BUILD_ID:-0}"
SOFTWARE_PART_NUMBER="${SOFTWARE_PART_NUMBER:-0000000}"
SOFTWARE_CHANGE_NUMBER="${SOFTWARE_CHANGE_NUMBER:-00}"
VERITY_BASE_NAME="${VERITY_BASE_NAME:-${SOFTWARE_PART_NUMBER}_${SOFTWARE_CHANGE_NUMBER}_${SOFTWARE_BUILD_ID}}"
bName="${APPNAME}_A7H4_${VERITY_BASE_NAME}"
bName="$(echo "${bName}" | tr - _)"

imageName="${VERITY_DIR}/${bName}.img"
hashesName="${VERITY_DIR}/${bName}.hashes"
tableRawName="${VERITY_DIR}/${bName}.tableraw"
tableName="${VERITY_DIR}/${bName}.table"
verityName="${VERITY_DIR}/${bName}.verity"
verityVerifyName="${VERITY_DIR}/${bName}.verity_verify"

# Check required files
for f in "${DEVMODE_CERT}" "${DEVMODE_KEY}" "${VERITY_TOOL}"; do
    [ -f "$f" ] || { echo "ERROR: Required file not found: $f"; exit 1; }
done

# Extract zip to staging
tmpDir="$(mktemp -d -t tmp.XXXX --tmpdir="${VERITY_DIR}")"
stageDir="${tmpDir}/stage"
mountDir="${tmpDir}/image"
mkdir -p "${stageDir}" "${mountDir}"

cleanup() {
    # Translate paths for Docker
    DOCKER_mountDir="${mountDir/${HOME}\/git\/gen7/${HOME}/repos}"
    DOCKER_tmpDir="${tmpDir/${HOME}\/git\/gen7/${HOME}/repos}"
    # Unmount if needed
    if mount 2>/dev/null | grep -q "${mountDir}"; then
        if docker ps --format "{{.Names}}" 2>/dev/null | grep -q "^${DOCKER_CONTAINER}$"; then
            docker exec "${DOCKER_CONTAINER}" umount "${DOCKER_mountDir}" 2>/dev/null
        else
            sudo umount "${mountDir}" 2>/dev/null
        fi
    fi
    # Remove tmpDir (may need root for root-owned content)
    if [ -d "${tmpDir}" ]; then
        if docker ps --format "{{.Names}}" 2>/dev/null | grep -q "^${DOCKER_CONTAINER}$"; then
            docker exec "${DOCKER_CONTAINER}" rm -rf "${DOCKER_tmpDir}" 2>/dev/null
        else
            rm -rf "${tmpDir}" 2>/dev/null || sudo rm -rf "${tmpDir}" 2>/dev/null
        fi
    fi
}
trap cleanup EXIT

echo "--- Extracting zip to staging..."
unzip -q "${ZIPNAME}" -d "${stageDir}" || { echo "ERROR: Failed to extract zip"; exit 1; }

# Calculate image size
INPUT_FOLDER_BLOCKS=$(du --summarize --block-size=4096 "${stageDir}" | cut -f1)
EXT_FS_BLOCKS=128
BLOCKS=$(echo "scale=0;(${INPUT_FOLDER_BLOCKS} + ${EXT_FS_BLOCKS}) * 2 / 1" | bc)
SIZE=$(echo "${BLOCKS}*128/1024" | bc)
echo "--- Verity image: ${BLOCKS} blocks (${SIZE}MB)"

# Create ext2 image
rm -f "${imageName}"
dd if=/dev/zero of="${imageName}" bs=4096 count="${BLOCKS}" 2>&1
/sbin/mkfs.ext2 "${imageName}" -b 4096 -F
/sbin/tune2fs -c0 -i0 "${imageName}"

# Mount, rsync, chown via Docker (needs root)
# Docker container maps /home/pf/git/gen7 -> /home/pf/repos
echo "--- Mounting and syncing via Docker..."
DOCKER_OK=false
if docker ps --format "{{.Names}}" 2>/dev/null | grep -q "^${DOCKER_CONTAINER}$"; then
    # Translate host paths to container paths
    DOCKER_imageName="${imageName/${HOME}\/git\/gen7/${HOME}/repos}"
    DOCKER_mountDir="${mountDir/${HOME}\/git\/gen7/${HOME}/repos}"
    DOCKER_stageDir="${stageDir/${HOME}\/git\/gen7/${HOME}/repos}"
    docker exec "${DOCKER_CONTAINER}" sudo bash -c "
        mount -t ext2 -o loop,rw '${DOCKER_imageName}' '${DOCKER_mountDir}' && \
        rsync -rlzW --delete --inplace --exclude=lost+found '${DOCKER_stageDir}/.' '${DOCKER_mountDir}/.' && \
        chown -R root:root '${DOCKER_mountDir}/.' && \
        sync && \
        umount '${DOCKER_mountDir}'
    " && DOCKER_OK=true
fi

if [ "${DOCKER_OK}" != "true" ]; then
    echo "--- Docker not available, trying sudo..."
    sudo mount -t ext2 -o loop,rw "${imageName}" "${mountDir}" && \
    sudo rsync -rlzW --delete --inplace --exclude=lost+found "${stageDir}/." "${mountDir}/." && \
    sudo chown -R root:root "${mountDir}/." && \
    sync && \
    sudo umount "${mountDir}" || { echo "ERROR: Mount/rsync failed"; exit 1; }
fi

# Resize image
echo "--- Resizing image..."
/sbin/e2fsck -f -p "${imageName}"
/sbin/resize2fs -M "${imageName}"

# Remove old metadata
rm -f "${hashesName}" "${tableRawName}" "${tableName}" "${verityName}" "${verityVerifyName}"

# Create verity hash (runs on host — needs libcrypto.so.1.1 which host has)
VERITY_HASH_ALGORITHM="sha256"
echo "--- Creating verity hash table (${VERITY_HASH_ALGORITHM})..."
"${VERITY_TOOL}" -c "${imageName}" "${hashesName}" \
    --data-block-size=4096 --hash-block-size=4096 \
    --no-superblock --algorithm=${VERITY_HASH_ALGORITHM} | tee "${tableRawName}"

# Post-process table
echo "--- Creating table file..."
tail -n 1 "${tableRawName}" | perl -pe \
    's/^target\s+line:\s+(\d+)\s+(\d+)\s+verity\s+1\s+\S+\s+\S+\s+(\d+)\s+(\d+)\s+(\d+)\s+0/$1 $2 verity 1 ROOT_DEV HASH_DEV $3 $4 $5 $5/o' \
    > "${tableName}"

# Create verity file (image + hashes)
echo "--- Creating verity file..."
cat "${imageName}" "${hashesName}" > "${verityName}"

# Sign with dev key (runs on host — needs OpenSSL 1.1 which host has)
echo "--- Signing verity..."

# Get password from encrypted filesystem
PASSWORD_REQUIRED=true
VERITY_KEY_PASSWORD_PATH="${HOME}/verity/VERITY_KEY_PASSWORD_PATH"
if [ -f "${VERITY_KEY_PASSWORD_PATH}" ]; then
    PASSWORD_FILE="$(cat "${VERITY_KEY_PASSWORD_PATH}")"
    eval PASSWORD_FILE="${PASSWORD_FILE}"
    if [ -f "${PASSWORD_FILE}" ]; then
        FILESYSTEM=$(stat -fc%T "${PASSWORD_FILE}")
        case "${FILESYSTEM}" in
            fuseblk)
                PASSIN_TYPE="file"
                PASSIN_ARG="${PASSWORD_FILE}"
                PASSWORD_REQUIRED=false
                ;;
        esac
    fi
fi

if [ "${PASSWORD_REQUIRED}" = "true" ]; then
    PASSIN_TYPE="pass"
    echo "Please enter the password for creating the dev verity verify"
    read -r -s PASSIN_ARG
fi

openssl smime -sign -in "${tableName}" \
    -signer "${DEVMODE_CERT}" \
    -inkey "${DEVMODE_KEY}" \
    -out "${verityVerifyName}" \
    -passin "${PASSIN_TYPE}:${PASSIN_ARG}"

# Validate
TABLEHASH="$( < "${tableName}" tr '\r\n' ' ' | sed 's|[[:space:]]*$||g' | sha256sum | awk '{print $1}')"
VERIFYHASH="$(openssl smime -verify -in "${verityVerifyName}" -noverify | tr '\r\n' ' ' | sed 's|[[:space:]]*$||g' | sha256sum | awk '{print $1}')"

if [ "${TABLEHASH}" = "${VERIFYHASH}" ]; then
    echo ""
    echo "=== verity_verify matches build — Success! ==="
else
    echo ""
    echo "=== verity_verify does NOT match build — Failure! ==="
    exit 1
fi

echo ""
echo "=== ${APPNAME} verity build complete ==="
echo ""
echo "SCP the following files to the target and key cycle:"
echo "  ${verityName}"
echo "  ${verityVerifyName}"
echo ""
ls -la "${verityName}" "${verityVerifyName}" 2>/dev/null
