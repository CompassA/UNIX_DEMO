#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

int main() {
    string* str = new string("absavdsvsda");
    /**
     * void *str = operator new(sizeof (string));
     * string* s = static_cast<string*>(str);
     * s->string::string("");
     *  */
    delete str;
    str = nullptr;
    /**
     * str->~string();
     * operator delete(str);
     */
    return 0;
}