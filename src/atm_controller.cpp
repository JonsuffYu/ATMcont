#include "atm_controller.hpp"

ATMController::ATMController()
{}

ATMController::~ATMController()
{}

void ATMController::init_atm_controller(std::string & card_info) {
    split_card_info_with_dash(card_info);
}

void ATMController::split_card_info_with_dash(std::string & card_info) {
    for (size_t i = 0; i < card_info.size(); i += NUM_CARD_DIGIT) {
        card_info_ += card_info.substr(i, NUM_CARD_DIGIT);
        if (i + NUM_CARD_DIGIT < card_info.size()) {
            card_info_ += "-";
        }
    }
    std::cout << "card info: " << card_info_ << std::endl;
}

bool ATMController::check_valid_card() {
    return account_handler_->check_if_card_info_is_valid(card_info_);
}

bool ATMController::verify_pin(std::string & pin_number) {
    return account_handler_->verify_pin(card_info_, pin_number);
}

std::string ATMController::get_account_name() {
    return account_handler_->get_account_name(card_info_);
}
std::vector<std::string> ATMController::get_account_num() {
    return account_handler_->get_account_num(card_info_);
}

bool ATMController::deposit_money(int & money) {

    return true;
}
