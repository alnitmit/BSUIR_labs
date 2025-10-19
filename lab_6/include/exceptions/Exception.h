#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <iostream>

class Exception {
private:
    std::string message;
    
public:
    explicit Exception(const std::string& msg = "General exception") : message(msg) {}
    virtual ~Exception() = default;
    
    virtual const std::string& what() const { return message; }
    virtual void print() const { std::cout << "Exception: " << message << std::endl; }
};

#endif