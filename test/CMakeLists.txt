include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# Windows compatibility
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../out/tests)
add_executable(test_wixed test_wixed_scalar.cpp test_wixed_binop.cpp test_wixed_unop.cpp test_wixed_serialization.cpp)
target_link_libraries(test_wixed caffeine winterval wixed gtest_main)
