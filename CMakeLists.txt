cmake_minimum_required(VERSION 3.11)

project(LotteryBotActivate CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set(PROJECT_NAME "LotteryBotActivate")
set(DIR "sources")

file(GLOB DATA_BASE_FOLDER "${DIR}/dataBaseTools/*.cpp" "${DIR}/dataBaseTools/*.h")
file(GLOB LOTTERY_FOLDER "${DIR}/lotteryLogic/*.cpp" "${DIR}/lotteryLogic/*.h")
file(GLOB TELEGRAM_BOT_FOLDER "${DIR}/telegramBotLogic/*.cpp" "${DIR}/telegramBotLogic/*.h")

add_executable(${PROJECT_NAME} ${DATA_BASE_FOLDER} ${LOTTERY_FOLDER} ${TELEGRAM_BOT_FOLDER} "${DIR}/main.cpp")

find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(fmt REQUIRED)



include_directories(/usr/local/include)
link_directories(/usr/local/lib)

target_include_directories(${PROJECT_NAME} PRIVATE /usr/local/include)
target_link_directories(${PROJECT_NAME} PRIVATE /usr/local/lib)

target_link_libraries(${PROJECT_NAME} fmt::fmt)
target_link_libraries(${PROJECT_NAME} TgBot Boost::system OpenSSL::SSL OpenSSL::Crypto SQLite::SQLite3)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/SQLiteCpp)