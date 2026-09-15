#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<ctype.h>

typedef struct {
    char *ip_address;
    uint16_t port;
} binding_args;

#define PORT 7890

void create_socket(int *sock){
    *sock = socket(PF_INET, SOCK_STREAM, 0); 
    if(*sock < 0){
        perror("create_socket");
        return;
    }
}

void set_socket_option(int *sock){
    int yes = 1;
    if (setsockopt(*sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0){ 
        perror("Setting-sock-Option");
        return;
    }
}

void set_own_addr_information(struct sockaddr_in *addr){
    addr->sin_family = AF_INET;
    addr->sin_port = htons(PORT);
    addr->sin_addr.s_addr = 0;
    memset(&(addr->sin_zero), '\0', 8);
}

void dump(const unsigned char *data, const unsigned int length){
    unsigned char byte;
    for(size_t i = 0; i < length; i+=16){
        size_t row_length = length - i;
        if (row_length > 16){
            row_length = 16;
        }

        for(size_t j = 0; j < 16; j++){
            if(j < row_length){
                printf("%02x", data[i + j]);
            }
            else{
                printf("  ");
            }
        }
        
        printf("| ");
        for(size_t j = 0; j < row_length; j++){
            unsigned char c = data[i + j];
            printf("%c", isprint(c) ? c : '.');
        }
        
        printf("\n");
    }
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

        printf("server: new connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        send(new_sock,  greeting, sizeof(greeting)-1, 0);
        recv_length = recv(new_sock, buffer, sizeof(buffer), 0);
        while(recv_length > 0){
            printf("RECV: %zd bytes\n", recv_length);
            dump(buffer, recv_length);
            recv_length = recv(new_sock, buffer, sizeof(buffer), 0);
        }
        close(new_sock);
    }
}

int main(void){
    int sock;
    create_socket(&sock);
    struct sockaddr_in host_addr, client_addr;
    set_socket_option(&sock);
    set_own_addr_information(&host_addr);

    if(bind(sock, (struct sockaddr *)&host_addr, sizeof(struct sockaddr)) < 0){
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
