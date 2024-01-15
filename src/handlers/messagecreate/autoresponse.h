#ifndef BUILDABOT_AUTORESPONSE_H
#define BUILDABOT_AUTORESPONSE_H

#include <string>
#include <unordered_map>

#include <dpp/dpp.h>

void autoresponse(const dpp::message_create_t &event, const std::unordered_map<std::string, std::string> &responses);

#endif //BUILDABOT_AUTORESPONSE_H
