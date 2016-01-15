#include <moveit/move_group_interface/move_group.h>
#include <moveit/robot_interaction/robot_interaction.h>
#include <moveit/robot_interaction/interaction_handler.h>

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/JointState.h"
#include "sensor_msgs/Joy.h"
#include "teleop_eef_joy.h"

#include <sstream>

void updateJointPositions(const sensor_msgs::JointState::ConstPtr& msg) {
  for(std::size_t i = 0; i < msg->position.size(); ++i) {
    // ROS_INFO("Joint %s: %f", msg->name[i].c_str(), msg->position[i]);
  }
}

void printAxes(const sensor_msgs::Joy::ConstPtr& msg) {
  std::ostringstream a;
  a << "[ " << msg->axes[0];
  for(std::size_t i = 1; i < msg->axes.size(); ++i) {
    a << ", " << msg->axes[i];
  }
  a << "]";

  std::string axes(a.str());
  ROS_INFO("Joy (axes): %s", axes.c_str());
}

void printButtons(const sensor_msgs::Joy::ConstPtr& msg) {
  std::ostringstream b;
  b << "[ " << msg->buttons[0];
  for(std::size_t i = 1; i < msg->buttons.size(); ++i) {
    b << ", " << msg->buttons[i];
  }
  b << "]";

  std::string buttons(b.str());
  ROS_INFO("Joy (buttons): %s", buttons.c_str());
}

void updateJoy(const sensor_msgs::Joy::ConstPtr& msg) {
  geometry_msgs::Pose currPose = arm_group.getCurrentPose().pose;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "teleop_eef_joy");
  ros::NodeHandle n;
  ros::Subscriber jointStateSub = n.subscribe("up1/joint_states", 10, updateJointPositions);
  ros::Subscriber joySub = n.subscribe("joy", 10, updateJoy);

  moveit::planning_interface::MoveGroup group("right_arm");
  teleop_eef_joy::arm_group = group;

  ros::spin();
  return 0;
}
