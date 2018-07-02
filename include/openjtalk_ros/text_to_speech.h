#ifndef TEXT_TO_SPEECH_H_INCLUDED
#define TEXT_TO_SPEECH_H_INCLUDED

//headers in ROS
#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>

//headers in this package
#include <openjtalk_ros/TextToSpeechAction.h>

class text_to_speech
{
    public:
        struct parameters
        {
            std::string voice_file_path;
            std::string tts_goal_topic;
            parameters()
            {
                ros::param::param<std::string>(ros::this_node::getName()+"/voice_file_path", voice_file_path, "");
                ros::param::param<std::string>(ros::this_node::getName()+"/tts_goal_topic", tts_goal_topic, "");
            }
        };
        text_to_speech();
        ~text_to_speech();
    private:
        parameters params_;
        ros::NodeHandle nh_;
        actionlib::SimpleActionServer<openjtalk_ros::TextToSpeechAction> tts_action_server_;
        void tts_goal_callback_(const openjtalk_ros::TextToSpeechGoalConstPtr &goal);
};

#endif  //TEXT_TO_SPEECH_H_INCLUDED