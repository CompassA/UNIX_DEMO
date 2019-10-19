#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {
    
    for (int i = 0; i < 4; ++i) {
        if (fork() == 0) {
            break;
        }
    }

    printf("pid = %d ppid = %d\n", getpid(), getppid());

    while (waitpid(-1, nullptr, 0) > 0) {}
    return 0;
}