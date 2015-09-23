#ifndef BUFRADIXSORT_PP_H
#define BUFRADIXSORT_PP_H

#include "bufradixsort_pp_primrec.h"

#define SPLAT8(x1, x2, x3, x4, x5, x6, x7, x8) x1, x2, x3, x4, x5, x6, x7, x8
#define SPLAT7(x1, x2, x3, x4, x5, x6, x7)     x1, x2, x3, x4, x5, x6, x7
#define SPLAT6(x1, x2, x3, x4, x5, x6)         x1, x2, x3, x4, x5, x6
#define SPLAT5(x1, x2, x3, x4, x5)             x1, x2, x3, x4, x5
#define SPLAT4(x1, x2, x3, x4)                 x1, x2, x3, x4
#define SPLAT3(x1, x2, x3)                     x1, x2, x3
#define SPLAT2(x1, x2)                         x1, x2
#define SPLAT1(x1)                             x1

/* arith */
#define ADD(n, m) ADD_E(PRIMREC(m, ADD_F, ADD_G, n))
#define ADD_E(x) ADD_EE(ADD_EE(x))
#define ADD_EE(x) x
#define ADD_F(n) n
#define ADD_G(m, n, r) SUCC(r)

#define MUL(n, m) MUL_E(PRIMREC(m, MUL_F, MUL_G, n))
#define MUL_E(x) MUL_EE(MUL_EE(x))
#define MUL_EE(x) x
#define MUL_F(n) 0
#define MUL_G(m, n, r) ADD(n, r)

#define POW(n, m) POW_E(PRIMREC(m, POW_F, POW_G, n))
#define POW_E(x) POW_EE(POW_EE(x))
#define POW_EE(x) x
#define POW_F(n) 1
#define POW_G(m, n, r) MUL(n, r)

#define PRED(n) PRED_E(PRIMREC(n, PRED_F, PRED_G, _))
#define PRED_E(x) PRED_EE(PRED_EE(x))
#define PRED_EE(x) x
#define PRED_F(_) 0
#define PRED_G(n, _, r) n

#define SUB(n, m) SUB_E(PRIMREC(m, SUB_F, SUB_G, n))
#define SUB_E(x) SUB_EE(SUB_EE(x))
#define SUB_EE(x) x
#define SUB_F(n) n
#define SUB_G(m, n, r) PRED(r)

#define IF0(n, x, y) IF0_E(PRIMREC(n, IF0_F, IF0_G, (x, y)))
#define IF0_E(x) IF0_EE(IF0_EE(x))
#define IF0_EE(x) x
#define IF0_F(xy) IF0_F_HELPER1(SPLAT2 xy)
#define IF0_F_HELPER1(splat_xy) IF0_F_HELPER2(splat_xy)
#define IF0_F_HELPER2(x, y) x
#define IF0_G(n, xy, _) IF0_G_HELPER1(SPLAT2 xy)
#define IF0_G_HELPER1(splat_xy) IF0_G_HELPER2(splat_xy)
#define IF0_G_HELPER2(x, y) y

#define DIV(n, m) DIV_HELPER1(DIV_E(PRIMREC(n, DIV_F, DIV_G, m)))
#define DIV_HELPER1(qr) DIV_HELPER2(SPLAT2 qr)
#define DIV_HELPER2(splat_qr) DIV_HELPER3(splat_qr)
#define DIV_HELPER3(q, r) q
#define DIV_E(x) DIV_EE(DIV_EE(x))
#define DIV_EE(x) x
#define DIV_F(m) (0, PRED(m))
#define DIV_G(i, m, qr) DIV_G_HELPER1(i, m, SPLAT2 qr)
#define DIV_G_HELPER1(i, m, splat_qr) DIV_G_HELPER2(i, m, splat_qr)
#define DIV_G_HELPER2(i, m, q, r) IF0(r, (SUCC(q), PRED(m)), (q, PRED(r)))

/* unrolling */
#define ITER(n, code) do { ITER_E(PRIMREC(n, ITER_F, ITER_G, code)) } while(0)
#define ITER_E(x) ITER_EE(ITER_EE(x))
#define ITER_EE(x) x
#define ITER_F(code)
#define ITER_G(n, code, rec) rec code();

#define ITERNUM(n, code) do { ITERNUM_E(PRIMREC(n, ITERNUM_F, ITERNUM_G, code)) } while(0)
#define ITERNUM_E(x) ITERNUM_EE(ITERNUM_EE(x))
#define ITERNUM_EE(x) x
#define ITERNUM_F(code)
#define ITERNUM_G(n, code, rec) rec code(n);

#define ITERARG(n, code, arg) do { ITERARG_E(PRIMREC(n, ITERARG_F, ITERARG_G, (code, arg))) } while(0)
#define ITERARG_E(x) ITERARG_EE(ITERARG_EE(x))
#define ITERARG_EE(x) x
#define ITERARG_F(code_arg)
#define ITERARG_G(n, code_arg, rec) ITERARG_G_HELPER1(SPLAT2 code_arg, rec)
#define ITERARG_G_HELPER1(splat_code_arg, rec) ITERARG_G_HELPER2(splat_code_arg, rec)
#define ITERARG_G_HELPER2(code, arg, rec) rec code(arg);

#define ITERLIST(listlen, list, code) ITERLIST_HELPER1(listlen, list, code)
#define ITERLIST_HELPER1(listlen, list, code) ITERLIST_HELPER2(listlen, code, SPLAT##listlen list)
#define ITERLIST_HELPER2(listlen, code, splat_list) do { ITERLIST_##listlen(code, splat_list) } while(0)
#define ITERLIST_8(code, a1, a2, a3, a4, a5, a6, a7, a8) code(a1); ITERLIST_7(code, a2, a3, a4, a5, a6, a7, a8)
#define ITERLIST_7(code, a1, a2, a3, a4, a5, a6, a7)     code(a1); ITERLIST_6(code, a2, a3, a4, a5, a6, a7)
#define ITERLIST_6(code, a1, a2, a3, a4, a5, a6)         code(a1); ITERLIST_5(code, a2, a3, a4, a5, a6)
#define ITERLIST_5(code, a1, a2, a3, a4, a5)             code(a1); ITERLIST_4(code, a2, a3, a4, a5)
#define ITERLIST_4(code, a1, a2, a3, a4)                 code(a1); ITERLIST_3(code, a2, a3, a4)
#define ITERLIST_3(code, a1, a2, a3)                     code(a1); ITERLIST_2(code, a2, a3)
#define ITERLIST_2(code, a1, a2)                         code(a1); ITERLIST_1(code, a2)
#define ITERLIST_1(code, a1)                             code(a1);

#endif /* BUFRADIXSORT_PP_H */
