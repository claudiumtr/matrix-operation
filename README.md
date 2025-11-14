# matrix-operation
In this project I've experienced different ways to calculate a matrix operation.


NEOPT

I calculated the transposes of the matrices A and B, and then I implemented the simplest matrix multiplication to which I added the upper triangular condition for A * B and lower triangular for A' * A.

For the rest, I added the matrices obtained from A * B * B' and from A' * A.

BLAS

The functions I used are cblas_dtrmm and cblas_dgemm.
I used cblas_dtrmm for A * B and for A' * A because
it is used for upper triangular matrices, and
cblas_dgemm is used for multiplying arbitrary matrices.
First, I stored the data from B in the matrix AB, then after the first call
of cblas_dtrmm in AB there is A * B. Then after the call of cblas_dgemm in the matrix
ABB there is A * B * B'. Then in AA I stored the data from A and after the second call of cblas_dtrmm in matrix AA there is A' * A. Then I added matrices ABB and AA to obtain the final result that I return.

OPT

I started from the optimizations in the laboratory and adjusted the method of multiplying 2D matrices to those stored in vector form. Thus, the optimizations used
are:
- retaining constants so that they are not calculated multiple times
- using the stdint library for uint_fast32_t instead of int
- loop unrolling (learned at IOCLA)
- accessing memory (taken and adjusted from the laboratory)
- using registers for faster access to variables

MEMORY CHECK

I ran the command with valgrind on each implementation variant, redirecting the outputs of the valgrind run in the files blas.memory, neopt.memory and
opt_m.memory and there are no errors or memory leaks.

CACHEGRIND

From the .cache files I notice that the most efficient is blas, and the most inefficient in terms of memory is neopt. In blas I have the fewest misses and refs, while in neopt I have the most misses and refs. The optimized variant is the middle one, which is not as optimized as blas in terms of memory, but not as unoptimized as neopt.

RESULTS ANALYSIS

I modified the input file and added 2 more values ​​for N, namely 600 and 1000. Then I loaded 5 runs on the fep queue.
I wrote down the results obtained in the "data" file. I made the arithmetic mean for each N and each solution method, then I used an online graph generator to obtain the graph from the "graf.jpeg" file.
From the results obtained, I can say that even for small numbers the differences are enormously large between the 3 solving methods. Until now, I didn't really give importance to these details, but as can be seen from the graph, they really do matter. As the matrix sizes grow, the differences are increasingly larger. I didn't imagine that these differences could be so large. For example, for N = 1200, the blas variant runs on average in about 0.86 seconds, while the optimized one in 8.52 (on average), and the non-optimized one in about 25 seconds. The speedup between neopt and opt_m is about 3, and between opt_m and blas is about 10. From this analysis, I concluded that using libraries for certain calculations is much more efficient than a normal implementation of your own (even optimized).
