//
//  log.h
//  Log
//
//  Created by Piotr Brzeski on 2023-10-04.
//  Copyright © 2023 Brzeski.net. All rights reserved.
//

#pragma once

#include <string>

namespace log {

void log(const char* message);
void log(std::string const& message);

}
