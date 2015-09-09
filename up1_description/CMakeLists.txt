cmake_minimum_required(VERSION 2.8.3)
project(up1_description)

find_package(catkin)
catkin_package()

foreach(dir launch meshes urdf)
  install(DIRECTORY ${dir}/
    DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
endforeach(dir)

install(
  FILES urdf.rviz urdf.vcg
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
