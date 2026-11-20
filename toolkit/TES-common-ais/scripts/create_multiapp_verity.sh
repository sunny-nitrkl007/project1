#######################
### Configurable values

### Verity file name variables
### format: (VERITY_PREFIX)_(SOFTWARE_PNUM)_(CHANGE_LEVEL)_(BUILD_ID).verity
export VERITY_PREFIX=aisCPM

export AIS_DIR=$1                               # Relative path to AIS directory (typically eta-ais)
export PLATFORM=$2                              # One of: A6N2, A6N1, D6XX, PL671
export RELEASE_DIR=$3                           # Location of VERITY_SETTINGS_FILE etc
export VERITY_SETTINGS_FILE=$3/$4               # Sets SOFTWARE_PNUM, CHANGE_LEVEL, BUILD_ID
export VERITY_FILE_LIST=$5                      # List of files to sync, paths are relative to the build directory (e.g. bin/pcm)

if [ -z ${VERITY_SETTINGS_FILE} ]; then
    echo "VERITY_SETTINGS_FILE must be set!"
    exit 1
fi

if [ -z ${VERITY_FILE_LIST} ]; then
    echo "VERITY_FILE_LIST must be set!"
    exit 2
fi

################################################
### Static values, should not need to be altered
VERITY_TOOL_PATH=prod/machineCommon/content/util/common/veritySetup
VERITY_OUT_PATH=$CAT_DIR/build-$PLATFORM/verity
VERITY_BUILD_SCRIPT=prod/machineCommon/content/scripts/build_verity.sh
BUILD_DIR=build-$PLATFORM
VERITY_DIR=$BUILD_DIR/$VERITY_PREFIX
VERITYSOURCE=$(find ${AIS_DIR}/$BUILD_DIR/prod -type f -name veritysetup.c)

source ${VERITY_SETTINGS_FILE}

# Assumes script is executed from base ssp directory
cd ${AIS_DIR}

# Replace the verity prefix in vehDataDir
sed -i "s,/CPM,/$VERITY_PREFIX," $BUILD_DIR/scripts/vehDataDir

source changeCatEnvToHere.sh

# Delete and create temporary directory
rm -rf $VERITY_DIR
mkdir -p $VERITY_DIR

# Build veritysetup
g++ -Wall -fpermissive -o $BUILD_DIR/verity/veritysetup ../$VERITYSOURCE -lpopt -DCRYPT_OPENSSL -lcrypto 2>/dev/null

# Sync files to temporary directory
rsync -r --delete --files-from=../$VERITY_FILE_LIST $BUILD_DIR $VERITY_DIR

# Copy any other files not in AIS_DIR
cp ../${RELEASE_DIR}/app_init.sh $VERITY_DIR

# Zip files
cd $VERITY_DIR
zip -r $VERITY_PREFIX.zip .

# Create Verity
cd ..
mkdir -p verity
bash $VERITY_BUILD_SCRIPT -z $VERITY_PREFIX/$VERITY_PREFIX.zip -p

# Remove temporary directory
rm -rf $VERITY_DIR
cd ..

# Restore the verity prefix in vehDataDir
# sed -i "s,$VERITY_PREFIX,CPM," $BUILD_DIR/scripts/vehDataDir
