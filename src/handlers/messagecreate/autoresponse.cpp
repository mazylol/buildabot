#include "autoresponse.h"

void autoresponse(const dpp::message_create_t &event, const std::unordered_map<std::string, std::string> &responses) {
    if (responses.find(event.msg.content) == responses.end()) {
        return;
    } else {
        event.reply(dpp::message(responses.at(event.msg.content)), true);
    }
}
