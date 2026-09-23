#!/bin/sh

# HTTP Header - Force download prompt with datetime stamp inserted into filename
DATETIME=$(date --utc +"%Y%m%dT%H%M%SZ")

VP3_PATH="/opt/appdata/CPM/VP3FileCreationApp/nvm/vp3"

TEMP_ROOT="/tmp/appdata/CPM/ServiceDashboard"

STORAGE_ROOT="/opt/appdata/CPM/ServiceDashboard/nvm"
/bin/mkdir -p "${STORAGE_ROOT}" 2> /dev/null

LAST_DOWNLOAD_TIME_FILE_PATH="${STORAGE_ROOT}/ProductivityData_DownloadTime"

TEMP_DATA_PREFIX="ProductivityData"

TEMP_DATA_PATH="${TEMP_ROOT}/${TEMP_DATA_PREFIX}"

/bin/rm -rf "${TEMP_DATA_PATH}"
/bin/rm -f "${TEMP_ROOT}/${TEMP_DATA_PREFIX}"*
/bin/mkdir -p "${TEMP_DATA_PATH}" 2> /dev/null

TEMP_TAR_FILE_NAME="${TEMP_DATA_PREFIX}_${DATETIME}.tar"
TEMP_TAR_FILE_PATH="${TEMP_ROOT}/${TEMP_TAR_FILE_NAME}"

TEMP_GZ_FILE_NAME="${TEMP_TAR_FILE_NAME}.gz"
TEMP_GZ_FILE_PATH="${TEMP_ROOT}/${TEMP_GZ_FILE_NAME}"

VP3_FILES="${VP3_PATH}/*.[vV][pP]3"

# This will give an error if no files are found
VP3_FILES=$(ls -t ${VP3_FILES} 2> /dev/null)

NUM_VP3_FILES=0

ERROR_OCCURRED=0

# Make symbolic links in a temp directory so that we can zip them up
for VP3_FILE in $VP3_FILES
do
  #echo ${VP3_FILE}
  /bin/ln -s "${VP3_FILE}" "${TEMP_DATA_PATH}/$(basename $VP3_FILE)" 2> /dev/null
  if [ $? -eq 0 ]
  then
    NUM_VP3_FILES=$((NUM_VP3_FILES+1))
  else
    ERROR_OCCURRED=1
  fi
done

# If everything is awesome, then make the tar file
if [ $ERROR_OCCURRED -eq 0 ] && [ $NUM_VP3_FILES -gt 0 ]
then
  /bin/tar --create --dereference --directory=$(dirname $TEMP_DATA_PATH) --file=${TEMP_TAR_FILE_PATH} $(basename $TEMP_DATA_PATH) 2> /dev/null
  ERROR_OCCURRED=$?
fi

# Clean up after yourself
# Remove the directory with the sym links
/bin/rm -rf "${TEMP_DATA_PATH}"

# If everything is awesome, then make the gzip file
if [ $ERROR_OCCURRED -eq 0 ] && [ $NUM_VP3_FILES -gt 0 ]
then
  /bin/gzip -f ${TEMP_TAR_FILE_PATH}
  ERROR_OCCURRED=$?
fi

# Clean up after yourself
# Remove the tar file (this should already have been done by gzip)
/bin/rm -f "${TEMP_TAR_FILE_PATH}"

# Respond back with the result
if [ $ERROR_OCCURRED -gt 0 ]
then
  echo "Status: 500 Internal Server Error"
  echo
else
  if [ $NUM_VP3_FILES -gt 0 ] && [ -f "${TEMP_GZ_FILE_PATH}" ]
  then
    echo "Content-Type: application/gzip; name=\"${TEMP_GZ_FILE_NAME}\""
    echo "Content-Disposition: attachment; filename=\"${TEMP_GZ_FILE_NAME}\""
    echo
    cat "${TEMP_GZ_FILE_PATH}"
    touch "${LAST_DOWNLOAD_TIME_FILE_PATH}"
  else
    echo "Content-Type: application/gzip; name=\"${TEMP_GZ_FILE_NAME}\""
    echo "Content-Disposition: attachment; filename=\"${TEMP_GZ_FILE_NAME}\""
    echo "Status: 204 No Content"
    echo "Content-Length: 0"
    echo
  fi
fi

# Clean up after yourself
# Remove the gz file
/bin/rm -f "${TEMP_GZ_FILE_PATH}"
