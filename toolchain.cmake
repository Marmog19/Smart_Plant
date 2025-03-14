# Target definition
set (CMAKE_SYSTEM_PROCESSOR "arm")
set (CMAKE_SYSTEM_NAME "Generic")

# tell CMake not to try to link executables during its checks
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)


set(TOOLCHAIN          "arm-none-eabi-")


set(CMAKE_C_COMPILER   "${TOOLCHAIN}gcc")
set(CMAKE_ASM_COMPILER "${TOOLCHAIN}gcc")


set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
