#include "telegramBot.h"
#include "../dataBaseTools/dataBase.h"

void TelegramBotSpace::InitBotCommands(TgBot::Bot& bot, sqlite3* dataBase) {

    bot.getEvents().onCommand("start", [&bot, &dataBase](TgBot::Message::Ptr message) {
    
    if (DataBaseSpace::TryAddUser(dataBase, message->from->id) == Info::USER_EXISTS) {
        bot.getApi().sendMessage(message->chat->id, "Твой id уже есть в базе данных. Ты можешь купить билет!");
    } else {
        bot.getApi().sendMessage(message->chat->id, "Мы внесли твой id в базу данных. Теперь ты можешь купить билет!");
    }
    });
}

void TelegramBotSpace::BotInProcess(TgBot::Bot& bot) {
    try {
        bot.getApi().deleteWebhook();
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            longPoll.start();
        }
    } catch (TgBot::TgException& exception) {
        std::cerr << "TgBot error: " << exception.what() << std::endl;
    } catch (std::runtime_error& exception) {
        std::cerr << "Runtime error: "<< exception.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error"<< std::endl;
    }
}