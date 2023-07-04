#ifndef __COROUTINES_RUNNER_H_INCLUDE__
#define __COROUTINES_RUNNER_H_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>
#include <stdbool.h>

#include "coroutines.h"

#define CORO_MAX_CONTEXTS   8
#define CORO_ERROR          CORO_MAX_CONTEXTS

#define CORO_TERMINATED     0x80

// initialize coroutine runner
void coro_runner_init(void);

// start coroutine, return coroutine id
uint8_t coro_runner_start(coro_t coro, uint8_t coro_bank, uint8_t * handle, void * user_data);

// kill running coroutine by id
void coro_runner_kill(uint8_t coro_id);

// process coroutines (run each until yield)
bool coro_runner_process(void);

#endif