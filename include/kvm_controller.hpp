#pragma once
#include "unique_fd.hpp"
/**
 * @class KvmController
 * @brief The KvmContoller serves as a abstraction layer for the API of Kernel-based Virtual 
 * Machine subsystem.
 */
class KvmController {
public:
  /**
   * @brief Opens up the /dev/kmv file de
   */
  KvmController();
  void api_check();

private:
  UniqueFd kvm_fd_;
};
