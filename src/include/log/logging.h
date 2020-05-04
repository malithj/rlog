//
// rlog Project
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

#ifndef __LOGGING_H_
#define __LOGGING_H_

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime> 
#include <exception>
#include "env.h"

#define ENABLE_LOGGING 1

#ifdef ENABLE_LOGGING
#define LOG(LEVEL, MSG) {     \
    logger->log(LEVEL, MSG);  \
}                             
#define LOG_DEBUG(MSG) {      \
    logger->debug(MSG);       \
} 
#define LOG_INFO(MSG) {       \
    logger->info(MSG);        \
} 
#define LOG_WARN(MSG) {       \
    logger->warn(MSG);        \
} 
#define LOG_ERROR(MSG) {      \
    logger->error(MSG);       \
} 
#define LOG_FATAL(MSG) {      \
    logger->fatal(MSG);       \
} 
#else                       
#define LOG(LEVEL, MSG)                  
#define LOG_DEBUG(MSG)
#define LOG_INFO(MSG)
#define LOG_WARN(MSG)
#define LOG_ERROR(MSG)
#define LOG_FATAL(MSG)
#endif

namespace Logging {

class logging_error : public std::exception {
    public:
        const char * what () const throw () {
            return "fatal logging exception occurred.";
        }
};

namespace LoggingInternals {
     enum Level {
        FATAL = 4,
        ERROR = 3,
        WARN = 2,
        INFO = 1,
        DEBUG = 0
    };

    enum Output {
        FILE = 1,
        CONSOLE = 0
    };

    using namespace Logging::LoggingInternals;
    // The Logger is not thread safe and should only 
    // be used in the main thread. The class can be extended 
    // to support the thread safety at the expense of performance.
    // The log lines will first be written to a buffer and then flushed 
    // to the console or log file. @TODO(malith): consider options
    //
    // Module has been designed with the intention of providing an 
    // easy plugin which provides essential functionality while also 
    // allowing to disable logging using preprocessor directives. Thus
    // removing logging overhead completely (for example, this is extremely 
    // useful in benchmarking performance in research).
    //
    // Example usage
    //     Logger * logger = new Logger(__FILE__); # provide context file
    //     logger->info("this is a log line");     # default output to console
    //
    // Example usage with toggled logging
    //     logger * logger = new logger(__file__); # provide context file
    //     log_info("this is a log line");         # default output to console
    //
    // Example usage with default file logging     # override chooses file I/O
    //     logger * logger = new logger(__file__, filename, 1);
    //     log_info("this is a log line");         # output to file
    //
    // Log serverity can be controlled by @Env class. See @Env in "env.h" for 
    // environment variable names available. This ensures that settings are 
    // globally visible and provides flexibility to the research developer.i
    //
    class Logger {
        private:
            // File for logging.
            Env<void> *env;
            Output output_mode;
            std::string context;
            std::ofstream logfile;
            std::string get_ts();
            std::string levels[5] = {"DEBUG", "INFO", "WARN", "ERROR", "FATAL"};
        public:
            Logger();
            Logger(const std::string& context);
            Logger(const std::string& context, const std::string& filepath, 
                   bool override);
            void log(Level s, const std::string& msg);
            // convienience messages
            void fatal(const std::string& msg);
            void error(const std::string& msg);
            void warn(const std::string& msg);
            void info(const std::string& msg);
            void debug(const std::string& msg);
            ~Logger();
    };

    inline Logger::Logger() : output_mode(CONSOLE), context("") {
        this->env = Env<void>::get_env();
        #ifdef ENABLE_LOGGING
            this->log(INFO, "initializing the logging process");
        #endif
    }

     inline Logger::Logger(const std::string& context) : output_mode(CONSOLE) {
        this->env = Env<void>::get_env();
        std::string _ctx = context;
        this->context = _ctx.append(" "); 
        #ifdef ENABLE_LOGGING                              
            this->log(INFO, "initializing the logging process");
        #endif
    }

    inline Logger::Logger(const std::string& context, const std::string& 
                          filepath, bool override) : output_mode(FILE) {
        this->env = Env<void>::get_env();
        const std::string filename = !override ? env->get_log_file() : filepath;
        this->logfile.open(filename);
        std::string _ctx = context;
        this->context = _ctx.append(" ");   
        #ifdef ENABLE_LOGGING
            this->log(INFO, "initializing the logging process");
        #endif
    }

    inline void Logging::LoggingInternals::Logger::fatal(const std::string& msg) { 
        this->log(FATAL, msg); 
    }

    inline void Logging::LoggingInternals::Logger::error(const std::string& msg) { 
        this->log(ERROR, msg); 
    }

    inline void Logging::LoggingInternals::Logger::warn(const std::string& msg) { 
        this->log(WARN, msg); 
    }

    inline void Logging::LoggingInternals::Logger::info(const std::string& msg) { 
        this->log(INFO, msg); 
    }

    inline void Logging::LoggingInternals::Logger::debug(const std::string& msg) { 
        this->log(DEBUG, msg); 
    }

    // construct timestamp in human readable format
    inline std::string Logging::LoggingInternals::Logger::get_ts() { 
        time_t curr = time(0); 
        tm *_tm = localtime(&curr);
        std::string year = std::to_string(1900 + _tm->tm_year);
        std::string month = std::to_string(1 + _tm->tm_mon);
        std::string day = std::to_string(_tm->tm_mday);
        std::string hour =  std::to_string(_tm->tm_hour);
        std::string min = std::to_string(_tm->tm_min);
        std::string sec = std::to_string(_tm->tm_sec);
        std::string fmt[6] = {year, month, day, hour, min, sec};
        for (int i = 0; i < 6; i ++) {
            if (fmt[i].length() < 2) {
                fmt[i] = "0" + fmt[i];
            }
        }
        std::string ts = fmt[1] + "-" + fmt[2] + "-" + fmt[0] + " " +
                         fmt[3] + ":" + fmt[4] + ":" + fmt[5];
        return ts;
    }

    // Log message through the framework
    inline void Logger::log(Level s, const std::string& msg) {
        if (env->get_min_log_level() > s) 
            return;
        std::string ts = get_ts();
        if (this->output_mode == CONSOLE) {
            std::cout << ts << " " << levels[static_cast<int>(s)] << ": " << context << msg << std::endl;
        } else if (this->output_mode == FILE && this->logfile.is_open()) {
            try {
                logfile <<  ts << " " << levels[static_cast<int>(s)] << ": " << context << msg << std::endl;
            } catch (Logging::logging_error &ex) {
                std::cout << ex.what() << std::endl;
            }
        }
    }

    inline Logger::~Logger() {
        #ifdef ENABLE_LOGGING
            this->log(INFO, "destroying the logging process");
        #endif
        logfile.close();
    }

} // LoggingInternals
} // Logger

#endif
