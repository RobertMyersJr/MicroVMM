#include "vmm/LinuxSyscall.hpp"

#include <fcntl.h>
#include <sys/ioctl.h>
#include <string>

UniqueFd LinuxSyscall::do_open(std::string_view path, int flag) {
    int fd = ::open(std::string(path).c_str(), flag | O_CLOEXEC);
    
    return UniqueFd(fd);
}

int LinuxSyscall::do_ioctl(int fd, int flag, void* arg) {
    return ::ioctl(fd, flag, arg);
}
