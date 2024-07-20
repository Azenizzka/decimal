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

// void dec_to_ldec(s21_decimal src, ldecimal *dst) {
//   for (uint8_t i = 0; i < 3; i++) dst->bits[i] = src.bits[i];
// }

// uint8_t ldec_to_dec(ldecimal src, s21_decimal *dst) {
//   for (uint8_t i = 0; i < 3; i++) dst->bits[i] = src.bits[i];

//   for (uint8_t i = 3; i < 8; i++) {

//   }
// }

void mul_by_10(s21_decimal *src) {
  for (uint8_t i = 0; i < 3; i++) {
    src->bits[i] = src->bits[i] * 10;
  }
}

void normalize(s21_decimal val_1, s21_decimal val_2, s21_decimal *norm_1,
               s21_decimal *norm_2) {
  //
  s21_decimal *max_sc_dec, *min_sc_dec;

  if (get_scale(val_1) > get_scale(val_2)) {
    max_sc_dec = &val_1;
    min_sc_dec = &val_2;
  } else {
    max_sc_dec = &val_2;
    min_sc_dec = &val_1;
  }

  uint8_t scale_diff = get_scale(*max_sc_dec) - get_scale(*min_sc_dec);

  printf("before:\n");
  print_decimal(val_1);
  mul_by_10(&val_1);

  printf("after:\n");
  print_decimal(val_1);
  printf("\n");
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  //
  normalize(value_1, value_2, NULL, NULL);
}

int s21_is_equal(s21_decimal value_1, s21_decimal valus_2) {
  return memcmp(value_1.bits, valus_2.bits, sizeof(uint32_t) * 4) == 0 &&
         get_sign(value_1) == get_sign(valus_2);
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}
