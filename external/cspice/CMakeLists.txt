file(GLOB CSPICE_SRC CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cspice/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/csupport/*.c)

add_library(cspice STATIC ${CSPICE_SRC})
target_include_directories(cspice
        PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/cspice)

target_compile_definitions(cspice PRIVATE
        _COMPLEX_DEFINED MSDOS OMIT_BLANK_CC NON_ANSI_STDIO)
target_compile_options(cspice PRIVATE -w -fno-strict-aliasing)

# CSpice is old-style C; keep it out of your project's C23 setting
set_target_properties(cspice PROPERTIES C_STANDARD 90 C_EXTENSIONS ON)