#include "client_manager.h"
#include "debug.h"
#include "utils.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

client_manager::client_manager() : buffer_size(0) {
}

int client_manager::get_fd() const {
    return client_fd;
}

void client_manager::accept(const int server_fd) {
    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    client_fd = safe_call(::accept4(server_fd, (sockaddr*)&client_addr, &client_len, ACCEPT_FLAGS));

    buffer_size = 0;
    debug::log(std::string("Accepted: ") + ::inet_ntoa(client_addr.sin_addr));
}

size_t client_manager::read(char* buffer, size_t size) {
    ssize_t readed = ::read(client_fd, buffer, size);
    safe_call(readed);
    return readed;
}

void client_manager::read_in_buffer() {
    buffer_size = read(buffer, BUFFER_SIZE);
}

void client_manager::write(const char* buffer, size_t size) {
    size_t writen = 0;
    while (writen < size) {
        ssize_t out = ::write(client_fd, buffer + writen, size - writen);
        safe_call(out);
        writen += out;
    }
    safe_call(writen == size);
}

void client_manager::write(std::string const& text) {
    write(text.c_str(), text.size());
}

void client_manager::write_from_buffer() {
    write(buffer, buffer_size);
}

void client_manager::close() {
    safe_call(::close(client_fd));
}
