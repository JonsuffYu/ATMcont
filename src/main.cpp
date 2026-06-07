#include <iostream>
#include <memory>
#include "atm_controller.hpp"

enum class ATMPhase
{
    INSERT_CARD,
    VERIFY_PIN,
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
    atm_controller = std::make_shared<ATMController>();
    while (current_phase != ATMPhase::EXIT) {
        switch (current_phase) {
            case ATMPhase::INSERT_CARD: {
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
                current_phase = ATMPhase::SELECT_MENU;
                break;
            }
        }
    }
   

    return 0;
}