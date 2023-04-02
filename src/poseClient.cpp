#include "ros/ros.h" 
#include "cwork4/getRelativePose.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Pose.h"

using namespace std;

int main(int argc, char** argv) {
    ros::init(argc, argv, "poseClinet");
    ros::NodeHandle n;

    ros::ServiceClient client = n.serviceClient<cwork4::getRelativePose>("getRelativePose");

    cwork4::getRelativePose srv;
    srv.request.ref_frame.data = "/camera_link";
    srv.request.frame.data = "/camera_link";

    cout<<srv.request.ref_frame.data<<endl<<srv.request.frame.data<<endl;
    ROS_INFO("Waiting for the client server\n");

	client.waitForExistence();
	ROS_INFO("Client server up now\n");

    if (!client.call(srv)) {
        ROS_ERROR("Error calling the service");
        return 1;
    }

    cout<<srv.response.pose<<endl;

    return 0;
}