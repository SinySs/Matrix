#pragma once

#include <exception>
#include <string>

class matrix_exception : public std::exception
{
    std::string msg_;
public:
    matrix_exception(const std::string &msg) : msg_(msg) {};
    const char * what() const noexcept override {
        return msg_.c_str();
    }
};
