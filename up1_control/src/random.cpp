#include <moveit/move_group_interface/move_group.h>
#include <moveit/robot_interaction/robot_interaction.h>
#include <moveit/robot_interaction/interaction_handler.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "move_test");
  ros::NodeHandle node_handle;
  ros::AsyncSpinner spinner(1);
  spinner.start();

  moveit::planning_interface::MoveGroup group("right_arm");

  //ROS_INFO("Reference frame: %s", group.getPlanningFrame().c_str());

  // Enable Approximate Solutions - how to get this to work?
  // kinematics::KinematicsQueryOptions o = query_goal_state_->getKinematicsQueryOptions();
  // o.return_approximate_solution = true;
  // query_goal_state_->setKinematicsQueryOptions(o);

  // Planning to a Pose goal
  geometry_msgs::PoseStamped poseStamped = group.getCurrentPose();
  geometry_msgs::Pose target_pose1 = poseStamped.pose;
  target_pose1.orientation.w = target_pose1.orientation.w;
  target_pose1.position.x = target_pose1.position.x + 0.01;
  target_pose1.position.y = target_pose1.position.y;
  target_pose1.position.z = target_pose1.position.z - 0.01;
  group.setPoseTarget(target_pose1);

  moveit::planning_interface::MoveGroup::Plan my_plan;
  bool success = group.plan(my_plan);

  ros::shutdown();
  return 0;
}
