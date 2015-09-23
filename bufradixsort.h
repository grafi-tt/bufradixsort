#ifndef BUFRADIXSORT_H
#define BUFRADIXSORT_H

#if defined(__cplusplus)
extern "C" {
#endif

#include <stddef.h>

#define BUFRADIX_LAYOUT_END    0
#define BUFRADIX_LAYOUT_UINT   1
#define BUFRADIX_LAYOUT_INT    2
#define BUFRADIX_LAYOUT_FLOAT  3
#define BUFRADIX_LAYOUT_IGNORE 4

typedef struct {
	unsigned char order;
	unsigned char type;
	unsigned short bits;
} bufradix_layout_t;

void bufradixsort(void *data, void *work, size_t elem_cnt, const bufradix_layout_t *elem_order);

#if defined(__cplusplus)
}
#endif

#endif
