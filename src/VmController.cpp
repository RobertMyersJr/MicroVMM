#include "vmm/VmController.hpp"
#include "unique_fd.hpp"
#include "vmm/GuestMemory.hpp"
#include "vmm/SyscallInterface.hpp"
#include <stdexcept>

VmController::VmController(UniqueFd &&vm_fd, SyscallInterface &sys)
    : vm_fd_(vm_fd.release()), sys_(sys) {
  if (!vm_fd_.is_valid()) {
    throw std::runtime_error("Failed to create VM");
  }
}

KvmGuestMemory VmController::createGuestMemory(std::size_t bytes_to_allocate) {
  return KvmGuestMemory{bytes_to_allocate, vm_fd_.get(), sys_};
}
