#ifndef INDEX_OUT_OF_BOUNDS_EXCEPTION_H
#define INDEX_OUT_OF_BOUNDS_EXCEPTION_H

#include "RangeException.h"

class IndexOutOfBoundsException : public RangeException {
public:
    explicit IndexOutOfBoundsException(const std::string& msg = "Index out of bounds") 
        : RangeException(msg) {}
    
    void print() const override { 
        std::cout << "IndexOutOfBoundsException: " << what() << std::endl; 
    }
};

#endif