cmake_minimum_required(VERSION 3.21)
project(g_mem_mac)

set(CMAKE_CXX_STANDARD 20)
set(MY_CODE_SIGN_IDENTITY "Dorving")
set(DEVELOPMENT_TEAM_ID "G-Earth")

if(NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED)
endif()

add_compile_options(
        -std=c++2a
        -Wall
        -Werror)

add_executable(g_mem_mac
        src/main.cpp
        src/process/memory/MemoryChunk.h src/process/memory/MemoryChunk.cc
        src/process/Process.h src/process/Process.cc
        src/process/mac/MacProcess.h src/process/mac/MacProcess.cc
        )

target_link_libraries(g_mem_mac PRIVATE spdlog::spdlog)

set_target_properties(g_mem_mac PROPERTIES
        XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "${MY_CODE_SIGN_IDENTITY}"
        XCODE_ATTRIBUTE_CODE_SIGN_ENTITLEMENTS my.entitlements
        XCODE_ATTRIBUTE_PRODUCT_NAME "G-Mem"
        XCODE_ATTRIBUTE_DEVELOPMENT_TEAM ${DEVELOPMENT_TEAM_ID}
        XCODE_ATTRIBUTE_PROVISIONING_PROFILE_SPECIFIER g_mem
        XCODE_ATTRIBUTE_DEPLOYMENT_POSTPROCESSING YES   # this is needed for strip symbols
)