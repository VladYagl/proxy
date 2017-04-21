#include "debug.h"

constexpr char debug::LOG_FILE[];
std::ofstream* debug::log_stream;

void debug::init() {
    if (log_stream == nullptr) {
        log_stream = new std::ofstream();
    }
    if (!log_stream->is_open()) {
        log_stream->open(LOG_FILE, std::ios_base::app);
    }
}

void debug::log_print(std::string text) {
    init();
    *log_stream << text;
}

void debug::log_println(std::string text) {
    log_print(text + "\n");
}

void debug::log(std::string text) {
    log_println(text);
    save();
}

void debug::log() {
    log("");
}

void debug::save() {
    log_stream->flush();
}
