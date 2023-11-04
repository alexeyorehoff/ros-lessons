#include "ros/ros.h"
#include <string>
#include "Matrix.h"
#include "det_solver/solver.h"

ros::Publisher det_solver_publisher;


bool det_solve(det_solver::solver::Request &req, det_solver::solver::Response &res) {
    auto size = (int)sqrt(req.data.size());
    Matrix mat = Matrix(size, size).fill_from_array(req.data.data());
    res.det = mat.det();

    // std::cout << mat;

    ROS_INFO("Request: calculate determinant for matrix");
    ROS_INFO("sending back response: %f", res.det);

    det_solver_publisher.publish(res);

    return true;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "det_solver_server");
    ros::NodeHandle nh;

    std::string det_solver_topic_name = "solver_topic";
    ros::param::set("det_solver_topic_name", det_solver_topic_name);

    ros::ServiceServer service = nh.advertiseService("det_solver", det_solve);
    det_solver_publisher = nh.advertise<det_solver::solver::Response>(det_solver_topic_name, 16);

    ROS_INFO("Started publisher %s",det_solver_topic_name.data());

    ROS_INFO("Ready to calculate determinant");
    ros::spin();
    return 0;
}