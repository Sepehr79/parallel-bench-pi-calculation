#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int done = 0, n = atoi(*(argv + 1)), myid, i;
    double PI25DT = 3.141592653589793238462643;
    double mypi, h, sum, x, a;
    clock_t startTime, endTime;
        
    if (n == 0) return 0;
    startTime = clock();
    h = 1.0 / (double) n; // width of the rectangles
    sum = 0.0;
    for (i = 1; i <= n; i += 1) { // pointer to my rectangles
        x = h * (((double)i) - 0.5); // to calculate length of each rectangle
        sum += 4.0 * sqrt (1.0 - x*x); // sum of lengths of rectangles (4 times)
    }

    mypi = h * sum; // sum of the areas of the rectangles for each process
    endTime = clock();
    unsigned long time = (unsigned long) endTime - (unsigned long) startTime;
    printf("%.16f, %.16f, %4ld\n",
    mypi, fabs(mypi - PI25DT), time);

    return 0;
}