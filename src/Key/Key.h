#pragma once

#include <iostream>
#include <string_view>

class Key {
public:
    Key();

    [[maybe_unused]] Key(std::string_view n, std::string_view v);

    std::string name;
    std::string value;
    std::string type;
};