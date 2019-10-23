#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

/**
 * 
 * void mylock(int *lock) {
 *     int flag = 1;
 *     while (flag == 1) {
 *         flag = *lock;  读取锁内存值
 *         *lock = 1;     将锁置为锁定状态 *lock = 1 有锁  *lock = 0 无锁
 *     }
 * } 
 * 
 */

static int spin = 0;
static int cnt = 0;

void spin_lock(int * shm) {
    __asm__ __volatile__(
        "1:\n\t"
        "movl $1,%%eax\n\t"
        "lock xchg %%eax, %0\n\t"
        "test %%eax, %%eax\n\t"
        "jnz 1b"
        :
        :"m"(*shm)
        :"%eax"
    );
}

void spin_unlock(int *shm) {
    *shm = 0;
}

void *task(void* arg) {
    int add_cnt = 0;
    while (true) {
        spin_lock(&spin);
        ++cnt;
        printf("%lx add cnt, cnt = %d\n", pthread_self(), cnt);
        add_cnt++;
        if (add_cnt == 10000) {
            spin_unlock(&spin);
            break;    
        }
        spin_unlock(&spin);
    }
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, nullptr, task, nullptr);
    pthread_create(&t2, nullptr, task, nullptr);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    printf("%d\n", cnt);
    return 0;
}