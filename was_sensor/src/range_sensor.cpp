#include "ros/ros.h"
#include <sensor_msgs/Range.h>
#include "BlackLib.h"
#include <sstream>
#include "std_msgs/String.h"

// Approximately calculated gradient of "range = f(voltage)"
// Because "f(voltage)" is approximately linear, the equation should be:
// range = SLOPE x Voltage + INTERCEPTER, where:
#define SLOPE        1
#define INTERCEPTER  0
/*
void motorCallback(const std_msgs::String::ConstPtr& msg)
{
	ROS_INFO("I heard: [%s]", msg->data.c_str());
}
*/
int main(int argc, char **argv)
{
        ros::init(argc, argv, "WUS_range_sensor");
        ros::NodeHandle n;
        ros::Publisher chatter_pub = n.advertise<sensor_msgs::Range>("was_sensor/range/ultrasound", 1000);
	//ros::Subscriber motor_sub = n.subscribe("motor", 1000, motorCallback);
        ros::Rate loop_rate(10);

        sensor_msgs::Range range_msg;
        range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
        range_msg.header.frame_id =  "/ultrasound";
        range_msg.field_of_view = 0.1;  // fake
        range_msg.min_range = 200;
        range_msg.max_range = 3000;

	BlackLib::BlackADC myADC(BlackLib::AIN0);

        while (ros::ok()) {
                range_msg.range = myADC.getNumericValue() * SLOPE + INTERCEPTER;

                chatter_pub.publish(range_msg);

                ros::spinOnce();

                loop_rate.sleep();
        }
        return 0;
}
