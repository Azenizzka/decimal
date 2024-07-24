#include "s21_decimal.h"

#include <math.h>
#include <stdio.h>

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  reset_decimal(dst);

  if (src < 0) {
    src *= -1;
    set_sign(dst, MINUS);
  }

  dst->bits[0] = src;
  return 0;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  copy_decimal(value, result);
  set_sign(result, get_sign(value) * -1);

  return 0;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  ldecimal lval_1 = {0};
  ldecimal lval_2 = {0};

  lshift(&lval_1, 1);

  uint8_t min_sc = fmin(get_scale(value_1), get_scale(value_2));
  uint8_t max_sc = fmax(get_scale(value_1), get_scale(value_2));

  dec_to_ldec(value_1, &lval_1);
  dec_to_ldec(value_2, &lval_2);

  printf("\n\n\nbefore\n");
  print_ldecimal(lval_1);
  printf("\n=== after\n");

  mul_by_10(&lval_1);

  print_ldecimal(lval_1);
  printf("\n\n\n\n");

  if (get_scale(value_1) < get_scale(value_2)) {
    normalize(&lval_1, &lval_2, min_sc, max_sc);
  } else {
    normalize(&lval_2, &lval_1, min_sc, max_sc);
  }

  return ARITHMETIC_OK;
}

int s21_is_equal(s21_decimal value_1, s21_decimal valus_2) {
  return memcmp(value_1.bits, valus_2.bits, sizeof(uint32_t) * 4) == 0 &&
         get_sign(value_1) == get_sign(valus_2);
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}
