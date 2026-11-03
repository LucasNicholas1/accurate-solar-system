cmake_minimum_required(VERSION 4.3)
project(accurate_solar_system C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.5.1
        GIT_SHALLOW ON
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
        cglm
        GIT_REPOSITORY https://github.com/recp/cglm.git
        GIT_TAG v0.9.6
        GIT_SHALLOW ON
)
FetchContent_MakeAvailable(cglm)

add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

add_executable(accurate_solar_system
        src/main.c
        src/program.h
        src/program.c
)

target_link_libraries(accurate_solar_system PRIVATE glfw glad cglm)

target_compile_definitions(accurate_solar_system PRIVATE
        ASSETS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets"
        GLFW_INCLUDE_NONE
)

target_compile_options(accurate_solar_system PRIVATE
        $<$<C_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall>
        $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wextra>
)