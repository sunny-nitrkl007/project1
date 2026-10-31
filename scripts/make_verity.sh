#!/bin/bash
echo "Loading verity settings $1"
source $1
cd eta-ais
source ./changeCatEnvToHere.sh
if [ "$#" -ge 3 ]; then
    make -f ../eta-ais.mk BUILD_DIR=$2 $3
    EC=$?
else
    echo "BUILD_DIR must be specified as second argument"
    echo "verity target must be specified as third argument"
    EC=1
fi
cd ..
if [ "${EC}" -eq 0 ]; then
    echo "VERITY CREATED - eta_ais/$2/verity ($3)"
else
    echo "VERITY CREATION FAILED! - eta_ais/$2/verity ($3)"
fi
exit ${EC}
