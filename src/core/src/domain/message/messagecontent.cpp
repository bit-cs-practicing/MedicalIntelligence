#include "messagecontent.h"

#include <stdexcept>

MessageContent::MessageContent(QString content) : content(content) {
    if (content.isEmpty()) {
        throw std::invalid_argument("消息内容不可以为空");
    }
}

const QString& MessageContent::getContent() const {
    return content;
}
