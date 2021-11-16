#include<stdio.h>
#include<malloc.h>
#include<math.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

#define max(a,b) a>b?a:b


void logArr(int *arr,int n);

int main() {
srand(time(NULL));   // Initialization, should only be called once.
int n=16;
int *arr=(int*) malloc(n*sizeof(int));
int d=0;
int threadCount=n/2;

// Initiate arr:
for (int i=0;i<n;i++) {
    *(arr+i)=rand() % 15;
    printf("%d ",*(arr+i));
}

printf("\n");

while(1) {

    //Update parameters for the current level.
    int step=pow(2,d);
    int range=pow(2,d+1);

    //Stop condition: 
    if(threadCount==1){
        *(arr)=max(*(arr),*(arr+step));
        break;
    }

    // Process for the current level of Binary tree in bottom-up manner.
    int id,idLeft,idRight;
    omp_set_num_threads(threadCount);
    #pragma omp parallel private(id,idLeft,idRight)   // [NOTE]: OpenMP only parallelize partially
    { // [NOTE]: must enter to new line. 
        id= omp_get_thread_num();
        idLeft=id*range;
        idRight=idLeft+step;
        *(arr+idLeft)=max(*(arr+idLeft),*(arr+idRight));
    }


    // Move to the next level of Binary tree.
    d++;
    threadCount/=2;
}

printf("Max value: %d\n", *(arr));

return 0;
}

void logArr(int *arr,int n){
    printf("\n");
    for(int i=0;i<n;i++) {
        printf("%d ", *(arr+i));
    }
    printf("\n");
}

