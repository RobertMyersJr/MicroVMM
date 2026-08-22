#include "vmm/LinuxSyscall.hpp"

#include <cstdlib>
#include <fcntl.h>
#include <stdexcept>
#include <string>
#include <sys/ioctl.h>

UniqueFd LinuxSyscall::do_open(std::string_view path, int flag) {
  int fd = ::open(std::string(path).c_str(), flag | O_CLOEXEC);

  return UniqueFd(fd);
}

int LinuxSyscall::do_ioctl(int fd, int flag, void *arg) {
  return ::ioctl(fd, flag, arg);
}

void *LinuxSyscall::do_memalign(size_t alignment, size_t size) {
  void *mem_address = nullptr;
  auto ret = posix_memalign(&mem_address, alignment, size);
  if (ret != 0) {
    std::string err_msg = "Failed to mem align: ERR " + std::to_string(ret);
    throw std::runtime_error(err_msg);
  }
  return mem_address;
}

void LinuxSyscall::do_free(void *ptr) { std::free(ptr); }
