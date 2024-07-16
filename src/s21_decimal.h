#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define SIGN_BIT_POS 31
// #define COEFF_MASK 0b00000000111111110000000000000000

typedef struct {
  uint32_t bits[4];
} s21_decimal;

typedef enum {
  ARITHMETIC_OK,
  TOO_LARGE,
  TOO_SMALL,
  DIVISION_BY_ZERO
} arithmetic_result;
typedef enum { CONVERTER_OK, CONVERTER_ERROR } converter_result;

typedef enum { PLUS = 1, MINUS = -1 } sign;

#include "utils.h"

// arithmetic

// TODO
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// TODO
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// s21_add
// TODO
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// s21_sub
// TODO
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// comparison
// return codes:
//
// - 0 -- FALSE
// - 1 -- TRUE

// TODO
int s21_is_less(s21_decimal value_1, s21_decimal value_2);  // <

// TODO
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);  // <=

// TODO
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);  // >

// TODO
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);  // >=

// TESTME
int s21_is_equal(s21_decimal value_1, s21_decimal valus_2);  // ==

// TESTME
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);  // !=

// convertor
// return codes:
//
// - 0 -- OK
// - 1 -- CALCULATION ERROR

// TESTME
int s21_from_int_to_decimal(int src, s21_decimal *dst);  // from int

// TODO
int s21_from_float_to_decimal(float src, s21_decimal *dst);  // from float

// TESTME
int s21_from_decimal_to_int(s21_decimal src, int *dst);  // to int

// TODO
int s21_from_decimal_to_float(s21_decimal src, float *dst);  // to float

// other
// return codes:
//
// - 0 -- OK
// - 1 -- CALCULATION ERROR

// TODO
int s21_floor(s21_decimal value, s21_decimal *result);

// TODO
int s21_round(s21_decimal value, s21_decimal *result);

// TODO
int s21_truncate(s21_decimal value, s21_decimal *result);

// TESTME
int s21_negate(s21_decimal value, s21_decimal *result);

#endif
