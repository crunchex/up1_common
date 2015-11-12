#include <ros/ros.h>
#include <control_msgs/GripperCommandAction.h>
#include <actionlib/client/simple_action_client.h>

// Our Action interface type, provided as a typedef for convenience
typedef actionlib::SimpleActionClient<control_msgs::GripperCommandAction> GripperClient;

class Gripper{
private:
  GripperClient* gripper_client_;

public:
  // Action client initialization
  Gripper(){

    // Initialize the client for the Action interface to the gripper controller
    //and tell the action client that we want to spin a thread by default
    gripper_client_ = new GripperClient("right_gripper_controller/gripper_action", true);

    // wait for the gripper action server to come up
    while(!gripper_client_->waitForServer(ros::Duration(5.0))){
      ROS_INFO("Waiting for the right_gripper_controller/gripper_action action server to come up");
    }
  }

  ~Gripper(){
    delete gripper_client_;
  }

  // Open the gripper
  void open(){
    control_msgs::GripperCommandGoal open;
    open.command.position = 0.08;
    open.command.max_effort = -1.0;  // Do not limit effort (negative)

    ROS_INFO("Sending open goal");
    gripper_client_->sendGoal(open);
    gripper_client_->waitForResult();
    if(gripper_client_->getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("The gripper opened!");
    else
      ROS_INFO("The gripper failed to open.");
  }

  // Close the gripper
  void close(){
    control_msgs::GripperCommandGoal squeeze;
    squeeze.command.position = 0.036;
    squeeze.command.max_effort = 50.0;  // Close gently

    ROS_INFO("Sending squeeze goal");
    gripper_client_->sendGoal(squeeze);
    gripper_client_->waitForResult();
    if(gripper_client_->getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("The gripper closed!");
    else
      ROS_INFO("The gripper failed to close.");
  }
};

int main(int argc, char** argv){
  ros::init(argc, argv, "up1_gripper");

  Gripper gripper;

  gripper.open();
  //gripper.close();

  return 0;
}
