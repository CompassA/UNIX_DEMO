#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
const int size = 4096;

int main() {
    int stdinFlag = fcntl(0, F_GETFL);
    stdinFlag |= O_NONBLOCK;
    fcntl(0, F_SETFL, stdinFlag);
    char buf[size];
    int i;
    int n;
    for (i = 0; i < 10; ++i) {
        if ((n = read(0, buf, size)) > 0) {
            break;
        } else {
            if (errno == EAGAIN) {
                sleep(1);
            } else {
                perror("read ");
            }
        }
    }
    if (i == 10) {
        printf("timeout\n");
    } else {
        write(1, buf, n);
    }
    return 0;
}