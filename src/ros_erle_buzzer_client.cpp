#include "ros/ros.h"
#include "ros_erle_buzzer/buzzer.h"
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "ros_erle_buzzer_client");
  if (argc != 2){
    ROS_INFO("usage: ros_erle_buzzer_client tune");
    return 1;
  }

  ros::NodeHandle n;
  ros::Publisher led_pub = n.advertise<ros_erle_buzzer::buzzer>("buzzer", 1000);
  ros_erle_buzzer::buzzer msg;

  msg.tune = atoi(argv[1]);

  ros::Rate loop_rate(1);

  int count = 0;
  while (ros::ok()){
    led_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }  
  return 0;
}
