#include "text_query.h"
#include <stdio.h>

void TextData::showText() const {
    for (auto it = _text->begin(); it != _text->end(); ++it) {
        printf("%s\n", it->c_str());
    }
}

// void TextData::removeLineFeed(char* line) {
//     while (*line != '\0') {
//         if (*line == '\n') {
//             *line = '\0';
//             break;
//         }
//         ++line;
//     }
// }

QueryResult TextData::query(const std::string word) {

}