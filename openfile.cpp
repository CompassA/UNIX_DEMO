#include <unistd.h>
#include <fcntl.h>
#include<stdio.h>

int main(int argsnum, char** args) {
    int fd = open("log_",  O_WRONLY | O_APPEND);
    char buffer[4096] = {0};
    int len = 0;
    while ((len = read(0, buffer, 4096)) > 0) {
        if (len != write(fd, buffer, len)) {
            perror(args[0]);
        }
    }
    close(fd);
    return 0;
}