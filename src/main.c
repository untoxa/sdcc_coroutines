#include <gbdk/platform.h>
#include <stdint.h>
#include <stdbool.h>

#include <stdio.h>

#include "coroutines.h"
#include "coroutines_runner.h"

void test_coro1(void * user_data) BANKED;
BANKREF_EXTERN(test_coro1)

void test_coro2(void * user_data) BANKED;
BANKREF_EXTERN(test_coro2)

void main(void) {
    printf("coroutine test\n");
    // initialize coroutine manager
    coro_runner_init();

    // start two coroutines
    coro_runner_start(test_coro1, BANK(test_coro1), NULL, (void *)0xCAFE);
    coro_runner_start(test_coro2, BANK(test_coro2), NULL, (void *)0xBEEF);

    // process coroutines until all finished
    while (coro_runner_process()) printf("loop\n");
    printf("all finished!\n");

    printf("done!");
}