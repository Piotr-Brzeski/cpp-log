//
//  target.h
//  cpp-log
//
//  Created by Piotr Brzeski on 2023-10-13.
//  Copyright © 2023 Brzeski.net. All rights reserved.
//

#pragma once

#include <string>
#include <fstream>
#include <memory>

namespace logger {

class target {
public:
	using ptr = std::unique_ptr<target>;
	virtual ~target() = default;
	virtual void log(std::string const& message) = 0;
};

class stream_target : public target {
public:
	stream_target(std::ostream& stream);
	void log(std::string const& message) override;
	
private:
	std::ostream& m_stream;
};

class file_target: public stream_target {
public:
	file_target(std::string const& path);
	
private:
	std::ofstream m_file;
};

target::ptr cout();
target::ptr cerr();
target::ptr file(std::string const& path);

}
