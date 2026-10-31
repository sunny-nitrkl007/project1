export TARGET_APP_VARIANT=adv
export PLATFORM=A7H4

rm -rf build
cmake -B build -DPLATFORM=A7H4
cmake --build build --verbose