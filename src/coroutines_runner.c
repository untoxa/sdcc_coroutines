#include <gbdk/platform.h>
#include <stdint.h>
#include <stdbool.h>

#include "coroutines_runner.h"

typedef struct coro_runner_context_t {
    struct coro_runner_context_t * next;
    uint8_t coro_id;
    uint8_t * handle;
    struct coro_context_t coro_context;
} coro_runner_context_t;

coro_runner_context_t coro_contexts[CORO_MAX_CONTEXTS];
coro_runner_context_t * coro_active_ctx = NULL, * coro_free_ctx = NULL;

void coro_runner_init(void) {
    coro_active_ctx = coro_free_ctx = NULL;
    uint8_t id = 0;
    for (coro_runner_context_t * i = coro_contexts; i != (coro_contexts + CORO_MAX_CONTEXTS); i++) {
        i->next = coro_free_ctx;
        i->coro_id = id++;
        coro_free_ctx = i;
    }
}

uint8_t coro_runner_start(coro_t coro, uint8_t coro_bank, uint8_t * handle, void * user_data) {
    if (coro_free_ctx) {
        coro_runner_context_t * tmp = coro_free_ctx;
        coro_free_ctx = tmp->next;
        tmp->next = coro_active_ctx;
        coro_active_ctx = tmp;
        coro_init(&coro_active_ctx->coro_context, coro, coro_bank, user_data);
        return (tmp->handle = handle) ? *handle = tmp->coro_id : tmp->coro_id;
    }
    return (CORO_ERROR | CORO_TERMINATED);
}

static coro_runner_context_t * runner_curr, * runner_prev;

void coro_runner_kill(uint8_t coro_id) {
    runner_curr = coro_active_ctx, runner_prev = NULL;
    while (runner_curr) {
        if (runner_curr->coro_id == coro_id) {
            if (runner_curr->handle) *runner_curr->handle |= CORO_TERMINATED;
            if (runner_prev) runner_prev->next = runner_curr->next;
            if (coro_active_ctx == runner_curr) coro_active_ctx = runner_curr->next;
            runner_curr->next = coro_free_ctx, coro_free_ctx = runner_curr;
            break;
        } else {
            runner_prev = runner_curr, runner_curr = runner_curr->next;
        }
    }
}

bool coro_runner_process(void) {
    runner_curr = coro_active_ctx, runner_prev = NULL;
    while (runner_curr) {
        if (!coro_continue(&runner_curr->coro_context)) {
            if (runner_curr->handle) *runner_curr->handle |= CORO_TERMINATED;
            if (runner_prev) runner_prev->next = runner_curr->next;
            if (coro_active_ctx == runner_curr) coro_active_ctx = runner_curr->next;
            runner_curr->next = coro_free_ctx, coro_free_ctx = runner_curr;
            if (runner_prev) runner_curr = runner_prev->next; else runner_curr = coro_active_ctx;
        } else {
            runner_prev = runner_curr, runner_curr = runner_curr->next;
        }
    }
    return (coro_active_ctx != NULL);
}