#pragma once
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif
void* hv_psram_malloc(size_t n);
void* hv_psram_realloc(void* p, size_t n);
#ifdef __cplusplus
}
#endif