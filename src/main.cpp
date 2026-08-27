#include "kvm_controller.hpp"
#include "vmm/LinuxSyscall.hpp"
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <iostream>

int main() {
  std::cout << "[MICRO VMM] Initializing workspace..." << std::endl;

  try {
    LinuxSyscall sys_call;

    std::cout << "Initializing hypervisor core...\n";

    KvmController kvm_controller(sys_call);

    std::cout << "KVM Handshake successful. API version 12 verified.\n";

    auto vm_controller = kvm_controller.kvm_create_vm();

    std::cout << "VM controller has been created.\n";

    auto guest_memory =
        vm_controller.createGuestMemory(1024 * 1024 * 64); // 64 MB

    std::cout << "Guest memory of size 64 MB has been allocated.\n";

    auto vcpu = vm_controller.createGuestVCpu();

    std::cout << "Virtual CPU has been created.\n";

    return EXIT_SUCCESS;

  } catch (std::runtime_error &err) {
    std::cerr << "KVM failed. Err: " << err.what() << "\n";
    return EXIT_FAILURE;
  }
}
