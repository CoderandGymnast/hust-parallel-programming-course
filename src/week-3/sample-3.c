#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>


int main() {
    int *A, sum
    #pragma omp parallel shared(count)
    {
    }
    printf("Sum: %d\n",stats[0]+stats[1]);
}