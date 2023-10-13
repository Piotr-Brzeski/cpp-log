//
//  message.h
//  cpp-log
//
//  Created by Piotr Brzeski on 2023-10-11.
//  Copyright © 2023 Brzeski.net. All rights reserved.
//

#pragma once

#include <chrono>
#include <thread>
#include <string>
#include <utility>
#include <memory>

namespace logger {

class message {
public:
	using clock = std::chrono::system_clock;
	using time_point = clock::time_point;
	using ptr = std::unique_ptr<message>;
	
	template<class Content>
	void set(Content&& content) {
		m_time = clock::now();
		m_thread = std::this_thread::get_id();
		m_content = std::forward<Content>(content);
	}
	
	time_point const& time() const {
		return m_time;
	}
	
	void format(std::string& dst);
	
private:
	time_point      m_time;
	std::thread::id m_thread;
	std::string     m_content;
};

}
