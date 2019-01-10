#include <iostream>
#include "MatricesClient.hpp"

void MatricesClient::init() {
	MatricesClient client;
	client.start();
}

void MatricesClient::onInput(const std::string &input) {
	std::cout << input;
}