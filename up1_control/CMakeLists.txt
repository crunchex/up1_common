cmake_minimum_required(VERSION 2.8.3)
project(up1_control)

find_package(catkin REQUIRED COMPONENTS
  roslaunch
  roscpp
  moveit_ros_planning_interface
  moveit_ros_robot_interaction
)

find_package(Qt4 REQUIRED)

catkin_package(
  CATKIN_DEPENDS roscpp moveit_ros_planning_interface moveit_ros_robot_interaction
)

include_directories(include ${Boost_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS})

add_executable(random src/random.cpp)
target_link_libraries(random ${catkin_LIBRARIES} ${Boost_LIBRARIES})

# http://wiki.ros.org/roslaunch#Catkin
roslaunch_add_file_check(launch)

install(DIRECTORY config launch scripts
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

catkin_install_python(PROGRAMS
  scripts/cmdr_joy
  scripts/moveit_joy
  scripts/teleop_arm_joy
  scripts/teleop_arm_key
  scripts/teleop_eef_joy
  scripts/teleop_twist_joy
  scripts/teleop_twist_key
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
