#ifndef SPI_LIB_C2S2_H
#define SPI_LIB_C2S2_H
char read_spi();
void write_spi(char c);
void array_read_spi(char* ptr, int size);
void run_spi();
#endif // ARITH_H