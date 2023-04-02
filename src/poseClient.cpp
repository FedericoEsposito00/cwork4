#include "ros/ros.h" 
#include "cwork4/getRelativePose.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Pose.h"
#include "tf/transform_broadcaster.h"

using namespace std;

int main(int argc, char** argv) {
    ros::init(argc, argv, "poseClinet");
    ros::NodeHandle n;

    ros::ServiceClient client = n.serviceClient<cwork4::getRelativePose>("getRelativePose");

    cwork4::getRelativePose srv;
    srv.request.ref_frame.data = "/base_link";
    srv.request.frame.data = "/camera_link";

    //cout<<srv.request.ref_frame.data<<endl<<srv.request.frame.data<<endl;
    ROS_INFO("Waiting for the client server\n");

	client.waitForExistence();
	ROS_INFO("Client server up now\n");

    tf::TransformBroadcaster br;
    tf::Transform transform;

    ros::Rate rate(10);

    while (ros::ok()) {

        if (!client.call(srv)) {
            ROS_ERROR("Error calling the service");
            return 1;
        }

        cout<<srv.response.pose<<endl;
        
        tf::Quaternion q(srv.response.pose.orientation.x, srv.response.pose.orientation.y, srv.response.pose.orientation.z, srv.response.pose.orientation.w);

        transform.setOrigin(tf::Vector3(srv.response.pose.position.x, srv.response.pose.position.y, srv.response.pose.position.z));
        transform.setRotation(q);
    
        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "base_link", "camera_link2"));
        rate.sleep();
    }



    return 0;
}