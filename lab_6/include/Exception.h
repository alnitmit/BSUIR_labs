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

class MemoryException : public Exception {
public:
    explicit MemoryException(const std::string& msg = "Memory exception") 
        : Exception(msg) {}
    
    void print() const override { 
        std::cout << "MemoryException: " << what() << std::endl; 
    }
};

class MemoryAllocationException : public MemoryException {
public:
    explicit MemoryAllocationException(const std::string& msg = "Memory allocation failed") 
        : MemoryException(msg) {}
    
    void print() const override { 
        std::cout << "MemoryAllocationException: " << what() << std::endl; 
    }
};

class RangeException : public Exception {
public:
    explicit RangeException(const std::string& msg = "Range exception") 
        : Exception(msg) {}
    
    void print() const override { 
        std::cout << "RangeException: " << what() << std::endl; 
    }
};

class IndexOutOfBoundsException : public RangeException {
public:
    explicit IndexOutOfBoundsException(const std::string& msg = "Index out of bounds") 
        : RangeException(msg) {}
    
    void print() const override { 
        std::cout << "IndexOutOfBoundsException: " << what() << std::endl; 
    }
};

class ArgumentException : public Exception {
public:
    explicit ArgumentException(const std::string& msg = "Argument exception") 
        : Exception(msg) {}
    
    void print() const override { 
        std::cout << "ArgumentException: " << what() << std::endl; 
    }
};

class InvalidArgumentException : public ArgumentException {
public:
    explicit InvalidArgumentException(const std::string& msg = "Invalid argument") 
        : ArgumentException(msg) {}
    
    void print() const override { 
        std::cout << "InvalidArgumentException: " << what() << std::endl; 
    }
};

class OverflowException : public Exception {
public:
    explicit OverflowException(const std::string& msg = "Overflow occurred") 
        : Exception(msg) {}
    
    void print() const override { 
        std::cout << "OverflowException: " << what() << std::endl; 
    }
};

class UnderflowException : public Exception {
public:
    explicit UnderflowException(const std::string& msg = "Underflow occurred") 
        : Exception(msg) {}
    
    void print() const override { 
        std::cout << "UnderflowException: " << what() << std::endl; 
    }
};

#endif