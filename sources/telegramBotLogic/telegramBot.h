#pragma once

#include <tgbot/tgbot.h>
#include <iostream>
#include <string>
#include <tgbot/tgbot.h>
#include <memory>
#include <fmt/core.h>
#include <sqlite3.h>

#define BOT_TOKEN "6837880673:AAEgxIHKJ-8b9qa0liNJNGtZptcv2vwYCYo"

namespace TelegramBotSpace {
    void BotInProcess(TgBot::Bot& bot);

    void InitBotCommands(TgBot::Bot& bot, sqlite3* dataBase);

}