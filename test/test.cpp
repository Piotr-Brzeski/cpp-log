//
//  test.cpp
//  cpp-log-test
//
//  Created by Piotr Brzeski on 2023-10-12.
//  Copyright © 2023 Brzeski.net. All rights reserved.
//

#include <cpp-log/log.h>
#include <thread>
#include <chrono>

int main(int argc, const char * argv[]) {
	logger::log("Not started");
	{
		auto log = logger::start();
		logger::log("Started");
		logger::log("First message");
		auto thread = std::thread([](){
			logger::log("Message from thread");
		});
		logger::log("Second message");
		thread.join();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		logger::log("Third message");
		logger::log("Stopping");
	}
	logger::log("Stopped");
	return 0;
}
