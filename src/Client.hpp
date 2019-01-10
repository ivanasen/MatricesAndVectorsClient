#pragma once

#include <string>

class Client {
public:
	virtual void start();

	virtual void onInput(const std::string &input) = 0;
};