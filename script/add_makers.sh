#! /bin/bash
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find map)/worlds/U_building.world"&
sleep 5
xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find map)/maps/map.yaml"&
sleep 5
xterm -e "roslaunch turtlebot_rviz_launchers view_teleop_navigation.launch"&
sleep 5
xterm -e "rosrun add_makers add_marker_blinking"
