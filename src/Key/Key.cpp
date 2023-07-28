#include "Key.h"

Key::Key() = default;

[[maybe_unused]] Key::Key(std::string_view n, std::string_view v) {
    this->name = n;
    this->value = v;
}