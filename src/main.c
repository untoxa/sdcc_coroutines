#include <gbdk/platform.h>
#include <stdint.h>
#include <stdbool.h>

#include <stdio.h>

#include "coroutines.h"
#include "coroutines_runner.h"

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
    // initialize coroutine manager
    coro_runner_init();

    // start two coroutines
    coro_runner_start(test_coro1, BANK(test_coro1), NULL, NULL);
    coro_runner_start(test_coro2, BANK(test_coro2), NULL, NULL);

    // process coroutines until all finished
    while (coro_runner_process()) printf("loop\n");

    printf("finished!\n");
    printf("done!");
}