#ifndef MEMORY_EXCEPTION_H
#define MEMORY_EXCEPTION_H

#include "Exception.h"

class MemoryException : public Exception {
public:
    explicit MemoryException(const std::string& msg = "Memory exception") 
        : Exception(msg) {}
    
    void print() const override { 
        std::cout << "MemoryException: " << what() << std::endl; 
    }
};

#endif