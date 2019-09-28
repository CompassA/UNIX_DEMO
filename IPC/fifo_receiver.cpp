#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

const char *fifo_file_name = "fifo_file";
const mode_t fifo_mode = 0644;

int main() {
    int fifo_fd;
    if ((fifo_fd = open(fifo_file_name, O_RDONLY))) {
        perror("open : ");
    }
    char buf[4096];
    int len;
    while ((len = read(fifo_fd, buf, 4096)) > 0) {
        write(STDOUT_FILENO, buf, len);
    }
    printf("receiver exit\n");
    return 0;
}