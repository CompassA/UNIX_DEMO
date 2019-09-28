#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

const char *fifo_file_name = "fifo_file";
const mode_t fifo_mode = 0644;

int main() {
    //mkfifo(fifo_file_name, fifo_mode);

    int fd = open(fifo_file_name, O_WRONLY);
    
    char buf[4096];
    int len;
    while ((len = read(STDIN_FILENO, buf, 4096)) > 0) {
        write(fd, buf, len);
    }
    return 0;
}