#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdint.h>

size_t calc_padding_with_header(uintptr_t ptr, size_t alignment, size_t header_size);

#endif