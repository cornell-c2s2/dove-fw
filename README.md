# Dove Firmware

A match filter implementation for the C2S2's Dove RISC-V processor (`RV32I_ZICSR`)

# Running the tests

```bash

mkdir build
cd build

# To use riscv
cmake .. -DCMAKE_TOOLCHAIN_FILE=../riscv64.cmake -DRISCV_BOARD=ON

# To use spike
cmake .. -DCMAKE_TOOLCHAIN_FILE=../riscv64.cmake -DRISCV_BOARD=OFF

# To run the apps
make run

# Only works on spike
make test_bitops
make test_arith

# Alternatively

make check
```

You can then run the tests (build in a `build` directory) as normal executables

```bash
spike pk ./test_bitops
spiek pk ./test_arith
```
