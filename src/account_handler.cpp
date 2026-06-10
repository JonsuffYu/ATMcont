#include "account_handler.hpp"

AccountHandler::AccountHandler()
{}

AccountHandler::~AccountHandler()
{}

bool AccountHandler::check_if_card_info_is_valid(const std::string & card_info) {
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

std::string AccountHandler::get_account_name(const std::string & card_info) {
    return loaded_data_[card_info]["name"].get<std::string>();
}

std::vector<std::string> AccountHandler::get_account_num(const std::string & card_info) {
    std::vector<std::string> accounts_per_name;
    for (auto & [account_num, info] : loaded_data_[card_info]["accounts"].items()) {
        accounts_per_name.push_back(account_num);
    }
    return accounts_per_name;
}
