#ifndef TEXT_TO_SPEECH_H_INCLUDED
#define TEXT_TO_SPEECH_H_INCLUDED

//headers in ROS
#include <ros/ros.h>
#include <ros/package.h>
#include <actionlib/server/simple_action_server.h>

//headers in this package
#include <openjtalk_ros/TextToSpeechAction.h>

//headers in boost
#include <boost/filesystem.hpp>

//headers in STL
#include <string>

class text_to_speech
{
    public:
        struct parameters
        {
            std::string voice_file_path;
            std::string tts_goal_topic;
            std::string dictionary_path;
            parameters()
            {
                ros::param::param<std::string>(ros::this_node::getName()+"/voice_file_path", voice_file_path, "");
                ros::param::param<std::string>(ros::this_node::getName()+"/tts_goal_topic", tts_goal_topic, ros::this_node::getName()+"/goal");
                ros::param::param<std::string>(ros::this_node::getName()+"/dictionary_path", dictionary_path, "/usr/local/share/open_jtalk/open_jtalk_dic_utf_8-1.09/");
            }
        };
        text_to_speech();
        ~text_to_speech();
    private:
        parameters params_;
        ros::NodeHandle nh_;
        bool exec_shell_command(const char* cmd, std::string& stdOut, int& exitCode);
        actionlib::SimpleActionServer<openjtalk_ros::TextToSpeechAction> tts_action_server_;
        void tts_goal_callback_(const openjtalk_ros::TextToSpeechGoalConstPtr &goal);
        openjtalk_ros::TextToSpeechFeedback feedback_;
        openjtalk_ros::TextToSpeechResult result_;
};

#endif  //TEXT_TO_SPEECH_H_INCLUDED