#include "DataLinkDataPublish.h"

int main(int argc, char** argv)
{
    return ros2_wrapper::Ros2TaskWrapper::run<DemoApp>(argc, argv, "DemoApp");
}
