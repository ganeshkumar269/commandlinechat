add_library(include
    STATIC
    functions.hpp
)
set_target_properties(include PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(include PUBLIC "${CMAKE_SOURCE_DIR}/dependencies/include")