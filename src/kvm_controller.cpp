#include "../include/kvm_controller.hpp"
#include "unique_fd.hpp"
#include "vmm/VmController.hpp"
#include <fcntl.h>
#include <linux/kvm.h>
#include <stdexcept>
#include <sys/ioctl.h>
#include <unistd.h>

KvmController::KvmController(SyscallInterface &sys)
    : sys_(sys), kvm_fd_(sys_.do_open("/dev/kvm", O_RDWR)) {
  if (!kvm_fd_.is_valid()) {
    throw std::runtime_error("Failed to open /dev/kvm");
  }
  api_check();
}

void KvmController::api_check() {
  auto api_version = sys_.do_ioctl(kvm_fd_.get(), KVM_GET_API_VERSION, 0);

  if (api_version < 0) {
    throw std::runtime_error("Failed to query KVM API version.");
  }

  if (api_version != 12) {
    throw std::runtime_error("Unsupported KVM API version! Expected 12, got " +
                             std::to_string(api_version));
  }
}

VmController KvmController::kvm_create_vm() {
  auto vm_fd = UniqueFd(sys_.do_ioctl(kvm_fd_.get(), KVM_CREATE_VM, 0));
  return VmController(std::move(vm_fd));
}
