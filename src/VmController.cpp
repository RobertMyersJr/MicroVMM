#include "vmm/VmController.hpp"
#include "unique_fd.hpp"
#include <stdexcept>

VmController::VmController(UniqueFd &&vm_fd) : vm_fd_(vm_fd.release()) {
  if (!vm_fd_.is_valid()) {
    throw std::runtime_error("Failed to create VM");
  }
}
