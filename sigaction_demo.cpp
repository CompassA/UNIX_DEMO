#include <stdio.h>
#include <unistd.h>
#include <signal.h>

typedef struct sigaction Sigaction;

void printsigset(const sigset_t * set) {
    for (int i = 1; i <= 64; ++i) {
        if (sigismember(set, i)) {
            putchar('1');
        } else {
            putchar('0');
        }
    }
    putchar('\n');
}

void SIGALRM_handler(int sig_no) {
    write(STDOUT_FILENO, "bomb!", 5);
    alarm(5);
}

int main() {
    Sigaction act, old;
    act.sa_handler = SIGALRM_handler;
    sigaction(SIGALRM, &act, &old);
    
    printsigset(&act.sa_mask);
    sigemptyset(&act.sa_mask);
    printsigset(&act.sa_mask);
    //sigaddset(&act.sa_mask, SIGINT);
    //sigdelset(&act.sa_mask, SIGINT);
    alarm(5);
    while (true) {
        write(STDOUT_FILENO, ".", 1);
        sleep(1);
    }
    return 0;
}