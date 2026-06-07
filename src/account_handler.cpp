#include "account_handler.hpp"

AccountHandler::AccountHandler()
{}

AccountHandler::~AccountHandler()
{}

// void AccountHandler::init_account_handler() {
//     load_json_db();
// }

nlohmann::json AccountHandler::load_json_db() {
    try {
        std::cout << "load 1" << std::endl;
        std::ifstream file("local_db/card_account_db.json");
        std::cout << "load 2" << std::endl;
        if (!file) {
            std::cerr << "Cannot find json file for DB" << std::endl;
            return nlohmann::json();
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        // nlohmann::json loaded_data_ = nlohmann::json::parse(buffer.str());
        nlohmann::json loaded_data = nlohmann::json::parse(buffer.str());
        return loaded_data;
    } catch (const std::exception& e) {
        std::cerr << "JSON error: " << e.what() << std::endl;
        return nlohmann::json();
    }
}

bool AccountHandler::check_if_card_info_is_valid(const std::string & card_info) {
    nlohmann::json json_data = load_json_db();

    if (!json_data.contains(card_info)) {
        std::cerr << "Failed to find certain card info: " << card_info << std::endl;
        return false;
    }
    return true;
}

bool AccountHandler::verify_pin(const std::string & card_info, const std::string & pin_number) {
    nlohmann::json json_data = load_json_db();
    std::string loaded_pin = json_data[card_info]["pin"].get<std::string>();
    if (loaded_pin != pin_number) {
        return false;
    }
    return true;
}
