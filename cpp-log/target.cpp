//
//  target.cpp
//  cpp-log
//
//  Created by Piotr Brzeski on 2023-10-13.
//  Copyright © 2023 Brzeski.net. All rights reserved.
//

#include "target.h"
#include <iostream>
#include <stdexcept>

namespace logger {

stream_target::stream_target(std::ostream& stream)
: m_stream(stream)
{
}

void stream_target::log(std::string const& message) {
	m_stream << message << std::endl;
}


file_target::file_target(std::string const& path)
: stream_target(m_file)
{
	m_file.open(path);
	if(!m_file) {
		throw std::runtime_error("Can not open log file \"" + path + '"');
	}
}

target::ptr cout() {
	return std::make_unique<stream_target>(std::cout);
}

target::ptr cerr() {
	return std::make_unique<stream_target>(std::cerr);
}

target::ptr file(std::string const& path) {
	return std::make_unique<file_target>(path);
}

}
