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

std::shared_ptr<object> get_or_create() {
	auto ptr = logger_object.lock();
	if(!ptr) {
		ptr = std::make_shared<object>();
		logger_object = ptr;
	}
	return ptr;
}

template<class Msg>
void log_message(Msg&& msg) {
	thread_local auto new_message = std::make_unique<message>();
	auto ptr = logger_object.lock();
	if(ptr) {
		new_message->set(std::forward<Msg>(msg));
		ptr->log(new_message);
	}
}

}

std::shared_ptr<object> logger::start(target::ptr target,
                                      target::ptr target2, target::ptr target3, target::ptr target4, target::ptr target5) {
	auto ptr = get_or_create();
	if(target) {
		ptr->add_target(std::move(target));
	}
	else {
		ptr->add_target(cout());
	}
	if(target2) {
		ptr->add_target(std::move(target2));
	}
	if(target3) {
		ptr->add_target(std::move(target3));
	}
	if(target4) {
		ptr->add_target(std::move(target4));
	}
	if(target5) {
		ptr->add_target(std::move(target5));
	}
	ptr->start();
	return ptr;
}

void logger::log(const char* msg) {
	log_message(msg);
}

void logger::log(std::string msg) {
	log_message(std::move(msg));
}
