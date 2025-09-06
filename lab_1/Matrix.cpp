#include <iostream>

class TestClass {
public:
    void hello() {
        std::cout << "Hello SonarCloud!" << std::endl;
    }
};

int main() {
    TestClass test;
    test.hello();
    return 0;
} 