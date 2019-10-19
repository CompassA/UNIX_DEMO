#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {

    for (int i = 0; i < 4; ++i) {
        if (fork() > 0) {
            break;
        }
    }

    printf("pid = %d ppid = %d\n", getpid(), getppid());
    while (waitpid(-1, nullptr, 0) != -1) {}
    return 0;
}