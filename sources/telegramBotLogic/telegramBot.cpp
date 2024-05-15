#include "telegramBot.h"
#include "botText.h"
#include "../dataBaseTools/dataBase.h"
#include "../lotteryLogic/lottery.h"

void TelegramBotSpace::InitBotCommands(TgBot::Bot& bot, sqlite3* dataBase) {
    CacheTEXTstrings();

    bot.getEvents().onCommand("start", [&bot, &dataBase](TgBot::Message::Ptr message) {
        const int64_t chatId = message->chat->id;
        std::string response = "";
        Info userInfo = DataBaseSpace::TryAddUser(dataBase, message->from->id);
        switch (userInfo) {
            case Info::USER_EXISTS:
                response = fmt::format(userJoinTEXT, message->from->firstName);
                TelegramBotSpace::SendMessage(bot, chatId, response);
                break;
            case Info::USER_NEW:
                response = newUserJoinTEXT;
                TelegramBotSpace::SendMessage(bot, chatId, response);
                break;
            case Info::ADMIN_JOIN:
                response = fmt::format(adminJoinTEXT, message->from->firstName);
                TelegramBotSpace::SendMessage(bot, chatId, response);
                break;
            default:
                throw std::runtime_error(fmt::format("Weird user: {}. No newUser, no admin, no defoultUser", chatId));
                break;
        }
    });

    bot.getEvents().onCommand("menu", [&bot](TgBot::Message::Ptr message) {
        const int64_t chatId = message->chat->id;

        auto menuData = move(TelegramBotSpace::MenuMain());

        TelegramBotSpace::SendMessage(bot, chatId, std::get<0>(menuData), std::get<1>(menuData));
    });

    bot.getEvents().onCallbackQuery([&bot](TgBot::CallbackQuery::Ptr query) {

        if (StringTools::startsWith(query->data, "MenuTickets")) {
            auto menuData = move(TelegramBotSpace::MenuTickets());
            TelegramBotSpace::EditMessage(bot, std::get<0>(menuData), query, std::get<1>(menuData));

        } else if (StringTools::startsWith(query->data, "returnToMenuMain")) {
            auto menuData = move(TelegramBotSpace::MenuMain());
            TelegramBotSpace::EditMessage(bot, std::get<0>(menuData), query, std::get<1>(menuData));
        } else if (StringTools::startsWith(query->data, "returnToMenuTickets")) {
            auto menuData = move(TelegramBotSpace::MenuTickets());
            TelegramBotSpace::EditMessage(bot, std::get<0>(menuData), query, std::get<1>(menuData));
            //bot.getApi().deleteMessage(query->message->chat->id, query->message->messageId);
        } else if (StringTools::startsWith(query->data, "BuyTicket")) {


            //покупка билета!!!

        }
    });

    bot.getEvents().onAnyMessage([&bot, &dataBase](TgBot::Message::Ptr message) {
        if (message == nullptr) return;

        std::string userText = message->text;
        
        if (userText.substr(0, 1) == "/" && userText.substr(userText.find(" ") + 1).substr(0, 1) != "/") {
            std::string command = userText.substr(0, userText.find(" ")); 
            std::string arguments = userText.substr(userText.find(" ") + 1);
            std::string response = "";

            if (message->from->id != ADMIN_ID) {
                if (command == "/buyTicket") {
                    arguments = arguments.substr(1);
                    arguments = arguments.substr(0, arguments.size() - 1);
                    int arguments_count = StringToVector(arguments).size();
                    auto menuData = move(TelegramBotSpace::MenuBuyTicket(arguments_count, arguments));
                    switch (TelegramBotSpace::TryMakeCorrectLotteryString(arguments)) {
                        case Info::IS_GOOD_NUMBERS:
                            DataBaseSpace::CreateUserTicket(dataBase, message->from->id, TelegramBotSpace::StringToVector(arguments), DataBaseSpace::GetNearLotteryId(dataBase));
                            TelegramBotSpace::SendMessage(bot, message->chat->id, std::get<0>(menuData), std::get<1>(menuData));
                            break;
                        case Info::SAME_NUMBERS:
                            response = fmt::format(sameNumbersTEXT, arguments);
                            TelegramBotSpace::SendMessage(bot, message->chat->id, response);
                            break;
                        case Info::UNCORRECT_INPUT:
                            response = fmt::format(uncorrectInputTEXT, arguments);
                            TelegramBotSpace::SendMessage(bot, message->chat->id, response);
                            break;
                        case Info::UNCORRECT_NUMBER:
                            response = fmt::format(uncorrectNumbersTEXT, arguments);
                            TelegramBotSpace::SendMessage(bot, message->chat->id, response);
                            break;
                        case Info::WRONG_COUNT_NUMBERS:
                            response = fmt::format(wrongCountNumbersTEXT, arguments);
                            TelegramBotSpace::SendMessage(bot, message->chat->id, response);
                            break;
                        default:
                            break;
                    }
                }
            } else {
                if (command == "/SetLotteryInterval") {
                    if (TelegramBotSpace::IsCorrectDataTime(arguments)) {
                        lotteryIntervalDataTime = arguments;
                        //DataBaseSpace::AddNewLottery(dataBase, arguments);
                        response = fmt::format(trySetLotteryIntervalSuccesTEXT, arguments.substr(0,10), arguments.substr(11,8));
                        TelegramBotSpace::SendMessage(bot, message->chat->id, response);
                    } else {
                        response = trySetLotteryIntervalFailedTEXT;
                        TelegramBotSpace::SendMessage(bot, message->chat->id, response);
                    }
                } else if (command == "/NearestLottery") {
                    std::string dataTimeNearLottery = move(DataBaseSpace::GetNearLotteryDataTime(dataBase));
                    response = fmt::format(nearestLotteryTEXT, dataTimeNearLottery.substr(0,10), dataTimeNearLottery.substr(11,5));
                    TelegramBotSpace::SendMessage(bot, message->chat->id, response);
                }
            }
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

inline void TelegramBotSpace::SendMessage(TgBot::Bot& bot, int64_t chatId, const std::string& message,
        std::shared_ptr<Keyboard> buttons) {
    bot.getApi().sendMessage(chatId, message, false, 0, buttons, "HTML", false);
}

inline void TelegramBotSpace::EditMessage(TgBot::Bot& bot, const std::string& message, const TgBot::CallbackQuery::Ptr& query,
        std::shared_ptr<Keyboard> buttons) {
    bot.getApi().editMessageText(message, query->message->chat->id, query->message->messageId, "", "HTML", false, buttons);
}

void TelegramBotSpace::AddRowButtons(const std::shared_ptr<Keyboard>& buttonsKeyboard, int countButtons, ...) {
    va_list buttonsParams;
    va_start(buttonsParams, countButtons*2);

    std::vector<Button::Ptr> buttonsRow;

    for (int numButton = 0; numButton < countButtons; numButton++) {
        auto button = std::make_shared<Button>();
        
        button->text = va_arg(buttonsParams, const char*);
        button->callbackData = va_arg(buttonsParams, const char*);

        buttonsRow.push_back(button);
    }

    buttonsKeyboard->inlineKeyboard.push_back(buttonsRow);
}

std::tuple<std::string, Keyboard::Ptr> TelegramBotSpace::MenuMain() {
    auto keyboardButtons = std::make_shared<Keyboard>();
    TelegramBotSpace::AddRowButtons(keyboardButtons, 1, "Меню билетов", "MenuTickets");
    const std::string& response = menuMainTEXT;
    return std::make_tuple(response, keyboardButtons);
}

std::tuple<std::string, Keyboard::Ptr> TelegramBotSpace::MenuTickets() {
    auto keyboardButtons = std::make_shared<Keyboard>();
    TelegramBotSpace::AddRowButtons(keyboardButtons, 1, "Назад", "returnToMenuMain");

    const std::string& response = menuTicketsTEXT;

    return std::make_tuple(response, keyboardButtons);
}

std::tuple<std::string, Keyboard::Ptr> TelegramBotSpace::MenuBuyTicket(int ticketAttempts, const std::string& typedNumber) {
    auto keyboardButtons = std::make_shared<Keyboard>();
    TelegramBotSpace::AddRowButtons(keyboardButtons, 2, "Отмена", "returnToMenuTickets", "Купить", "BuyTicket");

    const std::string& response = fmt::format(menuTypedTicketTEXT, ticketAttempts, typedNumber, ticketAttemptsAndCost.at(ticketAttempts));

    return std::make_tuple(response, keyboardButtons);
}

bool TelegramBotSpace::IsCorrectDataTime(const std::string& dataTime) {
    std::regex pattern("\\b(\\d{4})-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01]) (0[0-9]|1[0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])\\b");
    return std::regex_match(dataTime, pattern);
}

Info TelegramBotSpace::TryMakeCorrectLotteryString(const std::string& str) {
    std::vector<int> numbers;
    std::unordered_set<int> checker;
    numbers.reserve(10);
    std::string correctNum; 

    for(const char& c : str) {
        if (c == ',') {
            if (!correctNum.empty()) {
                numbers.push_back(std::stoi(correctNum));
                correctNum = "";
                if (!checker.insert(numbers.back()).second) return Info::SAME_NUMBERS;
            } else return Info::UNCORRECT_INPUT;
        } else if (c >= '0' && c <= '9') {
            correctNum += c;
        } else return Info::UNCORRECT_INPUT;
    }
    numbers.push_back(std::stoi(correctNum));
    correctNum = "";
    if (!checker.insert(numbers.back()).second) return Info::SAME_NUMBERS;
    if (!(numbers.size() <= 19 && numbers.size() >= 6)) return Info::WRONG_COUNT_NUMBERS;

    for (const int& num : numbers) {
        if (!(0 <= num && num <= LOTTERY_FIELD_SIZE)) return Info::UNCORRECT_NUMBER;
    }
    return Info::IS_GOOD_NUMBERS;
}

std::vector<int> TelegramBotSpace::StringToVector(const std::string& str) {
    std::vector<int> returnObject;
    std::string numStr;
    for (const char& c : str) {
        if (isdigit(c)) {
            numStr += c;
        } else {
            if (!numStr.empty()) {
                returnObject.push_back(std::stoi(numStr));
                numStr.clear();
            }
        }
    }
    if (!numStr.empty()) {
        returnObject.push_back(std::stoi(numStr));
    }
    return returnObject;
}