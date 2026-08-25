# MicroVMM

A minimal KVM-based virtual machine monitor written in C++20.

## Requirements

- Linux with `/dev/kvm` available
- CMake >= 3.20
- A C++20 compiler (e.g. GCC or Clang)
- Internet access on first build (GoogleTest is fetched automatically via CMake `FetchContent`)

### Optional: run without sudo

By default, access to `/dev/kvm` requires root. To avoid running the executable with `sudo`, add yourself to the `kvm` group:

```sh
sudo usermod -aG kvm $USER  # Adds current user to the kvm group
newgrp kvm                  # Refreshes the group
```

## Building

Configure and build with CMake:

```sh
cmake -S . -B build
cmake --build build
```

This produces the `micro_vmm` executable inside the `build/` directory.

## Running

```sh
./build/micro_vmm
```

## Running the tests

Tests are built with GoogleTest and registered with CTest. After building (see above), run:

```sh
ctest --test-dir build --output-on-failure
```

Alternatively, run the test binary directly:

```sh
./build/tests/run_vmm_tests
```
