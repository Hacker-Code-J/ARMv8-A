// add_int.c
void add_int(int *pa, int *pb, unsigned int n, int x) {
    unsigned int i;
    for (i = 0; i < n; i++) {
        pa[i] = pb[i] + x;
    }
}
