#include <unistd.h>
#include <stdio.h>
#include <wait.h>

const int n = 5;

int main() {
    int pid;
    for (int i = 0; i < n; ++i) {
        pid = fork();
        if (pid == 0) {
            break;
        }
    }
    int time = 4;
    if (pid == 0) {
        printf("pid = %d, work. \n", getpid());
        char *const args[] = {"ls", nullptr};
        execvp("ls", args);
        sleep(time);
        return 0;
    } else if (pid > 0) {
        while (true) {
            int stopPid = wait(nullptr);
            if (stopPid == -1) {
                printf("all children stop\n");
                break;
            } else {
                printf("pid = %d, stop.\n", stopPid);
            }
        }
    } else {
        perror("fork error\n");
    }
    return 0;
}