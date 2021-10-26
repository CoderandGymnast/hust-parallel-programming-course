#include <omp.h>
#include <stdio.h>

int main() {
    int threadnumber=1;
    int threadID=1;
    printf("I am thread %d, \tthreads %d \n",threadID,threadnumber);
    omp_set_num_threads(20);
    #pragma omp parallel     // [NOTE]: OpenMP only parallelize partially
    { // [NOTE]: must enter to new line. 
        threadnumber=omp_get_num_threads();
        threadID = omp_get_thread_num();
        printf("Hello from thread %d, \t nthreads %d\n",threadID,threadnumber);
    }
    printf("I am thread %d, \tnthreads %d\n",threadID,threadnumber);
}