#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* thread1(void* args) {
    for (int i = 0; i < 10; ++i) {
        printf("%d\n", i);
        usleep(1000 * 1000);
    }
    pthread_exit((void*)20);
}

int main() {
    pthread_t t1; 
    int err = pthread_create(&t1, nullptr, thread1, nullptr);
    if (err != 0) {
        perror("pthread_create");
    }

    void * ret;
    err = pthread_join(t1, &ret);
    if (err != 0) {
        perror("pthread_join");
    }

    printf("线程结束运行, thread exited with %d\n", (int)ret);
    return 0;
}