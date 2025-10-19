#ifndef MEMORY_ALLOCATION_EXCEPTION_H
#define MEMORY_ALLOCATION_EXCEPTION_H

#include "MemoryException.h"

class MemoryAllocationException : public MemoryException {
public:
    explicit MemoryAllocationException(const std::string& msg = "Memory allocation failed") 
        : MemoryException(msg) {}
    
    void print() const override { 
        std::cout << "MemoryAllocationException: " << what() << std::endl; 
    }
};

#endif