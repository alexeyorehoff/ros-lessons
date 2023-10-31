#include <iostream>
#include <string>
#include "ros/ros.h"
#include "det_solver/solver.h"



int main(int argc, char **argv) {
    ros::init(argc, argv, "det_solver_client");
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<det_solver::solver>("det_solver");
    det_solver::solver srv;


    while (ros::ok()) {
        int array_size = 0;
        std::cout << "Enter the size of the square matrix or enter 0 to quit" << std::endl;
        std::cin >> array_size;
        if (array_size == 0) break;
        srv.request.data.resize(array_size * array_size);

        for (int idx = 0; idx < array_size * array_size; idx++) {
            std::cout << "\nEnter " << idx << " element of matrix: ";
            std::cin >> srv.request.data[idx];
        }

        if (client.call(srv)) {
            double response = srv.response.det;
            ROS_INFO("Response: %f", response);
        } else {
            ROS_ERROR("Failed to call service det_solver");
            return 1;
        }
    }
    return 0;
}