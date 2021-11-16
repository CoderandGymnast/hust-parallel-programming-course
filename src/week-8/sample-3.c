// Bai Toan Nhan 2 Ma tran: A[m][n] x B[n][p] = C[m][p]
#include <stdio.h>
#include <malloc.h>

#include <mpi.h>

// Nhap cac kich thuoc cua ma tran
#define  m       6
#define  n       6
#define  p       8
//==================================
void DisplayMatrix(int *A, int row,  int col){
  int i,j;
  for(i=0;i<row;i++){
    for(j=0;j<col;j++) printf("%d\t",*(A+i*col+j));
    printf("\n");
  }
}
//==================================
int main(int argc, char *argv[])
{

  	MPI_Init(&argc,&argv);
	int cpu,Ncpu, IDcpu;
	MPI_Comm_size(MPI_COMM_WORLD,&Ncpu);
	MPI_Comm_rank(MPI_COMM_WORLD,&IDcpu);
  int i, j, k;
//==================================
// Khai bao ma tran A, B, C
  int *A, *B, *C;
  A = (int *) malloc ((m*n)*sizeof(int));
  B = (int *) malloc ((n*p)*sizeof(int));
  C = (int *) malloc ((m*p)*sizeof(int));

int ms=m/Ncpu;

int *As,*Bs,*Cs;
As = (int *) malloc (ms*n*sizeof(int));
	Bs = (int *) malloc (ms*p*sizeof(int));
	Cs = (int *) malloc (ms*p*sizeof(int));
//==================================
// Khoi Tao Du Lieu (Ma tran A, B)
  //Ma tran A la ma tran Don vi
   for (  i = 0 ; i < m ; i++ )
    for ( j = 0 ; j < n ; j++ ){
      if (i==j) 
        *(A+i*n+j) = 1.;
      else
        *(A+i*n+j) = 0;
    }
  //  printf("The matrix A:\n");
  //  DisplayMatrix(A, m, n);
  //Ma tran B
   for (  i = 0 ; i < n ; i++ )
    for ( j = 0 ; j < p ; j++ ){
      *(B+i*p+j) = 1*(i*p+j);
    }
    if(!IDcpu)   {
      
    printf("The matrix A:\n");
      DisplayMatrix(A, m, n);
printf("\n");
    printf("The matrix B:\n");
    DisplayMatrix(B, n, p);
    }
//==================================
// Domain decomposition: 
MPI_Scatter(A,ms*n,MPI_INT,As,ms*n,MPI_INT,0,MPI_COMM_WORLD); // Similar to steps 2,3.
MPI_Bcast(B,n*p,MPI_INT,0,MPI_COMM_WORLD);


//==================================
  // Nhan Ma Tran: C[m][p] = A[m][n] x B[n][p]
    for ( i = 0 ; i < ms ; i++ )
      for ( k = 0 ; k < p ; k++ ){
        *(Cs +  i*p + k) = 0;
        for ( j = 0 ; j < n ; j++ )
          *(Cs +  i*p + k) = *(Cs +  i*p + k) 
                      + (*(As + i*n + j)) * (*(B + j*p + k));
      }


MPI_Gather(Cs,ms*p,MPI_INT,C,ms*p,MPI_INT,0,MPI_COMM_WORLD); // Similar to steps 2,3.
        
//==================================  

 if(IDcpu==0) {
   printf("C:\n");
  DisplayMatrix(C, m, p);
 }
//==================================
 return 0;
}

