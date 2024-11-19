#!/bin/bash

SEQ_BENCH="pcalcseq"
MPI_BENCH="pcalcmpi"

gcc $SEQ_BENCH.c -o $SEQ_BENCH -lm
mpicc $MPI_BENCH.c -o $MPI_BENCH -lm

n=$1

SEQ_OUT=$(./$SEQ_BENCH $n)
MPI_OUT=$(mpirun -np $(nproc) ./$MPI_BENCH $n)

echo "Seq execution: $SEQ_OUT"
echo "MPI execution: $MPI_OUT"