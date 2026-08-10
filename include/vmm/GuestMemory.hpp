#pragma once
#include "SyscallInterface.hpp"
#include <cstddef>
#include <cstdint>
#include <span>
class KvmGuestMemory {
    public:
        explicit KvmGuestMemory(std::size_t bytes_to_allocate, SyscallInterface &sys) : 
            size_of_memory_(
                    bytes_to_allocate
                    ),
            sys_(sys) {
                const std::size_t alignment = 4096;
                address_of_guest_mem_ = reinterpret_cast<uint8_t*>(sys_.do_memalign(alignment, size_of_memory_));
            }
        [[nodiscard]] uint64_t userspace_addr() const noexcept {
            return reinterpret_cast<uint64_t>(address_of_guest_mem_);
        }

        [[nodiscard]] std::span<uint8_t> as_span() const noexcept {
            return std::span<uint8_t>(address_of_guest_mem_, size_of_memory_);

        }
    private:
        std::size_t size_of_memory_;
        SyscallInterface &sys_;
        uint8_t * address_of_guest_mem_;
};
