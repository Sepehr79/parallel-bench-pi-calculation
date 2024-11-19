#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int done = 0, n = atoi(argv[1]), myid, numprocs, i, rc;
    double PI25DT = 3.141592653589793238462643;
    double mypi, pi, h, sum, x, a;
    clock_t startTime, endTime;
    

    MPI_Init (&argc,&argv);
    MPI_Comm_size (MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank (MPI_COMM_WORLD,&myid);

    if (myid == 0) {
        startTime = clock();
    }
    MPI_Bcast (&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (n == 0) return 0;
    h = 1.0 / (double) n; // width of the rectangles
    sum = 0.0;
    for (i = myid + 1; i <= n; i += numprocs) { // pointer to my rectangles
        x = h * (((double)i) - 0.5); // to calculate length of each rectangle
        sum += 4.0 * sqrt (1.0 - x*x); // sum of lengths of rectangles (4 times)
    }
    mypi = h * sum; // sum of the areas of the rectangles for each process
    MPI_Reduce (&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (myid == 0) {
        endTime = clock();
        unsigned long time = (unsigned long) endTime - (unsigned long) startTime;
        printf("%.16f, %.16f, %4ld\n", pi, fabs(pi - PI25DT), time);
    }
    
    MPI_Finalize();
    return 0;
}