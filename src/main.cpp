#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fcntl.h>
#include "kvm_controller.hpp"
#include "vmm/LinuxSyscall.hpp"

int main() {
    std::cout << "[MICRO VMM] Initializing workspace..." << std::endl;

    try {
        LinuxSyscall sys_call;

        std::cout << "Initializing hypervisor core...\n";

        KvmController kvm_controller(sys_call);

        std::cout << "KVM Handshake successful. API version 12 verified.\n";

        return EXIT_SUCCESS;

    } catch (std::runtime_error &err) {
        std::cerr << "KVM failed the API check. Err: " << err.what() << "\n";
        return EXIT_FAILURE;
    }
}
