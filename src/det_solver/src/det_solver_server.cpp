#include "ros/ros.h"
#include "Matrix.h"
#include "det_solver/solver.h"

bool det_solve(det_solver::solver::Request &req, det_solver::solver::Response &res) {
    auto size = (int)sqrt(req.data.size());
    Matrix mat = Matrix(size, size).fill_from_array(req.data.data());
    res.det = mat.det();

    // std::cout << mat;

    ROS_INFO("Request: calculate determinant for matrix");
    ROS_INFO("sending back response: %f", res.det);
    return true;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "det_solver_server");
    ros::NodeHandle nh;

    ros::ServiceServer service = nh.advertiseService("det_solver", det_solve);
    ROS_INFO("Ready to calculate determinant");
    ros::spin();
    return 0;
}