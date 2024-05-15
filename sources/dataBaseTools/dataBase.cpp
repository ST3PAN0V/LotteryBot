#include "dataBase.h"

std::string lotteryIntervalDataTime = DEFAULT_LOTTERY_INTERVAL;

sqlite3* DataBaseSpace::ConnectToDataBase() {
    sqlite3* dataBase;
    int rc = sqlite3_open("../sources/dataBase.db", &dataBase);
    if (rc) {
        std::cout << sqlite3_errmsg(dataBase) << std::endl;
        std::cout << fmt::format("error {} {}", __FILE__, __LINE__).c_str() << std::endl;
        sqlite3_free(dataBase);
        throw std::runtime_error("DataBaseConnection");
    }
    return dataBase;
}

void DataBaseSpace::CreateDataBaseStructure(sqlite3* dataBase) {
    char* errorMessage = 0;
    int rc;

    const char* createUsersTableSQL = "CREATE TABLE IF NOT EXISTS Users ("
                                      "user_id INTEGER PRIMARY KEY,"
                                      "tickets_purchased INTEGER,"
                                      "wallet TEXT"
                                      ");";

    rc = sqlite3_exec(dataBase, createUsersTableSQL, 0, 0, &errorMessage);

    if (rc != SQLITE_OK) {
        std::cout << errorMessage <<std::endl;
        std::cout << fmt::format("error {} {}", __FILE__, __LINE__) <<std::endl;
        sqlite3_free(errorMessage);
        throw std::runtime_error("CreateTableError");
    }

    // Создание таблицы ticket
    const char* createTicketTableSQL = "CREATE TABLE IF NOT EXISTS tickets ("
                                       "ticket_id INTEGER PRIMARY KEY,"
                                       "owner_id INTEGER,"
                                       "lottery_id INTEGER,"
                                       "selected_numbers TEXT,"
                                       "active BOOL"
                                       ");";

    rc = sqlite3_exec(dataBase, createTicketTableSQL, 0, 0, &errorMessage);

    if (rc != SQLITE_OK) {
        std::cout << errorMessage <<std::endl;
        std::cout << fmt::format("error {} {}", __FILE__, __LINE__) <<std::endl;
        sqlite3_free(errorMessage);
        throw std::runtime_error("CreateTableError");
    }

    // Создание таблицы lotteries
    const char* createLotteriesTableSQL = "CREATE TABLE IF NOT EXISTS lotteries ("
                                          "lottery_id INTEGER PRIMARY KEY,"
                                          "prize_numbers TEXT,"
                                          "datetime_lottery DATETIME"
                                          ");";

    rc = sqlite3_exec(dataBase, createLotteriesTableSQL, 0, 0, &errorMessage);

    if (rc != SQLITE_OK) {
        std::cout << errorMessage <<std::endl;
        std::cout << fmt::format("error {} {}", __FILE__, __LINE__) <<std::endl;
        sqlite3_free(errorMessage);
        throw std::runtime_error("CreateTableError");
    }
}

Info DataBaseSpace::TryAddUser(sqlite3* dataBase, int userId) {
    char* errorMessage = 0;
    int rc;

    if (userId == ADMIN_ID) {
        return Info::ADMIN_JOIN;
    }
    std::string sqlCheck = fmt::format("SELECT user_id FROM users WHERE user_id = {}", userId);
    sqlite3_stmt* checkStmt;
    sqlite3_prepare_v2(dataBase, sqlCheck.c_str(), -1, &checkStmt, NULL);
    rc = sqlite3_step(checkStmt);
    if (rc == SQLITE_ROW) {
        sqlite3_finalize(checkStmt);
        return Info::USER_EXISTS;
    }
    sqlite3_finalize(checkStmt);

    std::string insertUserSQL = fmt::format("INSERT INTO Users (user_id, tickets_purchased, wallet) VALUES ({}, 0, NULL);", userId);
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(dataBase, insertUserSQL.c_str(), -1, &stmt, NULL);

    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE && rc != SQLITE_OK) {
        std::cout << errorMessage <<std::endl;
        std::cout << fmt::format("error {} {}", __FILE__, __LINE__) <<std::endl;
        sqlite3_free(errorMessage);
        throw std::runtime_error("CreateTableError");
    }

    return Info::USER_NEW;
}

Info DataBaseSpace::CreateUserTicket(sqlite3* dataBase, const int64_t userId, const std::vector<int>& numbers, const int64_t lotteryId) {  
    char* errorMessage = 0;
    std::string selected_numbers = move(DataBaseSpace::VectorToString(numbers));
    std::string ticketId = std::to_string(userId) + std::to_string(lotteryId);

    std::string insertSQL = "INSERT INTO tickets (active, ticket_id, owner_id, lottery_id, selected_numbers) VALUES ("
                            + std::to_string(false) + ","
                            + ticketId + ","
                            + std::to_string(userId) + ","
                            + std::to_string(lotteryId) + ",'"
                            + selected_numbers + "');";

    int rc = sqlite3_exec(dataBase, insertSQL.c_str(), NULL, 0, &errorMessage);

    if (rc != SQLITE_CONSTRAINT_PRIMARYKEY) return Info::TICKET_ALREADY_CREATED;
    else if (rc != SQLITE_OK) {
        std::cout << errorMessage <<std::endl;
        std::cout << fmt::format("error {} {}", __FILE__, __LINE__) <<std::endl;
        sqlite3_free(errorMessage);
        throw std::runtime_error("CreateTableError");
    }
    return Info::TICKET_CREATED;

}


std::vector<int> DataBaseSpace::StringToVector(const std::string& str) {
    std::vector<int> returnObject;
    std::string numStr;
    for (const char c : str) {
        if (c == ',') {
            if (!numStr.empty()) {
                returnObject.push_back(std::stoi(numStr));
                numStr.clear();
            }
        } else {
            numStr += c;
        }
    }
    if (!numStr.empty()) {
        returnObject.push_back(std::stoi(numStr));
    }
    return returnObject;
}

std::string DataBaseSpace::VectorToString(const std::vector<int>& vec) {
    std::string returnObject;
    for (size_t i = 0; i < vec.size(); ++i) {
        returnObject += std::to_string(vec[i]);
        if (i != vec.size() - 1) returnObject += ',';
    }
    return returnObject;
}

std::string DataBaseSpace::GetNearLotteryDataTime(sqlite3* dataBase) {
    std::string returnObject;
    std::string query = "SELECT * FROM lotteries ORDER BY datetime_lottery DESC LIMIT 1;";

    sqlite3_stmt* statement;
    int rc = sqlite3_prepare_v2(dataBase, query.c_str(), -1, &statement, nullptr);

    if (rc == SQLITE_OK || rc == SQLITE_DONE) {
        rc = sqlite3_step(statement);
        if (rc == SQLITE_ROW) {
            returnObject = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 2)));
        } else {
            return "";
        }
        sqlite3_finalize(statement);
    } else {
        std::cout << fmt::format("error {} {}", __FILE__, __LINE__) <<std::endl;
        throw std::runtime_error("Failed to execute query");
    }
    return returnObject;
}

int64_t DataBaseSpace::GetNearLotteryId(sqlite3* dataBase) {
    int64_t returnObject = -1;
    std::string query = "SELECT * FROM lotteries ORDER BY datetime_lottery DESC LIMIT 1;";

    sqlite3_stmt* statement;
    int rc = sqlite3_prepare_v2(dataBase, query.c_str(), -1, &statement, nullptr);

    if (rc == SQLITE_OK || rc == SQLITE_DONE) {
        rc = sqlite3_step(statement);
        if (rc == SQLITE_ROW) {
            try {
                returnObject = std::stoll(reinterpret_cast<const char*>(sqlite3_column_text(statement, 1)));
            } catch (...){
                returnObject = -1;
            }
        } else {
            return returnObject;
        }
        sqlite3_finalize(statement);
    } else {
        std::cout << fmt::format("error {} {}", __FILE__, __LINE__) <<std::endl;
        throw std::runtime_error("Failed to execute query");
    }
    return returnObject;
}

Info DataBaseSpace::AddNewLottery(sqlite3* dataBase, const std::string& dataTime) {
    char* errorMessage = 0;
    int64_t lotteryId = std::stoll(DataBaseSpace::GetlotteryIdfromDataTime(dataTime));
    
    std::string insertSQL = fmt::format("INSERT INTO lotteries (lottery_id, prize_numbers, datetime_lottery) "
                                                "VALUES ({}, '', '{}');", lotteryId, dataTime);
    
    int rc = sqlite3_exec(dataBase, insertSQL.c_str(), NULL, 0, &errorMessage);
    
    if (rc == SQLITE_CONSTRAINT_PRIMARYKEY) {
        return Info::LOTTERY_EXISTS;
    } else if (rc != SQLITE_OK && rc != SQLITE_DONE) {
        std::cout << errorMessage <<std::endl;
        std::cout << fmt::format("error {} {}", __FILE__, __LINE__) <<std::endl;
        sqlite3_free(errorMessage);
        throw std::runtime_error("CreateLotteryError");
    }
    return Info::LOTTERY_CREATED;
}

inline std::string DataBaseSpace::GetlotteryIdfromDataTime(const std::string& dataTime) {
    return dataTime.substr(0, 4) + dataTime.substr(5, 2) + dataTime.substr(8, 2) +
            dataTime.substr(11, 2) + dataTime.substr(14, 2) + dataTime.substr(17, 2);
}