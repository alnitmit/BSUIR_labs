#ifndef ARGUMENT_EXCEPTION_H
#define ARGUMENT_EXCEPTION_H

#include "Exception.h"

class ArgumentException : public Exception {
public:
    explicit ArgumentException(const std::string& msg = "Argument exception") 
        : Exception(msg) {}
    
    void print() const override { 
        std::cout << "ArgumentException: " << what() << std::endl; 
    }
};

#endif