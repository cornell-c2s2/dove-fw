cmake_minimum_required(VERSION 3.10)

project(DOVE_FW VERSION 1.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

set(UTILS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/utils")
set(TESTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")
set(FILTER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/filter")
set(RISCVAPP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/riscv-app")

option(RISCV_BOARD "Use riscv board" OFF)

add_compile_definitions(PROJ_ROOT=\"${PROJECT_SOURCE_DIR}\")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -O3 -std=c11")

message("CMake detected system processor: ${CMAKE_SYSTEM_PROCESSOR}")
if (CMAKE_SYSTEM_PROCESSOR STREQUAL riscv64)
  message("Cross-compiling with RISCV-GNU GCC Toolchain!")
  message("Cmake flags for riscv64: ${CMAKE_C_FLAGS}")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT WIN32)
  string(ASCII 27 Esc)
  set(Reset 		"${Esc}[m")
  set(Bold  		"${Esc}[1m")
  set(Red         	"${Esc}[31m")
  set(Green       	"${Esc}[32m")
  set(Blue        	"${Esc}[34m")
  set(Cyan        	"${Esc}[36m")
  set(Magenta     	"${Esc}[35m")
  set(Yellow      	"${Esc}[33m")
  set(White       	"${Esc}[37m")
  set(BoldRed     	"${Esc}[1;31m")
  set(BoldGreen   	"${Esc}[1;32m")
  set(BoldBlue    	"${Esc}[1;34m")
  set(BoldCyan    	"${Esc}[1;36m")
  set(BoldMagenta 	"${Esc}[1;35m")
  set(BoldYellow  	"${Esc}[1;33m")
  set(BoldWhite   	"${Esc}[1;37m")
endif()

function(remove_extension VARNAME FILE_NAME)
  string(REGEX REPLACE "\\.[^.]*$" "" NAME_WITHOUT_EXT ${FILE_NAME})
  set(${VARNAME} "${NAME_WITHOUT_EXT}" PARENT_SCOPE)
endfunction()

include_directories(${UTILS_DIR})

set(UTIL_FILES
  arith.c
  bitops.c
)
foreach(UTIL_FILE ${UTIL_FILES})
  set(LIB_UTILS ${LIB_UTILS} "${UTILS_DIR}/${UTIL_FILE}")
endforeach(UTIL_FILE)
add_library(UTIL_LIBRARY ${LIB_UTILS})

set(TEST_FILES
   test_arith.c
   test_bitops.c
 )
add_custom_target(check)
foreach(TEST_FILE ${TEST_FILES})

  remove_extension(TEST_BIN ${TEST_FILE})
  set(TEST_SRC "${TESTS_DIR}/${TEST_FILE}")

  add_executable(${TEST_BIN} EXCLUDE_FROM_ALL ${TEST_SRC})
  target_link_libraries(${TEST_BIN} m UTIL_LIBRARY) 
  add_dependencies(check ${TEST_BIN})

endforeach(TEST_FILE)

add_custom_command(TARGET check POST_BUILD
                   COMMAND echo ""
                   COMMAND echo "${Green}########################################${Reset}"
                   COMMAND echo "${Green}## All tests built in build directory${Reset}"
                   COMMAND echo "${Green}########################################${Reset}"
                   COMMAND echo ""
                  )

add_custom_target(run)
if(RISCV_BOARD) 
add_custom_command(
    TARGET run POST_BUILD
    COMMAND riscv64-unknown-elf-gcc -I${RISCVAPP_DIR}/ -I${RISCVAPP_DIR}/generated/ -O0 -mabi=ilp32 -march=rv32i_zicsr -D__vexriscv__ -Wl,-Bstatic,-T,${RISCVAPP_DIR}/sections.lds,--strip-debug -ffreestanding -nostdlib -o ${RISCVAPP_DIR}/blink/blink.elf ${RISCVAPP_DIR}/crt0_vex.S ${RISCVAPP_DIR}/isr.c ${RISCVAPP_DIR}/blink/blink.c 
    COMMAND riscv64-unknown-elf-objcopy -O verilog ${RISCVAPP_DIR}/blink/blink.elf ${RISCVAPP_DIR}/blink/blink.hex
    COMMAND sed -i='' 's/@1000/@0000/g' ${RISCVAPP_DIR}/blink/blink.hex  
    COMMAND ${RISCVAPP_DIR}/blink/util/caravel_hkflash.py ${RISCVAPP_DIR}/blink/blink.hex
)  
else() 
add_custom_command(
    TARGET run POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "SPIKE"
)  
endif()

add_custom_target(BUILD_SUCCESSFUL ALL
                   DEPENDS ${ALL_TARGETS}
                   COMMAND ${CMAKE_COMMAND} -E echo ""
                   COMMAND ${CMAKE_COMMAND} -E echo "${Magenta}########################################${Reset}"
                   COMMAND ${CMAKE_COMMAND} -E echo "${Magenta}## C2S2 Build System${Reset}"
                   COMMAND ${CMAKE_COMMAND} -E echo "${Magenta}########################################${Reset}"
                   COMMAND ${CMAKE_COMMAND} -E echo ""
                  )

                  
