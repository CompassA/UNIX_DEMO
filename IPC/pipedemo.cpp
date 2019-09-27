#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

const int buf_size = 4096;

//子进程代码段
void child_process(int *const pipe_fd) {
    const int pipe_read_fd = pipe_fd[0];
    const int pipe_write_fd = pipe_fd[1];

    //子进程关闭管道写描述符
    close(pipe_write_fd);

    char buf[buf_size];
    int length;
    while (true) {
        if ((length = read(pipe_read_fd, buf, buf_size)) < 0) {
            perror("read : ");
        } else {
            buf[length] = '\0';
            printf("子进程接收字符串: %s\n", buf);
        }
        if (buf[0] == 'q') {
            printf("子进程退出\n");
            close(pipe_read_fd);
            break;
        }
    }
    exit(0);
}

int main() {
    int pipe_fd[2];
    
    //创建管道 
    if (pipe(pipe_fd) < 0) {
        perror("pipe :");
    }
    
    //创建子进程
    if (fork() == 0) {
        child_process(pipe_fd);
    }
    const int pipe_read_fd = pipe_fd[0];
    const int pipe_write_fd = pipe_fd[1];

    //父进程关闭管道读描述符
    close(pipe_read_fd);

    char buf[buf_size];
    int length;
    //终端读入循环
    while (true) {
        if ((length = read(STDIN_FILENO, buf, buf_size)) < 0) {
            perror("read :");
        } else {
            //将终端读入的数据放入管道
            if (length != write(pipe_write_fd, buf, length)) {
                perror("write : ");
            }
        }
        if (buf[0] == 'q') {
            close(pipe_write_fd);
            break;
        }
    }
    waitpid(-1, nullptr, 0);
    return 0;
}