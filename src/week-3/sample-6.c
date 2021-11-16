#include <stdio.h>
#include <malloc.h>
#include <omp.h>

// Nhap cac kich thuoc cua ma tran
#define  m      9 
#define  n       6
#define  p      6 
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
        *(A+i*n+j) = 1;
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
int Nr_of_Threads=3;
int id,m_thread,p_thread,start_i,start_k,stop_i,stop_k;
    #pragma omp parallel private(id,i,j,k,m_thread,start_i,start_k,stop_i,stop_k)     // [NOTE]: OpenMP only parallelize partially
    { // [NOTE]: must enter to new line. 

        id=omp_get_thread_num();
        // Chuyen tu mot chieu thanh 2 chieu.
        int id_row, id_colum,Nr_of_Thread_colum=3, Nr_of_Thread_row=Nr_of_Threads/Nr_of_Thread_colum;
        id_row=id/Nr_of_Thread_colum; id_colum=id%Nr_of_Thread_colum;



// Xac dinh doman cho moi thread.
m_thread=m/Nr_of_Thread_row;
p_thread=p/Nr_of_Thread_colum;

start_i = m_thread*id_row;
start_k=p_thread*id_colum;





 stop_i=m_thread*(id_row+1);
 stop_k=p_thread*(id_colum+1);


  // Nhan Ma Tran: A x B = C
    for ( i = start_i; i < stop_i; i++ )
      for ( k = start_k; k < stop_k ; k++ ){
        *(C +  i*p + k) = 0;
        for ( j = 0 ; j < n ; j++ )
          *(C +  i*p + k) = *(C +  i*p + k) 
                      + (*(A + i*n + j)) * (*(B + j*p + k));
      }

    }

        
//==================================  
  printf( "Ma tran C:\n");
  DisplayMatrix(C, m, p);
//==================================
 return 0;
}

// 3 cách chia miền: 
// - 1 luồng tính dải cột liên tục.
// - 2 luồng tính dải hàng liên tục.
// - 3 tính rời rạc (cột, hàng).
// - 4 chia ban co

