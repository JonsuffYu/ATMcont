#include <iostream>
#include <memory>
#include "atm_controller.hpp"

int main() {
    std::shared_ptr<ATMController> atm_controller = std::make_shared<ATMController>();
    atm_controller->launch_controller();
    return 0;
}