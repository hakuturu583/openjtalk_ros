//headers in this package
#include <openjtalk_ros/text_to_speech.h>

text_to_speech::text_to_speech() : params_(), tts_action_server_(nh_, params_.tts_goal_topic, boost::bind(&text_to_speech::tts_goal_callback_, this, _1), true)
{

}

text_to_speech::~text_to_speech()
{
    
}

void text_to_speech::tts_goal_callback_(const openjtalk_ros::TextToSpeechGoalConstPtr &goal)
{

}

bool text_to_speech::exec_shell_command(const char* cmd, std::string& stdOut, int& exitCode)
{
	std::shared_ptr<FILE> pipe(popen(cmd, "r"), [&](FILE* p) {exitCode = pclose(p); });
	if (!pipe)
    {
		return false;
	}
	std::array<char, 256> buf;
	while (!feof(pipe.get()))
    {
		if (fgets(buf.data(), buf.size(), pipe.get()) != nullptr)
        {
			stdOut += buf.data();
		}
	}
	return true;
}