// main_bench.c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <errno.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

extern void add_int(int *pa, int *pb, unsigned int n, int x);

/* Return nanoseconds since an arbitrary epoch */
static inline uint64_t now_ns(void) {
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC_RAW, &ts) < 0) {
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }
    return (uint64_t)ts.tv_sec * 1000000000ULL + ts.tv_nsec;
}

int main(int argc, char *argv[]) {
    const unsigned int n     = (argc > 1 ? atoi(argv[1]) : 1<<20);
    const int          x     = (argc > 2 ? atoi(argv[2]) : 5);
    const int    iterations  = (argc > 3 ? atoi(argv[3]) : 1000);
    int *pa = aligned_alloc(64, n * sizeof *pa);
    int *pb = aligned_alloc(64, n * sizeof *pb);
    if (!pa || !pb) {
        perror("aligned_alloc");
        return EXIT_FAILURE;
    }

    /* Initialize source data */
    for (unsigned int i = 0; i < n; i++)
        pb[i] = (int)(i * 31 + 7);

    /* Warm-up phase */
    for (int w = 0; w < 10; w++)
        add_int(pa, pb, n, x);

    /* Timed runs */
    uint64_t t0 = now_ns();
    for (int iter = 0; iter < iterations; iter++)
        add_int(pa, pb, n, x);
    uint64_t t1 = now_ns();

    double avg_ns = (double)(t1 - t0) / iterations;
    printf("N = %u, iterations = %d\n", n, iterations);
    printf("Average time: %.2f ns/call\n", avg_ns);

    free(pa);
    free(pb);
    return EXIT_SUCCESS;
}
