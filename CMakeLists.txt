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
#find_package(PkgConfig)
#pkg_check_modules(BFL REQUIRED bfl)
#
#message("BFL include dirs:" ${BFL_INCLUDE_DIRS})
#message("BFL library dirs:" ${BFL_LIBRARY_DIRS})
#include_directories(${BFL_INCLUDE_DIRS})
#link_directories(${BFL_LIBRARY_DIRS})
catkin_package(
    CATKIN_DEPENDS
        roscpp
        geometry_msgs
    INCLUDE_DIRS
        include
)
set(BOOST_ROOT "/home/pengjiawei/boost_1_63/include/")
#include_directories("/home/pengjiawei/boost_1_63/include/")
#link_libraries("/home/pengjiawei/boost_1_63/lib")

find_package(Boost 1.63.0 COMPONENTS thread serialization REQUIRED)
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")

add_library(visual_tool SHARED src/visual_tool.cpp)
message(${catkin_INCLUDE_DIRS})
include_directories(${catkin_INCLUDE_DIRS})
add_executable(rviz_visualize_tools src/demo_main.cpp)
target_link_libraries(rviz_visualize_tools visual_tool ${catkin_LIBRARIES} boost_thread boost_serialization)
#target_link_libraries(rviz_visualize_tools $(BFL_LIBRARY_DIRS))