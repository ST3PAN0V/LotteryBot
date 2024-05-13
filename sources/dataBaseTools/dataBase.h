#pragma once

#include <sqlite3.h>
#include <iostream>
#include <fmt/core.h>

enum class Info {
    USER_EXISTS,
    USER_NEW
};

namespace DataBaseSpace {
    sqlite3* ConnectToDataBase();

    void CreateDataBaseStructure(sqlite3* dataBase);

    Info TryAddUser(sqlite3* dataBase, int userId);
}