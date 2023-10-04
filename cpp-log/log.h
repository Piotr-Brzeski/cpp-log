//
//  log.h
//  Log
//
//  Created by Piotr Brzeski on 2023-10-04.
//  Copyright © 2023 Brzeski.net. All rights reserved.
//

#pragma once

#include <string>

#ifndef __clang__
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"
#endif

namespace log {

void log(const char* message);
void log(std::string const& message);

}

#ifndef __clang__
	#pragma GCC diagnostic pop
#endif
