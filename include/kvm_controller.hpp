#pragma once
#include "unique_fd.hpp"
#include "vmm/SyscallInterface.hpp"
/**
 * @class KvmController
 * @brief The KvmContoller serves as a abstraction layer for the API of Kernel-based Virtual 
 * Machine subsystem.
 */
class KvmController {
public:
  /**
   * @brief Opens up the /dev/kmv file de
   * @param sys the system call interface we will use. Use LinuxSyscall for POSIX.
   */
  KvmController(SyscallInterface &sys);
  void api_check();

private:
  SyscallInterface &sys_;
  UniqueFd kvm_fd_;
};
