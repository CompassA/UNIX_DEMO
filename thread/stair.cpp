#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

void* climb(void* args) {
    const char * const name = (char *)args; 

    for (int i = 1; i <= 10; ++i) {
        printf("我是%s,我现在在%d楼\n", name, i);
        if (strcmp(name, "Allen") == 0) {
            usleep(1000 * 1000); //10ms
        } else {
            usleep(2000 * 1000);
        }
    }
 }

int main() {

    const char * const name1 = "Allen";
    const char * const name2 = "Jack";
    pthread_t allen, jack;

    //线程号，设置线程属性，线程入口函数，线程参数
    int err = pthread_create(&allen, nullptr, climb, (void*) name1);
    if (err != 0) {
        perror("pthread_create");
        return -1;
    }

    err = pthread_create(&jack, nullptr, climb, (void*) name2);
    if (err != 0) {
        perror("pthread_create");
        return -1;
    }

    sleep(120);

    return 0;
}