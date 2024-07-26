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
  ldecimal lvalue_1 = {0};
  ldecimal lvalue_2 = {0};
  ldecimal lresult = {0};

  dec_to_ldec(value_1, &lvalue_1);
  dec_to_ldec(value_2, &lvalue_2);

  lvalue_1.base_scale = get_scale(value_1);
  lvalue_2.base_scale = get_scale(value_2);
  lresult.base_scale = normalize(&lvalue_1, &lvalue_2);

  simple_add(lvalue_1, lvalue_2, &lresult);
  cut_ldecimal(&lresult);

  printf("\n\nexponent = [%d] || result:\n\n\n\n", lresult.base_scale);
  print_ldecimal(lresult);

  return ARITHMETIC_OK;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  ldecimal lvalue_1 = {0};
  ldecimal lvalue_2 = {0};
  ldecimal lresult = {0};

  dec_to_ldec(value_1, &lvalue_1);
  dec_to_ldec(value_2, &lvalue_2);

  lvalue_1.base_scale = get_scale(value_1);
  lvalue_2.base_scale = get_scale(value_2);
  lresult.base_scale = normalize(&lvalue_1, &lvalue_2);

  simple_add(lvalue_1, lvalue_2, &lresult);
  cut_ldecimal(&lresult);

  printf("\n\nexponent = [%d] || result:\n\n\n\n", lresult.base_scale);
  print_ldecimal(lresult);

  return ARITHMETIC_OK;
}

int s21_is_equal(s21_decimal value_1, s21_decimal valus_2) {
  return memcmp(value_1.bits, valus_2.bits, sizeof(uint32_t) * 4) == 0 &&
         get_sign(value_1) == get_sign(valus_2);
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}