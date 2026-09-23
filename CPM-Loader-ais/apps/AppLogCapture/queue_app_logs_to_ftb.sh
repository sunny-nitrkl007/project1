#!/bin/sh

DATETIME=$(date --utc +"%Y%m%dT%H%M%SZ")



#!/bin/bash
filename='/opt/appdata/CPM/debug/product_id.txt'
while read -r line; do
# reading each line
name="$line"
done < $filename


#touch "/opt/appdata/CPM/FileTransferBridgeApp/queue_app_logs_to_ftb_was_here_${DATETIME}.txt"

TEMP_ROOT="/tmp/appdata/CPM/AppLogCapture"

TEMP_DATA_PREFIX="10496_AppLog"

TEMP_DATA_PATH="${TEMP_ROOT}/${TEMP_DATA_PREFIX}"

/bin/rm -rf "${TEMP_DATA_PATH}"

/bin/rm -f "${TEMP_ROOT}/${TEMP_DATA_PREFIX}"*

/bin/mkdir -p "${TEMP_DATA_PATH}" 2> /dev/null

# 'ls' will give an error if no files are found, hence 2> /dev/null
# Filtering out log files that are particularly annoying and/or unuseful
IN_FILES="
$(ls -t /opt/appdata/CPM/debug/*.[cC][sS][vV] 2> /dev/null | grep -v -e 'weigh_cal_results_')
$(ls -t /opt/appdata/CPM/debug/*.[tT][xX][tT] 2> /dev/null)
$(ls -t /tmp/appdata/CPM/log/*[oO][uU][tT] |
  grep -v -e 'baseDiagManager*' -e 'Xcp*' -e 'TimeSyncSpoofMaster*' -e 'TimeSyncFromRtcToUdp*')
"

NUM_IN_FILES=0

# Make symbolic links in a temp directory so that we can zip them up
for IN_FILE in $IN_FILES
do
  #echo ${IN_FILE}
  IN_FILE_NAME=$(basename "${IN_FILE}")
  /bin/ln -s "${IN_FILE}" "${TEMP_DATA_PATH}/${IN_FILE_NAME}" 2> /dev/null
  if [ $? -eq 0 ]
  then
    NUM_IN_FILES=$((NUM_IN_FILES+1))
  fi
done

ERROR_OCCURRED=1

TEMP_TAR_FILE_NAME="${TEMP_DATA_PREFIX}_${name}_${DATETIME}.tar"

TEMP_TAR_FILE_PATH="${TEMP_ROOT}/${TEMP_TAR_FILE_NAME}"

# If everything is awesome, then make the tar file
if [ $NUM_IN_FILES -gt 0 ]
then
  /bin/tar --create --dereference --directory="$(dirname $TEMP_DATA_PATH)" --file="${TEMP_TAR_FILE_PATH}" "$(basename $TEMP_DATA_PATH)" 2> /dev/null
  ERROR_OCCURRED=$?
fi

# Clean up after yourself
# Remove the directory with the sym links
/bin/rm -rf "${TEMP_DATA_PATH}"

TEMP_GZ_FILE_NAME="${TEMP_TAR_FILE_NAME}.gz"

TEMP_GZ_FILE_PATH="${TEMP_ROOT}/${TEMP_GZ_FILE_NAME}"

# If everything is awesome, then make the gzip file
if [ $ERROR_OCCURRED -eq 0 ]
then
  /bin/gzip -f "${TEMP_TAR_FILE_PATH}"
  ERROR_OCCURRED=$?
fi

# Clean up after yourself
# Remove the tar file (this should already have been done by gzip)
/bin/rm -f "${TEMP_TAR_FILE_PATH}"

# Move the file to the File Transfer Bridge tx directory
DEST_PATH="/opt/appdata/CPM/FileTransferBridgeApp/TxFiles"

/bin/mv -f "${TEMP_GZ_FILE_PATH}" "${DEST_PATH}"
