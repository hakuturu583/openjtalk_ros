#include <ros/ros.h>

int main(int argc, char** argv)
{
    ros::init (argc, argv, "text_to_speech_node");
    ros::spin();
    return 0;
}