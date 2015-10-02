cmake_minimum_required(VERSION 2.8.3)
project(up1_control)

find_package(catkin REQUIRED COMPONENTS roslaunch)

catkin_package()

# http://wiki.ros.org/roslaunch#Catkin
roslaunch_add_file_check(launch)

catkin_install_python(PROGRAMS
  scripts/cmdr_joy
  scripts/moveit_joy
  scripts/teleop_arm_joy
  scripts/teleop_arm_key
  scripts/teleop_eef_joy
  scripts/teleop_twist_joy
  scripts/teleop_twist_key
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

install(DIRECTORY config launch scripts
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
