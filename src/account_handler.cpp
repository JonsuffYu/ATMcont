#include "account_handler.hpp"

AccountHandler::AccountHandler()
{}

AccountHandler::~AccountHandler()
{}

bool AccountHandler::check_if_card_info_is_valid(std::string & card_info) {
    if (!loaded_data_.contains(card_info)) {
        std::cerr << "Failed to find certain card info: " << card_info << std::endl;
        return false;
    }
    return true;
}

bool AccountHandler::verify_pin(const std::string & card_info, const std::string & pin_number) {
    std::string loaded_pin = loaded_data_[card_info]["pin"].get<std::string>();
    if (loaded_pin != pin_number) {
        return false;
    }
    return true;
}

std::string AccountHandler::get_account_owner(const std::string & card_info) {
    return loaded_data_[card_info]["name"].get<std::string>();
}

std::vector<std::string> AccountHandler::get_account_nums(const std::string & card_info) {
    std::vector<std::string> accounts_per_name;
    for (auto & [account_num, info] : loaded_data_[card_info]["accounts"].items()) {
        accounts_per_name.push_back(account_num);
    }
    return accounts_per_name;
}

std::string AccountHandler::get_owner_name_to_transfer(
    const std::string & account,
    const std::string & bank_name)
{
    std::string name;
    for (auto & [card_num, item] : loaded_data_.items()) {
        auto & accounts = item["accounts"];
        if (accounts.contains(account) && accounts[account]["bank_name"] == bank_name) {
            name = item["name"];
            break;
        }
    }
    return name;
}

void AccountHandler::set_account(const std::string & selected_account) {
    selected_account_ = selected_account;
}

std::string AccountHandler::get_selected_account() {
    return selected_account_;
}

void AccountHandler::reset_selected_account() {
    selected_account_ = "";
}
