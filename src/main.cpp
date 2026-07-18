#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fcntl.h>
#include "kvm_controller.hpp"

int main() {
    std::cout << "[MICRO VMM] Initializing workspace..." << std::endl;

    KvmController kvm_controller;

    try {
        kvm_controller.api_check();
    } catch (std::runtime_error &err) {
        std::printf("KVM failed the API check. Err: %s", err.what());
        std::exit(1);
    }

    return 0;
}
