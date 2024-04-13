# Dove Firmware

A match filter implementation for the C2S2's Dove RISC-V processor (`RV32I_ZICSR`)

# Running the tests

Currently, we're using a temporary build system, before implementing the real version in CMake. You can still compile the existing test files with the following commands:

```bash
make test_bitops
make test_arith

# Alternatively

make all
```

You can then run the tests (build in a `build` directory) as normal executables

```bash
build/test_bitops
build/test_arith
```
