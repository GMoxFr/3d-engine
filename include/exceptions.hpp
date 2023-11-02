#pragma once

#include <exception>

class DivisionByZeroException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Division by zero encountered";
    }
};