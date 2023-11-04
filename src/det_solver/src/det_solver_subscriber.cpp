#include "ros/ros.h"
#include "det_solver/solver.h"

void chatterCallback(const det_solver::solver::Response &msg) {
    ROS_INFO("Subscriber caught message: %f", msg.det);
    if (fmod(msg.det, 2) == 0.f) {
        ROS_INFO_STREAM("even");
    } else {
        ROS_INFO_STREAM("odd");
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "det_solver");
    ros::NodeHandle nh;
    ROS_INFO("det solver subscriber started");

    std::string topic_name;
    ros::param::get("det_solver_topic_name", topic_name);
    ROS_INFO_STREAM(topic_name);
    ros::Subscriber det_sub = nh.subscribe(topic_name, 16, chatterCallback);
    ros::spin();
    return 0;
}
