set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../out)

add_library(wixed STATIC WixedForm/WixedForm.cpp WixedForm/WixedForm.hpp)
add_executable(wixed_main main.cpp)
target_link_libraries(wixed_main caffeine winterval wixed)
