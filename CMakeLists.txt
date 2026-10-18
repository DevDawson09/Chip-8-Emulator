cmake_minimum_required(VERSION 4.3)
project(Chip_8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDL2_ROOT "C:/Users/kaicd/SDL3/SDL2-2.32.8")

add_executable(Chip_8 WIN32
        src/Chip-8.cpp
        src/Chip-8.h
        src/Helper.cpp
        src/Helper.h
        src/main.cpp
        src/setupFunctions.cpp
        src/setupFunctions.h
        src/Display.h
)

target_include_directories(Chip_8 PRIVATE
        "${SDL2_ROOT}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_directories(Chip_8 PRIVATE
        "${SDL2_ROOT}/lib/x64"
)

target_link_libraries(Chip_8 PRIVATE
        SDL2main
        SDL2
)

add_custom_command(TARGET Chip_8 POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
        "${SDL2_ROOT}/lib/x64/SDL2.dll"
        "$<TARGET_FILE_DIR:Chip_8>"
        VERBATIM
)