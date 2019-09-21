/**
 * SIGCHLD 子进程结束时向父进程发送的信号
 * 父进程需要接受此信号，否则子进程会成为僵尸进程
 */
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

void SIGCHLD_handler(int sig_no) {
    int status;
    pid_t pid;
    /**
     * 坑点  if ((pid = waitpid(-1, &status, 0)) { .. }
     * 子进程结束时，handler正在执行，会将多个SIGCHLD合并成一个
     */
    while ((pid = waitpid(-1, &status, 0)) > 0) {
        //进程被恢复执行
        if (WIFCONTINUED(status)) {
            printf("child %d continue\n", pid);
        }
        //进程正常退出
        else if (WIFEXITED(status)) {
            printf("child %d exit\n", pid);
        }
        //进程被信号终止
        else if (WIFSIGNALED(status)) {
            printf("child %d signaled\n", pid);
        }
        //进程被暂停执行
        else if (WIFSTOPPED(status)) {
            printf("child %d stopped\n", pid);
        }
    }
}

int main() {
    struct sigaction act, old;
    act.sa_handler = SIGCHLD_handler;
    sigaction(SIGCHLD, &act, &old);

    int fork_pid;
    for (int i = 0; i < 10; ++i) {
        if ((fork_pid = fork()) == 0) {
            break;
        } else {
            printf("创建子进程 pid %d\n", fork_pid);
        }
    }
    if (fork_pid == 0) {
        printf("I'm child no.%d\n", getpid());
        sleep(10);
        return 0;
    }
    while (true) {
        write(STDOUT_FILENO, ".", 1);
        sleep(5);
    }
    return 0;
}