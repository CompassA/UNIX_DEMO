#ifndef TEXTUTIL_H_
#define TEXTUTIL_H_
#include "text_query.h"

class TextUtil {
public:
    using str_vector_ptr = std::shared_ptr<std::vector<std::string>>;

    TextUtil() = delete;

    static TextData init_textQuery(const std::string& fileName);

    static str_vector_ptr split(const std::string& oneline);
private:
};

#endif