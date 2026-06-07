#include <iostream>
#include <memory>
#include <map>
#include <string>

#include "account_handler.hpp"
#include "banking_handler.hpp"

class ATMController {
public:
    explicit ATMController();
    virtual ~ATMController();

    bool check_valid_card();
    bool verify_pin(std::string & pin_number);
    void init_atm_controller(std::string & card_info);
    

private:
    std::string card_info_;
    uint8_t NUM_CARD_DIGIT = 4;

    std::shared_ptr<AccountHandler> account_handler_;

    void split_card_info_with_dash(std::string & card_info);
};
