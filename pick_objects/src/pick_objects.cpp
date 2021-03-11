#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal,goal2;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = 7.2099;
  goal.target_pose.pose.position.y = 5.5;
  goal.target_pose.pose.orientation.z = 1.5057;
  goal.target_pose.pose.orientation.w = 1.0;
   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
 if (ac.waitForResult()) {
  ROS_INFO("reached pickup_goal");
  sleep(5);
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();
  goal.target_pose.pose.position.x = 6.79;
  goal.target_pose.pose.position.y = -0.6025;
  goal.target_pose.pose.orientation.z = -1.5057;
  goal.target_pose.pose.orientation.w = 1.0;
   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending another_goal");
  ac.sendGoal(goal);
  ac.waitForResult();
  ROS_INFO("reached drop_off_goal");
  sleep(5);
}
  // Check if the robot reached its goal
  /*if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base moved 1 meter forward");
  else
    ROS_INFO("The base failed to move forward 1 meter for some reason");*/

  return 0;
}
