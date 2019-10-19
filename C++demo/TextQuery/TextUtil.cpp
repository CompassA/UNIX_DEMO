#include "TextUtil.h"

TextData TextUtil::init_textQuery(const std::string& fileName) {
    std::shared_ptr<std::vector<std::string>> text = 
            std::make_shared<std::vector<std::string>>();
    
    std::shared_ptr<
        std::unordered_map<std::string, std::shared_ptr<std::set<int>>>
    > wordOccuredLines = 
        std::make_shared<std::unordered_map<
            std::string, 
            std::shared_ptr<std::set<int>>
        >>();

    FILE* const fp = fopen(fileName.c_str(), "r"); 
    if (fp == nullptr) {
        perror("fopen");
        return TextData(text, wordOccuredLines);
    }

    char buf[TextData::QUERY_CONST::BUFFER_SIZE];
    while (!feof(fp)) {
        fgets(buf, TextData::QUERY_CONST::BUFFER_SIZE, fp);
        text->push_back(std::string(buf));
    }

    return TextData(text, wordOccuredLines);
}

TextUtil::str_vector_ptr TextUtil::split(const std::string& oneline) {
    std::shared_ptr<std::vector<std::string>> words = std::make_shared<std::vector<std::string>>();
    std::string curWord("");
    bool preSpaceFlag = false;
    for (int i = 0; i < oneline.size(); ++i) {
        const char curChar = oneline[i];
        if (curChar == ' ') {
            preSpaceFlag = true;
        } else {
            if (preSpaceFlag) {
                words->push_back(curWord);
                curWord.clear();
                preSpaceFlag = false;
            }
            curWord.push_back(curChar);
        }
    }
    return words;
}