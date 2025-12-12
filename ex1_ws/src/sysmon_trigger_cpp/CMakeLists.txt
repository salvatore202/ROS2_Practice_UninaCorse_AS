cmake_minimum_required(VERSION 3.8)
project(sysmon_trigger_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sysmonitor_interfaces REQUIRED)

add_executable(system_triggered_publisher src/system_triggered_publisher.cpp)

ament_target_dependencies(system_triggered_publisher
    rclcpp
    std_msgs
    sysmonitor_interfaces
)

install(TARGETS
    system_triggered_publisher
    DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
find_package(ament_lint_auto REQUIRED)
set(ament_cmake_copyright_FOUND TRUE)
set(ament_cmake_cpplint_FOUND TRUE)
ament_lint_auto_find_test_dependencies()
endif()

ament_package()
