#pragma once
#include "unique_fd.hpp"
class KvmController {
public:
  KvmController();
  void api_check();

private:
  UniqueFd kvm_fd_;
};
