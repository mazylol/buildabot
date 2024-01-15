#include <dpp/dpp.h>
#include <fmt/format.h>

#include "util/config.h"

int main() {
    Util::Config config = Util::Config::load("config.yaml");

    dpp::cluster bot(config.token, dpp::i_default_intents | dpp::i_message_content);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_message_create([&config](const dpp::message_create_t &event) {
        if (event.msg.author.is_bot()) return;

        if (config.responses.find(event.msg.content) == config.responses.end()) {
            return;
        } else {
            event.reply(dpp::message(config.responses.at(event.msg.content)));
        }
    });

    bot.on_ready([&bot, &config](const dpp::ready_t &event) {
        bot.log(dpp::ll_info, fmt::format("Logged in as {}#{}", bot.me.username, bot.me.discriminator));

        bot.set_presence(dpp::presence(config.presence.presence_status, config.presence.activity_type,
                                       config.presence.activity_description));
    });

    bot.start(dpp::st_wait);
    return 0;
}
