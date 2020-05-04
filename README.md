[![Build Status](https://travis-ci.org/malithj/rlog.svg?branch=master)](https://travis-ci.org/malithj/rlog)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
# rlog
C++ implementation of a logging module exclusively for research

## Why Should Researchers Use rlog?
Most C++ logging libraries are pretty bloated. For production uses, [glog](https://github.com/google/glog) is a great C++ logging library. However, its dependency on [gflags](https://github.com/gflags/gflags) makes configuration very difficult. In contrast, the main goals of a logging library in research are, 
1. Obtaining debug information from the program as much as possible.
2. Easy configuration of the logging library. 

## rlog is Completely Header Based
Configuring rlog is as simple as dropping `include/log/` directory in this repository to your own project. No additional build steps are required. rlog supports console based logging as well as file based logging.

## Quick Start: How Do I Use rlog?
### Default configuration outputs to console. 
```cpp
#include <memory>
#include "include/log/logging.h"

using namespace Logging::LoggingInternals;

//
// The input of @Logger is,
//    context:  std::string :file from which the logger is called
//
std::unique_ptr<Logger> logger(new Logger(__FILE__));
logger->info("Hello!");
```
### File configuration outputs to a prespecified log file.
```cpp
#include <memory>
#include "include/log/logging.h"

using namespace Logging::LoggingInternals;

//
// The inputs are,
//    context:  std::string :file from which the logger is called
//    filename: std::string :user specified log file name
//    override: bool        :whether to use the global log file or local log file
//
// Log severity and global log file name can be specified through env variables 
// configured in @Env class. see @Env for configurations
//
std::unique_ptr<Logger> logger(new Logger(__FILE__, filename, 1)); 
logger->info("Aloha!");
```

## Advanced Usage: Minimizing Overhead
Although for debugging and testing logs can be beneficial, for performance based benchmarking it is essential ideally to remove all logging information. rlog achieves this through macros defined in `logging.h`. Use a variable to specify whether logging has been enabled or not by `#define ENABLE_LOGGING 1` in the file `logging.h`. Use of macro based logging allows to run preprocessor directives so that logging information will not be available in the final binary.

```cpp
#include <memory>
#include "include/log/logging.h"

using namespace Logging::LoggingInternals;

//
// The input of @Logger is,
//    context:  std::string :file from which the logger is called
//
std::unique_ptr<Logger> logger(new Logger(__FILE__));
LOG_INFO("Aloha!");
```

## Future Work
C++20 introduces robust string formatting and variable inlining. The message information can be improved by employing python style string formatting.

## Contributions
Contributions are more than welcome! Made with ❤

## Feedback
Contact me at [malithjayaweera.com](https://malithjayaweera.com/contact/)

