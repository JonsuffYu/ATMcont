#include <iostream>
#include <memory>
#include "atm_controller.hpp"

enum class ATMPhase
{
    INSERT_CARD,
    VERIFY_PIN,
    SELECT_ACCOUNT,
    SELECT_MENU,
    DEPOSIT,
    WITHDRAW,
    TRANSFER,
    BALANCE_INQUIRY,
    EXIT
};

std::shared_ptr<ATMController> atm_controller;

int main() {
    ATMPhase current_phase = ATMPhase::INSERT_CARD;
    while (current_phase != ATMPhase::EXIT) {
        switch (current_phase) {
            case ATMPhase::INSERT_CARD: {
                atm_controller = std::make_shared<ATMController>();
                std::cout << "Enter card or type card number without '-'" << std::endl;
                std::string card_info, pin_info;
                std::cin >> card_info;
                atm_controller->init_atm_controller(card_info);
                bool is_valid_card = atm_controller->check_valid_card();
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
                if (!atm_controller->verify_pin(pin_info)) {
                    std::cerr << "Invalid pin number. Try other number." << std::endl;
                    current_phase = ATMPhase::INSERT_CARD;
                    break;
                }
                current_phase = ATMPhase::SELECT_ACCOUNT;
                break;
            }
            case ATMPhase::SELECT_ACCOUNT: {
                std::vector<std::string> account_candidates = atm_controller->get_account_num();
                std::string sample;
                int i = 0;
                for (auto & account_num : account_candidates) {
                    i += 1;
                    sample += std::to_string(i) + ") " + account_num + ", ";
                }
                std::cout << "Select account:" << sample << std::endl;
                std::string account_number;
                std::cin >> account_number;
            }
            case ATMPhase::SELECT_MENU: {
                std::string name = atm_controller->get_account_name();
                std::string print_out;
                print_out += "Hello " + name;
                print_out += ", Select menu: 1) DEPOSIT, 2) WITHDRAW, 3) TRANSFER, 4) BALANCE_INQUIRY, 5) EXIT";
                std::cout << print_out << std::endl;
                std::string menu;
                std::cin >> menu;
                if (menu == "1") {
                    current_phase = ATMPhase::DEPOSIT;
                } else if (menu == "2") {
                    current_phase = ATMPhase::WITHDRAW;
                } else if (menu == "3") {
                    current_phase = ATMPhase::TRANSFER;
                } else if (menu == "4") {
                    current_phase = ATMPhase::BALANCE_INQUIRY;
                } else if (menu == "5") {
                    std::cout << "Exit selected. Return to card inserting menu" << std::endl;
                    current_phase = ATMPhase::INSERT_CARD;
                } else {
                    std::cerr << "Invalid menu clicked, try again" << std::endl;
                    current_phase = ATMPhase::SELECT_MENU;
                    break;
                }
            }
            case ATMPhase::DEPOSIT: {
                std::cout << "Input cash and enter the amount of money" << std::endl;
                std::string amount_money;
                std::cin >> amount_money;
                // static_cast
            }
        }
    }
   

    return 0;
}