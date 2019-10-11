#include "text_query.h"
#include <stdio.h>

// void QueryResult::print_word_query_result() const {
//     printf("%s: %d\n", _word.c_str(), _occuredLines->size());
//     for (auto it = _occuredLines->begin(); it != _occuredLines->end(); ++it) {
//         const int lineNo = *it;
//         printf("line %d: %s\n", lineNo, (*_text)[lineNo].c_str());
//     }
// }

TextData::TextData(const std::string file_name)
        : _text(std::make_shared<std::vector<std::string>>()) {
    FILE * const fp = fopen(file_name.c_str(), "r");
    if (fp == nullptr) {
        perror("fopen: ");
        return;
    }

    char buf[QUERY_CONST::BUFFER_SIZE];
    while (!feof(fp)) {
        fgets(buf, QUERY_CONST::BUFFER_SIZE, fp);
        TextData::removeLineFeed(buf);
        std::string lineText(buf);
        _text->push_back(lineText);
        
        // std::string word("");
        // for (int i = 0; i < lineText.size(); ++i) {
        //     const char curC = lineText[i];
        //     if (curC == ' ' || i == lineText.size() - 1) {
        //         if (_wordOccuredLines.find(word) == _wordOccuredLines.end()) {
        //             _wordOccuredLines[word] = std::make_shared<std::set<int>>();
        //         }
        //         _wordOccuredLines[word]->insert(_text->size() - 1);
        //         word.clear();
        //     } else {
        //         word.push_back(curC);
        //     }
        // }
    }

    fclose(fp);
}

void TextData::showText() const {
    for (auto it = _text->begin(); it != _text->end(); ++it) {
        printf("%s\n", it->c_str());
    }
}

void TextData::removeLineFeed(char* line) {
    while (*line != '\0') {
        if (*line == '\n') {
            *line = '\0';
            break;
        }
        ++line;
    }
}

QueryResult TextData::query(const std::string word) {

}