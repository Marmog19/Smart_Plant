cmake_minimum_required(VERSION 3.20)
project(firmware LANGUAGES C)
enable_language(ASM)

set (MCPU               "-mcpu=cortex-m4")
set (MFPU               "-mfpu=fpv4-sp-d16")
set (LINKER_SCRIPT      "../STM32F446RETX_FLASH.ld")

set (PROJECT_SOURCES
	# LIST SOURCE FILES HERE
	Startup/startup_stm32f446retx.s
    Source/I2C_lib.c
	Source/main.c
	Source/syscalls.c
	Source/sysmem.c
    Source/system_stm32f4xx.c
    Source/SysTickDelay.c
	)


set (PROJECT_INCLUDES
	# LIST INCLUDE DIRECTORIES HERE
    Inc
    Drivers/CMSIS/Include
    Drivers/CMSIS/Device/ST/STM32F4xx/Include
    )

#add_library()
add_executable(firmware ${PROJECT_SOURCES})
#target_link_libraries()

set (CMAKE_EXECUTABLE_SUFFIX ".elf")
set (CMAKE_STATIC_LIBRARY_SUFFIX ".a")

add_compile_definitions(STM32F446xx)
include_directories (${PROJECT_INCLUDES})

# -mthumb               Generate thumb instructions.
# -Wall                 Print standard warnings
set (CMAKE_C_FLAGS "${MCPU} -std=gnu11 ${MFPU} -mthumb -Wall -mfloat-abi=hard")


# -Wl,--gc-sections     Perform the dead code elimination.
# --specs=nano.specs    Link with newlib-nano.
# --specs=nosys.specs   No syscalls
set (CMAKE_EXE_LINKER_FLAGS "-T${LINKER_SCRIPT} -nostdlib -nodefaultlibs --specs=nano.specs --specs=nosys.specs -lc -lgcc -Wl,--gc-sections -Wl,-Map=${CMAKE_PROJECT_NAME}.map")

set (CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -x assembler-with-cpp")
