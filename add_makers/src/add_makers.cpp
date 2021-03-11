#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
ros::Publisher marker_pub;
float x=0.0,y=0.0,w=0.0;
// callback function to track values of robot (pose and orientation)
void call_back(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg){
 ::x=msg->pose.pose.position.x;
  ::y=msg->pose.pose.position.y;
  ::w=msg->pose.pose.orientation.w;
//take all the values of the code below here cause it read it at all
ROS_INFO("positionX-> =%f",x);
ROS_INFO("positionY-> =%f",y);
ROS_INFO("orientationW-> =%f",w);

}


int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_makers");
  ros::NodeHandle n;
  ros::Rate r(1);
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1000);

  ros::Subscriber sub_pose=n.subscribe("amcl_pose",1000,call_back);

  // Set our initial shape type to be a cube
uint32_t shape = visualization_msgs::Marker::CUBE;


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
    marker.pose.position.x = 7.2099;
    marker.pose.position.y = 5.75;
    marker.pose.orientation.z = -0.72;
    marker.pose.orientation.w = 0.75;
    // Set the scale of the marker -- 1x1x1 here means 1m on a side

    marker.scale.x = 0.3;
    marker.scale.y = 0.3;
    marker.scale.z = 0.3;

    // Set the color -- be sure to set alpha to something non-zero!

    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;


//read the values odometry  
ROS_INFO("positionX-> =%f",x);
ROS_INFO("positionY-> =%f",y);
ROS_INFO("orientationW-> =%f",w);

bool catchup_the_object= true;
while (ros::ok()){
// if there is nothing then add maker
 if (catchup_the_object){
   
    marker_pub.publish(marker);
    float distx=fabs(marker.pose.position.x-x);
    //ROS_INFO("distx1-> =%f",distx);
    float disty=fabs(marker.pose.position.y-y);
     //ROS_INFO("disty1-> =%f",disty);
       if (distx<0.9 && disty <0.9)
    { sleep(5);
       // carry this object to another place
        marker.action = visualization_msgs::Marker::DELETE;
        marker_pub.publish(marker);
        catchup_the_object=false;
        }
}
 //   
 else { 
     //drop_off the object here
    marker.pose.position.x = 6.7;
    marker.pose.position.y = -0.61;
    marker.pose.orientation.z = 1.0;
    marker.pose.orientation.w =1.0;
    float distx=fabs(marker.pose.position.x-x);
   // ROS_INFO("distx2-> =%f",distx);
    float disty=fabs(marker.pose.position.y-y);
    //ROS_INFO("disty2-> =%f",disty);
   if (distx<0.8 && disty <0.8){
          sleep(5);
       marker.action = visualization_msgs::Marker::ADD;
       marker_pub.publish(marker);
       }

}
     // ROS_INFO("frist marker");
   
    // Publish the marker
/*
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }*/

  ros::spinOnce();
  r.sleep();
}
return 0;
}
