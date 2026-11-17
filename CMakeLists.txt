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

file(GLOB SOIL2_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/external/soil2/srcs/*.c"
)

add_library(soil2 STATIC ${SOIL2_SOURCES})

target_include_directories(soil2 PUBLIC
        external/soil2/incs
)

add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

find_package(OpenGL REQUIRED)

target_include_directories(soil2 PRIVATE
        external/glad/include
)
target_link_libraries(soil2 PUBLIC
        glad
        OpenGL::GL
)

add_subdirectory(external/cspice)

add_executable(accurate_solar_system
        src/main.c
        src/tools/program.h
        src/tools/program.c
        src/content/scene.h
        src/content/scene.c
        src/content/planet/planet.h
        src/content/planet/planet.c
        src/content/planet/sphere.c
        src/content/planet/sphere.h
        src/content/camera/camera.c
        src/content/camera/camera.h
        src/tools/texture.c
        src/tools/texture.h
        src/content/planet/planet_meta.c
        src/content/planet/planet_meta.h
        src/content/planet/planets.c
        src/content/planet/planets.h
        src/content/planet/fetcher.c
        src/content/planet/fetcher.h
)

#add_library(stbi STATIC external/stbi/src/stb_image.c)
target_include_directories(accurate_solar_system PRIVATE external/stbi/include)

target_link_libraries(accurate_solar_system PRIVATE
        glfw
#        glad
        cglm
#        stbi
        cspice
        soil2
)

target_compile_definitions(accurate_solar_system PRIVATE
        ASSETS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets/"
        GLFW_INCLUDE_NONE
)

target_compile_options(accurate_solar_system PRIVATE
        $<$<C_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall>
        $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wextra>
)

target_compile_definitions(accurate_solar_system PRIVATE
        KERNEL_DIR="${CMAKE_SOURCE_DIR}/external/cspice/kernels/")