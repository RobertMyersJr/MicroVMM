#include <iostream>
#include <fcntl.h>
#include "unique_fd.hpp"

int main() {
    std::cout << "[VMM] Initializing workspace..." << std::endl;

    // Test RAII wrapper using a harmless file (like /dev/null)
    UniqueFd fd(::open("/dev/null", O_RDONLY));
    
    if (!fd) {
        std::cerr << "Failed to open baseline target." << std::endl;
        return 1;
    }
    std::cout << "Successfully wrapped raw fd: " << fd.get() << std::endl;

    // Move ownership test
    UniqueFd moved_fd = std::move(fd);
    std::cout << "Ownership transferred. Old fd valid: " << fd.is_valid() 
              << ", New fd valid: " << moved_fd.is_valid() << std::endl;

    std::cout << "[VMM] Exiting scope. Fd will close automatically." << std::endl;
    return 0;
}
