#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <Matrix.hpp>


#include "Client.hpp"
#include "VariableManager.hpp"

class MatricesClient : public Client {
private:
	VariableManager mVariableManager;

	void onInput(const std::string &input) override;

public:
	MatricesClient();

	static void init();
};
