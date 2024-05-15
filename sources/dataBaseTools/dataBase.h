#pragma once

#include <sqlite3.h>
#include <iostream>
#include <fmt/core.h>
#include <vector>

#define ADMIN_ID 10669383830
#define DEFAULT_LOTTERY_INTERVAL "0000-00-00 03:00:00"

enum class Info {
    USER_EXISTS,
    USER_NEW,
    ADMIN_JOIN,
    TICKET_ALREADY_CREATED,
    TICKET_CREATED,
    LOTTERY_EXISTS,
    LOTTERY_CREATED,
    SAME_NUMBERS,
    UNCORRECT_NUMBER,
    UNCORRECT_INPUT,
    IS_GOOD_NUMBERS,
    WRONG_COUNT_NUMBERS
};

extern std::string lotteryIntervalDataTime;

namespace DataBaseSpace {
    sqlite3* ConnectToDataBase();

    void CreateDataBaseStructure(sqlite3* dataBase);

    Info TryAddUser(sqlite3* dataBase, int userId);

    Info CreateUserTicket(sqlite3* dataBase, const int64_t userId, const std::vector<int>& numbers, const int64_t lotteryId);

    std::vector<int> StringToVector(const std::string& str);

    std::string VectorToString(const std::vector<int>& vec);

    int64_t GetNearLotteryId(sqlite3* dataBase);

    std::string GetNearLotteryDataTime(sqlite3* dataBase);

    Info AddNewLottery(sqlite3* dataBase, const std::string& dataTime);

    inline std::string GetlotteryIdfromDataTime(const std::string& dataTime);
}