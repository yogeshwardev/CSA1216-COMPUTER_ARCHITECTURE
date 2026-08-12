#include <stdio.h>

int sign_extend(int x, int n) {
    int mask = (1 << n) - 1;
    x &= mask;
    if (x & (1 << (n - 1)))
        x |= ~mask;
    return x;
}

int booth_multiply(int M, int Q, int n) {
    int A = 0, Qm1 = 0;
    int mask = (1 << n) - 1;

    M = sign_extend(M, n);
    Q &= mask;

    for (int i = 0; i < n; i++) {
        int Q0 = Q & 1;

        /* Booth rules:
           01 -> A = A + M
           10 -> A = A - M
           00/11 -> no operation
        */
        if (Q0 == 1 && Qm1 == 0)
            A = sign_extend(A - M, n);
        else if (Q0 == 0 && Qm1 == 1)
            A = sign_extend(A + M, n);

        /* Arithmetic right shift of A:Q:Q-1 */
        Qm1 = Q0;
        int A_lsb = A & 1;
        Q = (Q >> 1) | (A_lsb << (n - 1));
        Q &= mask;
        A = sign_extend(A >> 1, n);
    }

    return (A << n) | Q;
}

int main(void) {
    int M = -5, Q = 3, n = 4;
    int product = booth_multiply(M, Q, n);

    int mask = (1 << (2 * n)) - 1;
    product &= mask;
    if (product & (1 << (2 * n - 1)))
        product -= (1 << (2 * n));

    printf("Multiplicand = %d\n", M);
    printf("Multiplier   = %d\n", Q);
    printf("Booth result = %d\n", product);
    printf("Expected     = %d\n", M * Q);

    if (product == M * Q)
        printf("DEBUG: PASS - signed multiplication is correct.\n");
    else
        printf("DEBUG: FAIL - check Q0/Q-1, arithmetic shift, or sign extension.\n");

    return 0;
}
