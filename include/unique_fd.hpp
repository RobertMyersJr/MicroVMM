#pragma once
#include <unistd.h>
#include <utility>

class UniqueFd {
public:
  UniqueFd() : fd_(-1) {}

  explicit UniqueFd(int fd) : fd_(fd) {}

  // Destructor: This is the heart of RAII. Automatically releases the resource.
  ~UniqueFd() { reset(); }

  // Disable copying: A file descriptor must have a single distinct owner
  UniqueFd(const UniqueFd &) = delete;
  UniqueFd &operator=(const UniqueFd &) = delete;

  UniqueFd(UniqueFd &&other) noexcept : fd_(other.release()) {}

  UniqueFd &operator=(UniqueFd &&other) noexcept {
    if (this != &other) {
      reset(other.release());
    }
    return *this;
  }

  // Accessors
  [[nodiscard]] int get() const noexcept { return fd_; }
  [[nodiscard]] bool is_valid() const noexcept { return fd_ >= 0; }

  // Explicit bool conversion for simple checks: if (fd) { ... }
  explicit operator bool() const noexcept { return is_valid(); }

  // Release ownership without closing the underlying descriptor
  int release() noexcept { return std::exchange(fd_, -1); }

  // Close current descriptor and optionally take ownership of a new one
  void reset(int new_fd = -1) noexcept {
    if (fd_ >= 0) {
      ::close(fd_);
    }
    fd_ = new_fd;
  }

private:
  int fd_;
};
