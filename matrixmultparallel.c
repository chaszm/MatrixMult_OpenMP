#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#define N 1024
#define FactorIntToDouble 1.1

double firstMatrix[N][N] = {0.0};
double secondMatrix[N][N] = {0.0};
double matrixMultiResult[N][N] = {0.0};



void matrixMulti() {
 
 	#pragma omp parallel for collapse(2)
 	
    for ( int row=0 ; row < N; row++) {
        for (int col=0 ; col < N; col++) {
            double resultValue = 0;
            
            for (int transNumber = 0; transNumber < N; transNumber++) {
                resultValue += firstMatrix[row][transNumber] * secondMatrix[transNumber][col];
              
            }
            
            matrixMultiResult[row][col] = resultValue;
        }
    }
    //end of parallel
}



void matrixInit() {
	#pragma omp parallel for collapse(2)
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            firstMatrix[row][col] = (row + col) * FactorIntToDouble;
            secondMatrix[row][col] = (row + col) * FactorIntToDouble;
        }
    }
    }
int main()
{
matrixInit();

double t1 = omp_get_wtime();
matrixMulti();
double t2 = omp_get_wtime();
printf("parallel time: %3f\n", ((double)t2 - t1) / CLOCKS_PER_SEC *
1000000.0);
return 0;
}











