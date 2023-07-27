cmake_minimum_required(VERSION 3.26)
project(JSONParser)

set(CMAKE_CXX_STANDARD 23)

add_executable(JSONParser main.cpp
        src/Tokenizer/Tokenizer.cpp
        src/Tokenizer/Tokenizer.h)
