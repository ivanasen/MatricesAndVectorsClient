#include <vector>
#include <iostream>
#include "Client.hpp"

void Client::start() {
	std::string input;
	while (getline(std::cin, input) && input != "quit") {
		onInput(input);
	}
}

