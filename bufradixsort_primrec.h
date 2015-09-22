#ifndef BUFRADIXSORT_PRIMREC_H
#define BUFRADIXSORT_PRIMREC_H

#define EMPTY

#define PRIMREC(          n, f, g, x) PRIMREC_INDIRECT1 EMPTY (n, f, g, x)
#define PRIMREC_INDIRECT1(n, f, g, x) PRIMREC_INDIRECT2 EMPTY (n, f, g, x)
#define PRIMREC_INDIRECT2(n, f, g, x) PRIMREC_##n(f, g, x)
#define PRIMREC_64(f, g, x) g EMPTY (63, x, PRIMREC_63(f, g, x))
#define PRIMREC_63(f, g, x) g EMPTY (62, x, PRIMREC_62(f, g, x))
#define PRIMREC_62(f, g, x) g EMPTY (61, x, PRIMREC_61(f, g, x))
#define PRIMREC_61(f, g, x) g EMPTY (60, x, PRIMREC_60(f, g, x))
#define PRIMREC_60(f, g, x) g EMPTY (59, x, PRIMREC_59(f, g, x))
#define PRIMREC_59(f, g, x) g EMPTY (58, x, PRIMREC_58(f, g, x))
#define PRIMREC_58(f, g, x) g EMPTY (57, x, PRIMREC_57(f, g, x))
#define PRIMREC_57(f, g, x) g EMPTY (56, x, PRIMREC_56(f, g, x))
#define PRIMREC_56(f, g, x) g EMPTY (55, x, PRIMREC_55(f, g, x))
#define PRIMREC_55(f, g, x) g EMPTY (54, x, PRIMREC_54(f, g, x))
#define PRIMREC_54(f, g, x) g EMPTY (53, x, PRIMREC_53(f, g, x))
#define PRIMREC_53(f, g, x) g EMPTY (52, x, PRIMREC_52(f, g, x))
#define PRIMREC_52(f, g, x) g EMPTY (51, x, PRIMREC_51(f, g, x))
#define PRIMREC_51(f, g, x) g EMPTY (50, x, PRIMREC_50(f, g, x))
#define PRIMREC_50(f, g, x) g EMPTY (49, x, PRIMREC_49(f, g, x))
#define PRIMREC_49(f, g, x) g EMPTY (48, x, PRIMREC_48(f, g, x))
#define PRIMREC_48(f, g, x) g EMPTY (47, x, PRIMREC_47(f, g, x))
#define PRIMREC_47(f, g, x) g EMPTY (46, x, PRIMREC_46(f, g, x))
#define PRIMREC_46(f, g, x) g EMPTY (45, x, PRIMREC_45(f, g, x))
#define PRIMREC_45(f, g, x) g EMPTY (44, x, PRIMREC_44(f, g, x))
#define PRIMREC_44(f, g, x) g EMPTY (43, x, PRIMREC_43(f, g, x))
#define PRIMREC_43(f, g, x) g EMPTY (42, x, PRIMREC_42(f, g, x))
#define PRIMREC_42(f, g, x) g EMPTY (41, x, PRIMREC_41(f, g, x))
#define PRIMREC_41(f, g, x) g EMPTY (40, x, PRIMREC_40(f, g, x))
#define PRIMREC_40(f, g, x) g EMPTY (39, x, PRIMREC_39(f, g, x))
#define PRIMREC_39(f, g, x) g EMPTY (38, x, PRIMREC_38(f, g, x))
#define PRIMREC_38(f, g, x) g EMPTY (37, x, PRIMREC_37(f, g, x))
#define PRIMREC_37(f, g, x) g EMPTY (36, x, PRIMREC_36(f, g, x))
#define PRIMREC_36(f, g, x) g EMPTY (35, x, PRIMREC_35(f, g, x))
#define PRIMREC_35(f, g, x) g EMPTY (34, x, PRIMREC_34(f, g, x))
#define PRIMREC_34(f, g, x) g EMPTY (33, x, PRIMREC_33(f, g, x))
#define PRIMREC_33(f, g, x) g EMPTY (32, x, PRIMREC_32(f, g, x))
#define PRIMREC_32(f, g, x) g EMPTY (31, x, PRIMREC_31(f, g, x))
#define PRIMREC_31(f, g, x) g EMPTY (30, x, PRIMREC_30(f, g, x))
#define PRIMREC_30(f, g, x) g EMPTY (29, x, PRIMREC_29(f, g, x))
#define PRIMREC_29(f, g, x) g EMPTY (28, x, PRIMREC_28(f, g, x))
#define PRIMREC_28(f, g, x) g EMPTY (27, x, PRIMREC_27(f, g, x))
#define PRIMREC_27(f, g, x) g EMPTY (26, x, PRIMREC_26(f, g, x))
#define PRIMREC_26(f, g, x) g EMPTY (25, x, PRIMREC_25(f, g, x))
#define PRIMREC_25(f, g, x) g EMPTY (24, x, PRIMREC_24(f, g, x))
#define PRIMREC_24(f, g, x) g EMPTY (23, x, PRIMREC_23(f, g, x))
#define PRIMREC_23(f, g, x) g EMPTY (22, x, PRIMREC_22(f, g, x))
#define PRIMREC_22(f, g, x) g EMPTY (21, x, PRIMREC_21(f, g, x))
#define PRIMREC_21(f, g, x) g EMPTY (20, x, PRIMREC_20(f, g, x))
#define PRIMREC_20(f, g, x) g EMPTY (19, x, PRIMREC_19(f, g, x))
#define PRIMREC_19(f, g, x) g EMPTY (18, x, PRIMREC_18(f, g, x))
#define PRIMREC_18(f, g, x) g EMPTY (17, x, PRIMREC_17(f, g, x))
#define PRIMREC_17(f, g, x) g EMPTY (16, x, PRIMREC_16(f, g, x))
#define PRIMREC_16(f, g, x) g EMPTY (15, x, PRIMREC_15(f, g, x))
#define PRIMREC_15(f, g, x) g EMPTY (14, x, PRIMREC_14(f, g, x))
#define PRIMREC_14(f, g, x) g EMPTY (13, x, PRIMREC_13(f, g, x))
#define PRIMREC_13(f, g, x) g EMPTY (12, x, PRIMREC_12(f, g, x))
#define PRIMREC_12(f, g, x) g EMPTY (11, x, PRIMREC_11(f, g, x))
#define PRIMREC_11(f, g, x) g EMPTY (10, x, PRIMREC_10(f, g, x))
#define PRIMREC_10(f, g, x) g EMPTY ( 9, x, PRIMREC_9( f, g, x))
#define PRIMREC_9( f, g, x) g EMPTY ( 8, x, PRIMREC_8( f, g, x))
#define PRIMREC_8( f, g, x) g EMPTY ( 7, x, PRIMREC_7( f, g, x))
#define PRIMREC_7( f, g, x) g EMPTY ( 6, x, PRIMREC_6( f, g, x))
#define PRIMREC_6( f, g, x) g EMPTY ( 5, x, PRIMREC_5( f, g, x))
#define PRIMREC_5( f, g, x) g EMPTY ( 4, x, PRIMREC_4( f, g, x))
#define PRIMREC_4( f, g, x) g EMPTY ( 3, x, PRIMREC_3( f, g, x))
#define PRIMREC_3( f, g, x) g EMPTY ( 2, x, PRIMREC_2( f, g, x))
#define PRIMREC_2( f, g, x) g EMPTY ( 1, x, PRIMREC_1( f, g, x))
#define PRIMREC_1( f, g, x) g EMPTY ( 0, x, PRIMREC_0( f, g, x))
#define PRIMREC_0( f, g, x) f EMPTY (x)

#define SUCC(n) SUCC_HELPER(n)
#define SUCC_HELPER(n) SUCC_##n
#define SUCC_63 64
#define SUCC_62 63
#define SUCC_61 62
#define SUCC_60 61
#define SUCC_59 60
#define SUCC_58 59
#define SUCC_57 58
#define SUCC_56 57
#define SUCC_55 56
#define SUCC_54 55
#define SUCC_53 54
#define SUCC_52 53
#define SUCC_51 52
#define SUCC_50 51
#define SUCC_49 50
#define SUCC_48 49
#define SUCC_47 48
#define SUCC_46 47
#define SUCC_45 46
#define SUCC_44 45
#define SUCC_43 44
#define SUCC_42 43
#define SUCC_41 42
#define SUCC_40 41
#define SUCC_39 40
#define SUCC_38 39
#define SUCC_37 38
#define SUCC_36 37
#define SUCC_35 36
#define SUCC_34 35
#define SUCC_33 34
#define SUCC_32 33
#define SUCC_31 32
#define SUCC_30 31
#define SUCC_29 30
#define SUCC_28 29
#define SUCC_27 28
#define SUCC_26 27
#define SUCC_25 26
#define SUCC_24 25
#define SUCC_23 24
#define SUCC_22 23
#define SUCC_21 22
#define SUCC_20 21
#define SUCC_19 20
#define SUCC_18 19
#define SUCC_17 18
#define SUCC_16 17
#define SUCC_15 16
#define SUCC_14 15
#define SUCC_13 14
#define SUCC_12 13
#define SUCC_11 12
#define SUCC_10 11
#define SUCC_9  10
#define SUCC_8  9
#define SUCC_7  8
#define SUCC_6  7
#define SUCC_5  6
#define SUCC_4  5
#define SUCC_3  4
#define SUCC_2  3
#define SUCC_1  2
#define SUCC_0  1

#define SPLAT1(x1) x1
#define SPLAT2(x1, x2) x1, x2
#define SPLAT3(x1, x2, x3) x1, x2, x3
#define SPLAT4(x1, x2, x3, x4) x1, x2, x3, x4

/* arith */
#define ADD(n, m) ADD_E(PRIMREC(n, ADD_F, ADD_G, m))
#define ADD_E(x) ADD_EE(ADD_EE(x))
#define ADD_EE(x) x
#define ADD_F(m) m
#define ADD_G(n, m, r) SUCC(r)

#define MUL(n, m) MUL_E(PRIMREC(n, MUL_F, MUL_G, m))
#define MUL_E(x) MUL_EE(MUL_EE(x))
#define MUL_EE(x) x
#define MUL_F(m) 0
#define MUL_G(n, m, r) ADD(m, r)

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

/* old DIV
// 0 -> TT, otherwise -> FF
#define TOBOOL(n) TOBOOL_E(PRIMREC(n, TOBOOL_F, TOBOOL_G, _))
#define TOBOOL_E(x) TOBOOL_EE(TOBOOL_EE(x))
#define TOBOOL_EE(x) x
#define TOBOOL_F(_) TT
#define TOBOOL_G(n, _, r) FF

// this do not expand the other branch
#define IFBOOL(b, x, xarg, y, yarg) IFBOOL_HELPER(b, x, xarg, y, yarg)
#define IFBOOL_HELPER(b, x, xarg, y, yarg) IFBOOL_##b(x, xarg, y, yarg)
#define IFBOOL_TT(x, xarg, y, yarg) IFBOOL_E(x xarg)
#define IFBOOL_FF(x, xarg, y, yarg) IFBOOL_E(y yarg)
#define IFBOOL_E(z) z

// naive impl of DIV can cause an overflow, so IFBOOL is used
#define DIV(n, m) IF0(PRED(m), n, DIV_E(PRIMREC(n, DIV_F, DIV_G, (n, m))))
#define DIV_E(x) DIV_EE(DIV_EE(x))
#define DIV_EE(x) x
#define DIV_F(nm) 0
#define DIV_G(i, nm, q) IFBOOL(TOBOOL(q), DIV_TRY_HELPER1, (i, nm, q), DIV_KEEP_HELPER, (q))
#define DIV_TRY_HELPER1(i, nm, q) DIV_TRY_HELPER2(i, SPLAT2 nm, q)
#define DIV_TRY_HELPER2(i, splat_nm, q) DIV_TRY_HELPER3(i, splat_nm, q)
#define DIV_TRY_HELPER3(i, n, m, q) IF0(SUB(SUCC(SUB(n, MUL(m, i))), m), i, 0)
#define DIV_KEEP_HELPER(q) q
*/

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
#define ITER(n, code) do { PRIMREC(n, ITER_F, ITER_G, code) } while(0)
#define ITER_E(x) ITER_EE(ITER_EE(x))
#define ITER_EE(x) x
#define ITER_F(code)
#define ITER_G(n, code, rec) rec code();

#define ITERNUM(n, code) do { PRIMREC(n, ITERNUM_F, ITERNUM_G, code) } while(0)
#define ITERNUM_E(x) ITERNUM_EE(ITERNUM_EE(x))
#define ITERNUM_EE(x) x
#define ITERNUM_F(code)
#define ITERNUM_G(n, code, rec) rec code(n);

#define ITERARG(n, code, arg) do { PRIMREC(n, ITERARG_F, ITERARG_G, (code, arg)) } while(0)
#define ITERARG_E(x) ITERARG_EE(ITERARG_EE(x))
#define ITERARG_EE(x) x
#define ITERARG_F(code_arg)
#define ITERARG_G(n, code_arg, rec) ITERARG_G_HELPER1(SPLAT2 code_arg, rec)
#define ITERARG_G_HELPER1(splat_code_arg, rec) ITERARG_G_HELPER2(splat_code_arg, rec)
#define ITERARG_G_HELPER2(code, arg, rec) rec code(arg);

#endif /* BUFRADIXSORT_PRIMREC_H */
