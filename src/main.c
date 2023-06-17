#include <gbdk/platform.h>
#include <stdint.h>
#include <stdbool.h>

#include <stdio.h>

#include "coroutines.h"

void test_coro1(void) BANKED;
BANKREF_EXTERN(test_coro1)

void test_coro2(void) BANKED;
BANKREF_EXTERN(test_coro2)

coro_context_t ctx0;
bool ctx0_active = false;

coro_context_t ctx1;
bool ctx1_active = false;

void main(void) {
    printf("coroutine test\n");
    ctx0_active = coro_start(&ctx0, test_coro1, BANK(test_coro1));
    ctx1_active = coro_start(&ctx1, test_coro2, BANK(test_coro2));
    do {
        ctx0_active = (ctx0_active) ? coro_continue(&ctx0) : false;
        ctx1_active = (ctx1_active) ? coro_continue(&ctx1) : false;
    } while (ctx0_active || ctx1_active);
    printf("finished!\n");
    printf("done!\n");
}