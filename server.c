#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>

typedef struct {
    char *ip_address;
    size_t port;
}f_args_1;

int establish_connection(){
    int sock = socket(AF_INET, SOCK_STREAM, 0); 
    if(sock < 0){
        perror("Socket-Fehler!");
        return -1;
    }
    printf("Socket erfolgreich erstellt.\n");
    return 0;
}

int bind_socket_base(int socket_fd, char *ip_addr, size_t port){
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip_addr);
    address.sin_port = htons(port);
    if(bind(socket_fd, (struct sockaddr*)&address, sizeof(address)) < 1){
        return -1;
    }
    return 0;    
}

int bind_socket(int socket_fd, f_args_1 in){
    char *ip_add_out = in.ip_address ? in.ip_address : "127.0.0.1";
    size_t port_out = in.port ? in.port : 8080;
    return bind_socket_base(socket_fd, ip_add_out, port_out);
}

void terminate_connection(int *sock){
    printf("Socket wieder geschlossen.\n");
    close(*sock);
} 

int main(int argc, char *argv[]){
    int i = 150;
    int sock = establish_connection();
    if(sock < 0){
        return EXIT_FAILURE;
    };
    bind_socket(sock);
    while(i > 1){
        printf("Countdown Läuft. %d\n", i);
        i--;
    }
    terminate_connection(&sock);
    return EXIT_SUCCESS;
}
