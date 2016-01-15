cmake_minimum_required(VERSION 2.8.3)
project(up1_control)

find_package(catkin REQUIRED COMPONENTS
  roslaunch
  roscpp
  moveit_ros_planning_interface
  moveit_ros_robot_interaction
)

catkin_package(
  CATKIN_DEPENDS roscpp moveit_ros_planning_interface moveit_ros_robot_interaction
)

include_directories(include ${Boost_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS})

add_executable(random src/random.cpp)
target_link_libraries(random ${catkin_LIBRARIES} ${Boost_LIBRARIES})

add_executable(ik_test src/ik_test.cpp)
target_link_libraries(ik_test ${catkin_LIBRARIES} ${Boost_LIBRARIES})

add_executable(teleop_eef_joy src/teleop_eef_joy.cpp)
target_link_libraries(teleop_eef_joy ${catkin_LIBRARIES} ${Boost_LIBRARIES})

# http://wiki.ros.org/roslaunch#Catkin
roslaunch_add_file_check(launch)

install(
  DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
install(
  TARGETS random ik_test teleop_eef_joy
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

catkin_install_python(PROGRAMS
  scripts/cmdr_joy
  scripts/moveit_joy
  scripts/teleop_arm_joy
  scripts/teleop_arm_key
  scripts/teleop_eef_joy_py
  scripts/teleop_twist_joy
  scripts/teleop_twist_key
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
