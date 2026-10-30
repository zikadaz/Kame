cmake_minimum_required(VERSION 3.10)
project(KameLang)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(kame
    src/main.c
    src/lexer.c
)