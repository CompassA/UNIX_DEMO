/**
 * shmctl 
 */
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

static const int KEY = 0x8888;

int main() {
    //根据键值获取共享内存
    int id = shmget(KEY, 0, 0);
    
    //获取内存
    char *buf = (char*) shmat(id, nullptr, 0);
    if (buf == (char*)-1) {
        perror("shmat: ");
        return -1;
    }

    printf("%s", buf);
    
    //卸载内存
    if (shmdt(buf) < 0) {
        perror("shmdt: ");
    }

    //销毁共享内存对象
    if (shmctl(id, IPC_RMID, nullptr) < 0) {
        perror("shmctl: ");
    } else {
        printf("内核对象(id = %d)删除成功\n", id);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork: ");
    } else if (pid == 0) {
        char *const args[] = {"ipcs", "-m", nullptr};
        execvp("ipcs", args);
    }

    waitpid(pid, nullptr, 0);

    return 0;
}