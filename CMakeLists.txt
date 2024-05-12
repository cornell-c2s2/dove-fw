#========================================================================
# CMakeLists.txt
#========================================================================
# A CMake Project for building firmware using RISCV

#------------------------------------------------------------------------
# Set the files for the project
#------------------------------------------------------------------------

set(SRC_FILES
  utils/arith.c
  utils/bitops.c
  utils/mem_array.c
  filter/src.c
  utils/SPI_Lib_C2S2.c
  utils/gpio.c
)
set(TEST_FILES
  tests/test_arith.c
  tests/test_bitops.c
  tests/test_filter.c
)
set(APP_FILES
  riscv-apps/blink.c
  riscv-apps/iterate.c
  riscv-apps/mem-test.c
  riscv-apps/filter-blink.c
)

set(INCLUDE_DIRS
  utils
  filter
  board-utils
)

#------------------------------------------------------------------------
# Use the RISCV Compiler
#------------------------------------------------------------------------
# Used from riscv64.cmake (from Derin Ozturk)
#
# We have to set these before any calls to project() or enable_language()

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

STRING(REGEX REPLACE "-gcc" "-" CROSS_COMPILE ${RISCV_TOOLCHAIN_BIN_GCC})
message("RISC-V Cross Compile: ${CROSS_COMPILE}")

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR riscv64)

set(CMAKE_C_COMPILER ${RISCV_GCC_COMPILER})
set(CMAKE_CXX_COMPILER ${RISCV_TOOLCHAIN_BIN_PATH}/${CROSS_COMPILE}g++)
set(CMAKE_ASM_COMPILER ${RISCV_GCC_COMPILER})
set(CMAKE_OBJCOPY ${RISCV_TOOLCHAIN_BIN_PATH}/${CROSS_COMPILE}objcopy CACHE FILEPATH "The toolchain objcopy command " FORCE)
set(CMAKE_OBJDUMP ${RISCV_TOOLCHAIN_BIN_PATH}/${CROSS_COMPILE}objdump CACHE FILEPATH "The toolchain objdump command " FORCE)

#------------------------------------------------------------------------
# Boilerplate CMake for the project
#------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.10)
project(DOVE_FW VERSION 1.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

enable_testing()


#------------------------------------------------------------------------
# Enable both Assembly and C compilation
#------------------------------------------------------------------------

enable_language(C ASM)

#------------------------------------------------------------------------
# Define whether we're using the RISCV Board
#------------------------------------------------------------------------

option(RISCV_BOARD OFF)

if(RISCV_BOARD) 
  add_compile_definitions(RISCV_BOARD="1")
endif()

#------------------------------------------------------------------------
# Define which pk to use based on processor
#------------------------------------------------------------------------

if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "arm64")
    set(PK_EXECUTABLE "pk")
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64")
    set(PK_EXECUTABLE "pk64")
else()
    #message(FATAL_ERROR "Unsupported architecture")
    set(PK_EXECUTABLE "pk64")
endif()

#------------------------------------------------------------------------
# Define flags and other sources based on how we're running the code
#------------------------------------------------------------------------

if(RISCV_BOARD)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall -mabi=ilp32 -march=rv32i_zicsr -D__vexriscv__ -Wl,-Bstatic,-T,${CMAKE_CURRENT_SOURCE_DIR}/board-utils/sections.lds,--strip-debug -ffreestanding -nostdlib")
  set(SRC_FILES ${SRC_FILES} board-utils/crt0_vex.S board-utils/isr.c )
else()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall -static" CACHE STRING "Spike needs static..." FORCE)
endif()

SET(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -x assembler-with-cpp")

#------------------------------------------------------------------------
# remove_extension
#------------------------------------------------------------------------
# A function to remove a file's extension

function(remove_extension VARNAME FILE_NAME)
  string(REGEX REPLACE "\\.[^.]*$" "" NAME_WITHOUT_EXT ${FILE_NAME})
  set(${VARNAME} "${NAME_WITHOUT_EXT}" PARENT_SCOPE)
endfunction()

#-------------------------------------------------------------------------
# get_leaf
#-------------------------------------------------------------------------
# Gets the leaf file of a path.

function(get_leaf VARNAME FILE_NAME)
  string(REGEX REPLACE "[^/]*/" "" NAME_WITHOUT_EXT ${FILE_NAME})
  set(${VARNAME} "${NAME_WITHOUT_EXT}" PARENT_SCOPE)
endfunction()

#------------------------------------------------------------------------
# Include all directories in INCLUDE_DIRS
#------------------------------------------------------------------------

foreach(INCLUDE_DIR ${INCLUDE_DIRS})
  include_directories("${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR}")
endforeach(INCLUDE_DIR)

#------------------------------------------------------------------------
# Create a library with our source files
#------------------------------------------------------------------------

foreach(SRC_FILE ${SRC_FILES})
  set(LIB_SRCS ${LIB_SRCS} "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_FILE}")
endforeach(SRC_FILE)
add_library(SRC_LIBRARY STATIC ${LIB_SRCS})

#------------------------------------------------------------------------
# Add a run target for each application, to run the application
#------------------------------------------------------------------------

foreach(APP_RPATH ${APP_FILES})
  get_leaf(APP_FILE ${APP_RPATH})
  remove_extension(APP_BIN ${APP_FILE})
  set(APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${APP_RPATH}")

  add_custom_target(run-${APP_BIN})

  add_executable(${APP_BIN} EXCLUDE_FROM_ALL ${APP_PATH})
  target_link_libraries(${APP_BIN} m SRC_LIBRARY)
  add_dependencies(run-${APP_BIN} ${APP_BIN})

  if(RISCV_BOARD)
    set(APP_HEX "${CMAKE_CURRENT_BINARY_DIR}/${APP_BIN}.hex")
    add_custom_command(
      TARGET run-${APP_BIN} POST_BUILD
      COMMAND ${CMAKE_OBJCOPY} -O verilog ${APP_BIN} ${APP_HEX}
      COMMAND sed -i='' 's/@1000/@0000/g' ${APP_HEX}
      COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/board-utils/caravel_hkflash.py ${APP_HEX}
    ) 
  else()
    add_custom_command(
      TARGET run-${APP_BIN} POST_BUILD
      COMMAND spike ${PK_EXECUTABLE} ${APP_BIN}
    )
  endif()
endforeach(APP_RPATH)

#------------------------------------------------------------------------
# Test files when using spike
#------------------------------------------------------------------------

if(NOT RISCV_BOARD)
  #Adds custom target named check (runs tests)
  add_custom_target(check COMMAND ctest "--timeout" "10")

  #Runs through each test file and creates an executable (of file name without extension) while also testing with ctest
  foreach(TEST_RPATH ${TEST_FILES})
    get_leaf(TEST_FILE ${TEST_RPATH})
    remove_extension(TEST_BIN ${TEST_FILE})
    set(TEST_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${TEST_RPATH}")
    add_executable(${TEST_BIN} EXCLUDE_FROM_ALL ${TEST_PATH})
    target_link_libraries(${TEST_BIN} m SRC_LIBRARY) 
    add_dependencies(check ${TEST_BIN})
    add_test(NAME ${TEST_BIN} COMMAND spike ${PK_EXECUTABLE} ${TEST_BIN})
  endforeach(TEST_RPATH)
endif()
