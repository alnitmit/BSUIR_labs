#ifndef INVALID_ARGUMENT_EXCEPTION_H
#define INVALID_ARGUMENT_EXCEPTION_H

#include "ArgumentException.h"

class InvalidArgumentException : public ArgumentException {
public:
    explicit InvalidArgumentException(const std::string& msg = "Invalid argument") 
        : ArgumentException(msg) {}
    
    void print() const override { 
        std::cout << "InvalidArgumentException: " << what() << std::endl; 
    }
};

#endif