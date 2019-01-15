#include <vector>
#include <iostream>
#include "Client.hpp"

void Client::start() {
	std::string input;
	std::cout << mCmdPrefix;
	do {
		getline(std::cin, input);
		if (!input.empty()) {
			onInput(input);
			std::cout << mCmdPrefix;
		}
	} while (input != mQuitCmd);
}

void Client::setCommandPrefix(const std::string &startString) {
	mCmdPrefix = startString;
}

std::string Client::getCommandPrefix() {
	return mCmdPrefix;
}

std::string Client::DEFAULT_CMD_PREFIX() {
	return ">> ";
}

std::string Client::DEFAULT_QUIT_CMD() {
	return "quit";
}

Client::Client() : mCmdPrefix(DEFAULT_CMD_PREFIX()), mQuitCmd(DEFAULT_QUIT_CMD()) {
}

Client::Client(const std::string &commandPrefix, const std::string &quitCommand) : mCmdPrefix(commandPrefix),
                                                                                   mQuitCmd(quitCommand) {
}
