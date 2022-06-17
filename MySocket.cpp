#include "MySocket.h"

/**
 * Reads the data received from the client and saves it in buffer.
 * @param socket_fd socket file descriptor.
 * @param buffer memory space for the data received from the client.
 * @param n size of memory space.
 * @return number of bytes read.
 */
size_t read_data(const int socket_fd, char *buffer, const size_t n) {
    size_t bytes_read, bytes_counter = 0;
    while (bytes_counter < n) { /* loop until full buffer */
        bytes_read = read(socket_fd, buffer, n - bytes_counter);
        if (bytes_read > 0)  {
            bytes_counter += bytes_read;
            buffer += bytes_read;
        }
        if (bytes_read < 1) {
            close(socket_fd);
            err_exit(EXIT_ERROR,READ_FUNC);
        }
    }
    return bytes_counter;
}

/**
 * Configs a general socket based on the port received as an argument.
 * @param port port to connect from by the new socket.
 * @param sa struct to hold all socket details.
 * @return the new socket file descriptor.
 */
int config_socket(const unsigned short port, struct sockaddr_in &sa) {
    struct hostent *hp;
    int socket_fd;
    if ((hp = gethostbyname(LOCALHOST)) == nullptr) {
        return EXIT_ERROR;
    }
    bzero(&sa, sizeof sa);
    memcpy((char *)&sa.sin_addr, hp->h_addr_list[0],hp->h_length);
    sa.sin_family = hp->h_addrtype;
    sa.sin_port = htons((u_short)port);

    if ((socket_fd = socket(hp->h_addrtype, SOCK_STREAM, PROTOCOL)) == EXIT_ERROR)
        return EXIT_ERROR;
    return socket_fd;
}

/**
 * performs bind() and validates its result.
 * @param sa struct with the socket's details.
 * @param socket_fd socket file descriptor.
 */
void do_bind(sockaddr_in &sa, const int socket_fd) {
    int return_val = bind(socket_fd, (struct sockaddr*)&sa, sizeof (struct sockaddr_in));
    if (return_val == EXIT_ERROR) { close(socket_fd); }
    err_exit(return_val,BIND_FUNC);
}

/**
 * performs listen() and validates its result.
 * @param socket_fd socket file descriptor.
 */
void do_listen(const int socket_fd) {
    int return_val;
    return_val = listen(socket_fd,MAX_CLIENTS);
    if (return_val == EXIT_ERROR) { close(socket_fd); }
    err_exit(return_val,LISTEN_FUNC);
}

/**
 * Keeps the server socket alive and waiting for clients to connect.
 * @param socket_fd socket file descriptor
 */
void event_loop(const int socket_fd) {
    while(SERVER_ALIVE) {
        const int client_socket_fd = accept(socket_fd, nullptr, nullptr);
        if (client_socket_fd == EXIT_ERROR)
            continue;
        else {
            char* buffer[BUFFER_SIZE];
            read_data(client_socket_fd, *buffer, BUFFER_SIZE);
            int return_val = system(*buffer);
            err_exit(return_val, SYSTEM_FUNC);
        }
    }
}

/**
 * creates a socket for a server based on the given port.
 * @param port port to connect from by the new socket.
 */
void server(const unsigned short port) {
    struct sockaddr_in sa{};
    const int socket_fd = config_socket(port,sa);
    
    do_bind(sa, socket_fd);

    do_listen(socket_fd);

    event_loop(socket_fd);
}

/**
 * performs connect() and validates its result.
 * @param sa struct with the socket's details.
 * @param socket_fd socket file descriptor.
 */
void do_connect(sockaddr_in &sa, const int socket_fd) {
    int return_val = connect(socket_fd, (struct sockaddr*)&sa, sizeof (struct sockaddr_in));
    if (return_val == EXIT_ERROR) { close(socket_fd); }
    err_exit(return_val, CONNECT_FUNC);
}

/**
 * performs write() and validates its result.
 * @param terminal_command_to_run the command to send to the server by the client
 * @param socket_fd socket file descriptor.
 */
void do_write(const char *terminal_command_to_run, const int socket_fd) {
    int return_val = (int)write(socket_fd, terminal_command_to_run, BUFFER_SIZE);
    if (return_val == EXIT_ERROR) { close(socket_fd); }
    err_exit(return_val, WRITE_FUNC);
}

/**
 * creates a socket for a client based on the given port.
 * @param port port to connect from by the new socket.
 * @param terminal_command_to_run the command to send to the server by the client
 */
void client(const unsigned short port, const char * terminal_command_to_run) {
    struct sockaddr_in sa{};
    const int socket_fd = config_socket(port, sa);

    do_connect(sa, socket_fd);

    do_write(terminal_command_to_run, socket_fd);
}

int main(int argc, char* argv[]) {
    const char * app = argv[1];
    auto port = (unsigned short) std::strtoul(argv[2], nullptr, DECIMAL_BASE);
    if (strcmp(app, SERVER) == 0) {
        server(port);
    } else {
        const char * terminal_program_to_run = argv[3];
        client(port, terminal_program_to_run);
    }
}