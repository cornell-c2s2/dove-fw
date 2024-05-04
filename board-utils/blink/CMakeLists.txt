cmake_minimum_required(VERSION 3.10)

project(Blink VERSION 1.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

add_compile_definitions(PROJ_ROOT=\"${PROJECT_SOURCE_DIR}\")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -O3 -std=c11")

message("CMake detected system processor: ${CMAKE_SYSTEM_PROCESSOR}")
if (CMAKE_SYSTEM_PROCESSOR STREQUAL riscv64)
  message("Cross-compiling with RISCV-GNU GCC Toolchain!")
  message("Cmake flags for riscv64: ${CMAKE_C_FLAGS}")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_custom_target(flash)
add_custom_command(
    TARGET flash POST_BUILD
    COMMAND riscv64-unknown-elf-gcc -I../../ -I../../generated/ -O0 -mabi=ilp32 -march=rv32i_zicsr -D__vexriscv__ -Wl,-Bstatic,-T,../../sections.lds,--strip-debug -ffreestanding -nostdlib -o ../blink.elf ../../crt0_vex.S ../../isr.c ../blink.c 
    COMMAND riscv64-unknown-elf-objcopy -O verilog ../blink.elf ../blink.hex
    COMMAND sed -i='' 's/@1000/@0000/g' ../blink.hex  
    COMMAND ${PROJECT_SOURCE_DIR}/util/caravel_hkflash.py ${PROJECT_SOURCE_DIR}/blink.hex
)  

add_custom_target(cleaner)
add_custom_command(
    TARGET cleaner POST_BUILD
    COMMAND rm -f ../*.elf ../*.hex
)  