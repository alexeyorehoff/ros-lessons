#include <iostream>
#include <exception>
#include "ros/ros.h"
#include "det_solver/solver.h"


bool is_numerical(const std::string &str) {
    return std::all_of(str.begin(), str.end(), [](char c) {return std::isdigit(c) or c == '.';});
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "det_solver_client");
    ros::NodeHandle nh;

    ros::ServiceClient client = nh.serviceClient<det_solver::solver>("det_solver");
    det_solver::solver srv;

    while (ros::ok()) {
        int array_size;
        std::string input;
        std::cout << "Enter the size of the square matrix or enter 0 to quit" << std::endl;

        while (true) {
            std::cin >> input;
            if (is_numerical(input)) {
                array_size = std::stoi(input);
                break;
            } else ROS_ERROR("Matrix size must be numerical, enter again\r");
        }

        if (array_size == 0) break;

        srv.request.data.resize(array_size * array_size);

        for (int idx = 0; idx < array_size * array_size; idx++) {
            std::cout << "Enter " << idx << " element of matrix: ";
            input.clear();

            while (true) {
                std::cin >> input;
                if (is_numerical(input)) {
                    srv.request.data[idx] = std::stof(input);
                    break;
                } else
                    ROS_ERROR("Element must be numerical, enter again\r");
            }
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