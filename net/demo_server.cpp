#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#define SIZE 1024

int main(int args, char** argv) {
    //创建服务端套接字
    int socket_fd;
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
    }

    //将服务器的众所周知的端口绑定到套接字
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(13);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    //将套接字转换为监听套接字
    listen(socket_fd, 3);

    for (;;) {
        int conn_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL);
        time_t ticks = time(NULL);
        char buf[SIZE];
        snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&ticks));
        int length = strlen(buf);
        if (write(conn_fd, buf, length) != length) {
            perror("write");
        }
        close(conn_fd);
    }
    return 0;
}