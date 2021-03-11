#! /bin/bash
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch"&
sleep 5
xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch"&
sleep 5
xterm -e "roslaunch turtlebot_rviz_launchers view_teleop_navigation.launch"&
sleep 5
xterm -e "rosrun add_makers add_makers"
