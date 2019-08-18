#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

const int size = 4096;

int main() {
    int stdinFlag = fcntl(0, F_GETFL);
    stdinFlag |= O_NONBLOCK;
    fcntl(0, F_SETFL, stdinFlag);
    int second;
    int n;
    char buf[size];
    for (second = 10; second > 0; --second) {
        if ((n = read(0, buf, size)) > 0) {
            write(1, buf, n);
            break;
        }
        if (errno == EAGAIN) {
            printf("rest %d seconds\n", second);
            sleep(1);
        } else {
            perror("read");
            return 1;
        }
    }
    if (second == 0) {
        printf("timeout\n");
    }
    return 0;
}