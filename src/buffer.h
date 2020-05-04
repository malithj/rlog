//
// rlog Example Project
// Copyright (c) 2020 Malith Jayaweera https://malithjayaweera.com
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#include "include/log/logging.h"
#include <memory>
#include <unistd.h>

using namespace Logging::LoggingInternals;

class Buffer {
    private:
	std::unique_ptr<Logger> logger_;
    public:
        Buffer();
	~Buffer() {}
};

Buffer::Buffer() {
   logger_ = std::unique_ptr<Logger>(new Logger(__FILE__));
   Logger * logger = logger_.get();
   LOG_INFO("Aloha!");
   LOG_WARN("temporarily snoozing down the system");
   usleep(2000000); 
   LOG_ERROR("critical computation time lost");
}
