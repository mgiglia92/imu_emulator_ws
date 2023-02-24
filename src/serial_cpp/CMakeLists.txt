cmake_minimum_required(VERSION 3.8)
project(serial_cpp)

# if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#   add_compile_options(-Wall -Wextra -Wpedantic)
# endif()
include_directories("${CMAKE_SOURCE_DIR}/include")

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rclcpp REQUIRED)
add_executable(serial_node src/serial_node.cpp)

target_link_libraries(serial_node CppLinuxSerial)

ament_target_dependencies(serial_node rclcpp std_msgs)
install(TARGETS 
  serial_node 
  DESTINATION lib/${PROJECT_NAME}
  )


ament_package()
