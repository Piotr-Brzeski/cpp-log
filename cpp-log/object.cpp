//
//  object.cpp
//  cpp-log
//
//  Created by Piotr Brzeski on 2023-10-12.
//  Copyright © 2023 Brzeski.net. All rights reserved.
//

#include "object.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

using namespace logger;

object::~object() {
	{
		auto lock = std::lock_guard(m_mutex);
		if(m_run) {
			m_run = false;
			m_condition.notify_one();
		}
	}
	if(m_thread.joinable()) {
		m_thread.join();
	}
}

void object::add_target(target::ptr target) {
	m_targets.push_back(std::move(target));
}

void object::start() {
	auto lock = std::lock_guard(m_mutex);
	if(m_run || m_thread.joinable()) {
		throw std::runtime_error("Logger is already started.");
	}
	m_run = true;
	m_thread = std::thread(&object::do_work, this);
}

void object::log(message::ptr& message) {
	{
		auto lock = std::unique_lock(m_mutex);
		m_messages_to_log.push_back(std::move(message));
	}
	m_condition.notify_one();
	get_empty_message(message);
}

void object::do_work() {
	std::vector<message::ptr> messages;
	auto lock = std::unique_lock(m_mutex);
	while(m_run || !m_messages_to_log.empty()) {
		messages.swap(m_messages_to_log);
		lock.unlock();
		log_messages(messages);
		move_to_empty_messages(messages);
		lock.lock();
		if(m_run && m_messages_to_log.empty()) {
			m_condition.wait(lock);
		}
	}
}

void object::move_to_empty_messages(std::vector<message::ptr>& messages) {
	if(!messages.empty()) {
		{
			auto lock = std::lock_guard(m_empty_messages_mutex);
			m_empty_messages.reserve(m_empty_messages.size() + messages.size());
			std::ranges::move(messages, std::back_inserter(m_empty_messages));
		}
		messages.clear();
	}
}

void object::get_empty_message(message::ptr& msg) {
	{
		auto lock = std::lock_guard(m_empty_messages_mutex);
		if(!m_empty_messages.empty()) {
			msg = std::move(m_empty_messages.back());
			m_empty_messages.pop_back();
			return;
		}
	}
	msg = std::make_unique<message>();
}

void object::log_messages(std::vector<message::ptr>& messages) {
	switch(messages.size()) {
		case 0:
			return;
		case 1:
			log_message(*messages.front());
			break;
		default:
			std::ranges::sort(messages, [](auto& a, auto&b){
				return a->time() < b->time();
			});
			for(auto& message : messages) {
				log_message(*message);
			}
			break;
	}
}

void object::log_message(message& message) {
	message.format(m_formatted_message);
	for(auto& target : m_targets) {
		target->log(m_formatted_message);
	}
}
