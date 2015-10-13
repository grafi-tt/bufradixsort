#ifndef BUFRADIXSORT_PP_H
#define BUFRADIXSORT_PP_H

#include "bufradixsort_pp_primrec.h"

/* tuple */
#define FST(tuple) FST_EVAL(FST_HELPER tuple)
#define FST_EVAL(helper_tuple) helper_tuple
#define FST_HELPER(fst, snd) fst

#define SND(tuple) SND_EVAL(SND_HELPER tuple)
#define SND_EVAL(helper_tuple) helper_tuple
#define SND_HELPER(fst, snd) snd

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
#define IF0_F(xy) FST(xy)
#define IF0_G(n, xy, _) SND(xy)

#define DIV(n, m) FST(DIV_E(PRIMREC(n, DIV_F, DIV_G, m)))
#define DIV_E(x) DIV_EE(DIV_EE(x))
#define DIV_EE(x) x
#define DIV_F(m) (0, PRED(m))
#define DIV_G(i, m, qr) IF0(SND(qr), (SUCC(FST(qr)), PRED(m)), (FST(qr), PRED(SND(qr))))

/* list */
#define DECONS(len, list) DECONS_EVAL(DECONS_HELPER(len, list))
#define DECONS_EVAL(x) x
#define DECONS_HELPER(len, list) DECONS_##len list
#define DECONS_8(x1, x2, x3, x4, x5, x6, x7, x8) (x1, (x2, x3, x4, x5, x6, x7, x8))
#define DECONS_7(x1, x2, x3, x4, x5, x6, x7)     (x1, (x2, x3, x4, x5, x6, x7))
#define DECONS_6(x1, x2, x3, x4, x5, x6)         (x1, (x2, x3, x4, x5, x6))
#define DECONS_5(x1, x2, x3, x4, x5)             (x1, (x2, x3, x4, x5))
#define DECONS_4(x1, x2, x3, x4)                 (x1, (x2, x3, x4))
#define DECONS_3(x1, x2, x3)                     (x1, (x2, x3))
#define DECONS_2(x1, x2)                         (x1, (x2))
#define DECONS_1(x1)                             (x1, ())

#define INDEX(i, len, list) FST(SND(INDEX_E(PRIMREC(i, INDEX_F,INDEX_G, (len, list)))))
#define INDEX_E(x) INDEX_EE(INDEX_EE(x))
#define INDEX_EE(x) x
#define INDEX_F(len_list) (PRED(FST(len_list)), DECONS(FST(len_list), SND(len_list)))
#define INDEX_G(i, _, len_head_list) (PRED(FST(len_head_list)), DECONS(FST(len_head_list), SND(SND(len_head_list))))

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
#define ITERARG_G(n, code_arg, rec) rec FST(code_arg)(SND(code_arg));

#define ITERNUMARG(n, code, arg) do { ITERNUMARG_E(PRIMREC(n, ITERNUMARG_F, ITERNUMARG_G, (code, arg))) } while(0)
#define ITERNUMARG_E(x) ITERNUMARG_EE(ITERNUMARG_EE(x))
#define ITERNUMARG_EE(x) x
#define ITERNUMARG_F(code_arg)
#define ITERNUMARG_G(n, code_arg, rec) rec FST(code_arg)(n, SND(code_arg));

#define ITERLIST(len, list, code) \
	do { ITERLIST_E(PRIMREC(len, ITERLIST_F, ITERLIST_G, (code, (len, list)))) } while(0)
#define ITERLIST_E(x) ITERLIST_EE(ITERLIST_EE(x))
#define ITERLIST_EE(x) x
#define ITERLIST_F(code_len_list)
#define ITERLIST_G(n, code_len_list, rec) rec FST(code_len_list) \
	(INDEX(n, FST(SND(code_len_list)), SND(SND(code_len_list))));

#define ITERLISTARG(len, list, code, arg) \
	do { ITERLISTARG_E(PRIMREC(len, ITERLISTARG_F, ITERLISTARG_G, ((code, arg), (len, list)))) } while(0)
#define ITERLISTARG_E(x) ITERLISTARG_EE(ITERLISTARG_EE(x))
#define ITERLISTARG_EE(x) x
#define ITERLISTARG_F(code_arg_len_list)
#define ITERLISTARG_G(n, code_arg_len_list, rec) rec FST(FST(code_arg_len_list)) \
	(INDEX(n, FST(SND(code_arg_len_list)), SND(SND(code_arg_len_list))), SND(FST(code_arg_len_list)));

/* utils */
#define CAT(x, y) CAT_HELPER(x, y)
#define CAT_HELPER(x, y) x##y

#endif /* BUFRADIXSORT_PP_H */
