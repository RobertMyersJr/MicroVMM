#pragma once

#include "unique_fd.hpp"
#include <string_view>
class SyscallInterface {
    public:
        virtual UniqueFd do_open(std::string_view path, int flag) = 0;
        virtual int do_ioctl(int fd, int flag, void* arg) = 0;

        int do_ioctl(const UniqueFd& fd, int flag, void* arg) {
            return do_ioctl(fd.get(), flag, arg);
        }

        virtual ~SyscallInterface() = default;
};
