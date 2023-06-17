#pragma bank 2

#include <stdio.h>

#include "coroutines.h"

void test_coro2(void) BANKED {
    uint8_t i = 0;
    printf("coro2 started...\n");
    while (true) {
        printf("coro2: %hd\n", i++);
        if (i == 3) return;
        coro_yield();
    }
}
BANKREF(test_coro2)
