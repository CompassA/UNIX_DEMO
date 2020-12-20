#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <signal.h>
#include <wait.h>
#define STACK_SIZE (1024 * 1024)

static int child_func(void* arg) {
    char* const cmd[] = {"/bin/bash", NULL};
    execvp(cmd[0], cmd);
    return 0;
}

int main(int argc, char const *argv[]) {
    void* const buffer = malloc(STACK_SIZE);
    void* const stack_top = buffer + STACK_SIZE;
    if (clone(child_func, stack_top, CLONE_NEWNS | SIGCHLD, NULL) != 0) {
        int child_pid;
        while ((child_pid = wait(NULL)) != -1) {
            printf("child process %d exited\n", child_pid);
        }
    }
    return 0;
}
