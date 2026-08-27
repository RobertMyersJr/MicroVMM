#pragma once
#include "SyscallInterface.hpp"
#include <cstddef>
#include <cstdint>
#include <linux/kvm.h>
#include <span>
#include <stdexcept>
#include <unistd.h>
/**
 * @class KvmVCpu
 * @brief Represents a virtual CPU (vCPU) for a KVM virtual machine. This class
 * is responsible for creating and managing a vCPU instance within the context
 * of a KVM virtual machine.
 */
class KvmVCpu {
public:
  explicit KvmVCpu(int vm, SyscallInterface &sys, unsigned int vcpu_id)
      : vm_(vm), sys_(sys) {
    vcpu_fd_ = UniqueFd{
        sys_.do_ioctl(vm_, KVM_CREATE_VCPU, reinterpret_cast<void *>(vcpu_id))};

    int errno_do_ioctl = errno;

    if (!vcpu_fd_.is_valid()) {
      throw std::runtime_error(
          "Failed to create vCPU id : " + std::to_string(vcpu_id) +
          ". Error code: " + std::to_string(errno_do_ioctl));
    }
  }

private:
  int vm_;
  SyscallInterface &sys_;
  UniqueFd vcpu_fd_;
};
