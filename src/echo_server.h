#ifndef ECHO_SERVER_H
#define ECHO_SERVER_H

#include <cstdint>
#include <exception>
#include <stdexcept>

#include <atomic>

#include <netinet/in.h>


class echo_server {
    // FIXME:
public:
    static const uint16_t DEFAULT_PORT = 8668;

    std::atomic_bool ended, closed, running;

    int socket_fd;
    uint16_t port;

    static const size_t BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];

    void init_socket();

    void bind_socket(sockaddr_in addr);

    sockaddr_in make_socketaddr(uint16_t port);

    void listen_socket();

    int accept_socket();

public:
    echo_server();

    echo_server(uint16_t port);

    ~echo_server();

    echo_server(echo_server const&) {
        throw std::runtime_error("unsupported");
    };

    echo_server& operator=(echo_server const&) {
        throw std::runtime_error("unsupported");
    };

    void start();

    void close();
};

#endif  // ECHO_SERVER_H
