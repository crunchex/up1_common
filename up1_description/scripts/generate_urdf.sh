#!/usr/env/bin bash

# TODO: make this into an actual script at some point.

# rosdep install joint_state_publisher
# rosrun xacro xacro.py xacro/up1_two_arms.xacro > urdf/up1.urdf
# rosrun xacro xacro.py xacro/up1_right_arm.xacro > urdf/up1_right_arm.urdf
# rosrun xacro xacro.py xacro/up1_left_arm.xacro > urdf/up1_left_arm.urdf
# check_urdf urdf/up1.urdf
# urdf_to_graphiz urdf/up1.urdf
# roslaunch up1_description display.launch
