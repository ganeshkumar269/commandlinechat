add_library(util
    STATIC
    getToken.cpp
)

target_include_directories(util PUBLIC "${CMAKE_SOURCE_DIR}/include")
