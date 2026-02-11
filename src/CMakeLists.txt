set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../out)

add_library(dualdomain STATIC MixedForm/MixedForm.cpp MixedForm/MixedForm.hpp)
target_link_libraries(dualdomain caffeine winterval)
add_executable(dual_main main.cpp)
target_link_libraries(dual_main dualdomain)
