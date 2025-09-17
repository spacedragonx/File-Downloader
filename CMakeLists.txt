# CMakeList.txt : CMake project for MTFD, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

cmake_minimum_required(VERSION 3.16)
project(MTFD)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(downloader
    main.cpp
    MTFD.cpp
    MTFD.h
)

# vcpkg dependencies
if(DEFINED CMAKE_TOOLCHAIN_FILE)
    message(STATUS "Using vcpkg toolchain: ${CMAKE_TOOLCHAIN_FILE}")
endif()

find_package(cpr CONFIG REQUIRED)
find_package(CLI11 CONFIG REQUIRED)
find_package(indicators CONFIG REQUIRED)
find_package(ZLIB REQUIRED)

# Link libraries
target_link_libraries(downloader
    PRIVATE
        cpr::cpr
        CLI11::CLI11
        indicators::indicators
        ZLIB::ZLIB
)

# Disable PCH (if you’re not using it)
if(MSVC)
    target_compile_options(downloader PRIVATE /Y-)
endif()
