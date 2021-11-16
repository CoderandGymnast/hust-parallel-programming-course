// Bai Toan Nhan 2 Ma tran: A[m][n] x B[n][p] = C[m][p]
#include <stdio.h>
#include <malloc.h>
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
  int i, j, k;
//==================================
// Khai bao ma tran A, B, C
  int *A, *B, *C;
  A = (int *) malloc ((m*n)*sizeof(int));
  B = (int *) malloc ((n*p)*sizeof(int));
  C = (int *) malloc ((m*p)*sizeof(int));
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
    printf("The matrix B\n");
    DisplayMatrix(B, n, p);
//==================================
  // Nhan Ma Tran: C[m][p] = A[m][n] x B[n][p]
    for ( i = 0 ; i < m ; i++ )
      for ( k = 0 ; k < p ; k++ ){
        *(C +  i*p + k) = 0;
        for ( j = 0 ; j < n ; j++ )
          *(C +  i*p + k) = *(C +  i*p + k) 
                      + (*(A + i*n + j)) * (*(B + j*p + k));
      }
        
//==================================  
  printf( "Ma tran C:\n");
  DisplayMatrix(C, m, p);
//==================================
 return 0;
}

