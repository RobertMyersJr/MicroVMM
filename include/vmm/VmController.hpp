#pragma once
#include "../unique_fd.hpp"

class VmController {
public:
  explicit VmController(UniqueFd &&vm_fd);

  [[nodiscard]] bool is_valid() const noexcept { return vm_fd_.is_valid(); }
  [[nodiscard]] int get() const noexcept { return vm_fd_.get(); }

private:
  UniqueFd vm_fd_;
};
