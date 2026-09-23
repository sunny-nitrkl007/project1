#!/bin/sh

# This script will cause the web browser to generate a prompt asking the user to download the file.

# HTTP Header - Force download prompt with datetime stamp inserted into filename
datetime=$(date --utc +'%Y%m%dT%H%M%SZ')

echo "Content-Type:text/csv; charset=utf-8; name=\"OperatorID_$datetime.csv\""
echo "Content-Disposition: attachment; filename=\"OperatorID_$datetime.csv\""
echo
# Must match path of tempRoot in LpsSaListMgrApp.rb
cat /tmp/appdata/CPM/LpsSaListMgrApp/OperatorID.csv
