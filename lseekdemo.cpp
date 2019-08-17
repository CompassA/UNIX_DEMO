#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
/**
 * test
 * abcdefghijklmnopqrstuvwxyz
 */
int main() {
    int openfd = open("test", O_RDONLY);
    char buf[2048];
    lseek(openfd, 6, SEEK_SET);
    int n = read(openfd, buf, 12);
    buf[n] = '\n';
    write(1, buf, n+1);

    lseek(openfd, 12, SEEK_SET);
    n = read(openfd, buf, 12);
    buf[n] = '\n';
    write(1, buf, n+1);

    lseek(openfd, 1, SEEK_CUR);
    n = read(openfd, buf, 12);
    buf[n] = '\n';
    write(1, buf, n+1);

    lseek(openfd, 3, SEEK_END);
    write(openfd, buf,3);

    return 0;
}