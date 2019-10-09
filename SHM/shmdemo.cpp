/**
 * shmget shmat shmdt
 */
#include <unistd.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

static const key_t KEY = 0x8888;
static const size_t SIZE = 4096;
static const int SHM_FLAG = IPC_CREAT | IPC_EXCL | 0644;

int main(int argnum, char ** args) {
    //创建内核对象
    int id = shmget(KEY, SIZE, SHM_FLAG);
    if (id < 0) {
        perror("shmget: ");
    } else {
        printf("内核对象创建成功， id = %d\n", id);
    }

    //查看内核对象
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork: ");
    } else if (pid == 0) {
        char *const args[] = {"ipcs", "-m", nullptr};
        execvp("ipcs", args);
        return 0;
    } else {
        if (waitpid(pid, nullptr, 0) < 0) {
            perror("waitpid");
        }
    }

    //挂接内存
    char* mem = (char*) shmat(id, nullptr, 0);

    //拷贝数据
    strncpy(mem, "hello world\n", 13);

    //卸载内存
    if (shmdt(mem) < 0) {
        perror("shmdt: ");
    }
    return 0;
}