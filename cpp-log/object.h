//
//  object.h
//  cpp-log
//
//  Created by Piotr Brzeski on 2023-10-12.
//  Copyright © 2023-2024 Brzeski.net. All rights reserved.
//

#pragma once

#include "message.h"
#include "target.h"
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace logger {

class object {
public:
	~object();
	void add_target(target::ptr target);
	void start();
	void log(message::ptr& message);
	
private:
	void do_work();
	void move_to_empty_messages(std::vector<message::ptr>& messages);
	void get_empty_message(message::ptr& msg);
	void log_messages(std::vector<message::ptr>& messages);
	void log_message(message& message);
	
	bool                      m_run = false;
	std::thread               m_thread;
	std::mutex                m_mutex;
	std::condition_variable   m_condition;
	std::vector<message::ptr> m_messages_to_log;
	std::vector<message::ptr> m_empty_messages;
	std::mutex                m_empty_messages_mutex;
	std::vector<target::ptr>  m_targets;
	std::string               m_formatted_message;
	
};

}
