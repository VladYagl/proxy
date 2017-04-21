#ifndef DEBUG_H
#define DEBUG_H

#include <fstream>
#include <iostream>

class debug {
    constexpr static char LOG_FILE[8] = "log.txt";

    static std::ofstream* log_stream;

    static void init();

public:

    static void log_print(std::string text);

    static void log_println(std::string text);

    static void log(std::string text);
    static void log();

    static void save();
};

#define log_name() debug::log(__PRETTY_FUNCTION__)

#endif  // DEBUG_H
