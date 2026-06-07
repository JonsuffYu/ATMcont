cmake_minimum_required(VERSION 4.3)
project(ATMcount)

set(CMAKE_CXX_STANDARD 17)

add_executable(ATMcount
    src/main.cpp
    src/account_handler.cpp
    src/atm_controller.cpp
)

target_include_directories(ATMcount PRIVATE
    include
)

file(COPY
    ${CMAKE_SOURCE_DIR}/local_db
    DESTINATION
    ${CMAKE_BINARY_DIR}
)