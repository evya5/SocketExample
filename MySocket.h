#ifndef EX5_MYSOCKET_H
#define EX5_MYSOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <cstring>
#include <cstdio>
#include <string>
#include "ErrHandler.h"

#define BUFFER_SIZE 256
#define SERVER "server"
#define DECIMAL_BASE 10
#define LOCALHOST "localhost"
#define MAX_CLIENTS 5
#define PROTOCOL 0
#define SERVER_ALIVE true

#define READ_FUNC "read()"
#define CONNECT_FUNC "connect()"
#define WRITE_FUNC "write()"
#define SYSTEM_FUNC "system()"
#define BIND_FUNC "bind()"

#define LISTEN_FUNC "listen()"

int main(int argc, char* argv[]);

#endif
