#ifndef BUFRADIXSORT_UNROLL_H
#define BUFRADIXSORT_UNROLL_H

/*
 * The outermost ITER must be covered by EVAL. EVAL repeatedly evaluates the
 * given argument, enabling nest of ITER. If deeper nest is required, EVAL can
 * be modified to carry out more numbers of evaluations.
 */
#define EVAL(x) EVAL1(EVAL1(x))
#define EVAL1(x) EVAL2(EVAL2(x))
#define EVAL2(x) x

/* ITER n times */
#define ITER(      n, code)      ITER_INDIRECT EMPTY (n, code, IGN_NUM_IGN_ARG, dummy)
#define ITERARG(   n, code, arg) ITER_INDIRECT EMPTY (n, code, IGN_NUM_PAS_ARG, arg  )
#define ITERNUM(   n, code)      ITER_INDIRECT EMPTY (n, code, PAS_NUM_IGN_ARG, dummy)
#define ITERNUMARG(n, code, arg) ITER_INDIRECT EMPTY (n, code, PAS_NUM_PAS_ARG, arg  )

#define ITER_INDIRECT(n, code, control, arg) do { ITER_##n(code, control, arg) } while(0)

#define EMPTY
#define IGN_NUM_IGN_ARG(n, a) ()
#define IGN_NUM_PAS_ARG(n, a) (a)
#define PAS_NUM_IGN_ARG(n, a) (n)
#define PAS_NUM_PAS_ARG(n, a) (n, a)

#define ITER_32(code, control, arg) ITER_31(code, control, arg) code control(31, arg);
#define ITER_31(code, control, arg) ITER_30(code, control, arg) code control(30, arg);
#define ITER_30(code, control, arg) ITER_29(code, control, arg) code control(29, arg);
#define ITER_29(code, control, arg) ITER_28(code, control, arg) code control(28, arg);
#define ITER_28(code, control, arg) ITER_27(code, control, arg) code control(27, arg);
#define ITER_27(code, control, arg) ITER_26(code, control, arg) code control(26, arg);
#define ITER_26(code, control, arg) ITER_25(code, control, arg) code control(25, arg);
#define ITER_25(code, control, arg) ITER_24(code, control, arg) code control(24, arg);
#define ITER_24(code, control, arg) ITER_23(code, control, arg) code control(23, arg);
#define ITER_23(code, control, arg) ITER_22(code, control, arg) code control(22, arg);
#define ITER_22(code, control, arg) ITER_21(code, control, arg) code control(21, arg);
#define ITER_21(code, control, arg) ITER_20(code, control, arg) code control(20, arg);
#define ITER_20(code, control, arg) ITER_19(code, control, arg) code control(19, arg);
#define ITER_19(code, control, arg) ITER_18(code, control, arg) code control(18, arg);
#define ITER_18(code, control, arg) ITER_17(code, control, arg) code control(17, arg);
#define ITER_17(code, control, arg) ITER_16(code, control, arg) code control(16, arg);
#define ITER_16(code, control, arg) ITER_15(code, control, arg) code control(15, arg);
#define ITER_16(code, control, arg) ITER_15(code, control, arg) code control(15, arg);
#define ITER_15(code, control, arg) ITER_14(code, control, arg) code control(14, arg);
#define ITER_14(code, control, arg) ITER_13(code, control, arg) code control(13, arg);
#define ITER_13(code, control, arg) ITER_12(code, control, arg) code control(12, arg);
#define ITER_12(code, control, arg) ITER_11(code, control, arg) code control(11, arg);
#define ITER_11(code, control, arg) ITER_10(code, control, arg) code control(10, arg);
#define ITER_10(code, control, arg) ITER_9( code, control, arg) code control( 9, arg);
#define ITER_9( code, control, arg) ITER_8( code, control, arg) code control( 8, arg);
#define ITER_8( code, control, arg) ITER_7( code, control, arg) code control( 7, arg);
#define ITER_7( code, control, arg) ITER_6( code, control, arg) code control( 6, arg);
#define ITER_6( code, control, arg) ITER_5( code, control, arg) code control( 5, arg);
#define ITER_5( code, control, arg) ITER_4( code, control, arg) code control( 4, arg);
#define ITER_4( code, control, arg) ITER_3( code, control, arg) code control( 3, arg);
#define ITER_3( code, control, arg) ITER_2( code, control, arg) code control( 2, arg);
#define ITER_2( code, control, arg) ITER_1( code, control, arg) code control( 1, arg);
#define ITER_1( code, control, arg) ITER_0( code, control, arg) code control( 0, arg);
#define ITER_0( code, control, arg)

/*
 * More general and possibly more elegant solution is to write an DIV as an
 * instance of a (primitive) recursive function, with extending the definiton of
 * ITER to recursive functions. Here, however, I prefer to the simpler approach
 * since it is easy to implement and understand.
 */
#define DIV(n, m) DIV_HELPER(n, m)
#define DIV_HELPER(n, m) DIV_##n##_##m

#define DIV_1_256 256
#define DIV_1_128 128
#define DIV_1_64  64
#define DIV_1_32  32
#define DIV_1_16  16
#define DIV_1_8   8
#define DIV_1_4   4
#define DIV_1_2   2
#define DIV_1_1   1

#define DIV_2_256 128
#define DIV_2_128 64
#define DIV_2_64  32
#define DIV_2_32  16
#define DIV_2_16  8
#define DIV_2_8   4
#define DIV_2_4   2
#define DIV_2_2   1

#define DIV_4_256 64
#define DIV_4_128 32
#define DIV_4_64  16
#define DIV_4_32  8
#define DIV_4_16  4
#define DIV_4_8   2
#define DIV_4_4   1

#define DIV_8_256 32
#define DIV_8_128 16
#define DIV_8_64  8
#define DIV_8_32  4
#define DIV_8_16  2
#define DIV_8_8   1

#define DIV_16_256 16
#define DIV_16_128 8
#define DIV_16_64  4
#define DIV_16_32  2
#define DIV_16_16  1

#define DIV_32_256 8
#define DIV_32_128 4
#define DIV_32_64  2
#define DIV_32_32  1

#endif /* BUFRADIXSORT_UNROLL_H */
