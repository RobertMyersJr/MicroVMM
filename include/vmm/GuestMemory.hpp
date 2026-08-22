#pragma once
#include "SyscallInterface.hpp"
#include <cstddef>
#include <cstdint>
#include <linux/kvm.h>
#include <span>
#include <stdexcept>
#include <unistd.h>
/**
 * @class KvmGuestMemory
 * @brief Represents the guest memory for a KVM virtual machine. This storage is
 * allocated in the userspace and is used to simulate the memory of a guest
 * operating system.
 */
class KvmGuestMemory {
public:
  explicit KvmGuestMemory(std::size_t bytes_to_allocate, int vm,
                          SyscallInterface &sys)
      : size_of_memory_(bytes_to_allocate), sys_(sys) {
    // KVM expects the guest memory to be page aligned, so we need to allocate
    // memory.
    const std::size_t page_size = ::sysconf(_SC_PAGESIZE);
    address_of_guest_mem_ = reinterpret_cast<uint8_t *>(
        sys_.do_memalign(page_size, size_of_memory_));

    struct kvm_userspace_memory_region kvm_userspace_memory_region_setup = {
        .slot = 0,
        .flags = 0,
        .guest_phys_addr = 0x0, // Starts the memory at 0x00000000
        .memory_size = size_of_memory_,
        .userspace_addr = reinterpret_cast<__u64>(address_of_guest_mem_)};

    auto success = sys_.do_ioctl(vm, KVM_SET_USER_MEMORY_REGION,
                                 &kvm_userspace_memory_region_setup);
    if (!success) {
      throw std::runtime_error("Failed to create Memory space");
    }
  }

  [[nodiscard]] uint64_t userspace_addr() const noexcept {
    return reinterpret_cast<uint64_t>(address_of_guest_mem_);
  }

  [[nodiscard]] std::span<uint8_t> as_span() const noexcept {
    return std::span<uint8_t>(address_of_guest_mem_, size_of_memory_);
  }

  ~KvmGuestMemory() {
    struct kvm_userspace_memory_region kvm_userspace_memory_region_setup = {
        .slot = 0,
        .flags = 0,
        .guest_phys_addr = 0x0,
        .memory_size = 0, // Leave as zero to delete the slot
        .userspace_addr = reinterpret_cast<__u64>(address_of_guest_mem_)};

    sys_.do_ioctl(vm_, KVM_SET_USER_MEMORY_REGION,
                  &kvm_userspace_memory_region_setup);
    sys_.do_free(address_of_guest_mem_);
  }

private:
  std::size_t size_of_memory_;
  int vm_;
  SyscallInterface &sys_;
  uint8_t *address_of_guest_mem_;
};
