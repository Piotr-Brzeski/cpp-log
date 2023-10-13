//
//  log.h
//  cpp-log
//
//  Created by Piotr Brzeski on 2023-10-04.
//  Copyright © 2023 Brzeski.net. All rights reserved.
//

#pragma once

#include "target.h"
#include <string>
#include <memory>

namespace logger {

class object;

std::shared_ptr<object> start(target::ptr target,
                              target::ptr target2 = nullptr,
                              target::ptr target3 = nullptr,
                              target::ptr target4 = nullptr,
                              target::ptr target5 = nullptr);

void log(const char* msg);
void log(std::string msg);

}
