//
//  log.h
//  cpp-log
//
//  Created by Piotr Brzeski on 2023-10-04.
//  Copyright © 2023 Brzeski.net. All rights reserved.
//

#pragma once

#include <string>
#include <memory>

namespace logger {

class object;

std::shared_ptr<object> start();

void log(const char* msg);
void log(std::string msg);

}
