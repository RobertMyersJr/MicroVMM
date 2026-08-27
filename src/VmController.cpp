#include "vmm/VmController.hpp"
#include "unique_fd.hpp"
#include "vmm/KvmGuestMemory.hpp"
#include "vmm/KvmVCpu.hpp"
#include "vmm/SyscallInterface.hpp"
#include <stdexcept>
#include <utility>

VmController::VmController(UniqueFd &&vm_fd, SyscallInterface &sys)
    : vm_fd_(std::move(vm_fd)), sys_(sys) {
  if (!vm_fd_.is_valid()) {
    throw std::runtime_error("Failed to create VM: Invalid file descriptor.");
  }
}

KvmGuestMemory VmController::createGuestMemory(std::size_t bytes_to_allocate) {
  if (!vm_fd_.is_valid()) {
    throw std::runtime_error(
        "Cannot create guest memory: VM descriptor is invalid.");
  }
  // Standardized signature: sys, vm_fd, slot_id, bytes, guest_phys_addr
  return KvmGuestMemory{vm_fd_.get(), sys_, bytes_to_allocate};
}

KvmVCpu VmController::createGuestVCpu() {
  if (!vm_fd_.is_valid()) {
    throw std::runtime_error("Cannot create vCPU: VM descriptor is invalid.");
  }
  static unsigned int next_vcpu_id = 0;
  return KvmVCpu{vm_fd_.get(), sys_, next_vcpu_id++};
}
