# Dove Firmware

A match filter implementation for the C2S2's Dove RISC-V processor (`RV32I_ZICSR`)

# Running the tests

```bash
make test_bitops
make test_arith

# Alternatively

make check
```

You can then run the tests (build in a `build` directory) as normal executables

```bash
./test_bitops
./test_arith
```
