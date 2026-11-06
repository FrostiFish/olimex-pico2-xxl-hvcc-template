#include <Arduino.h>
#include <string.h>
#include <stdint.h>
#include "heavy_psram.h"

static const size_t kPsramThreshold = 64 * 1024;

static bool inPsram(void* p) {
  uintptr_t a = (uintptr_t)p;
  return a >= 0x11000000 && a < 0x12000000;
}

extern "C" void* hv_psram_malloc(size_t n) {
  if (n >= kPsramThreshold) {
    void* p = pmalloc(n);
    if (p) return p;                 // falls back to SRAM if PSRAM fails
  }
  return malloc(n);
}

extern "C" void* hv_psram_realloc(void* p, size_t n) {
  if (!p) return hv_psram_malloc(n);
  if (n >= kPsramThreshold && !inPsram(p)) {
    void* q = pmalloc(n);            // growing past the threshold: move to PSRAM
    if (q) {
      memset(q, 0, n);               // old contents not copied
      free(p);
      return q;
    }
  }
  return realloc(p, n);              // everything else: normal realloc
}