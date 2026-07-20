#include <gtest/gtest.h>
#include <stdexcept>
#include <string_view>

#include "kvm_controller.hpp"
#include "vmm/SyscallInterface.hpp"

namespace {

class MockSyscall : public SyscallInterface {
public:
  int open_fd = 42;
  int ioctl_result = 12;

  UniqueFd do_open(std::string_view, int) override {
    return UniqueFd(open_fd);
  }

  int do_ioctl(int, int, void *) override {
    return ioctl_result;
  }
};

}

TEST(KvmHandshakeTest, SucceedsOnVersion12) {
  MockSyscall sys;
  sys.ioctl_result = 12;

  EXPECT_NO_THROW({ KvmController vmm(sys); });
}

TEST(KvmHandshakeTest, HandlesUnsupportedApiVersion) {
  MockSyscall sys;
  sys.ioctl_result = 11;

  EXPECT_THROW({ KvmController vmm(sys); }, std::runtime_error);
}

TEST(KvmHandshakeTest, HandlesIoctlFailure) {
  MockSyscall sys;
  sys.ioctl_result = -1;

  EXPECT_THROW({ KvmController vmm(sys); }, std::runtime_error);
}

TEST(KvmHandshakeTest, HandlesOpenFailure) {
  MockSyscall sys;
  sys.open_fd = -1;

  EXPECT_THROW({ KvmController vmm(sys); }, std::runtime_error);
}
