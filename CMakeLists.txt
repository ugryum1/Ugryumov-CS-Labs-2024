cmake_minimum_required(VERSION 3.20)

project(Encryption)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/encryption.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/encryption.hpp
)

add_executable(Encryption ${SOURCES} ${HEADERS})
set_property(TARGET Encryption PROPERTY CXX_STANDARD 20)
target_compile_options(Encryption PRIVATE -Wall -Wextra -Werror -Wpedantic)

add_custom_target(
    clang-format
    COMMAND clang-format
    --dry-run
    -Werror
    ${SOURCES}
    ${HEADERS}
)
