#include <fstream>
#include <iostream>
#include <json.hpp>
#include <memory>
#include <map>
#include <sstream>
#include <string>

#include "json_handler.hpp"

class AccountHandler {
public:
    explicit AccountHandler();
    virtual ~AccountHandler();

    bool check_if_card_info_is_valid(std::string & card_info);
    bool verify_pin(const std::string & card_info, const std::string & pin_number);
    std::string get_account_owner(const std::string & card_info);
    std::vector<std::string> get_account_nums(const std::string & card_info);
    std::string get_owner_name_to_transfer(const std::string & account, const std::string & bank_name);
    void set_account(const std::string & selected_account);
    void reset_selected_account();
    std::string get_selected_account();
    void reset_account_selection();

private:
    inline static nlohmann::json loaded_data_ = load_json_db();
    std::string selected_account_;
    void init_account_handler();
};
