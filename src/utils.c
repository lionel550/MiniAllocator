#include <assert.h>
#include "../include/utils.h"

int is_power_of_two(size_t n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

size_t calc_padding_with_header(uintptr_t ptr, size_t alignment, size_t header_size) {
    uintptr_t p, a, modulo, padding, needed_space;

    assert(is_power_of_two(alignment));

    p = ptr;
    a = alignment;
    modulo = p & (a-1); // (p % a) as it assumes alignment is a power of two

    padding = 0;
    needed_space = 0;

    if (modulo != 0) { // Same logic as 'align_forward'
        padding = a - modulo;
    }

    needed_space = (uintptr_t)header_size;

    if (padding < needed_space) {
        needed_space -= padding;

        if ((needed_space & (a-1)) != 0) {
            padding += a * (1+(needed_space/a));
        } else {
            padding += a * (needed_space/a);
        }
    }

    return (size_t)padding;
}
