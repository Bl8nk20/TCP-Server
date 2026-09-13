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

#define PORT 7890

void create_socket(int *sock){
    sock = socket(PF_INET, SOCK_STREAM, 0); 
    if(sock < 0){
        perror("create_socket");
        return;
    }
}

void set_socket_option(int *sock){
    int yes = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0){ 
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
    unsigned int i, j;
    for(i = 0; i < length; i++){
        byte = data[i];
        printf("%02x", data[i]); // byte in hexadecimal
        if((i%16)==15 || i ==length - 1){
            for(j=0; j < 15-(i%16);j++){
                printf(" ");
            }
            printf("| ");
            for(j=i-(i%16); j<= i; j++){
                byte = data[j];
                if(byte > 31 && byte < 127){
                    printf("%c", byte);
                }
                else{
                    printf(".");
                }
            }
            printf("\n");
        }
    }
}

void event_loop(int sock){
    socklen_t sin_size;
    struct sockaddr_in client_addr;
    int new_sock, recv_length;
    char buffer[1024] = {0};
    while (1) {
        sin_size = sizeof(struct sockaddr_in);
        new_sock = accept(sock, (struct sockaddr_in *)&client_addr, &sin_size); 
        if(new_sock < 0){
            perror("accept");
            continue;
        }

        printf("server: new connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        send(new_sock,  "Hello, there!\n", 13, 0);
        recv_length = recv(new_sock, buffer, 1024, 0);
        while(recv_length > 0){
            printf("RECV: %d bytes\n", recv_length);
            dump(buffer, recv_length);
            recv_length = recv(new_sock, buffer, 1024, 0);
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

    if(bind(sock, (struct sockaddr_in *)&host_addr, sizeof(struct sockaddr)) < 0){
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
