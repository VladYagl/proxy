#include "client_manager.h"
#include "debug.h"
#include "utils.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

void client_manager::accept(int server_fd) {
    // TODO: I'm not sure about that flags
    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    client_fd = safe_call(::accept4(server_fd, (sockaddr*)&client_addr, &client_len, ::SOCK_CLOEXEC));
    debug::log(std::string("Accepted: ") + ::inet_ntoa(client_addr.sin_addr));
}

size_t client_manager::read(char* buffer, size_t size) {
    ssize_t readed = ::read(client_fd, buffer, size);
    safe_call(readed);
    return readed;
}

void client_manager::write(char* buffer, size_t size) {
    size_t writen = 0;
    while (writen < size) {
        ssize_t out = ::write(client_fd, buffer + writen, size - writen);
        safe_call(out);
        writen += out;
    }
    safe_call(writen == size);
}

void client_manager::close() {
    safe_call(::close(client_fd));
}
