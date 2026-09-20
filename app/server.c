#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<ctype.h>

#include "shared/shared.h"
#include "factory/service_factory.h"

#define PORT 7890

int create_socket(void){
    int sock = socket(AF_INET, SOCK_STREAM, 0); 
    if(sock < 0){
        perror("create_socket");
        return -1;
    }

    return sock;
}

int set_socket_option(int sock){
    int yes = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0){ 
        perror("Setting-sock-Option");
        return -1;
    }

    return 0;
}

void event_loop(int sock){
    socklen_t sin_size;
    struct sockaddr_in client_addr;
    int new_sock;
    ssize_t recv_length;
    static const char greeting[] = "Hello there! \n";
    unsigned char buffer[1024];
    while (1) {
        sin_size = sizeof(struct sockaddr_in);
        new_sock = accept(sock, (struct sockaddr *)&client_addr, &sin_size); 
        if(new_sock < 0){
            perror("accept");
            continue;
        }
        char ip_str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET,&(client_addr.sin_addr), ip_str, sizeof(ip_str));
        printf("server: new connection from %s:%d\n", ip_str, ntohs(client_addr.sin_port));
        ssize_t sent = send(new_sock, greeting, sizeof(greeting) -1, 0);
        if (sent < 0){
            perror("send");
        }
        while((recv_length = recv(new_sock, buffer, sizeof(buffer), 0)) > 0 ){
            printf("RECV: %zd bytes\n", recv_length);
            dump(buffer, recv_length);
            
            CommandContext ctx = {
                .client_sox = new_sock,
                .payload = buffer,
                .payload_len = recv_len
            };

            Command *cmd = service_factory_create(buffer, recv_len);
            if (cmd){
                cmd->execute(cmd, &ctx);
                cmd->destroy(cmd);
            }

        }
        if(recv_length < 0){
            perror("receive");
        }

        close(new_sock);
    }
}

int main(void){
    int sock = create_socket();
    if(sock < 0){
        return EXIT_FAILURE;
    }
    if(set_socket_option(sock) < 0){
        close(sock);
        return EXIT_FAILURE;
    }

    struct sockaddr_in host_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(PORT),
        .sin_addr.s_addr = htonl(INADDR_ANY)
    };

    if(bind(sock, (struct sockaddr *)&host_addr, sizeof(host_addr)) < 0){
        perror("bind");
        close(sock);
        return EXIT_FAILURE;
    }
    
    if( listen(sock, 3) < 0){
        perror("listen");
        close(sock);
        return EXIT_FAILURE;
    }

    event_loop(sock);

    close(sock);
    return EXIT_SUCCESS;
}
