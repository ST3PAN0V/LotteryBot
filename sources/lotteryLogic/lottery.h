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

extern const std::unordered_map<int,int> ticketAttemptsAndCost;
extern const std::unordered_map<int,int> countGuessesAndWinAmount;

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