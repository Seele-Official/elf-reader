cmake_minimum_required(VERSION 3.15)


project(elf-reader LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -Wall -Wextra -g")

add_definitions(-DMY_LITTLE_ENDIAN=0)
add_definitions(-DMY_BIG_ENDIAN=1)
add_definitions(-DMY_BYTE_ORDER=MY_LITTLE_ENDIAN)


set(CMAKE_BUILD_TYPE "Debug")



set(SOURCES
    "main.cpp"
)


add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ./lib)

