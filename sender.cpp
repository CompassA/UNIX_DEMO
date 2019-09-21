/*
 * @Author: FanQie 
 * @Date: 2019-09-21 16:15:52 
 * @Last Modified by: FanQie
 * @Last Modified time: 2019-09-21 16:50:44
 */
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>

const char *filename = "log_";
const int bufsize = 4096;

int main(int argnum, char **args) {
    if (argnum != 2) {
        printf("argnum error\n");
        return 0;
    }
    int target_pid;
    sscanf(args[1], "%d", &target_pid);
    
    char buf[bufsize];
    int length;
    while ((length = read(STDIN_FILENO, buf, bufsize)) > 0) {
        int fd = -1;
        //打开文件
        if ((fd = open(filename, O_WRONLY | O_APPEND)) < 0) {
            perror("open: ");
        }
        //写入输入
        if (write(fd, buf, length) != length) {
            perror("write: ");
        }
        //关闭文件
        if (close(fd) < 0) {
            perror("close: ");
        }
        //向另一个进程发信号
        if (kill(target_pid, SIGUSR1) < 0) {
            perror("kill: ");
        }
    }
    return 0;
}