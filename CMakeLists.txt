cmake_minimum_required(VERSION 3.20.0)

project(aos
    VERSION 0.1.0
    LANGUAGES CXX C ASM_NASM)

set(CMAKE_CXX_EXTENSIONS off)
set(CMAKE_C_EXTENSIONS off)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/iso_root/boot")

file(GLOB SRC 
    "src/*.cxx"
    "src/${CMAKE_SYSTEM_PROCESSOR}/*.cxx"
    "src/${CMAKE_SYSTEM_PROCESSOR}/*.s")
file(GLOB flanterm_SRC 
    "thirdparty/Flanterm/src/*.c" 
    "thirdparty/Flanterm/src/flanterm_backends/*.c")

add_executable(aos.kernel
    ${SRC}
    ${flanterm_SRC})

target_include_directories(aos.kernel
    PRIVATE "include" 
            "include/${CMAKE_SYSTEM_PROCESSOR}"
            "thirdparty/limine/limine-protocol/include"
            "thirdparty/freestnd-c-hdrs-0bsd/include"
            "thirdparty/freestnd-cxx-hdrs/${CMAKE_SYSTEM_PROCESSOR}/include"
            "thirdparty/Flanterm/src"
            "thirdparty/printf")
