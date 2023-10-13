//
//  log.cpp
//  cpp-log
//
//  Created by Piotr Brzeski on 2023-10-04.
//  Copyright © 2023 Brzeski.net. All rights reserved.
//

#include "log.h"
#include "object.h"

using namespace logger;

namespace {

std::weak_ptr<object> logger_object;

template<class Msg>
void log_message(Msg&& msg) {
	thread_local auto new_message = std::make_unique<message>();
	auto object = logger_object.lock();
	if(object) {
		new_message->set(std::forward<Msg>(msg));
		object->log(new_message);
	}
}

}

std::shared_ptr<object> logger::start() {
	auto ptr = std::make_shared<object>();
	logger_object = ptr;
	ptr->start();
	return ptr;
}

void logger::log(const char* msg) {
	log_message(msg);
}

void logger::log(std::string msg) {
	log_message(std::move(msg));
}
