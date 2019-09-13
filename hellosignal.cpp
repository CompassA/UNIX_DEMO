/**
 *  信号的使用
 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

typedef void (*SigHandler)(int);

/**
 * callback function
 */
void sigHandler(int signal) {
    switch (signal) {
    case SIGUSR1:
        printf("SIGUSR1\n");
        break;
    case SIGUSR2:
        printf("SIGUSR1\n");
        break;
    case SIGINT:
        printf("SIGINT 收到Ctrl C\n");
        break;
    case SIGSEGV:
        printf("SIGSEGV\n");
        break;
    default:
        printf("other sig");
    }
}

int main() {
    printf("hello pid = %d\n", getpid());
    
    /**
     * 信号注册函数 SigHandler signal(int sig_no, SigHandler callback_function) 
     */
    signal(SIGUSR1, sigHandler);
    signal(SIGUSR2, sigHandler);
    signal(SIGINT, sigHandler);
    signal(SIGSEGV, sigHandler);
    
    while (true) {
        /*
         * printf(".");
         * 不会输出屏幕，printf向终端输出条件 缓冲区满或遇\n
         * printf(".\n");
         * 会输出屏幕
         */
        write(STDOUT_FILENO, ".", 1);
        /**
         * 处于sleep状态的进程到信号后,会执行回调函数，执行完后会立即输出"."
         * 信号打断了sleep函数
         */
        sleep(10);
    }
    return 0;
}