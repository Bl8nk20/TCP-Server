#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

typedef struct {
    char *ip_address;
    uint16_t port;
} binding_args;

int establish_connection(){
    int sock = socket(AF_INET, SOCK_STREAM, 0); 
    if(sock < 0){
        perror("Socket-Fehler!");
        return -1;
    }
    printf("Socket erfolgreich erstellt.\n");
    return sock;
}

struct sockaddr_in bind_socket_base(int socket_fd, char *ip_addr, uint16_t port){
    struct sockaddr_in address = {0};

    address.sin_family = AF_INET;
    if(inet_pton(AF_INET, ip_addr, &address.sin_addr) < 0){
        perror("inet_pton");
        return (struct sockaddr_in){0};
    }
    address.sin_port = htons(port);
    
    if(bind(socket_fd, (struct sockaddr*)&address, sizeof(address)) < 0){
        perror("Socket-Binding-Fehler!");
        return (struct sockaddr_in){0};
    }
    printf("Socket erfolgreich festgelegt auf %s:%hu\n", ip_addr, port);
    return address;    
}

struct sockaddr_in bind_socket_variadic(int socket_fd, binding_args args){
    char *ip_add_out = args.ip_address ? args.ip_address : "127.0.0.1";

    uint16_t port_out = args.port ? args.port : 8080;

    return bind_socket_base(socket_fd, ip_add_out, port_out);
}

#define bind_socket(socket_fd, ...) bind_socket_variadic(socket_fd, (binding_args) {__VA_ARGS__})

void terminate_connection(int *sock){
    printf("Socket wieder geschlossen.\n");
    close(*sock);
} 

void event_loop(int sock, struct sockaddr_in address){
    while(1){
        socklen_t addrlen = sizeof(address);
        int new_socket = accept(sock, (struct sockaddr *)&address, &addrlen);
        
        if(new_socket < 0){
            perror("Failed to connect.");
            continue;
        }

        printf("Connection accepted. \n");

        char buffer[1024] = {0};
        ssize_t bytes_read = read(new_socket, buffer, sizeof(buffer) - 1);

        if(bytes_read < 1){
            perror("read");
            terminate_connection(&new_socket);
            continue;
        }
        buffer[bytes_read] = '\0';

        printf("Client Message : %s \n", buffer);
        
        char *response = "Hello from Server!";
        
        if(write(new_socket, response, strlen(response))){
            perror("");
            continue;
        }

        terminate_connection(&new_socket);
    }
}

int main(int argc, char *argv[]){
    int sock = establish_connection();
    if(sock < 0){
        return EXIT_FAILURE;
    };
    struct sockaddr_in bound_socket = bind_socket(sock);
   
    if( listen(sock, 3) < 0){
        perror("listen");
        return EXIT_FAILURE;
    }
    event_loop(sock, bound_socket);

    terminate_connection(&sock);
    return EXIT_SUCCESS;
}
