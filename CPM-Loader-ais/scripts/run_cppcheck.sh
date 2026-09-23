#!/bin/bash

function printUsage {
    echo "Usage: "
    echo "  run_cppcheck.sh <CPM_Loader-ais root directory>"
}

#Get the directory for mtp_pm00 folder
if [[ -d "${1}" ]]; then
    code_dir=${1}
else
    printUsage
    exit 1
fi  


#Check if cppcheck is installed
cppcheck --version
if [  $? -ne 0 ]; then
    echo ""
    echo "*** Installing cppcheck ***"
    sudo apt-get install cppcheck 
fi

SCRIPT_RDIR="$( dirname "${BASH_SOURCE[0]}" )"

#Create cpp_check_results folder in the parent directory
if [ ! -d "cpp_check_results" ]; then
    mkdir "cpp_check_results";
fi

#Goto code directory
cd $code_dir

echo ""
echo "*** CPM_Loader-ais ***"

OPTS="--enable=style \
--std=c11 --std=c++11 \
-UDEBUG -D__cplusplus -D__unix__ \
-D__ORDER_LITTLE_ENDIAN__=1234 -D__BYTE_ORDER__=__ORDER_LITTLE_ENDIAN__ \
--max-configs=1 \
--suppressions-list=$SCRIPT_RDIR/cppcheck_suppressions.txt \
--includes-file=$SCRIPT_RDIR/cppcheck_includes.txt \
--quiet"

IGNORE=""

echo "Running CPP Check on /apps folder"
IGNORE=""
echo cppcheck $OPTS $IGNORE apps 2> ~-/cpp_check_results/cppCheck_apps.txt
cppcheck $OPTS $IGNORE apps 2> ~-/cpp_check_results/cppCheck_apps.txt
echo ""

echo "Running CPP Check on /prod folder (without /prod/common/interfaces)"
IGNORE="-iprod/common/interfaces"
echo cppcheck $OPTS $IGNORE prod 2> ~-/cpp_check_results/cppCheck_prod.txt
cppcheck $OPTS $IGNORE prod 2> ~-/cpp_check_results/cppCheck_prod.txt
echo ""

echo "Running CPP Check on /prod/common/interfaces folder"
IGNORE=""
echo cppcheck $OPTS $IGNORE prod/common/interfaces 2> ~-/cpp_check_results/cppCheck_interfaces.txt
cppcheck $OPTS $IGNORE prod/common/interfaces 2> ~-/cpp_check_results/cppCheck_interfaces.txt
echo ""

# Go back to last directory
cd ~-

echo "Done running CPP Check. Results placed in /cpp_check_results"
echo ""
