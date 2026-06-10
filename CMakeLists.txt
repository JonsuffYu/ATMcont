cmake_minimum_required(VERSION 4.3)
project(ATMcount)

set(CMAKE_CXX_STANDARD 17)

add_executable(ATMcount
    src/main.cpp
    src/account_handler.cpp
    src/atm_controller.cpp
    src/banking_handler.cpp
)
target_include_directories(ATMcount PRIVATE
    include
)

add_executable(atm_tests
    src/test_atm_controller.cpp
    src/atm_controller.cpp
    src/account_handler.cpp
    src/banking_handler.cpp
)
target_include_directories(atm_tests PRIVATE include)


file(COPY
    ${CMAKE_SOURCE_DIR}/local_db
    DESTINATION
    ${CMAKE_BINARY_DIR}
)

add_custom_command(TARGET ATMcount POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/local_db/card_account_db.json
        $<TARGET_FILE_DIR:ATMcount>/card_account_db.json)
