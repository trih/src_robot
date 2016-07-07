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
BlackUART motor_Uart_L(UART2, myProp);
BlackUART motor_Uart_R(UART4, myProp);

void motorCallback(const std_msgs::String::ConstPtr& msg)
{
	ROS_INFO("I heard: [%s]", msg->data.c_str());
	if (msg->data.c_str()=="Stop") {
                motor_Uart_L.write("S");
                motor_Uart_R.write("S");

	}
	else if (msg->data.c_str()=="Going") {
                motor_Uart_L.write("G");
                motor_Uart_R.write("G");

	}
	else {
                motor_Uart_L.write("S");
                motor_Uart_R.write("S");
	}
}

int main(int argc, char **argv)
{
        ros::init(argc, argv, "motor_msg");
        ros::NodeHandle motor_node;
	ros::Subscriber motor_sub = motor_node.subscribe("motor", 1000, motorCallback);
        ros::Rate loop_rate(10);

        if ( !motor_Uart_L.open(ReadWrite | NonBlock) ) {
                cout << "Failed to open UART2" << endl;
                return -1;
        }
        motor_Uart_L.flush(bothDirection);

        if ( !motor_Uart_R.open(ReadWrite | NonBlock) ) {
                cout << "Failed to open UART4" << endl;
                return -1;
        }
        motor_Uart_R.flush(bothDirection);

        while (ros::ok()) {
                ros::spinOnce();
                loop_rate.sleep();
        }
        return 0;
}
