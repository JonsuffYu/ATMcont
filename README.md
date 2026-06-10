# ATM controller

## Purpose of the project
- This project is to make a simple ATM, including functions below
  - Identification by inserting card and entering PIN number
  - Selecting bank account
  - See balance / deposit / withdraw

## Functions
- Insert card: type a card number without any dashes
- Verify PIN: checking 4 digit PIN to get access for target accounts
- Select account: pick one if the card has multiple accounts
- Select menu: select a menu for banking;deposit, withdraw, transfer, balance inquiry ..
  - Balances are saved to card_account_db.json, so they stay between runs

## Launch project
### How to install main program
- Type the instruction below to build project
```
mkdir build
cd build

cmake ..
cmake --build .
```
- On Windows the exe will be located in build/Debug/. The json db needs to be
reachable from there, so copy card_account_db.json next to the exe if
it can't find it.

### How to run
- Type the command below to run project
```
cd Debug
ATMcount.exe
```

## Test
- test_atm_controller.cpp runs some checks on ATMController:
  - valid card accepted, invalid card rejected
  - right/wrong PIN
  - owner name and account list
  - deposit / withdraw, and over-withdraw gets rejected
  - transfer

### How to install test program
- Type the instruction below to build project
```
cmake --build . --target atm_tests
```

### How to run
- Type the command below to run project
```
cd Debug
atm_tests.exe
```