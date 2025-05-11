/* main.c
 *
 * Test driver for the add_int function.
 * Allocates two arrays of length n, initializes the source array
 * with consecutive integers, adds a constant offset x to each element,
 * and prints both the input and the result.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/* Prototype for the external function under test */
void add_int(int *pa, int *pb, unsigned int n, int x);

int main(void) {
    const unsigned int  n = 16;    /* number of elements */
    const int           x = 5;    /* constant offset to add */
    unsigned int        i;
    int                *pb = NULL;
    int                *pa = NULL;

    /* Allocate source and destination arrays */
    pb = malloc(sizeof *pb * n);
    pa = malloc(sizeof *pa * n);
    if (pb == NULL || pa == NULL) {
        perror("malloc");
        free(pb);
        free(pa);
        return EXIT_FAILURE;
    }

    /*
     * Initialize the source array pb[] with a simple sequence, e.g.,
     * pb[i] = i*2 to illustrate nontrivial values.
     */
    for (i = 0; i < n; i++) {
        pb[i] = (int)(i * 2);
    }

    /* Invoke the function under test */
    add_int(pa, pb, n, x);

    /*
     * Verify and display:
     *   pa[i] == pb[i] + x  for all i in [0,n)
     */
    printf("Index | pb[i] (input) | x = %d | pa[i] (output)\n", x);
    printf("------+---------------+-------+---------------\n");
    for (i = 0; i < n; i++) {
        printf("%5u | %13d | %5d | %13d\n",
               i, pb[i], x, pa[i]);
    }

    /* Clean up */
    free(pb);
    free(pa);

    return EXIT_SUCCESS;
}
