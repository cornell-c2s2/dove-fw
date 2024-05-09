# Dove Firmware

A match filter implementation for the C2S2's Dove RISC-V processor (`RV32I_ZICSR`)

# Running apps and tests

```bash

mkdir build
cd build

# To compile for spike
cmake ..

# To compile for the eFabless RISCV board
cmake .. -DRISCV_BOARD=ON

# To run the tests (only on Spike)
make check

# To run a program <prog> (on spike or the board)
make run-<prog>
```
