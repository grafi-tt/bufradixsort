#ifndef BUFRADIXSORT_H
#define BUFRADIXSORT_H

#include <limits.h>
#include <stdlib.h>

#define BUFRADIX_BKT_POS_BIT  (CHAR_BIT-2)
#define BUFRADIX_BKT_POS_MASK ((1<<BUFRADIX_BKT_POS_BIT)-1)
#define BUFRADIX_KEY          ((unsigned char)0 << BUFRADIX_BKT_POS_BIT)
#define BUFRADIX_KEY_SIGN_INT ((unsigned char)1 << BUFRADIX_BKT_POS_BIT)
#define BUFRADIX_KEY_SIGN_FLT ((unsigned char)2 << BUFRADIX_BKT_POS_BIT)
#define BUFRADIX_IGN          ((unsigned char)3 << BUFRADIX_BKT_POS_BIT)

#if defined(__cplusplus)
extern "C" {
#endif

void bufradixsort(void *data, void *work, size_t elem_cnt, unsigned int elem_size, unsigned char *elem_order);

#if defined(__cplusplus)
}
#endif

#endif
