#pragma once

#include <string>
#include <fstream>

class Client {
private:
	std::string mCmdPrefix;
	std::string mQuitCmd;
protected:
	void setCommandPrefix(const std::string &startString);

	std::string getCommandPrefix();

	static std::string DEFAULT_CMD_PREFIX();

	static std::string DEFAULT_QUIT_CMD();

	virtual void onInput(const std::string &input) = 0;

public:
	Client();

	Client(const std::string &commandPrefix, const std::string &quitCommand);

	virtual void start();
};