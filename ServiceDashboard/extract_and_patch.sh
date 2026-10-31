#!/bin/bash

# determine this scripts local directory
SCRIPTDIR=$(dirname $0)
verityImage=${SCRIPTDIR}/ServiceDashboard_Lite_A6N2_02020082802.verity

echo "verityImage=${verityImage}"

BUILDDIR=$1
echo "BUILDDIR=${BUILDDIR}"

function rm_tmpDir() {
    [ "X" != "X${tmpDir}" ] && [ -d "${tmpDir}" ] && \
        rm -fr "${tmpDir}" 2>/dev/null || \
            echo "WARNING: Could not remove temp directory ${tmpDir}"
}

function unmount_image() {
    # unmount the image only if its exist and mounted
    if [[ "X" != "X${mountDir}" && -d "${mountDir}" ]]
    then
        echo "Unmounting ${mountDir} ..."
        sudo umount "${mountDir}"
    fi
}

# this will execute at script EXIT
function exeunt() {
    # unmount the image incase we exited the script abruptly
    unmount_image
    rm_tmpDir
}
trap exeunt EXIT

####
# We are going to create a temporary directory
# to which we will both copy content and mount our file image
# -d : Create a directory, not a file
# -t tmp.XXXX : Template for the temp name
####
tmpDir=$(mktemp -d -t ServiceDashboard.XXXX --tmpdir=${BUILDDIR}) || \
    { echo "ERROR: could not create temp directory in ${BUILDDIR} using 'mktemp -d'" && exit 1; }

mountDir=${tmpDir}

echo "Mounting ${verityImage} to ${mountDir} ..."
sudo mount -o loop,ro "${verityImage}" "${mountDir}"

stageDir="${BUILDDIR}/ServiceDashboard"

mkdir -p "${stageDir}"

echo "Syncing ${mountDir} to ${stageDir} ..."
sudo rsync -rlW --delete --inplace "${mountDir}/." "${stageDir}/." || \
    { echo "ERROR: rsync of ${mountDir}/. to ${stageDir} failed" && exit 1; }

sudo chown -R $USER: "${stageDir}/."

echo "Applying patch ${SCRIPTDIR}/ServiceDashboard.patch ..."
patch -u -p0 -d "${BUILDDIR}" < "${SCRIPTDIR}/ServiceDashboard.patch"
