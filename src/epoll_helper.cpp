#include "epoll_helper.h"
#include "utils.h"

#include <fcntl.h>
#include <signal.h>
#include <sys/signalfd.h>
#include <unistd.h>
#include <cstring>

void epoll_helper::add_event(int fd, uint32_t events) {
    epoll_event event;
    event.events = events;
    event.data.fd = fd;
    safe_call(::epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event));
}

epoll_helper::epoll_helper(int server_fd) : event_count(0), event_position(0) {
    epoll_fd = safe_call(::epoll_create1(CREATE_FLAGS));
    add_event(server_fd, ::EPOLLIN);

    // Adding catching system signals
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGTERM);  // Termination signal
    sigaddset(&mask, SIGINT);   // Interrupt from keyboard

    safe_call(sigprocmask(SIG_BLOCK, &mask, NULL));
    signal_fd = safe_call(signalfd(-1, &mask, 0));
    add_event(signal_fd, ::EPOLLIN);
}

epoll_helper::~epoll_helper() {
    safe_call(::close(epoll_fd));
}

void epoll_helper::add_client(int client_fd) {
    add_event(client_fd, ::EPOLLIN | ::EPOLLET | ::EPOLLOUT);
}

void epoll_helper::remove_client(int client_fd) {
    ::epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_fd, nullptr);
}

void epoll_helper::sleep(int timeout) {
    // timeout * 1000 cause in milliseconds
    event_count = safe_call(::epoll_wait(epoll_fd, events, MAX_EVENTS, timeout * 1000));
    event_position = 0;
}

epoll_event& epoll_helper::next_event() {
    return events[event_position++];
}

bool epoll_helper::empty() {
    return event_position >= event_count;
}
