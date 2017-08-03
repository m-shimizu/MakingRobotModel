#cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
cmake_minimum_required(VERSION 2.8.3)
#project(crawler_plugin_and_controller)

################################################
# Find System files
find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
# Find Gazebo
find_package(GAZEBO)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
#include_directories(${GAZEBO_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR}/msgs)
#link_directories(${GAZEBO_LIBRARY_DIRS} ${CMAKE_CURRENT_BINARY_DIR}/msgs)

add_compile_options(-std=gnu++11)
#add_compile_options(-traditional)

################################################
# Build flipper control message
include_directories(${CMAKE_CURRENT_BINARY_DIR}/msgs)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/msgs)
add_subdirectory(msgs)

###############################################
# Build the Crawler-Flipper Arm plugin
add_library(crawler_robot_1DEG SHARED src/crawler_robot_1DEG.cc)
target_link_libraries(crawler_robot_1DEG flipper_control_msgs ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES})
add_dependencies(crawler_robot_1DEG flipper_control_msgs)

###############################################
# Build the robot controller
add_executable (robot_teleop src/robot_teleop.cc)
target_link_libraries(robot_teleop flipper_control_msgs ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES})
add_dependencies(robot_teleop flipper_control_msgs)
