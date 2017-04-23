#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include <netinet/in.h>
#include <string>

class client_manager {
    // FIXME:
public:
    // TODO: WTF IS THIS???
    // O_CLOEXEC (Since Linux 2.6.23)
    //              Enable  the  close-on-exec  flag  for  the new file descriptor.  Specifying this flag permits a program to avoid additional fcntl(2) F_SETFD
    //              operations to set the FD_CLOEXEC flag.  Additionally, use of this flag is essential in some multithreaded programs since using a separate
    //              fcntl(2) F_SETFD operation to set the FD_CLOEXEC flag does not suffice to avoid race conditions where one thread
    //              opens a file descriptor at the same time as another thread does a fork(2) plus execve(2).
    constexpr static int ACCEPT_FLAGS = ::SOCK_CLOEXEC;
    constexpr static int BUFFER_SIZE = 1024;

    int client_fd;
    ::sockaddr_in client_addr;

    char buffer[BUFFER_SIZE];
    size_t buffer_size;

public:
    client_manager();

    int get_fd() const;

    void accept(const int server_fd);

    size_t read(char* buffer, size_t size);

    void read_in_buffer();

    void write(const char* buffer, size_t size);

    void write(std::string const& text);

    void write_from_buffer();

    void close();
};

#endif  // CLIENT_MANAGER_H
