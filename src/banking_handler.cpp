#include "banking_handler.hpp"

BankingHandler::BankingHandler()
{}

BankingHandler::~BankingHandler()
{}

bool BankingHandler::deposit_or_withdraw(
    const std::string & card_num,
    const std::string & account,
    const int & money)
{
    int current_balance = loaded_data_[card_num]["accounts"][account]["balance"].get<int>();
    int new_balance = current_balance + money;
    std::string print_out;
    if (new_balance < 0) {
        return false;
    }
    print_out += "Your current balance is '" + std::to_string(new_balance) + "$'. Returning to SELECT_MENU";
    std::cout << print_out << std::endl;
    nlohmann::json new_json = load_json_db();
    new_json[card_num]["accounts"][account]["balance"] = new_balance;
    dump_json(new_json);
    loaded_data_ = load_json_db();
    return true;
}

bool BankingHandler::transfer_money(
    const std::string & source_card_num,
    const std::string & source_account,
    const std::string & target_account,
    const std::string & target_bank_name,
    int & money)
{
    bool result = false;
    int withdraw_money = 0 - money;
    if (!this->deposit_or_withdraw(source_card_num, source_account, withdraw_money)) {
        std::cerr << "Not enough money to transfer! Try different amount of money again." << std::endl;
        return result;
    }
    for (auto & [card_num, item] : loaded_data_.items()) {
        auto & accounts = item["accounts"];
        if (accounts.contains(target_account) && accounts[target_account]["bank_name"] == target_bank_name) {
            int balance = accounts[target_account]["balance"].get<int>();
            int new_balance = balance + money;
            accounts[target_account]["balance"] = new_balance;
            
            nlohmann::json new_json = load_json_db();
            new_json[card_num]["accounts"][target_account]["balance"] = new_balance;
            dump_json(new_json);
            loaded_data_ = load_json_db();
            result = true;
            break;
        }
    }
    return result;
}

int BankingHandler::get_current_balance(const std::string & card_num, const std::string & account) {
    return loaded_data_[card_num]["accounts"][account]["balance"].get<int>();
}

std::string BankingHandler::get_target_bank_name(const std::string & card_num, const std::string & account) {
    return loaded_data_[card_num]["accounts"][account]["bank_name"].get<std::string>();
}
