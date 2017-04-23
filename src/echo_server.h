#ifndef ECHO_SERVER_H
#define ECHO_SERVER_H

#include <cstdint>
#include <exception>
#include <stdexcept>

#include <netinet/in.h>
#include <sys/socket.h>
#include <map>

#include "client_manager.h"

class echo_server {
    // FIXME:
public:
    constexpr static uint16_t DEFAULT_PORT = 8668;
    // AF_INET         IPv4 Internet protocols
    constexpr static int SOCKET_DOMAIN = AF_INET;
    // SOCK_STREAM     Provides sequenced, reliable, two-way, connection-based byte  streams.   An  out-of-band  data transmission mechanism may be supported.
    constexpr static int SOCKET_TYPE = SOCK_STREAM;

    int socket_fd;
    uint16_t port;

    static const size_t BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];

    std::map<int, client_manager> clients;

    void init_socket();

    void bind_socket(sockaddr_in addr);

    sockaddr_in make_socketaddr(uint16_t port);

    void listen_socket();

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
