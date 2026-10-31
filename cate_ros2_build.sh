set -e
export ROS2_SDK_PACKAGE_NAME="cate_ros2"
export ROS2_SDK_PACKAGE_VERSION="jazzy-test-4"
export ROS2_SDK_PACKAGE_ID="32c4b6ffa78d2cc335909101a0302a7ff8c79c5c"
export ROS2_SDK_PACKAGE_ARCH="armv8" #not using
export ROS2_SDK_PACKAGE_BUILD_TYPE="RelWithDebInfo" #not using
export ROS2_SDK_REMOTE="cat-e-conan-rel"
export ROS2_SDK_PACKAGE="${ROS2_SDK_PACKAGE_NAME}/${ROS2_SDK_PACKAGE_VERSION}:${ROS2_SDK_PACKAGE_ID}"
export DEST="$(pwd)/ros2_sdk"


CACHE_PATH=$(conan cache path "${ROS2_SDK_PACKAGE}")

conan download "${ROS2_SDK_PACKAGE}" -r="${ROS2_SDK_REMOTE}"

echo "CACHE_PATH=${CACHE_PATH}"
echo "DEST=${DEST}"

mkdir -p "${DEST}"

if [ -d "${CACHE_PATH}" ]; then
    cp -a "${CACHE_PATH}/." "${DEST}/"
else
    echo "Package path not found: ${CACHE_PATH}"
fi

#./CPM-Loader-ais/apps/conan_build.sh










#conan list cate_"ros2/jazzy-test-4:*" -c
#conan download "cate_ros2/1.0.0:*" -r=myremote --package-query="arch=armv8 AND build_type=Release"

