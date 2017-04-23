#include "echo_server.h"
#include "client_manager.h"
#include "debug.h"
#include "epoll_helper.h"
#include "exceptions.h"
#include "utils.h"

#include <arpa/inet.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

void echo_server::init_socket() {
    socket_fd = safe_call(::socket(SOCKET_DOMAIN, SOCKET_TYPE, 0));
}

void echo_server::bind_socket(sockaddr_in addr) {
    safe_call(::bind(socket_fd, (sockaddr*)&addr, sizeof(sockaddr)));
}

sockaddr_in echo_server::make_socketaddr(uint16_t port) {
    sockaddr_in addr;
    addr.sin_family = SOCKET_DOMAIN;
    addr.sin_port = htons(port);               // function converts the unsigned short integer hostshort from host byte order to network byte order.
    addr.sin_addr.s_addr = htonl(INADDR_ANY);  // htonl - same but long,
    return addr;
}

void echo_server::listen_socket() {
    safe_call(::listen(socket_fd, SOMAXCONN));
}

void echo_server::close() {
    // TODO: close all clients
    log_name();
    safe_call(::close(socket_fd));
    debug::log("R.I.P.");
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

    listen_socket();

    epoll_helper epoll(socket_fd);

    while (true) {
        epoll.sleep(2);
        while (!epoll.empty()) {
            epoll_event event = epoll.next_event();

            if (event.data.fd == socket_fd) {
                debug::log("New client");
                // FIXME: stop making tons of copies of client_manager pls
                client_manager client;
                client.accept(socket_fd);
                int client_fd = client.get_fd();
                epoll.add_client(client_fd);
                clients.emplace(client_fd, client);
            } else if (event.data.fd == epoll.signal_fd) {
                // FIXME use another exception here
                throw new server_exception("signal caught");
            } else {
                if ((event.events & ::EPOLLIN) != 0) {
                    clients[event.data.fd].read_in_buffer();
                    clients[event.data.fd].write_from_buffer();
                }
                /* if ((event.events & ::EPOLLOUT) != 0) { */
                /* debug::log("Write to client"); */
                /* clients[event.data.fd].write_from_buffer(); */
                /* } */
            }
        }
    }

    /* client_manager client; */
    /* while (!closed) { */
    /*     client.accept(socket_fd); */
    /*     while (size_t readed = client.read(buffer, BUFFER_SIZE)) { */
    /*         client.write(buffer, readed); */
    /*     } */
    /* } */
}
