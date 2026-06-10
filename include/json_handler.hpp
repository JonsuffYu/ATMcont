#pragma once
#include <fstream>
#include <iostream>
#include <json.hpp>
#include <memory>
#include <map>
#include <sstream>
#include <string>

inline std::string file_name = "card_account_db.json";

inline nlohmann::json load_json_db() {
    try {
        std::ifstream file(file_name);
        if (!file) {
            std::cerr << "Cannot find json file for DB" << std::endl;
            return nlohmann::json();
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        nlohmann::json loaded_data = nlohmann::json::parse(buffer.str());
        return loaded_data;
    } catch (const std::exception& e) {
        std::cerr << "JSON error: " << e.what() << std::endl;
        return nlohmann::json();
    }
}

inline bool dump_json(const nlohmann::json& json_data) {
    std::ofstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Cannot open file" << std::endl;
        return false;
    }
    file << json_data.dump(4);
    return true;
}