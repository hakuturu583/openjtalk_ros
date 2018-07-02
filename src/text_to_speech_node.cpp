//headers in this package
#include <openjtalk_ros/text_to_speech.h>

//headers in ROS
#include <ros/ros.h>

int main(int argc, char** argv)
{
    ros::init (argc, argv, "text_to_speech_node");
    text_to_speech tts;
    ros::spin();
    return 0;
}