#include <stdio.h>
#include <stdint.h>

int main(void) {
    int8_t a = 120, b = 50;
    int16_t wider = (int16_t)a + (int16_t)b;
    int8_t result = (int8_t)wider;

    int overflow = ((a > 0 && b > 0 && result < 0) ||
                    (a < 0 && b < 0 && result >= 0));

    printf("A = %d\nB = %d\n", a, b);
    printf("8-bit result = %d\n", result);
    printf("Correct result using wider integer = %d\n", wider);

    if (overflow)
        printf("DEBUG: Signed overflow detected.\n");
    else
        printf("DEBUG: No signed overflow.\n");

    return 0;
}
