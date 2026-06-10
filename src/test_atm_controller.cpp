#include <iostream>
#include <string>
#include <vector>

#include "atm_controller.hpp"

static int count_pass = 0;
static int count_fail = 0;

static const std::string CARD  = "1234abcd5678efgh"; // raw, no dashes (split inserts dashes)
static const std::string PIN   = "2468";
static const std::string OWNER = "Jon";

void check(bool cond, const std::string & msg) {
    if (cond) {
        std::cout << "PASS: " << msg << std::endl;
        ++ count_pass;
    } else {
        std::cout << "FAIL: " << msg << std::endl;
        ++ count_fail;
    }
}

static void test_valid_card() {
    std::cout << "Card validation" << std::endl;

    std::shared_ptr<ATMController> atm_controller = std::make_shared<ATMController>();
    std::string card = CARD;
    atm_controller->init_atm_controller(card);
    check(atm_controller->check_valid_card(), "registered card is accepted");

    std::shared_ptr<ATMController> atm_controller_2 = std::make_shared<ATMController>();
    std::string bad = "0000000000000000";
    atm_controller_2->init_atm_controller(bad);
    check(!atm_controller_2->check_valid_card(), "unregistered card is rejected");
}

static void test_pin() {
    std::cout << "PIN verification" << std::endl;

    std::shared_ptr<ATMController> atm_controller = std::make_shared<ATMController>();
    std::string card = CARD;
    atm_controller->init_atm_controller(card);

    std::string ok = PIN;
    check(atm_controller->verify_pin(ok), "correct PIN passes");

    std::string ng = "0000";
    check(!atm_controller->verify_pin(ng), "wrong PIN is rejected");
}

static void test_owner_and_accounts() {
    std::cout << "Owner / account list" << std::endl;

    std::shared_ptr<ATMController> atm_controller = std::make_shared<ATMController>();
    std::string card = CARD;
    atm_controller->init_atm_controller(card);

    check(atm_controller->get_account_owner() == OWNER, "owner name is Jon");

    std::vector<std::string> accounts = atm_controller->get_account_nums();
    check(accounts.size() == 2, "two accounts are listed");
}

static void test_deposit_withdraw() {
    std::cout << "Deposit / withdraw" << std::endl;

    std::shared_ptr<ATMController> atm_controller = std::make_shared<ATMController>();
    std::string card = CARD;
    atm_controller->init_atm_controller(card);

    std::vector<std::string> accounts = atm_controller->get_account_nums();
    if (accounts.empty()) { check(false, "no accounts - DB load probably failed"); return; }
    atm_controller->set_account(accounts[0]);

    int before = atm_controller->get_current_balance();

    std::string deposit_money = "100";
    atm_controller->deposit_money(deposit_money);
    check(atm_controller->get_current_balance() == before + 100, "balance +100 after deposit");

    std::string withdraw_money = "100";
    atm_controller->withdraw_money(withdraw_money);
    check(atm_controller->get_current_balance() == before, "balance restored after withdraw");
}

static void test_over_withdraw() {
    std::cout << "Over-withdraw" << std::endl;

    std::shared_ptr<ATMController> atm_controller = std::make_shared<ATMController>();
    std::string card = CARD;
    atm_controller->init_atm_controller(card);

    std::vector<std::string> accounts = atm_controller->get_account_nums();
    if (accounts.empty()) { check(false, "no accounts - DB load probably failed"); return; }
    atm_controller->set_account(accounts[0]);

    int before = atm_controller->get_current_balance();
    std::string big = std::to_string(before + 1000000); // far more than the balance
    atm_controller->withdraw_money(big);
    check(atm_controller->get_current_balance() == before, "over-withdraw rejected (balance unchanged)");
}

static void test_transfer() {
    std::cout << "Transfer" << std::endl;

    std::shared_ptr<ATMController> atm_controller = std::make_shared<ATMController>();
    std::string card = CARD;
    atm_controller->init_atm_controller(card);

    std::vector<std::string> accounts = atm_controller->get_account_nums();
    if (accounts.size() < 2) { check(false, "two accounts required"); return; }

    const std::string source = accounts[1];
    const std::string target = accounts[0];
    const std::string target_bank = "cool_bank";

    atm_controller->set_account(source);
    int source_before = atm_controller->get_current_balance();
    atm_controller->set_account(target);
    int target_before = atm_controller->get_current_balance();

    atm_controller->set_account(source);
    std::string transfer_money = "50";
    atm_controller->transfer_money(target, target_bank, transfer_money);

    atm_controller->set_account(source);
    int source_after = atm_controller->get_current_balance();
    atm_controller->set_account(target);
    int target_after = atm_controller->get_current_balance();

    check(source_after == source_before - 50, "source account -50 after transfer");
    check(target_after == target_before + 50, "destination account +50 after transfer");

    atm_controller->set_account(target);
    std::string back = "50";
    atm_controller->transfer_money(source, target_bank, back);
}

// ---------------------------------------------------------------------
int main() {
    std::cout << "   ATMController tests start" << std::endl;

    test_valid_card();
    test_pin();
    test_owner_and_accounts();
    test_deposit_withdraw();
    test_over_withdraw();
    test_transfer();

    std::cout << "   Result: " << count_pass << " PASS / " << count_fail << " FAIL" << std::endl;

    return (count_fail == 0) ? 0 : 1;
}
