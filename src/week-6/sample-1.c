#include <stdio.h>
#include <mpi.h>
#include <malloc.h>

int main(int argc, char *argv[]){ // Can use "char **argv",
    MPI_Init(&argc,&argv); // Start MPI.
MPI_Status status;
int num_process, ID_process;
MPI_Comm_size(MPI_COMM_WORLD,&num_process);
MPI_Comm_rank(MPI_COMM_WORLD,&ID_process);

if(ID_process==0) {
    int count=5;
    int *A=(int*) malloc(count*sizeof(int));
    for(int i =0;i<count;i++) *(A+i)=i+1;
    MPI_Send(A,count, MPI_INT,1,3112021,MPI_COMM_WORLD);
} else {
int count=5;
int *B,*C;
    B=(int*) malloc(count*sizeof(int));

    C=(int*) malloc(count*sizeof(int));
    MPI_Recv(B,count, MPI_INT,0,3112021,MPI_COMM_WORLD,&status);
    for(int i=0;i<count;i++) *(C+i)=2* *(B+i);
    for(int i =0;i<count;i++) printf("%d \t",*(C+i));
}


// p0 init A={1,2,3,4,5}; send to p1

// p1 recev, save to B. c = 2*b. print c.

    MPI_Finalize();
 
return 0;
}

