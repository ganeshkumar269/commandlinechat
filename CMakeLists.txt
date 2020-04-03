cmake_minimum_required(VERSION 3.14)
project(chatclient)

add_library(FUNCTIONS
    STATIC
    "include/functions.h"
    src/create.cpp
    src/getMessages.cpp
    src/inputParse.cpp
    src/login.cpp
    src/ping.cpp
    src/sendMessage.cpp
    util/getToken.cpp
    )


target_include_directories(FUNCTIONS PUBLIC "include")
target_include_directories(FUNCTIONS PUBLIC dependencies/include)
target_compile_options(FUNCTIONS PUBLIC "-std=c++11")
target_compile_options(FUNCTIONS PUBLIC "-DCURL_STATICLIB")
target_link_directories(FUNCTIONS PUBLIC "${CMAKE_SOURCE_DIR}/dependencies/lib")
target_link_libraries(FUNCTIONS PUBLIC 
    libcrypto.a
    libcurl.a
    libssl.a
    libz.a
    ws2_32
    wldap32
    ws2_32
    winmm
    gdi32
)


add_executable(main main.cpp)

target_link_libraries(main PUBLIC FUNCTIONS)
