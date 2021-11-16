#include <stdio.h>
#include <mpi.h>
#include <malloc.h>
#define m 20
int main(int argc, char *argv[]){
	MPI_Init(&argc,&argv);
	MPI_Status thongbao;
	int cpu,Ncpu, IDcpu;
	MPI_Comm_size(MPI_COMM_WORLD,&Ncpu);
	MPI_Comm_rank(MPI_COMM_WORLD,&IDcpu);
//Step 0: Khai bao, cap phat A,B,C, As,Bs,Cs
	int i,*A,*B,*C;
	A = (int *) malloc (m*sizeof(int));
	B = (int *) malloc (m*sizeof(int));
	C = (int *) malloc (m*sizeof(int));
// Domain decomposition
	int ms,*As,*Bs,*Cs;
	ms = m/Ncpu;
	As = (int *) malloc (ms*sizeof(int));
	Bs = (int *) malloc (ms*sizeof(int));
	Cs = (int *) malloc (ms*sizeof(int));
// Step 1: Khoi tao mang A, B tai Process 0
	if (IDcpu == 0)
		for (i=0;i<m;i++) {
			*(A+i) = i;
			*(B+i) = 2*i;
		}
// // Step 2: Pro 0 chia mien, gui cac phan den tung Pro tuong ung
// 	if (IDcpu == 0) {
// 		for (i=0;i<ms;i++){
// 			*(As+i) = *(A+i);
// 			*(Bs+i) = *(B+i);
// 		}
// 		for (cpu = 1;cpu<Ncpu;cpu++){
// 			MPI_Send(A+cpu*ms,ms,MPI_INT,cpu,cpu,MPI_COMM_WORLD);
// 			MPI_Send(B+cpu*ms,ms,MPI_INT,cpu,cpu+100,MPI_COMM_WORLD);
// 		}
// 	} else {
// // Step 3:Cac Process nhan mien tinh toan cua minh, ky hieu la As, Bs
// 		MPI_Recv(As,ms,MPI_INT,0,IDcpu,MPI_COMM_WORLD,&thongbao);
// 		MPI_Recv(Bs,ms,MPI_INT,0,IDcpu+100,MPI_COMM_WORLD,&thongbao);
// 	}

MPI_Scatter(A,ms,MPI_INT,As,ms,MPI_INT,0,MPI_COMM_WORLD); // Similar to steps 2,3.
MPI_Scatter(B,ms,MPI_INT,Bs,ms,MPI_INT,0,MPI_COMM_WORLD);
// Step 4: Tat ca cac Process tinh: As + Bs = Cs
	for (i=0;i<ms;i++)	*(Cs+i) = *(As+i) + *(Bs+i);
// // Step 5: Cac Process <>0 gui Cs ve Process 0 
// 	if (IDcpu != 0) {
// 		MPI_Send(Cs,ms,MPI_INT,0,IDcpu+200,MPI_COMM_WORLD);
// 	} else {
// // Step 6: Process 0 nhan cac Cs, tong hop thanh C
// 		for (i=0;i<ms;i++)
// 			*(C+i) = *(Cs+i);
// 		for (cpu = 1;cpu<Ncpu;cpu++)
// 			MPI_Recv(C+cpu*ms,ms,MPI_INT,cpu,cpu+200,MPI_COMM_WORLD,&thongbao);
// 	}
MPI_Gather(Cs,ms,MPI_INT,C,ms,MPI_INT,0,MPI_COMM_WORLD); // Similar to steps 2,3.
// Step 7: Process 0 in ket qua ra man hinh
	if (IDcpu == 0)
		for (i=0;i<m;i++) printf("%d  ",*(C+i)); printf("\n");
//
	MPI_Finalize();
return 0;
}












