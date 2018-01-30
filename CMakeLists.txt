cmake_minimum_required(VERSION 2.8.3)
project(rviz_visualise_tools)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
include_directories(SYSTEM include )
#ROS_DEBUG
add_definitions(-DCMAKE_BUILD_TYPE=Debug)
add_definitions(-std=c++11)
add_definitions(-W -Wall -Wextra
        #-Wcast-qual
        -Wwrite-strings -Wunreachable-code -Wpointer-arith
        -Winit-self -Wredundant-decls
        -Wno-unused-parameter -Wno-unused-function)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  geometry_msgs
  std_msgs
)

catkin_package(
    CATKIN_DEPENDS
        roscpp
        geometry_msgs
    INCLUDE_DIRS
        include
)
add_library(visual_tool SHARED src/visual_tool.cpp)

include_directories(${catkin_INCLUDE_DIRS})
add_executable(rviz_visualize_tools src/demo_main.cpp)
target_link_libraries(rviz_visualize_tools visual_tool ${catkin_LIBRARIES})