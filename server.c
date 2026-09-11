#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<errno.h>

typedef struct {
    char *ip_address;
    uint16_t port;
} binding_args;


struct sockaddr_in create_sockaddr(char *ip_addr, uint16_t port){
    struct sockaddr_in address = {0};

    address.sin_family = AF_INET;

    int result = inet_pton(address.sin_family, ip_addr, &address.sin_addr);
    if(result != 1){
        if (result < 0){
            perror("inet_pton");
        }
        else{
            fprintf(stderr, "Invalid IP-Address %s \n", ip_addr);
        }
        return (struct sockaddr_in){0};
    }
    address.sin_port = htons(port);

    return address;
}

int create_socket(){
    int sock = socket(AF_INET, SOCK_STREAM, 0); 
    if(sock < 0){
        perror("create_socket");
        return -1;
    }
    printf("socket created successfully\n");
    return sock;
}

struct sockaddr_in bind_socket_base(int socket_fd, char *ip_addr, uint16_t port){
    struct sockaddr_in address = create_sockaddr(ip_addr, port);
    if(bind(socket_fd, (struct sockaddr*)&address, sizeof(address)) < 0){
        perror("bind_socket_base");
        return (struct sockaddr_in){0};
    }
    printf("socket bound to %s:%hu\n", ip_addr, port);
    return address;    
}

struct sockaddr_in bind_socket_variadic(int socket_fd, binding_args args){
    char *ip_add_out = args.ip_address ? args.ip_address : "127.0.0.1";
    uint16_t port_out = args.port ? args.port : 8080;

    return bind_socket_base(socket_fd, ip_add_out, port_out);
}

#define bind_socket(socket_fd, ...) bind_socket_variadic(socket_fd, (binding_args) {__VA_ARGS__})

void event_loop(int sock){
    while (1) {
        struct sockaddr_in client_address;
        socklen_t addrlen = sizeof(client_address);

        int new_socket = accept(
            sock,
            (struct sockaddr *)&client_address,
            &addrlen
        );

        if (new_socket < 0) {
            perror("accept");
            continue;
        }

        printf("Connection accepted.\n");

        char buffer[1024] = {0};

        ssize_t bytes_read = read(
            new_socket,
            buffer,
            sizeof(buffer) - 1
        );

        if(bytes_read < 1){
            perror("reading");
            close(new_socket);
            continue;
        }

        if(bytes_read == 0){
            printf("Client closed connection.");
            close(new_socket);
            continue;
        }

        buffer[bytes_read] = '\0';

        printf("Client Message: %s\n", buffer);

        const char *response = "Hello from Server!";

        ssize_t bytes_written = write(
            new_socket,
            response,
            strlen(response)
        );

        if (bytes_written < 0) {
            perror("write");
        }

        close(new_socket);
    }
}

int main(int argc, char *argv[]){
    int sock = create_socket();
    if(sock < 0){
        return EXIT_FAILURE;
    };
    struct sockaddr_in bound_socket = bind_socket(sock);
   
    if( listen(sock, 3) < 0){
        perror("listen");
        close(sock);
        return EXIT_FAILURE;
    }
    event_loop(sock);

    close(sock);
    return EXIT_SUCCESS;
}
