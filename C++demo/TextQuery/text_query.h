#ifndef TEXT_QUERY_H
#define TEXT_QUERY_H
#include <string>
#include <unordered_map>
#include <set>
#include <vector>
#include <memory>

class QueryResult {
public:
    QueryResult(
        const std::string word, 
        std::shared_ptr<std::set<int>> occuredLines,
        std::shared_ptr<std::vector<std::string>> text
    ): _word(word), _occuredLines(occuredLines), _text(text) {};

    /**
     * 打印查找信息
     */
    void print_word_query_result() const;
private:
    std::string _word;
    std::shared_ptr<std::set<int>> _occuredLines;
    std::shared_ptr<std::vector<std::string>> _text;
};

class TextData {
public:
    /**
     * 初始化资源
     */
    TextData(const std::string file_name);

    /**
     * 查找单词
     */
    QueryResult query(const std::string word);

    void showText() const;

private:
    enum QUERY_CONST {
        BUFFER_SIZE = 4096
    };
    /**
     * 行(vector index) -> 该行文本
     */
    std::shared_ptr<std::vector<std::string>> _text;
    
    /**
     * word -> word出现的行
     */ 
    std::unordered_map<std::string, std::shared_ptr<std::set<int>>> _wordOccuredLines;

    static void removeLineFeed(char* line);
};

#endif