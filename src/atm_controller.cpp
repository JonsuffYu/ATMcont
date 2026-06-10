#include "atm_controller.hpp"

ATMController::ATMController()
{
    account_handler_ = std::make_shared<AccountHandler>();
    banking_handler_ = std::make_shared<BankingHandler>();
}

ATMController::~ATMController()
{
    if (account_handler_) {
        account_handler_.reset();
    }
    if (banking_handler_) {
        banking_handler_.reset();
    }
}

void ATMController::launch_controller() {
    ATMPhase current_phase = ATMPhase::INSERT_CARD;
    while (current_phase != ATMPhase::EXIT) {
        switch (current_phase) {
            case ATMPhase::INSERT_CARD: {
                std::cout << "Enter card or type card number without '-'" << std::endl;
                std::string card_info, pin_info;
                std::cin >> card_info;
                this->init_atm_controller(card_info);
                bool is_valid_card = this->check_valid_card();
                if (!is_valid_card) {
                    std::cerr << "Unregistered card number detected. Try different number." << std::endl;
                    current_phase = ATMPhase::INSERT_CARD;
                    break;
                }
                current_phase = ATMPhase::VERIFY_PIN;
                break;
            }
            case ATMPhase::VERIFY_PIN: {
                std::cout << "Enter 4 digits pin number" << std::endl;
                std::string pin_info;
                std::cin >> pin_info;
                if (!this->verify_pin(pin_info)) {
                    std::cerr << "Invalid pin number. Try other number." << std::endl;
                    current_phase = ATMPhase::INSERT_CARD;
                    break;
                }
                current_phase = ATMPhase::SELECT_ACCOUNT;
                break;
            }
            case ATMPhase::SELECT_ACCOUNT: {
                std::vector<std::string> account_candidates = this->get_account_nums();
                std::string sample;
                int i = 0;
                for (auto & account_num : account_candidates) {
                    i += 1;
                    sample += std::to_string(i) + ") " + account_num + ", ";
                }
                std::cout << "Select account:" << sample << std::endl;
                int account_selection;
                std::cin >> account_selection;
                if (account_selection <= account_candidates.size()) {
                    this->set_account(account_candidates[account_selection - 1]);
                }
                current_phase = ATMPhase::SELECT_MENU;
                break;
            }
            case ATMPhase::SELECT_MENU: {
                std::string name = this->get_account_owner();
                std::string print_out;
                print_out += "Hello " + name;
                print_out += ", Select menu: 1) DEPOSIT, 2) WITHDRAW, 3) TRANSFER, 4) BALANCE_INQUIRY, ";
                print_out += "5) SELECT_ACCOUNT, 6) INSERT_OTHER_CARD, 7) EXIT";
                std::cout << print_out << std::endl;
                int menu;
                std::cin >> menu;
                if (menu == 1) {
                    current_phase = ATMPhase::DEPOSIT;
                    break;
                } else if (menu == 2) {
                    current_phase = ATMPhase::WITHDRAW;
                    break;
                } else if (menu == 3) {
                    current_phase = ATMPhase::TRANSFER;
                    break;
                } else if (menu == 4) {
                    current_phase = ATMPhase::BALANCE_INQUIRY;
                    break;
                } else if (menu == 5) {
                    current_phase = ATMPhase::SELECT_ACCOUNT;
                    break;
                } else if (menu == 6) {
                    current_phase = ATMPhase::INSERT_CARD;
                    break;
                } else if (menu == 7) {
                    current_phase = ATMPhase::EXIT;
                    break;
                } else {
                    std::cerr << "Invalid input! Try again." << std::endl;
                    current_phase = ATMPhase::SELECT_MENU;
                    break;
                }
            }
            case ATMPhase::DEPOSIT: {
                std::cout << "Enter the amount you want to deposit, or enter 'menu' to select menu" << std::endl;
                std::string amount_money_str;
                std::cin >> amount_money_str;
                current_phase = this->deposit_money(amount_money_str);
                break;
            }
            case ATMPhase::WITHDRAW: {
                std::cout << "Enter the amount you want to withdraw, or enter 'menu' to select menu" << std::endl;
                std::string amount_money_str;
                std::cin >> amount_money_str;
                current_phase = this->withdraw_money(amount_money_str);
                break;
            }
            case ATMPhase::TRANSFER: {
                std::cout << "Enter the account you want to transfer, or enter 'menu' to select menu" << std::endl;
                std::string account;
                std::cin >> account;
                if (account == "menu") {
                    current_phase = ATMPhase::SELECT_MENU;
                    break;
                }
                std::cout << "Enter the bank name of the account, or enter 'menu' to select menu" << std::endl;
                std::string bank_name;
                std::cin >> bank_name;
                if (account == "menu") {
                    current_phase = ATMPhase::SELECT_MENU;
                    break;
                }
                std::cout << "Enter the amount you want to transfer, or enter 'menu' to select menu" << std::endl;
                std::string money_str;
                std::cin >> money_str;
                if (money_str == "menu") {
                    current_phase = ATMPhase::SELECT_MENU;
                    break;
                }
                std::string account_owner_name = this->get_owner_name_to_transfer(account, bank_name);
                if (account_owner_name.empty()) {
                    std::cerr << "Cannot find owner name for the account! Try other account." << std::endl;
                    current_phase = ATMPhase::SELECT_MENU;
                    break;
                }
                std::string print_out;
                print_out += "Are you sure sending '" + money_str + " $' to '" + account_owner_name + "'?";
                print_out += " (y / n)";
                std::cout << print_out << std::endl;
                std::string confirm;
                std::cin >> confirm;
                if (confirm == "y") {
                    current_phase = this->transfer_money(account, bank_name, money_str);
                    break;
                }
            }
            case ATMPhase::BALANCE_INQUIRY: {
                int current_balance = this->get_current_balance();
                std::cout <<  "Your current balance is '" << current_balance <<" $'. Returning to SELECT_MENU" << std::endl;
                current_phase = ATMPhase::SELECT_MENU;
                break;
            }
        }
    }
   
}

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

std::string ATMController::get_account_owner() {
    return account_handler_->get_account_owner(card_info_);
}


void ATMController::set_account(const std::string & selected_account) {
    selected_account_ = selected_account;
}

std::string ATMController::get_selected_account() {
    return selected_account_;
}

void ATMController::reset_selected_account() {
    selected_account_ = "";
}

ATMPhase ATMController::deposit_money(std::string & money_str) {
    int money;
    ATMPhase result = ATMPhase::DEPOSIT;
    try {
        money = std::stoi(money_str);
        if (money < 0) {
            std::cerr << "Only positive amount can be entered! Try again." << std::endl;
        }
    }
    catch(const std::exception & e) {
        if (money_str != "menu") {
            std::cerr << "Invalid input! Try again." << e.what() << std::endl;
        } else {
            return ATMPhase::SELECT_MENU;
        }
    }
    if (!banking_handler_->deposit_or_withdraw(card_info_, selected_account_, money)) {
        std::cerr << "Failed to deposit money! Try again." << std::endl;
    } else {
        std::cout << "Successfully deposited '" << money << " $'. Returning to SELECT_MENU" << std::endl;
        result = ATMPhase::SELECT_MENU;
    }
    return result;
}

ATMPhase ATMController::withdraw_money(std::string & money_str) {
    int money;
    ATMPhase result = ATMPhase::WITHDRAW;
    try {
        money = std::stoi(money_str);
        if (money < 0) {
            std::cerr << "Only positive amount can be entered! Try again." << std::endl;
        }
    }
    catch(const std::exception & e) {
        if (money_str != "menu") {
            std::cerr << "Invalid input! Try again." << e.what() << std::endl;
        } else {
            return ATMPhase::SELECT_MENU;
        }
    }
    int withdraw_money = 0 - money;
    if (!banking_handler_->deposit_or_withdraw(card_info_, selected_account_, withdraw_money)) {
        std::cerr << "Not enough money to withdraw! Try again." << std::endl;
    } else {
        std::cout << "Successfully withdrew '" << money << " $'. Returning to SELECT_MENU" << std::endl;
        result = ATMPhase::SELECT_MENU;
    }
    return result;
}

ATMPhase ATMController::transfer_money(
    const std::string & target_account,
    const std::string & target_bank_name,
    const std::string & money_str)
{
    int money;
    ATMPhase result = ATMPhase::TRANSFER;
    try {
        money = std::stoi(money_str);
        if (money < 0) {
            std::cerr << "Only positive amount can be entered! Try again." << std::endl;
        }
    }
    catch(const std::exception & e) {
        if (money_str != "menu") {
            std::cerr << "Invalid input! Try again." << e.what() << std::endl;
        } else {
            return ATMPhase::SELECT_MENU;
        }
    }
    if (!banking_handler_->transfer_money(
        card_info_, selected_account_, target_account, target_bank_name, money))
    {
        std::cerr << "Failed to transfer money. Try again." << std::endl;
    }
    else
    {
        result = ATMPhase::SELECT_MENU;
    }
    return result;
}

int ATMController::get_current_balance() {
    int balance = -1;
    if (!selected_account_.empty()) {
        balance = banking_handler_->get_current_balance(card_info_, selected_account_);
    }
    return balance;
}

std::string ATMController::get_owner_name_to_transfer(
    const std::string & account,
    const std::string & bank_name)
{
    return account_handler_->get_owner_name_to_transfer(account, bank_name);
}

std::vector<std::string> ATMController::get_account_nums() {
    return account_handler_->get_account_nums(card_info_);
}