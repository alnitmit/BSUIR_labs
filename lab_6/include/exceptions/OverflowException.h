#ifndef OVERFLOW_EXCEPTION_H
#define OVERFLOW_EXCEPTION_H

#include "Exception.h"

class OverflowException : public Exception {
public:
    explicit OverflowException(const std::string& msg = "Overflow occurred") 
        : Exception(msg) {}
    
    void print() const override { 
        std::cout << "OverflowException: " << what() << std::endl; 
    }
};

#endif