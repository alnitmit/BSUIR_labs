#ifndef RANGE_EXCEPTION_H
#define RANGE_EXCEPTION_H

#include "Exception.h"

class RangeException : public Exception {
public:
    explicit RangeException(const std::string& msg = "Range exception") 
        : Exception(msg) {}
    
    void print() const override { 
        std::cout << "RangeException: " << what() << std::endl; 
    }
};

#endif