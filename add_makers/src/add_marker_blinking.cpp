#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

ros::Publisher marker_pub;

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_marker_blinking");
  ros::NodeHandle n;
  ros::Rate r(1);
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 100);

  // Set our initial shape type to be a cube
uint32_t shape = visualization_msgs::Marker::CUBE;
bool carry_up=true;
bool pick_up= true;
  //this solve the problem  pickup marker does not appear
while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
  /*
  or sleep(5)
  */
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "cube_shape";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;
    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;
    marker.lifetime=ros::Duration();
    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = 0.0;
    marker.pose.position.y = 0.0;
    marker.pose.position.z = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;
    // Set the scale of the marker -- 1x1x1 here means 1m on a side

    marker.scale.x = 0.3;
    marker.scale.y = 0.3;
    marker.scale.z = 0.3;

    // Set the color -- be sure to set alpha to something non-zero!

    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

while (ros::ok()){
// pick_up zone
 if (pick_up){
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = 7.2099;
    marker.pose.position.y = 5.75;
    marker.pose.position.z = 0.0;
    marker.pose.orientation.z = 1.0;
    marker.pose.orientation.w = 1.0;
    marker_pub.publish(marker);
   sleep(10);
       // carry this object to another place
     pick_up=false;
ROS_INFO("pick_up ...");
        }

//carry the object
 else if (pick_up==false &&carry_up){

    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);
ROS_INFO("carry up ...");
carry_up=false;
}

 //Drop_off zone  
 else { 
     //drop_off the object here
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = 6.7;
    marker.pose.position.y = -0.61;
    marker.pose.orientation.z = 1.0;
    marker.pose.orientation.w =1.0;
     // sleep(5);   
    marker_pub.publish(marker);
ROS_INFO("Drop off ...");
}
  ros::spinOnce();
  r.sleep();
}
return 0;
}
