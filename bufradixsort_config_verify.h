#ifndef BUFRADIXSORT_CONFIG_VERIFY_H
#define BUFRADIXSORT_CONFIG_VERIFY_H

#include <limits.h>

#if BKT_BIT != CHAR_BIT
#error "currently BKT_BIT must be equal to CHAR_BIT"
#endif

#if SUPPORTED_INT_BITS_LIST > (1 << CHAR_BIT) * CHAR_BIT
#error "currently the number of bytes in an int must be representable by a char, for the sake of endianness check"
#endif

#endif /* BUFRADIXSORT_CONFIG_VERIFY_H */
