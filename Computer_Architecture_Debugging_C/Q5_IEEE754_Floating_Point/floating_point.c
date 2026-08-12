#include <stdio.h>
#include <stdint.h>
#include <string.h>

void show_float_bits(float x) {
    uint32_t bits;
    memcpy(&bits, &x, sizeof(bits));
    printf("IEEE 754 bits: ");
    for (int i = 31; i >= 0; i--)
        printf("%d", (bits >> i) & 1);
    printf("\n");
}

int main(void) {
    float large_f = 1.0e20f;
    float small_f = 1.0f;
    double large_d = 1.0e20;
    double small_d = 1.0;

    float single_result = large_f + small_f;
    double double_result = large_d + small_d;

    printf("Single precision:\n");
    printf("Large + Small = %.20g\n", single_result);
    show_float_bits(large_f);

    printf("\nDouble precision:\n");
    printf("Large + Small = %.20g\n", double_result);

    printf("\nDEBUG: Single precision has limited fraction bits.\n");
    printf("When exponents are aligned, the very small operand can lose significance.\n");
    printf("Optimization: use double precision or numerically stable summation.\n");

    return 0;
}
