set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../out)

add_executable(wixed_main main.cpp WixedForm/WixedForm.cpp WixedForm/WixedForm.hpp)
target_link_libraries(wixed_main waffine winterval)
