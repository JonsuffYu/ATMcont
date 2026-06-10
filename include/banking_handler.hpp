#include <iostream>
#include <json.hpp>
#include <memory>
#include <map>
#include <sstream>
#include <string>

#include "json_handler.hpp"

class BankingHandler {
public:
    explicit BankingHandler();
    virtual ~BankingHandler();

    bool deposit_money(int & money);
    bool withdraw_money(int & money);
    bool transfer_money(int & money);
    int balance_inquiry();

private:
    inline static nlohmann::json loaded_data_ = load_json_db();
};
