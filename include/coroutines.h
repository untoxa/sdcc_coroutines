#ifndef __COROUTINES_H_INCLUDE__
#define __COROUTINES_H_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_CORO_STACK_SIZE 128

typedef struct coro_context_t {
    uint16_t * SP;
    void * user_data;
    uint16_t stack[MAX_CORO_STACK_SIZE >> 1];
} coro_context_t;
typedef void (* coro_t)(void) BANKED;

extern coro_context_t * coro_current_context;

bool coro_yield(void);

bool coro_start(coro_context_t * context, coro_t coro, uint8_t coro_bank);
bool coro_continue(coro_context_t * context);

#endif