set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../out)

add_library(dualdomain STATIC MixedForm.cpp MixedForm.hpp)
add_executable(dual_main main.cpp)
target_link_libraries(dual_main caffeine winterval dualdomain)
