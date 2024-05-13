#include "dataBase.h"

sqlite3* DataBaseSpace::ConnectToDataBase() {
    sqlite3* dataBase;
    int rc = sqlite3_open("../sources/dataBase.db", &dataBase);
    if (rc) {
        throw std::runtime_error(fmt::format("error {} {}", __FILE__, __LINE__).c_str()); //sqlite3_errmsg(dataBase)
    }
    return dataBase;
}

void DataBaseSpace::CreateDataBaseStructure(sqlite3* dataBase) {
    char* errorMessage = 0;
    int rc;

    const char* createUsersTableSQL = "CREATE TABLE IF NOT EXISTS Users ("
                                      "user_id INTEGER PRIMARY KEY,"
                                      //"username TEXT,"
                                      "wallet TEXT"
                                      ");";

    rc = sqlite3_exec(dataBase, createUsersTableSQL, 0, 0, &errorMessage);

    if (rc != SQLITE_OK) {
        sqlite3_free(errorMessage);
        throw std::runtime_error(errorMessage);
    }

    // Создание таблицы ticket
    const char* createTicketTableSQL = "CREATE TABLE IF NOT EXISTS ticket ("
                                       "ticket_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                       "owner_id INTEGER,"
                                       "lottery_id INTEGER,"
                                       "selected_numbers TEXT"
                                       ");";

    rc = sqlite3_exec(dataBase, createTicketTableSQL, 0, 0, &errorMessage);

    if (rc != SQLITE_OK) {
        sqlite3_free(errorMessage);
        throw std::runtime_error(errorMessage);
    }

    // Создание таблицы lotteries
    const char* createLotteriesTableSQL = "CREATE TABLE IF NOT EXISTS lotteries ("
                                          "lottery_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                          "prize_numbers TEXT,"
                                          "data_lottery TEXT"
                                          ");";

    rc = sqlite3_exec(dataBase, createLotteriesTableSQL, 0, 0, &errorMessage);

    if (rc != SQLITE_OK) {
        sqlite3_free(errorMessage);
        throw std::runtime_error(fmt::format("error {} {}", __FILE__, __LINE__).c_str()); //errorMessage
    }
}

Info DataBaseSpace::TryAddUser(sqlite3* dataBase, int userId) {
    char* errorMessage = 0;
    int rc;

    std::string sqlCheck = fmt::format("SELECT user_id FROM users WHERE user_id = {}", userId);
    sqlite3_stmt* checkStmt;
    sqlite3_prepare_v2(dataBase, sqlCheck.c_str(), -1, &checkStmt, NULL);
    rc = sqlite3_step(checkStmt);
    if (rc == SQLITE_ROW) {
        sqlite3_finalize(checkStmt);
        return Info::USER_EXISTS;
    }
    sqlite3_finalize(checkStmt);

    std::string insertUserSQL = fmt::format("INSERT INTO Users (user_id, wallet) VALUES ({}, NULL);", userId);
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(dataBase, insertUserSQL.c_str(), -1, &stmt, NULL);

    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE && rc != SQLITE_OK) {
        sqlite3_free(errorMessage);
        throw std::runtime_error(fmt::format("error {} {}", __FILE__, __LINE__).c_str()); //errmes
    }

    return Info::USER_NEW;
}