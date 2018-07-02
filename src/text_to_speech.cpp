//headers in this package
#include <openjtalk_ros/text_to_speech.h>

text_to_speech::text_to_speech() : params_(), tts_action_server_(nh_, params_.tts_goal_topic, boost::bind(&text_to_speech::tts_goal_callback_, this, _1), true)
{
	boost::filesystem::path voice_file(params_.voice_file_path);
	if(boost::filesystem::exists(voice_file) == false)
	{
		ROS_ERROR_STREAM("ERROR : " << params_.voice_file_path << " does not exist." );
		std::exit(0);
	}
}

text_to_speech::~text_to_speech()
{
    
}

void text_to_speech::tts_goal_callback_(const openjtalk_ros::TextToSpeechGoalConstPtr &goal)
{
	feedback_.wav_file_generated = false;
	int exit_code;
	std::string out;
	std::string generate_text_file_command;
	std::string generate_wav_file_command = std::string("open_jtalk -m ") + params_.voice_file_path + 
		" -ow " + ros::package::getPath("openjtalk_ros") +  "/data/voice.wav -x " + params_.dictionary_path + " " + ros::package::getPath("openjtalk_ros") + "/data/text.txt";
	exec_shell_command(generate_wav_file_command.c_str(),out,exit_code);
	feedback_.wav_file_generated = true;
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