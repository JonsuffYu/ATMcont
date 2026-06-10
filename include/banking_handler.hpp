#include <iostream>
#include <json.hpp>
#include <memory>
#include <map>
#include <sstream>
#include <string>
#include <cstdlib>

#include "json_handler.hpp"

class BankingHandler {
public:
    explicit BankingHandler();
    virtual ~BankingHandler();

    bool deposit_or_withdraw(const std::string & card_num, const std::string & account, const int & money);
    std::string get_owner_name_for_transfer(const std::string & account, const std::string & bank_name);
    bool transfer_money(
        const std::string & source_card_num,
        const std::string & source_account,
        const std::string & target_account,
        const std::string & target_bank_name,
        int & money);
    int get_current_balance(const std::string & card_num, const std::string & account);
    std::string get_target_bank_name(const std::string & card_num, const std::string & account);

private:
    inline static nlohmann::json loaded_data_ = load_json_db();
    void set_transfer_info();
};
