#ifndef UTILS_H
#define UTILS_H

#include "exceptions.h"

#include <string>
#include <exception>
#include <system_error>

namespace utils {
    static int check_syscall(int result, std::string message) {
        if (result == -1) {
            throw new server_exception(message);
        }
        return result;
    }
}

//TODO: PLS DONT USE IT!!! 
#define safe_call(result) utils::check_syscall(result, __PRETTY_FUNCTION__)

#endif // UTILS_H
