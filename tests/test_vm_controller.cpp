#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include <string_view>

#include "MockSyscall.hpp"
#include "kvm_controller.hpp"
#include "vmm/KvmVCpu.hpp"
#include "vmm/LinuxSyscall.hpp"
#include "vmm/SyscallInterface.hpp"
#include "vmm/VmController.hpp"

TEST(VmControllerTest, SucceedsOnValidFd) {
  MockSyscall sys;
  EXPECT_NO_THROW({ VmController vmc(UniqueFd(12), sys); });
}

TEST(VmControllerTest, HandlesBadFileDescriptor) {
  LinuxSyscall sys;
  EXPECT_THROW({ VmController vmc(UniqueFd(-1), sys); }, std::runtime_error);
}

TEST(VmControllerIntegrationTest, CreatesGuestMemory) {
  LinuxSyscall sys;

  std::unique_ptr<KvmController> kvm;
  try {
    kvm = std::make_unique<KvmController>(sys);
  } catch (const std::runtime_error &err) {
    GTEST_SKIP() << "Skipping KVM integration test, /dev/kvm is unavailable: "
                 << err.what();
  }

  VmController vmc = kvm->kvm_create_vm();
  ASSERT_TRUE(vmc.is_valid());

  constexpr std::size_t page_size = 4096;
  KvmGuestMemory guest_memory;

  EXPECT_NO_THROW(guest_memory = vmc.createGuestMemory(page_size));

  EXPECT_NE(guest_memory.userspace_addr(), 0u);
  EXPECT_EQ(guest_memory.as_span().size(), page_size);
}

TEST(VmControllerIntegrationTest, CreatesVCpu) {
  LinuxSyscall sys;

  std::unique_ptr<KvmController> kvm;
  try {
    kvm = std::make_unique<KvmController>(sys);
  } catch (const std::runtime_error &err) {
    GTEST_SKIP() << "Skipping KVM integration test, /dev/kvm is unavailable: "
                 << err.what();
  }

  VmController vmc = kvm->kvm_create_vm();
  ASSERT_TRUE(vmc.is_valid());

  KvmVCpu guest_cpu = vmc.createGuestVCpu();
}
