# #!/bin/bash

# set -euf -o pipefail

# SCRIPT_DIR=$(realpath $(dirname $0))
# ROOT_DIR=$(realpath ${SCRIPT_DIR})

# conan build ${ROOT_DIR} \
#     -pr:b=tgt_gcc_x86_64_ubuntu_tool_release \
#     -pr:h=tgt_gcc_arm64_guest_relwithdebinfo


#        -o "cpython/*:with_gdbm=False"



#!/bin/bash

set -euf -o pipefail

#type adv/sa
#export TARGET_APP_VARIANT=sa
export TARGET_APP_VARIANT=adv
export PLATFORM=A7H4

SCRIPT_DIR=$(realpath "$(dirname "$0")")
ROOT_DIR=$(realpath "${SCRIPT_DIR}")

BUILD_DIR="${ROOT_DIR}/build"


clean() {
    echo "Cleaning build artifacts..."

    rm -rf "${BUILD_DIR}"
    rm -f "${ROOT_DIR}/CMakeUserPresets.json"
    find "${ROOT_DIR}" -name CMakeCache.txt -delete
    find "${ROOT_DIR}" -name CMakeFiles -type d -exec rm -rf {} + 2>/dev/null || true

    echo "Clean completed."
}

build() {
    echo "Starting Conan build..."
        # -pr:b=tgt_gcc_x86_64_ubuntu_tool_release \
        # -pr:h=tgt_gcc_arm64_guest_relwithdebinfo
    conan build "${ROOT_DIR}" \
        -pr:b=tgt_gcc_x86_64_ubuntu_workstation \
        -pr:h=tgt_gcc_arm64_guest_os_26_3_0 \
        -s:b build_type=RelWithDebInfo \
        -s:h build_type=RelWithDebInfo \
        -c:b tools.system.package_manager:mode=install \
        -c:h tools.system.package_manager:mode=install \
        -o "cpython/*:with_tkinter=False" \
        -o "cpython/*:with_curses=False" \
        --build=missing
        # --build=boost/1.83.0 \
        # --build=cate_sdk_arm64_guest/arm64_guest_os_2026.3.0 \
        # --build=cpython/3.12.7 \
        # --build=b2/5.3.3 \
        # --build=gdbm/1.23 \
        # --build=xz_utils/5.4.5
        
        # --build=missing


        # -o "cpython/*:with_tkinter=False" \
        # -o "cpython/*:with_curses=False" \
        #         -c tools.system.package_manager:mode=install \

        # conan build "${ROOT_DIR}" \
        # -pr:b=tgt_gcc_x86_64_ubuntu_workstation \
        # -pr:h=tgt_gcc_arm64_guest \
        # -s:b build_type=Release \
        # -s:h build_type=RelWithDebInfo \
        # -o "cpython/*:with_tkinter=False" \
        # -o "cpython/*:with_curses=False" \
        # --build=missing \
        # -c tools.system.package_manager:mode=install
}

graph() {
    echo "Starting Conan graph..."
    #conan graph info . \
    conan graph info . --format=html > graph.html \
        -pr:b=tgt_gcc_x86_64_ubuntu_workstation \
        -pr:h=tgt_gcc_arm64_guest 
}

case "${1:-build}" in
    build)
        build
        ;;
    clean)
        clean
        ;;
    graph)
        graph
        ;;    
    rebuild)
        clean
        build
        ;;
    *)
        echo "Usage: $0 {build|clean|rebuild}"
        exit 1
        ;;
esac







# # Build
# ./conan_build.sh

# # Build explicitly
# ./conan_build.sh build

# # Clean only
# ./conan_build.sh clean

# # Clean + Build
# ./conan_build.sh rebuild


# conan build "${ROOT_DIR}" \
#     -pr:b=tgt_gcc_x86_64_ubuntu_workstation \
#     -pr:h=tgt_gcc_arm64_guest \
#     -s:b build_type=Release \
#     -s:h build_type=RelWithDebInfo \
#     --build=missing







#conan remove "openssl/*" -c
# conan install   --requires=openssl/3.5.8   -pr:b=tgt_gcc_x86_64_ubuntu_workstation   -pr:h=tgt_gcc_arm64_guest   --build=missing



# python issue fix


# export LD_LIBRARY_PATH=/home/u_via/.conan2/p/opens2331352ca1b62/p/lib:$LD_LIBRARY_PATH

# /home/u_via/.conan2/p/b/cpythfe50a280aae42/p/bin/python3.12 -c "
# import ssl
# print(ssl.OPENSSL_VERSION)
# "

# def package_info(self):
#     self.runenv_info.prepend_path(
#         "LD_LIBRARY_PATH",
#         os.path.join(self.package_folder, "lib")
#     )