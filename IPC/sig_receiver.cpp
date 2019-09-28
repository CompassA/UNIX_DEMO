/*
 * @Author: FanQie 
 * @Date: 2019-09-21 16:15:44 
 * @Last Modified by: FanQie
 * @Last Modified time: 2019-09-21 16:35:57
 */
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>

const char *file_name = "log_";
const int bufsize = 4096;

void SIGUSR1_handler(int sig_no) {
    int fd;
    if ((fd = open(file_name, O_RDONLY)) == -1) {
        perror("open: ");
    }
    char buf[bufsize];
    int length;
    while ((length = read(fd, buf, bufsize)) > 0) {
        for (int i = 0; i < length; ++i) {
            if (buf[i] >= 'a' && buf[i] <= 'z') {
                buf[i] -= 32;
            }
        }
        if (write(STDOUT_FILENO, buf, length) != length) {
            perror("write:");
        }
    }
    if (length < 0) {
        perror("read: ");
    }
    close(fd);
}

int main() {
    printf("receiver pid: %d\n", getpid());
    struct sigaction act;
    act.sa_handler = SIGUSR1_handler;
    if (sigaction(SIGUSR1, &act, nullptr) < 0) {
        perror("sigaction: ");
    }
    while (true) {
        pause();
    }
    return 0;
}