#include "ros/ros.h"
#include <std_msgs/UInt32.h>
#include "BlackLib.h"
#include <sstream>
#include <bitset>

//Define bits for LED on BFD-1000
#define T1      0
#define T2      1
#define T3      2
#define T4      3
#define T5      4

int main(int argc, char **argv)
{
        ros::init(argc, argv, "WUS_lineTracker_sensor");
        ros::NodeHandle n;
        ros::Publisher chatter_pub = n.advertise<std_msgs::UInt32>("was_sensor/movement/lineTracking", 1000);
        ros::Rate loop_rate(10);

        std::bitset<5> trackingValue_bitset;
        BlackLib::BlackGPIO t1Value(BlackLib::GPIO_65, BlackLib::input);
        BlackLib::BlackGPIO t2Value(BlackLib::GPIO_66, BlackLib::input);
        BlackLib::BlackGPIO t3Value(BlackLib::GPIO_67, BlackLib::input);
        BlackLib::BlackGPIO t4Value(BlackLib::GPIO_68, BlackLib::input);
        BlackLib::BlackGPIO t5Value(BlackLib::GPIO_69, BlackLib::input);

        std_msgs::UInt32 trackingValue;

        while (ros::ok()) {
                trackingValue_bitset[T1] = t1Value.getNumericValue();
                trackingValue_bitset[T2] = t2Value.getNumericValue();
                trackingValue_bitset[T3] = t3Value.getNumericValue();
                trackingValue_bitset[T4] = t4Value.getNumericValue();
                trackingValue_bitset[T5] = t5Value.getNumericValue();

                trackingValue.data = (int)trackingValue_bitset.to_ulong();

                chatter_pub.publish(trackingValue);

                ros::spinOnce();

                loop_rate.sleep();
        }
        return 0;
}
