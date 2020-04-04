add_library(src
    STATIC
    create.cpp
    getMessages.cpp
    inputParse.cpp
    login.cpp
    ping.cpp
    sendMessage.cpp
)

target_include_directories(src PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_include_directories(src PUBLIC "${CMAKE_SOURCE_DIR}/dependencies/include")
target_compile_options(src PUBLIC "-std=c++11")
target_compile_options(src PUBLIC "-DCURL_STATICLIB")
target_link_directories(src PUBLIC "${CMAKE_SOURCE_DIR}/dependencies/lib")
target_link_libraries(src
    PUBLIC 
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