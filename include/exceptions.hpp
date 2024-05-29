#pragma once

#include <exception>

class DivisionByZeroException : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Division by zero encountered";
    }
};

class InvalidColorException : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Invalid color encountered";
    }
};

class CouldNotOpenFileException : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Could not open file";
    }
};

class InvalidShapeException : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Invalid shape encountered";
    }
};