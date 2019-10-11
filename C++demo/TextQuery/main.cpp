#include "text_query.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("argc != 2\n");
        return 0;
    }
    TextData textData(argv[1]);
    textData.showText();
    return 0;
}