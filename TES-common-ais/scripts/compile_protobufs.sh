#!/bin/bash

# Compiles protocol buffers from AIS GRPC tag


# functions common to all platforms
COMMON_SCRIPTS_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"/../../eta-ais/prod/platformCommon/content/common/scripts

source "$COMMON_SCRIPTS_DIR"/functions.sh

# load latest tags
source "$COMMON_SCRIPTS_DIR"/tags.sh

# check for adequate arguments
[ 2 -gt $# ] && failure "USAGE: $(basename ${BASH_SOURCE[0]}) [SSP-LINUX DIR] [TES-common-ais DIR]"

# First argument must be your ssp-linux project repo (eg: /home/pf/pathfinder/ref-ssp)
# Second argument must be your target platformCommon repo directory
# eg: /home/pf/pathfinder/eta-ais/prod/platformCommon/content/${PLATFORM}
SOURCE=$1; shift
DEST=$1; shift

# must set ${SOURCE} env variable
for var in SOURCE DEST
do
    [ "X" == "X${!var}" ] && failure "${var} must be set!"
    [ -d "${!var}" ] || failure "${var} directory ${!var} does not exist!"
done

source ../../eta-ais/prod/platformCommon/content/common/scripts/functions.sh
source ../../eta-ais/prod/platformCommon/content/common/scripts/tags.sh

PROTOC_DIR=$SOURCE/lib_oss/grpc-a/tgt_gcc_4.4.3_ubuntu/protoc/
cdValidate $PROTOC_DIR
checkoutValidate "$GRPC_TAG"

echo "GRPC_TAG=$GRPC_TAG"

proto_dirs=(
    protobuf/proto
    apps/RemotePrinterApp/Payload
    apps/FileTransferBridgeApp/ReportTrigger
)
# run em!
{ 
    for proto in ${proto_dirs[@]}; do \
        echo "Generating protobufs in ${DEST}${proto}" ; \
        "${PROTOC_DIR}"/protoc --proto_path="${DEST}"/"${proto}"  --cpp_out="${DEST}"/"${proto}" "${DEST}"/"${proto}"/*.proto ; \
    done;
}
