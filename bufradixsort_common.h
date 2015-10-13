#include "bufradixsort_config.h"
#include "bufradixsort_pp.h"
#include "bufradixsort_config_verify.h"

#define BKT (1u<<BKT_BIT)

#define UTYP(bits) UTYP_HELPER(bits)
#define UTYP_HELPER(bits) uint##bits##_t

#define LOGUTYP(n) UTYP(MUL(POW(2, n), CHAR_BIT))
#define SIZEUTYP(n) UTYP(MUL(n, BKT_BIT))
