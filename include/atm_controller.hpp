#include <iostream>
#include <memory>
#include <map>
#include <string>

#include "account_handler.hpp"
#include "banking_handler.hpp"

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

class ATMController {
public:
    explicit ATMController();
    virtual ~ATMController();
    void launch_controller();

    bool check_valid_card();
    bool verify_pin(std::string & pin_number);
    std::string get_account_owner();
    std::vector<std::string> get_account_nums();
    ATMPhase deposit_money(std::string & money_str);
    ATMPhase withdraw_money(std::string & money_str);
    ATMPhase transfer_money(
        const std::string & target_account,
        const std::string & target_bank_name,
        const std::string & money_str);
    void init_atm_controller(std::string & card_info);

    void set_account(const std::string & selected_account);
    void reset_selected_account();
    std::string get_selected_account();
    void reset_account_selection();

    int get_current_balance();
    

private:
    std::string card_info_;
    uint8_t NUM_CARD_DIGIT = 4;

    std::shared_ptr<AccountHandler> account_handler_;
    std::shared_ptr<BankingHandler> banking_handler_;
    std::string selected_account_;

    void split_card_info_with_dash(std::string & card_info);
    std::string get_owner_name_to_transfer(
        const std::string & account,
        const std::string & bank_name);
};
