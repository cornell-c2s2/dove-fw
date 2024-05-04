if(RISCV_TOOLCHAIN_INCLUDED)
  return()
endif(RISCV_TOOLCHAIN_INCLUDED)
set(RISCV_TOOLCHAIN_INCLUDED true)

FIND_FILE(RISCV_GCC_COMPILER "riscv64-unknown-elf-gcc" PATHS ENV INCLUDE)
if (EXISTS ${RISCV_GCC_COMPILER})
  message("Found RISC-V GCC Toolchain: ${RISCV_GCC_COMPILER}")
else()
  message(FATAL_ERROR "RISC-V GCC Toolchain not found!")
endif()

get_filename_component(RISCV_TOOLCHAIN_BIN_PATH ${RISCV_GCC_COMPILER} DIRECTORY)
get_filename_component(RISCV_TOOLCHAIN_BIN_GCC ${RISCV_GCC_COMPILER} NAME_WE)
get_filename_component(RISCV_TOOLCHAIN_BIN_EXT ${RISCV_GCC_COMPILER} EXT)

message("Toolchain path, prefix, and ext: ${RISCV_TOOLCHAIN_BIN_PATH}, ${RISCV_TOOLCHAIN_BIN_GCC}, ${RISCV_TOOLCHAIN_BIN_EXT}")

STRING(REGEX REPLACE "\-gcc" "-" CROSS_COMPILE ${RISCV_TOOLCHAIN_BIN_GCC})
message("RISC-V Cross Compile: ${CROSS_COMPILE}")

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR riscv64)

set(CMAKE_C_COMPILER ${RISCV_GCC_COMPILER})
set(CMAKE_OBJCOPY ${RISCV_TOOLCHAIN_BIN_PATH}/${CROSS_COMPILE}objcopy CACHE FILEPATH "The toolchain objcopy command " FORCE)
set(CMAKE_OBJDUMP ${RISCV_TOOLCHAIN_BIN_PATH}/${CROSS_COMPILE}objdump CACHE FILEPATH "The toolchain objdump command " FORCE)

# Very important to include -static flag in order to run on Spike. It needs a
# static binary.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static" CACHE STRING "Spike needs static..." FORCE)
