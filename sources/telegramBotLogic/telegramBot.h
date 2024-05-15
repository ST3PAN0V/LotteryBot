#pragma once

#include "../dataBaseTools/dataBase.h"

#include <tgbot/tgbot.h>
#include <iostream>
#include <string>
#include <memory>
#include <tuple>
#include <fmt/core.h>
#include <unordered_set>
#include <stdarg.h>
#include <sqlite3.h>
#include <regex>

#define BOT_TOKEN "6837880673:AAEgxIHKJ-8b9qa0liNJNGtZptcv2vwYCYo"
#define LOTTERY_FIELD_SIZE 45

using Keyboard = TgBot::InlineKeyboardMarkup;
using Button = TgBot::InlineKeyboardButton;

namespace TelegramBotSpace {
    void BotInProcess(TgBot::Bot& bot);

    void InitBotCommands(TgBot::Bot& bot, sqlite3* dataBase);

    inline void SendMessage(TgBot::Bot& bot, int64_t chatId, const std::string& message,
            std::shared_ptr<TgBot::InlineKeyboardMarkup> buttons = std::shared_ptr<TgBot::InlineKeyboardMarkup>(nullptr));
    
    inline void EditMessage(TgBot::Bot& bot, const std::string& message, const TgBot::CallbackQuery::Ptr& query,
        std::shared_ptr<TgBot::InlineKeyboardMarkup> buttons = std::shared_ptr<TgBot::InlineKeyboardMarkup>(nullptr));

    void AddRowButtons(const std::shared_ptr<TgBot::InlineKeyboardMarkup>& buttonsKeyboard, int countButtons, ...);

    std::tuple<std::string, Keyboard::Ptr> MenuMain();

    std::tuple<std::string, Keyboard::Ptr> MenuBuyTicket(int ticketAttempts, const std::string& typedNumber);

    std::tuple<std::string, Keyboard::Ptr> MenuTickets();

    bool IsCorrectDataTime(const std::string& dataTime);

    Info TryMakeCorrectLotteryString(const std::string& str);

    std::vector<int> StringToVector(const std::string& str);
}