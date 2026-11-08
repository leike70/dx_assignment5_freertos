cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME dx_assignment5_freertos)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME}
        Task/led_task.h
        Task/led_task.c
        Task/led_task.h
        Task/M3508_task.cpp
        Task/M3508_task.h
        Task/rc.c
        Task/Power.cpp
        Task/Power.h)

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
file(GLOB_RECURSE USER_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Bsp/*.*
        ${CMAKE_CURRENT_SOURCE_DIR}/User_Driver/*.*
        ${CMAKE_CURRENT_SOURCE_DIR}/Task/*.*
)
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
        ${USER_SOURCES}
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
        Bsp
        User_Driver
        User_Driver/Motor_Driver
        Task
        User_Driver/Components
        User_Driver/Components/Devices
        User_Driver/Components/Algorithm
        User_Driver/Components/Algorithm/Include
        User_Driver/Components/Controller
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
        ARM_MATH_CM4
)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx
        ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/GCC/libarm_cortexM4lf_math.a

        # Add user defined libraries
)
