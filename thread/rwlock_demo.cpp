#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static pthread_rwlock_t rwlock;
static int left_num = 20;
static int buy = 0;

void *querier(void *arg) {
    while (true) {
        pthread_rwlock_rdlock(&rwlock);
        if (left_num == 0) {
            pthread_rwlock_unlock(&rwlock);
            break;
        }
        printf("querier %lx: left num = %d\n", (unsigned long) pthread_self(), left_num);
        pthread_rwlock_unlock(&rwlock);
        usleep(1000 * 1000);
    }
    return nullptr;
}

void *buyer(void* arg) {
    while (true) {
        pthread_rwlock_wrlock(&rwlock);
        if (left_num == 0) {
            pthread_rwlock_unlock(&rwlock);
            break;
        }
        --left_num;
        printf("thread %lx gets one thing, left num = %d\n", pthread_self(), left_num);
        pthread_rwlock_unlock(&rwlock);
        usleep(3000 * 1000);
    }
    return nullptr;
}

int main() {
    pthread_rwlock_init(&rwlock, nullptr);
    pthread_rwlock_destroy(&rwlock);

    pthread_t t1, t2, t3;

    pthread_create(&t1, nullptr, querier, nullptr);
    pthread_create(&t2, nullptr, querier, nullptr);
    pthread_create(&t3, nullptr, buyer, nullptr);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    pthread_join(t3, nullptr);

    printf("program exit, left num = %d\n", left_num);
    return 0;
} 