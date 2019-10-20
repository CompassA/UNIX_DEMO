#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

static pthread_mutex_t mutex;
static int left_num = 10;
static int a_cnt = 0;
static int b_cnt = 0;

void* buy(void* arg) {
    while (true) {
        pthread_mutex_lock(&mutex);
        if (left_num == 0) {
            //坑 跳出循环前没释放锁
            pthread_mutex_unlock(&mutex);
            break;
        }
        --left_num;
        if (strncmp((char*) arg, "a", 1) == 0) {
            ++a_cnt;
            printf("A gets the thing, left_num = %d, a_cnt = %d, b_cnt = %d\n",
                left_num, a_cnt, b_cnt);
        } else {
            ++b_cnt;
            printf("B gets the thing, left_num = %d, a_cnt = %d, b_cnt = %d\n",
                left_num, a_cnt, b_cnt);
        }
        pthread_mutex_unlock(&mutex);
        usleep(1000 * 1000);
    }
    return (void*)0;
}

int main() {
    pthread_mutex_init(&mutex, nullptr);
    
    pthread_t t1, t2;

    pthread_create(&t1, nullptr, buy, (void *) "a");
    pthread_create(&t2, nullptr, buy, (void *) "b");

    void *ret1, *ret2;
    pthread_join(t1, &ret1);
    pthread_join(t2, &ret2);

    pthread_mutex_destroy(&mutex);
    return 0;
}