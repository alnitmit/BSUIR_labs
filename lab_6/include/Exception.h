#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <iostream>

class Exception {
protected:
    std::string message;
    
public:
    Exception(const std::string& msg = "General exception") : message(msg) {}
    virtual ~Exception() = default;
    
    virtual const std::string& what() const { return message; }
    virtual void print() const { std::cout << "Exception: " << message << std::endl; }
};

class MemoryException : public Exception {
public:
    MemoryException(const std::string& msg = "Memory exception") 
        : Exception(msg) {}
    
    void print() const override { 
        std::cout << "MemoryException: " << message << std::endl; 
    }
};

class MemoryAllocationException : public MemoryException {
public:
    MemoryAllocationException(const std::string& msg = "Memory allocation failed") 
        : MemoryException(msg) {}
    
    void print() const override { 
        std::cout << "MemoryAllocationException: " << message << std::endl; 
    }
};

class RangeException : public Exception {
public:
    RangeException(const std::string& msg = "Range exception") 
        : Exception(msg) {}
    
    void print() const override { 
        std::cout << "RangeException: " << message << std::endl; 
    }
};

class IndexOutOfBoundsException : public RangeException {
public:
    IndexOutOfBoundsException(const std::string& msg = "Index out of bounds") 
        : RangeException(msg) {}
    
    void print() const override { 
        std::cout << "IndexOutOfBoundsException: " << message << std::endl; 
    }
};

class ArgumentException : public Exception {
public:
    ArgumentException(const std::string& msg = "Argument exception") 
        : Exception(msg) {}
    
    void print() const override { 
        std::cout << "ArgumentException: " << message << std::endl; 
    }
};

class InvalidArgumentException : public ArgumentException {
public:
    InvalidArgumentException(const std::string& msg = "Invalid argument") 
        : ArgumentException(msg) {}
    
    void print() const override { 
        std::cout << "InvalidArgumentException: " << message << std::endl; 
    }
};

class OverflowException : public Exception {
public:
    OverflowException(const std::string& msg = "Overflow occurred") 
        : Exception(msg) {}
    
    void print() const override { 
        std::cout << "OverflowException: " << message << std::endl; 
    }
};

class UnderflowException : public Exception {
public:
    UnderflowException(const std::string& msg = "Underflow occurred") 
        : Exception(msg) {}
    
    void print() const override { 
        std::cout << "UnderflowException: " << message << std::endl; 
    }
};

#endif