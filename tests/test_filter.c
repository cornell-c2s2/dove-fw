#include <assert.h>
#include <src.h>
#include <mem_array.h>
#include <stdio.h>
#include <stdlib.h>
void no_match () {
    int *ptr = malloc(100000);
    int num_samples = 500;
    int kernel_length = 250;

    get_samples(ptr, num_samples,kernel_length);
    new_matched_filter(ptr,num_samples,kernel_length);

    int threshold = 1700;
    int start = num_samples + kernel_length;
    for (int i; i< start; i++){
        assert (ptr[start +i] < threshold);
    }
}

void match () {
    #include <bird_2.h>
    #include <bird_1.h>
    int *ptr = malloc(100000);
    int num_samples = 500;
    int kernel_length = 250;

    get_samples(ptr, num_samples,kernel_length);
    for (int i = 0; i < kernel_length; i++)
    {
        ptr[num_samples + i] = samples[100000 + i];
    }

    new_matched_filter(ptr,num_samples,kernel_length);

    int threshold = 1600;
    int start = num_samples + kernel_length;
    int pass_threshold = 0;
    for (int i; i< start; i++){
        if (ptr[start +i] > threshold){
        pass_threshold = 1;
        }
    }
    assert(pass_threshold);
}

int main (void) {
    no_match();
    match();
    printf( "All tests passed!\n" );
    return 0;
}