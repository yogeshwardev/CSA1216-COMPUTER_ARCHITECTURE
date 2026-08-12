#include <stdio.h>

int ripple_add(int A, int B, int n, int *stages) {
    int carry = 0, result = 0;
    *stages = 0;

    for (int i = 0; i < n; i++) {
        int a = (A >> i) & 1;
        int b = (B >> i) & 1;
        int sum = a ^ b ^ carry;

        carry = (a & b) | ((a ^ b) & carry);
        result |= sum << i;
        (*stages)++;
    }
    return result | (carry << n);
}

int cla_add(int A, int B, int n) {
    int P[8], G[8], C[9] = {0};

    for (int i = 0; i < n; i++) {
        int a = (A >> i) & 1;
        int b = (B >> i) & 1;
        P[i] = a ^ b;
        G[i] = a & b;
    }

    /* Carry equations. */
    C[0] = 0;
    for (int i = 0; i < n; i++)
        C[i + 1] = G[i] | (P[i] & C[i]);

    int result = 0;
    for (int i = 0; i < n; i++)
        result |= (P[i] ^ C[i]) << i;

    return result | (C[n] << n);
}

int main(void) {
    int A = 15, B = 1, n = 4, stages;
    int rca = ripple_add(A, B, n, &stages);
    int cla = cla_add(A, B, n);

    printf("A = %d, B = %d\n", A, B);
    printf("Ripple Carry result = %d\n", rca);
    printf("RCA carry stages = %d\n", stages);
    printf("Carry Look-Ahead result = %d\n", cla);
    printf("DEBUG: RCA waits for carry propagation; CLA calculates carries earlier.\n");

    return 0;
}
