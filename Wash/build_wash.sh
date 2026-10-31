#!/bin/bash

# determine this scripts local directory
SCRIPTDIR=$(dirname $0)
SOURCEDIR=${SCRIPTDIR}/content

echo "SOURCEDIR=${SOURCEDIR}"

BUILDDIR=$1
echo "BUILDDIR=${BUILDDIR}"

OUTPUTDIR="${BUILDDIR}/Wash"

mkdir -p "${OUTPUTDIR}"

echo "Syncing ${SOURCEDIR} to ${OUTPUTDIR} ..."
sudo rsync -rlW --delete --inplace "${SOURCEDIR}/." "${OUTPUTDIR}/." || \
    { echo "ERROR: rsync of ${SOURCEDIR}/. to ${OUTPUTDIR} failed" && exit 1; }

sudo chown -R $USER: "${OUTPUTDIR}/."
