#include <unistd.h>
#include <signal.h>
#include <stdio.h>

const int SECONDS = 5;

void SIGALRM_handler(int signal) {
    printf("bomb!!!\n");
    alarm(SECONDS);
}

int main() {
    if (SIG_ERR == signal(SIGALRM, SIGALRM_handler)) {
        perror("signal error!\n");
    }
    alarm(SECONDS);
    while (true) {
        write(STDOUT_FILENO, ".", 1);
        /*
         *     pause();
         *让程序暂停直到被信号打断
         *
         *     sleep(n)
         *让程序暂停直到被信号打断,或过了n秒
         */
         sleep(1);
    }
    return 0;
}