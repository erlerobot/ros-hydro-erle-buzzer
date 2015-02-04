cmake_minimum_required(VERSION 2.8.3)
project(ros_erle_buzzer)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)

## Declare ROS messages and services
add_message_files(DIRECTORY msg FILES buzzer.msg)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(ros_erle_buzzer_writer examples/ros_erle_buzzer_writer.cpp)
target_link_libraries(ros_erle_buzzer_writer ${catkin_LIBRARIES})
add_dependencies(ros_erle_buzzer_writer ros_erle_buzzer_generate_messages_cpp)

add_executable(ros_erle_buzzer_main src/ros_erle_buzzer_main.cpp src/ToneAlarmDriver.cpp)
target_link_libraries(ros_erle_buzzer_main ${catkin_LIBRARIES})
add_dependencies(ros_erle_buzzer_main ros_erle_buzzer_generate_messages_cpp)
