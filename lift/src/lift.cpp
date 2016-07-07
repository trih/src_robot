#include "ros/ros.h"
#include "BlackLib.h"
#include <sstream>
#include "std_msgs/String.h"
#include <iostream>

using namespace BlackLib;
using namespace std;

BlackUartProperties myProp( Baud9600,
                           Baud9600,
			   ParityNo,
                           StopOne,
                           Char8 );
BlackUART lift_Uart(UART2, myProp);

void liftCallback(const std_msgs::String::ConstPtr& msg)
{
	ROS_INFO("I heard: [%s]", msg->data.c_str());
	if (msg->data.c_str()== "Up") {
                lift_Uart.write("Up");
	}

	if (msg->data.c_str()=="Down") {
                lift_Uart.write("Down");
	}
	//else {
          //      lift_Uart.write("Wrong");
	//}
}

int main(int argc, char **argv)
{
        ros::init(argc, argv, "lift_msg");
        ros::NodeHandle lift_node;
	ros::Subscriber lift_sub = lift_node.subscribe("lift", 1000, liftCallback);
        ros::Rate loop_rate(10);

        if ( !lift_Uart.open(ReadWrite | NonBlock) ) {
                cout << "Failed to open UART2" << endl;
                return -1;
        }
        lift_Uart.flush(bothDirection);

        while (ros::ok()) {
                ros::spinOnce();
                loop_rate.sleep();
        }
        return 0;
}
