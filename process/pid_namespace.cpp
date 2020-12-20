#include <stdio.h>
#include <sched.h>
#include <signal.h>
#include <wait.h> 
#include <unistd.h>
#include <stdlib.h>
#define STACK_SIZE (1024 * 1024)

static int child_func(void* arg) {
    printf("child process: my pid is %d\n", getpid());
    return 0;
}

int main() {
    void* stack = malloc(STACK_SIZE);
    void* stack_top = stack + STACK_SIZE; 
    // 创建子进程 CLONE_NEWPID代表子进程使用新的pid namespcce
    int pid = clone(child_func, stack_top, CLONE_NEWPID | SIGCHLD, NULL);
    if (pid != 0) {
        printf("parent process: the pid of child process is %d\n", pid);
        while (-1 != wait(NULL)) {
        }
    }
    return 0;
}
