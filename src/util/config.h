#ifndef BUILDABOT_CONFIG_H
#define BUILDABOT_CONFIG_H

#include <string>
#include <unordered_map>
#include <utility>

#include <dpp/dpp.h>

class Util {
public:
    struct Presence {
        dpp::presence_status presence_status = dpp::ps_online;
        dpp::activity_type activity_type = dpp::at_game;
        std::string activity_description;
    };

    struct Config {
        std::string token;
        Presence presence;

        std::unordered_map<std::string, std::string> responses;

        static Config load(const std::string &path);
    };
};

#endif //BUILDABOT_CONFIG_H
