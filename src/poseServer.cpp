#include "ros/ros.h" 
#include "cwork4/getRelativePose.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Pose.h"
#include "tf/transform_listener.h"

using namespace std;

bool service_callback(cwork4::getRelativePose::Request &req, cwork4::getRelativePose::Response &res) {
    bool working_fine = true;

    tf::TransformListener listener;
    tf::StampedTransform transform;

    cout<<req.ref_frame.data<<endl<<req.frame.data<<endl;

    try {
        listener.lookupTransform(req.ref_frame.data, req.frame.data, ros::Time(0), transform);
        working_fine = true;    
        res.pose.position.x = transform.getOrigin().x();
        res.pose.position.y = transform.getOrigin().y();
        res.pose.position.z = transform.getOrigin().z();
        res.pose.orientation.x = transform.getRotation().x();
        res.pose.orientation.y = transform.getRotation().y();
        res.pose.orientation.z = transform.getRotation().z();
        res.pose.orientation.w = transform.getRotation().w();
    } catch (tf::TransformException ex) {
        ROS_ERROR("%s", ex.what());
        working_fine = false;
    }

    return working_fine;
}

int main(int argc, char** argv) {

    ros::init(argc, argv, "poseServer");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("getRelativePose", service_callback);

    ros::spin();

    return 0;
}