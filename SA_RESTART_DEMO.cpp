#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

void SIGALRM_handler(int sig_no) {
    printf("alarm bomb!!!");
    alarm(5);
}

int main(int argnum, char ** args) {
    struct sigaction act;
    act.sa_handler = SIGALRM_handler;
    
    //自动重启
    //act.sa_flags |= SA_RESTART;
    if (sigaction(SIGALRM, &act, nullptr) < 0) {
        perror("SIGALRM sigaction");
    } 

    alarm(5);

    char buf[4096];
    while (true) {
        int n = -1;
        if ((n = read(STDIN_FILENO, buf, 4096)) >= 0) {
            write(STDOUT_FILENO, buf, n);
        } else {
            if (errno == EINTR) {
                perror("read");
            }
        }
    }
    return 0;
}