#pragma once
#include "../unique_fd.hpp"
#include "vmm/KvmGuestMemory.hpp"
#include "vmm/KvmVCpu.hpp"
#include "vmm/SyscallInterface.hpp"

class VmController {
public:
  explicit VmController(UniqueFd &&vm_fd, SyscallInterface &sys);

  KvmGuestMemory createGuestMemory(std::size_t bytes_to_allocate);

  KvmVCpu createGuestVCpu();

  [[nodiscard]] bool is_valid() const noexcept { return vm_fd_.is_valid(); }
  [[nodiscard]] int get() const noexcept { return vm_fd_.get(); }

private:
  UniqueFd vm_fd_;
  SyscallInterface &sys_;
};
