#include "lottery.h"

//---------------------------------USER---------------------------------

User::User() : name_("NONE"), balance_(0), ticket_(nullptr) {}

User::User(std::string name, int balance) : name_(name), balance_(balance), ticket_(nullptr) {}

void User::BuyTicket(int ticketAttempts) {
    try {
        if (LotteryDraw::GetLotteryIsStart()) throw std::runtime_error("You can't buy a ticket! Lottery is already started.");
        if (balance_ - ticketAttemptsAndCost.at(ticketAttempts) >= 0) {
            ticket_ = std::make_unique<Ticket>(ticketAttempts);
            balance_ -= ticketAttemptsAndCost.at(ticketAttempts);
        } else throw std::runtime_error("Not enought money!");
        
    }
    catch (const std::runtime_error& error) {
        std::cout<<error.what()<<std::endl;
        return;
    } catch(...) {
        std::cout<<"Something went wrong :("<<std::endl;
        return;
    }
    UseTicket();
    std::cout<<std::endl<<"Ticket successfully used! wait for the lottery to start."<<std::endl<<std::endl;
}

int User::GetBalance() const {
    return balance_;
}

std::string User::GetName() const {
    return name_;
}

void User::UseTicket() {
    std::cout<<"* "<<this->GetName()<<" - use a ticket *"<<std::endl<<std::endl;
    std::vector<int> typedNumbers;
    for (int attempt = 0; attempt < ticket_->GetTicketAttempts(); attempt++) {
        std::cout<<attempt+1<<" number : ";
        int tmp;
        std::cin>>tmp;
        typedNumbers.push_back(tmp);
    }
    try{
        ticket_->GuessNumbers(typedNumbers);
    }
    catch (const std::runtime_error& error) {
        if (std::string(error.what()) == "You can't choose the same slot twice" || std::string(error.what()) == "Wrong number. please type number in range from 1 to 45!") {
            std::cout<<std::endl<<error.what()<<std::endl<<std::endl;
            UseTicket();
        } else std::cout<<error.what()<<std::endl;
    }
    catch (...) {
        std::cout<<"Something went wrong :("<<std::endl;
    }
}

const std::vector<int>& User::GetTicketField() const {
    return ticket_->GetTicketField();
}

void User::IncreaseBalance(int prize) {
    balance_ += prize;
}

bool User::HasValidTicket() const {
    return ticket_ != nullptr;
}

void User::UsedTicket() {
    ticket_.reset();
    ticket_ = nullptr;
}

//---------------------------------RANDOM GENERATOR---------------------------------

RandomGenerator::RandomGenerator() : gen_(rd()) {}

int RandomGenerator::GetRandomNumber(int maxValue) {
    return gen_() % maxValue + 1;
}

RandomGenerator::~RandomGenerator() = default;

//---------------------------------LOTTERY FIELD---------------------------------


LotteryField::LotteryField() : lotteryField_(), randomGenerator_() {
    GeneratePriseSlots();
}


void LotteryField::GeneratePriseSlots() {
    int currentPrizeSlots = 0;
    while(currentPrizeSlots < PRIZE_SLOTS) {
        int randNumber = randomGenerator_.GetRandomNumber(LOTTERY_FIELD_SIZE);
        if (std::find(lotteryField_.begin(), lotteryField_.end(), randNumber) == lotteryField_.end()) {
            lotteryField_.push_back(randNumber);
            currentPrizeSlots++;
        }
    }
}

const std::vector<int>& LotteryField::GetPrizeField() const {
    return lotteryField_;
}

//---------------------------------TICKET---------------------------------

Ticket::Ticket() : attempts_(DEFAULT_TICKET_ATTEMPTS), ticketField_() {}

Ticket::Ticket(int attempts) : attempts_(attempts), ticketField_() {}

void Ticket::GuessNumbers(std::vector<int>& selectedNumbers) {
    ticketField_.clear();
    for (const auto number : selectedNumbers) {
        if (std::find(ticketField_.begin(), ticketField_.end(), number) != ticketField_.end()) throw std::runtime_error("You can't choose the same slot twice");
        if (number < 1 || number > 45) throw std::runtime_error("Wrong number. please type number in range from 1 to 45!");
        ticketField_.push_back(number);
    }
}

int Ticket::GetTicketAttempts() const {
    return attempts_;
}

const std::vector<int>& Ticket::GetTicketField() const {
    return ticketField_;
}

//---------------------------------LOTTERY DRAW---------------------------------

LotteryDraw::LotteryDraw() {}

void LotteryDraw::StartLottery() {
    lotteryIsStart = true;
    std::cout<<"The lottery begins..."<<std::endl;
    prizeField_ = std::make_unique<LotteryField>();
}

void LotteryDraw::FinishLottery() {
    prizeField_.reset();
    lotteryIsStart = false;
    std::cout<<"The lottery finished"<<std::endl;
}

void LotteryDraw::AddNewUser(std::string name, int balance) {
    users_.push_back(std::make_unique<User>(name, balance));
}

bool LotteryDraw::GetLotteryIsStart() {
    return lotteryIsStart;
}

void LotteryDraw::OpenTicketsAndGetPrizes() {
    for (auto& user : users_) {
        if (!user->HasValidTicket()) continue;
        int totalGuess = 0;
        for (const auto userNumber : user->GetTicketField()) {
            if (std::find(prizeField_->GetPrizeField().begin(), prizeField_->GetPrizeField().end(), userNumber) != 
                    prizeField_->GetPrizeField().end()) totalGuess++;
        }
        user->UsedTicket();
        if (totalGuess > 1) {
            std::cout<<user->GetName()<<" - guess "<<totalGuess<<" and won "<<countGuessesAndWinAmount.at(totalGuess)<<" points!"<<std::endl;
            user->IncreaseBalance(countGuessesAndWinAmount.at(totalGuess));
        } else {
            std::cout<<user->GetName()<<" - just lost money."<<std::endl;
        }
    }
}

User* LotteryDraw::ControlUser(std::string name) {
    for (auto& user : users_) {
        if (user->GetName() == name) return user.get();
    }
    return nullptr;
}

bool LotteryDraw::lotteryIsStart = false;