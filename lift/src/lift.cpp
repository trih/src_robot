#include "ros/ros.h"
#include "BlackLib.h"
#include <sstream>
#include "std_msgs/String.h"
#include <iostream>

using namespace BlackLib;
using namespace std;


void liftCallback(const std_msgs::String::ConstPtr& msg)
{
        BlackLib::BlackGPIO lift1(BlackLib::GPIO_115, BlackLib::output, BlackLib::SecureMode);
        BlackLib::BlackGPIO lift2(BlackLib::GPIO_60, BlackLib::output, BlackLib::SecureMode);
    
        ROS_INFO("I heard: [%s]", msg->data.c_str());
        if (msg->data== "Up") {
		lift1.setValue(BlackLib::low);
		lift2.setValue(BlackLib::high);
	}

        if (msg->data=="Down") {
                lift1.setValue(BlackLib::high);
                lift2.setValue(BlackLib::low);

	}
}

int main(int argc, char **argv)
{
        ros::init(argc, argv, "lift_msg");
        ros::NodeHandle lift_node;
        ros::Subscriber lift_sub = lift_node.subscribe("lift", 1000, liftCallback);
        ros::Rate loop_rate(10);


        while (ros::ok()) {
                ros::spinOnce();
                loop_rate.sleep();
        }
        return 0;
}

