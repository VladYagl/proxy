#include "echo_server.h"
#include "debug.h"
#include "utils.h"
#include "exceptions.h"
#include "client_manager.h"

#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

void echo_server::init_socket() {
    // int socket(int domain, int type, int protocol);
    // AF_INET         IPv4 Internet protocols
    // SOCK_STREAM     Provides sequenced, reliable, two-way, connection-based byte  streams.   An  out-of-band  data transmission mechanism may be supported.
    socket_fd = safe_call(::socket(AF_INET, SOCK_STREAM, 0));
}

void echo_server::bind_socket(sockaddr_in addr) {
    safe_call(::bind(socket_fd, (sockaddr*)&addr, sizeof(sockaddr)));
}

sockaddr_in echo_server::make_socketaddr(uint16_t port) {
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);               // function converts the unsigned short integer hostshort from host byte order to network byte order.
    addr.sin_addr.s_addr = htonl(INADDR_ANY);  // htonl - same but long,
    return addr;
}

void echo_server::listen_socket() {
    safe_call(::listen(socket_fd, SOMAXCONN));
}

int echo_server::accept_socket() {
    // TODO: I'm not sure about that flags
    sockaddr_in client_addr = make_socketaddr(DEFAULT_PORT);
    socklen_t client_len = sizeof(client_addr);
    int result = safe_call(::accept4(socket_fd, (sockaddr*)&client_addr, &client_len, ::SOCK_CLOEXEC));
    debug::log(std::string("Accepted: ") + ::inet_ntoa(client_addr.sin_addr));
    return result;
}

void echo_server::close() {
    log_name();
    if (!closed) {
        closed = true;
        while (!ended) {
        }
        safe_call(::close(socket_fd));
    }
}

echo_server::echo_server() : echo_server(DEFAULT_PORT) {
}

echo_server::echo_server(uint16_t port) {
    this->port = port;
    init_socket();
    bind_socket(make_socketaddr(port));
}

echo_server::~echo_server() {
    close();
}

void echo_server::start() {
    debug::log();
    debug::log();
    log_name();

    ended = false;
    closed = false;

    listen_socket();
    client_manager client;
    while (!closed) {
        client.accept(socket_fd);
        while (size_t readed = client.read(buffer, BUFFER_SIZE)) {
            client.write(buffer, readed);
        }
    }
    ended = true;
    close();
}
