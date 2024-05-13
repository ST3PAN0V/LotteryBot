#include "./dataBaseTools/dataBase.h"
#include "./lotteryLogic/lottery.h"
#include "./telegramBotLogic/telegramBot.h"

int main() {
    TgBot::Bot bot(BOT_TOKEN);
    sqlite3* dataBase = DataBaseSpace::ConnectToDataBase();
    DataBaseSpace::CreateDataBaseStructure(dataBase);
    TelegramBotSpace::InitBotCommands(bot, dataBase);
    TelegramBotSpace::BotInProcess(bot);
    return 0;
}