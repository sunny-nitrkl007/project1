

echo "Copying header file................."
SRCPATH=/home/u_via/repo/ros2_model/install
DESTPATH=/home/u_via/repo/ssp-CPM_Loader-ais/ros2_models/include/

cp -r ${SRCPATH}/job_mgr_interfaces/include/job_mgr_interfaces/job_mgr_interfaces ${DESTPATH}

cp -r ${SRCPATH}/weigh_app_interfaces/include/weigh_app_interfaces/weigh_app_interfaces ${DESTPATH}

cp -r ${SRCPATH}/cpm_common_interfaces/include/cpm_common_interfaces/cpm_common_interfaces ${DESTPATH}

echo "Copying header Completed ................."




LIB_SRCPATH=/home/u_via/repo/ros2_model/install
LIB_DESTPATH=/home/u_via/repo/ssp-CPM_Loader-ais/ros2_models/lib

echo "Deleteing file................."

rm -rf ${LIB_DESTPATH}
mkdir -p ${LIB_DESTPATH}

mkdir -p ${LIB_DESTPATH}/job_mgr_interfaces
mkdir -p ${LIB_DESTPATH}/weigh_app_interfaces
mkdir -p ${LIB_DESTPATH}/cpm_common_interfaces


echo "Copying lib file................."
cp -r ${LIB_SRCPATH}/job_mgr_interfaces/lib/* ${LIB_DESTPATH}/job_mgr_interfaces/

cp -r ${LIB_SRCPATH}/weigh_app_interfaces/lib/* ${LIB_DESTPATH}/weigh_app_interfaces/

cp -r ${LIB_SRCPATH}/cpm_common_interfaces/lib/* ${LIB_DESTPATH}/cpm_common_interfaces/

echo "Copying Lib Completed ................."