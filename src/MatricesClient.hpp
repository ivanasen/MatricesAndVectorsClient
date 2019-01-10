#pragma once

#include <vector>
#include <string>
#include "Client.hpp"

class MatricesClient : public Client {
public:
	void onInput(const std::string &input) override;
	static void init();
};
