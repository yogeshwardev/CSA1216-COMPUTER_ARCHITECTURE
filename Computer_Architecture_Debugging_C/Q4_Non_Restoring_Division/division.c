#include <stdio.h>

void non_restoring_division(int dividend, int divisor, int n,
                            int *quotient, int *remainder) {
    int A = 0, Q = dividend;
    int mask = (1 << n) - 1;

    for (int i = 0; i < n; i++) {
        A = (A << 1) | ((Q >> (n - 1)) & 1);
        Q = (Q << 1) & mask;

        /* Do not restore a negative remainder immediately. */
        if (A >= 0) {
            A = A - divisor;
            Q |= 1;
        } else {
            A = A + divisor;
            Q &= ~1;
        }
    }

    if (A < 0)
        A += divisor;   /* Only final correction if necessary. */

    *quotient = Q;
    *remainder = A;
}

int main(void) {
    int dividend = 13, divisor = 3;
    int quotient, remainder;

    non_restoring_division(dividend, divisor, 4, &quotient, &remainder);

    printf("Dividend  = %d\n", dividend);
    printf("Divisor   = %d\n", divisor);
    printf("Quotient  = %d\n", quotient);
    printf("Remainder = %d\n", remainder);

    if (quotient == dividend / divisor &&
        remainder == dividend % divisor)
        printf("DEBUG: PASS - non-restoring division is correct.\n");
    else
        printf("DEBUG: FAIL - inspect shift/add/subtract operations.\n");

    return 0;
}
