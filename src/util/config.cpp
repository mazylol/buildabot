#include "config.h"

#include <yaml-cpp/yaml.h>

Util::Config Util::Config::load(const std::string &path) {
    YAML::Node configNode = YAML::LoadFile(path);

    Util::Config config;

    config.token = configNode["token"].as<std::string>();

    auto presenceStatus = configNode["presence"]["presence_status"].as<std::string>();

    if (presenceStatus == "online") {
        config.presence.presence_status = dpp::ps_online;
    } else if (presenceStatus == "idle") {
        config.presence.presence_status = dpp::ps_idle;
    } else if (presenceStatus == "dnd") {
        config.presence.presence_status = dpp::ps_dnd;
    } else if (presenceStatus == "invisible") {
        config.presence.presence_status = dpp::ps_invisible;
    }

    auto presenceActivityType = configNode["presence"]["activity_type"].as<std::string>();

    if (presenceActivityType == "game") {
        config.presence.activity_type = dpp::at_game;
    } else if (presenceActivityType == "streaming") {
        config.presence.activity_type = dpp::at_streaming;
    } else if (presenceActivityType == "listening") {
        config.presence.activity_type = dpp::at_listening;
    } else if (presenceActivityType == "watching") {
        config.presence.activity_type = dpp::at_watching;
    } else if (presenceActivityType == "custom") {
        config.presence.activity_type = dpp::at_custom;
    }

    config.presence.activity_description = configNode["presence"]["activity_description"].as<std::string>();

    std::unordered_map<std::string, std::string> responses;
    for (YAML::detail::iterator_value response: configNode["responses"]) {
        responses[response.first.as<std::string>()] = response.second.as<std::string>();
    }
    config.responses = responses;

    return config;
}
