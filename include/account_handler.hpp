#include <fstream>
#include <iostream>
#include <json.hpp>
#include <memory>
#include <map>
#include <sstream>
#include <string>

class AccountHandler {
public:
    explicit AccountHandler();
    virtual ~AccountHandler();
    bool check_if_card_info_is_valid(const std::string & card_info);
    bool verify_pin(const std::string & card_info, const std::string & pin_number);

private:
    std::map<std::string, std::string> access_tokens_per_card_;
    std::map<std::string, int> db_card_account_;
    nlohmann::json loaded_data_;

    void init_account_handler();
    nlohmann::json load_json_db();
};
