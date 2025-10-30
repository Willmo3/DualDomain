include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# Windows compatibility
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../out/tests)
add_executable(test_mixed test_mixed_scalar.cpp test_mixed_binop.cpp test_mixed_unop.cpp test_mixed_serialization.cpp)
target_link_libraries(test_mixed caffeine winterval dualdomain gtest_main)
