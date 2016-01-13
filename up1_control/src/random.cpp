#include <moveit/move_group_interface/move_group.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "move_group_interface_tutorial");
  ros::NodeHandle node_handle;
  ros::AsyncSpinner spinner(1);
  spinner.start();

  /* This sleep is ONLY to allow Rviz to come up */
  sleep(20.0);

  moveit::planning_interface::MoveGroup group("right_arm");
  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;

  // (Optional) Create a publisher for visualizing plans in Rviz.
  ros::Publisher display_publisher = node_handle.advertise<moveit_msgs::DisplayTrajectory>("/move_group/display_planned_path", 1, true);
  moveit_msgs::DisplayTrajectory display_trajectory;

  ROS_INFO("Reference frame: %s", group.getPlanningFrame().c_str());
  ROS_INFO("Reference frame: %s", group.getEndEffectorLink().c_str());

  // Planning to a Pose goal
  // ^^^^^^^^^^^^^^^^^^^^^^^
  // We can plan a motion for this group to a desired pose for the
  // end-effector.
  geometry_msgs::Pose target_pose1;
  target_pose1.orientation.w = 1.0;
  target_pose1.position.x = 0.28;
  target_pose1.position.y = -0.7;
  target_pose1.position.z = 1.0;
  group.setPoseTarget(target_pose1);

  moveit::planning_interface::MoveGroup::Plan my_plan;
  bool success = group.plan(my_plan);

  ROS_INFO("Visualizing plan 1 (pose goal) %s",success?"":"FAILED");
  /* Sleep to give Rviz time to visualize the plan. */
  sleep(5.0);

  // Visualizing plans
  // ^^^^^^^^^^^^^^^^^
  // Now that we have a plan we can visualize it in Rviz.  This is not
  // necessary because the group.plan() call we made above did this
  // automatically.  But explicitly publishing plans is useful in cases that we
  // want to visualize a previously created plan.
  if (1)
  {
    ROS_INFO("Visualizing plan 1 (again)");
    display_trajectory.trajectory_start = my_plan.start_state_;
    display_trajectory.trajectory.push_back(my_plan.trajectory_);
    display_publisher.publish(display_trajectory);
    /* Sleep to give Rviz time to visualize the plan. */
    sleep(5.0);
  }

  std::vector<double> group_variable_values;
  group.getCurrentState()->copyJointGroupPositions(group.getCurrentState()->getRobotModel()->getJointModelGroup(group.getName()), group_variable_values);

  // Now, let's modify one of the joints, plan to the new joint
  // space goal and visualize the plan.
  group_variable_values[0] = -1.0;
  group.setJointValueTarget(group_variable_values);
  success = group.plan(my_plan);

  ROS_INFO("Visualizing plan 2 (joint space goal) %s",success?"":"FAILED");
  /* Sleep to give Rviz time to visualize the plan. */
  sleep(5.0);

  // Cartesian Paths
  // ^^^^^^^^^^^^^^^
  // You can plan a cartesian path directly by specifying a list of waypoints
  // for the end-effector to go through. Note that we are starting
  // from the new start state above.  The initial pose (start state) does not
  // need to be added to the waypoint list.
  std::vector<geometry_msgs::Pose> waypoints;

  geometry_msgs::Pose target_pose3 = start_pose2;
  target_pose3.position.x += 0.2;
  target_pose3.position.z += 0.2;
  waypoints.push_back(target_pose3);  // up and out

  target_pose3.position.y -= 0.2;
  waypoints.push_back(target_pose3);  // left

  target_pose3.position.z -= 0.2;
  target_pose3.position.y += 0.2;
  target_pose3.position.x -= 0.2;
  waypoints.push_back(target_pose3);  // down and right (back to start)

  // We want the cartesian path to be interpolated at a resolution of 1 cm
  // which is why we will specify 0.01 as the max step in cartesian
  // translation.  We will specify the jump threshold as 0.0, effectively
  // disabling it.
  moveit_msgs::RobotTrajectory trajectory;
  double fraction = group.computeCartesianPath(waypoints,
                                               0.01,  // eef_step
                                               0.0,   // jump_threshold
                                               trajectory);

  ROS_INFO("Visualizing plan 4 (cartesian path) (%.2f%% acheived)",
        fraction * 100.0);
  /* Sleep to give Rviz time to visualize the plan. */
  sleep(15.0);

  ros::shutdown();
  return 0;
}
