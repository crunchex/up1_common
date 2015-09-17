#!/usr/env/bin bash

# TODO: make this into an actual script at some point.

# rosrun collada_urdf urdf_to_collada up1_right_arm.urdf up1_right_arm.dae
# rosrun moveit_ikfast round_collada_numbers.py up1_right_arm.dae up1_right_arm_rounded.dae 5
# openrave-robot.py up1_right_arm_rounded.dae --info links
# python `openrave-config --python-dir`/openravepy/_openravepy_0_9/ikfast.py --robot=`rospack find up1_description`/robots/up1_right_arm_rounded.dae --iktype=translationdirection5d --baselink=1 --eelink=8 --savefile=ikfast_up1_right_arm.cpp
# catkin_create_pkg up1_right_arm_kinematics
# cp ../up1_description/robots/ikfast_up1_right_arm.cpp .
# rosrun moveit_ikfast create_ikfast_moveit_plugin.py up1 right_arm up1_right_arm_kinematics ikfast_up1_right_arm.cpp
# catkin_make
