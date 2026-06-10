#pragma once
#include <fstream>
#include <iostream>
#include <json.hpp>
#include <memory>
#include <map>
#include <sstream>
#include <string>


inline nlohmann::json load_json_db() {
    try {
        std::ifstream file("../local_db/card_account_db.json");
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
