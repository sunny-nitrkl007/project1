cmake_minimum_required(VERSION 3.8)
project(demo_app_interfaces)

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(weigh_app_interfaces REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/DemoAppRequest.msg"
  "msg/DemoAppRequestBatch.msg"
  "msg/DemoAppCycle.msg"
  "msg/DemoAppHealth.msg"
  DEPENDENCIES weigh_app_interfaces
)

ament_export_dependencies(rosidl_default_runtime)

ament_package()
