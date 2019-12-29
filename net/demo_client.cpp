#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#define SIZE 4096

int main(int args, char** argv) {
    //创建客户端套接字
    int socket_fd;
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
    }

    //指定服务端地址、端口
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(13);
    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) < 0) {
        perror("inet_pton");
    }

    //与服务端建立连接
    if (connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
    }

    //读服务端数据
    char buffer[SIZE];
    int length;
    while ((length = read(socket_fd, buffer, SIZE)) > 0) {
        buffer[length] = 0;
        printf("%s\n", buffer);
    }
    return 0;
}