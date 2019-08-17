#include <stdio.h>
#include <new>

class TestClass {
public:
    TestClass(): id(DEFAULT) {
        printf("TestClass() id = DEFAULT\n");
    }

    TestClass(const int _id): id(_id) {
        printf("TestClass(%d) id = %d\n", id, id);
    }

    ~TestClass() {
        printf("~TestClass() id = %d\n", id);
    }

    TestClass(const TestClass& other) = delete;
private:
    static const int DEFAULT;
    int id;
};

const int TestClass::DEFAULT = -1;
const int LENGTH = 8;

int main() {
    TestClass* array = new TestClass[LENGTH];
    for (int i = 0; i < LENGTH; ++i) {
        /**
         * placement new
         */
        new (array + i)TestClass(i);
    }
    //delete array; 只调用一次构造函数
    delete[] array;

    int * p = new int[10];
    //delete p; 简单类型两种方式都一样
    delete[] p;
    return 0;
}