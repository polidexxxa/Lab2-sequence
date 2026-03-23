#include "Tests.hpp"

int main() {
    try {
        Tests::runAllTests();
    } catch (const std::exception& e) {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}