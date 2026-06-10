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
    bool check_if_card_info_is_valid(const std::string & card_info);
    bool verify_pin(const std::string & card_info, const std::string & pin_number);
    std::string get_account_name(const std::string & card_info);
    std::vector<std::string> get_account_num(const std::string & card_info);

private:
    inline static nlohmann::json loaded_data_ = load_json_db();

    void init_account_handler();
};
