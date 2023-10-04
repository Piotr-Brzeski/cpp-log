//
//  log.cpp
//  Log
//
//  Created by Piotr Brzeski on 2023-10-04.
//  Copyright © 2023 Brzeski.net. All rights reserved.
//

#include "log.h"
#include <iostream>
#include <chrono>
#include <iomanip>

namespace {

void print_now() {
	auto now = std::chrono::system_clock::now();
	auto time = std::chrono::system_clock::to_time_t(now);
	auto now_seconds = std::chrono::system_clock::from_time_t(time);
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now - now_seconds);
	std::tm tm = *std::localtime(&time);
	std::cout << std::put_time(&tm, "%F %T") << '.';
	if(milliseconds.count() < 100) {
		std::cout << '0';
		if(milliseconds.count() < 10) {
			std::cout << '0';
		}
	}
	std::cout << milliseconds.count();
}

template<class T>
void log_message(T const& message) {
	print_now();
	std::cout << ' ' << message << std::endl;
}

}

void log::log(const char* message) {
	log_message(message);
}

void log::log(std::string const& message) {
	log_message(message);
}
