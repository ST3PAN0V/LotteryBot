#pragma once

#include <random>
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <iostream>
#include <algorithm>


#define DEFAULT_TICKET_ATTEMPTS 6
#define LOTTERY_FIELD_SIZE 45
#define PRIZE_SLOTS 6

//---------------------------------FORWARD DECLARATION---------------------------------

class User;
class Ticket;
class LotteryField;

const std::unordered_map<int,int> ticketAttemptsAndCost = {
    {6, 50},
    {7, 350},
    {8, 1'400},
    {9, 4'200},
    {10, 10'500},
    {11, 23'100},
    {12, 46'200},
    {13, 85'800},
    {14, 150'150},
    {15, 250'250},
    {16, 400'400},
    {17, 618'800},
    {18, 928'200},
    {19, 1'356'600}
};

const std::unordered_map<int,int> countGuessesAndWinAmount = {
    {2, 100},
    {3, 300},
    {4, 1'500},
    {5, 100'000},
    {6, 150'000'000}
};

//-------------------------------------------------------------------------------------

class User {
public:
    User();
    User(std::string name, int balance);

    void BuyTicket(int num);
    void IncreaseBalance(int prize);
    void UsedTicket();

    int GetBalance() const;
    std::string GetName() const;
    const std::vector<int>& GetTicketField() const;
    bool HasValidTicket() const;

private:
    std::string name_;
    int balance_;
    std::unique_ptr<Ticket> ticket_;
    
    void UseTicket();

};

class Ticket {
public:
    Ticket();
    Ticket(int attempts);

    void GuessNumbers(std::vector<int>& selectedNumbers);

    int GetTicketAttempts() const;
    const std::vector<int>& GetTicketField() const;

private:
    std::vector<int> ticketField_;
    int attempts_;

}; 

class RandomGenerator {
public:
    RandomGenerator();

    int GetRandomNumber(int maxValue);

    ~RandomGenerator();

private:
    std::random_device rd;
    std::mt19937 gen_;

};

class LotteryField {
public:
    LotteryField();

    const std::vector<int>& GetPrizeField() const;

private:
    RandomGenerator randomGenerator_;
    std::vector<int> lotteryField_;

    void GeneratePriseSlots();

};

class LotteryDraw {
public:
    LotteryDraw();

    void StartLottery();
    User* ControlUser(std::string name);
    void FinishLottery();
    void AddNewUser(std::string name, int balance);
    void OpenTicketsAndGetPrizes();
    static bool GetLotteryIsStart();

private:
    static bool lotteryIsStart;
    std::vector<std::unique_ptr<User>> users_;
    std::unique_ptr<LotteryField> prizeField_;

};