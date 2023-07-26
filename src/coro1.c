#pragma bank 1

#include <stdio.h>

#include "coroutines.h"

void some_internal_call(uint8_t i) {
    printf("coro1: %hd\n", i);
    coro_yield();
}

void test_coro1(void * user_data) BANKED {
    uint8_t i = 0;
    printf("run coro1(%x)\n", (uint16_t)user_data);
    while (true) {
        if (i == 5) return;
        some_internal_call(i++);
    }
}
BANKREF(test_coro1)
