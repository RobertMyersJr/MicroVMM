include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(run_vmm_tests
    test_kvm_controller.cpp
    ${CORE_SOURCES}
)

target_link_libraries(run_vmm_tests
    PRIVATE
    gtest_main
    micro_vmm_headers
)

include(GoogleTest)
gtest_discover_tests(run_vmm_tests)
