//
//  message.cpp
//  cpp-log
//
//  Created by Piotr Brzeski on 2023-10-12.
//  Copyright © 2023 Brzeski.net. All rights reserved.
//

#include "message.h"
#include <map>
#include <mutex>
#include <ctime>
#include <cassert>

using namespace logger;

namespace {

std::string thread_id(std::thread::id& id) {
	static int counter = 0;
	static std::map<std::thread::id, std::string> thread_ids;
	static std::mutex mutex;
	auto lock = std::lock_guard(mutex);
	auto& str_id = thread_ids[id];
	if(str_id.empty()) {
		str_id = std::to_string(++counter);
	}
	return str_id;
}

void append(std::string& str, message::time_point time) {
	auto time_t = message::clock::to_time_t(time);
	auto seconds = message::clock::from_time_t(time_t);
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(time - seconds).count();
	auto pos = str.size();
	str += "YYYY-mm-DD HH:MM:SS.___";
	std::tm tm = *std::localtime(&time_t);
	auto len = std::strftime(str.data() + pos, 20, "%F %T", &tm);
	assert(len == 19);
	str[pos + 19] = '.';
	str[pos + 20] = '0' + static_cast<char>(milliseconds % 1000 / 100);
	str[pos + 21] = '0' + static_cast<char>(milliseconds % 100 / 10);
	str[pos + 22] = '0' + static_cast<char>(milliseconds % 10);
}

}

void message::format(std::string &dst) {
	dst.clear();
	append(dst, m_time);
	dst += ' ';
	dst += thread_id(m_thread);
	dst += ' ';
	dst += m_content;
}
