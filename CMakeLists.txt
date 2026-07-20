cmake_minimum_required(VERSION 3.20)
project(MicroVMM CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Sources shared between the main executable and the test binary
set(CORE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/kvm_controller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/LinuxSyscall.cpp
)

set(SOURCES
    src/main.cpp
    ${CORE_SOURCES}
)

# Enable strong warnings to catch low-level mistakes early
add_compile_options(-Wall -Wextra -Wpedantic)

add_library(micro_vmm_headers INTERFACE)

target_include_directories(micro_vmm_headers INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(micro_vmm ${SOURCES})

target_link_libraries(micro_vmm PRIVATE micro_vmm_headers)

enable_testing()
add_subdirectory(tests)

