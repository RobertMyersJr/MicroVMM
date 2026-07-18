#include "../include/kvm_controller.hpp"
#include <fcntl.h>
#include <linux/kvm.h>
#include <stdexcept>
#include <sys/ioctl.h>
#include <unistd.h>

KvmController::KvmController() : kvm_fd_(::open("/dev/kvm", O_RDWR)) {
    if(!kvm_fd_.is_valid()) {
        throw std::runtime_error("Failed to open /dev/kvm");
    }
}

void KvmController::api_check() {
  auto api_version = ::ioctl(kvm_fd_.get(), KVM_GET_API_VERSION, 0);

  if (api_version < 0) {
    throw std::runtime_error("Failed to query KVM API version.");
  }

  if (api_version != 12) {
    throw std::runtime_error("Unsupported KVM API version! Expected 12, got " +
                             std::to_string(api_version));
  }
}
