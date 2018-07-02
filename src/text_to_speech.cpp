//headers in this package
#include <openjtalk_ros/text_to_speech.h>

text_to_speech::text_to_speech() : params_(), tts_action_server_(nh_, params_.tts_goal_topic, boost::bind(&text_to_speech::tts_goal_callback_, this, _1), false)
{
    
}

text_to_speech::~text_to_speech()
{
    
}

void text_to_speech::tts_goal_callback_(const openjtalk_ros::TextToSpeechGoalConstPtr &goal)
{

}