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

#ifndef __ENV_H_
#define __ENV_H_

#include <stdlib.h>

// Env class accesses environment variables relating to log severity
// and global log file. To enable header based implementation, static 
// initialization of a singleton pattern based variable has been enforced
// by using cpp dummy template. The template forces the linker to select the 
// header file based initialization of the static variable @env_instance. 
// Otherwise, the linker cannot decide which initialization is to be used.
//
// The issue can be resolved by variable inlining available in c++20.
// @TODO(malith): convert initialization to an inlined variable.
// For now, backward compatibility is preferred than avoiding hacked code.
//
template <typename D> class Env {
    private:
        static Env * env_instance;
        Env();
    public:
        std::string get_log_file();
        int get_min_log_level();
        static Env *get_env();
        ~Env() {}
};

template <typename D>  Env<D>* Env<D>::env_instance = nullptr;

template <typename D> Env<D>::Env() {
    setenv("CPP_MINIMUM_LOG_LEVEL", "0", 1);
    setenv("CPP_LOG_FILE", "log.log", 1);
}

template <typename D> Env<D> *Env<D>::get_env() {
    if (Env::env_instance == nullptr) {
        Env::env_instance = new Env();
    } 
    return Env::env_instance;
}

template <typename D> std::string Env<D>::get_log_file() {
    return std::string(getenv("CPP_LOG_FILE"));
}

template <typename D> int Env<D>::get_min_log_level() {
    return atoi(getenv("CPP_MINIMUM_LOG_LEVEL"));
}

#endif
