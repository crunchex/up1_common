cmake_minimum_required(VERSION 2.8.3)
project(up1_description)

find_package(catkin REQUIRED COMPONENTS roslaunch)

catkin_package()

# http://wiki.ros.org/roslaunch#Catkin
roslaunch_add_file_check(launch)

# TODO: rename xacro => urdf
# TODO: create real scripts
install(DIRECTORY config launch meshes xacro
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
