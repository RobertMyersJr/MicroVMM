#pragma once
#include "SyscallInterface.hpp"

class LinuxSyscall : public SyscallInterface {
    public:
        LinuxSyscall() = default;
        ~LinuxSyscall() override = default;

        UniqueFd do_open(std::string_view path, int flag) override;
        int do_ioctl(int fd, int flag, void* arg) override;
};
