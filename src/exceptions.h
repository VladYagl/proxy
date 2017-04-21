#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>
#include <system_error>

//TODO: make two different exceptions:
//      1. with errno
//      2. without errno
struct server_exception : std::system_error {
    std::string message;

    server_exception(std::string message) : std::system_error(errno, std::generic_category()), message(message) {
    }

    virtual const char* what() const throw() {
        return (message + ": " + std::system_error::what()).c_str();
    }
};

#endif  // EXCEPTIONS_H
