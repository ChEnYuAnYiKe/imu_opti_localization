cmake_minimum_required(VERSION 3.0.2)
project(imu_filter)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES imu_filter
  CATKIN_DEPENDS roscpp sensor_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(imu_filter_node src/imu_filter_node.cpp)
target_link_libraries(imu_filter_node ${catkin_LIBRARIES})
