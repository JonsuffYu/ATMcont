#include "banking_handler.hpp"

BankingHandler::BankingHandler()
{}

BankingHandler::~BankingHandler()
{}

bool BankingHandler::deposit_money(int & money) {
    nlohmann::json json_data = load_json_db();
    if (!loaded_data_.contains(card) ||
        !loaded_data_[card]["accounts"].contains(acc)) {
        std::cerr << "계좌를 찾을 수 없습니다\n";
        return false;
    }

    // 잔액 수정
    int current = loaded_data_[card]["accounts"][acc]["balance"].get<int>();
    loaded_data_[card]["accounts"][acc]["balance"] = current + amount;

    // 파일에 저장
    std::ofstream file("local_db/card_account_db.json");
    if (!file) {
        std::cerr << "파일을 쓸 수 없습니다\n";
        return false;
    }
    file << loaded_data_.dump(4);
    return true;
}

bool BankingHandler::withdraw_money(int & money) {
    return true;
}

bool BankingHandler::transfer_money(int & money) {
    return true;
}

int BankingHandler::balance_inquiry() {
    return true;
}
