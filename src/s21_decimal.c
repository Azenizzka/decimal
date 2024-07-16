#include "s21_decimal.h"

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

char *get_str_integer_part(s21_decimal src) {
  uint8_t coeff = get_coeff(src);
  long double num = 0;
  static char str[32] = {0};

  for (uint8_t i = 0; i < 3; i++) num += src.bits[i] * pow(2, i * 32);
  sprintf(str, "%.0Lf", num);

  if (coeff < strlen(str)) {
    str[strlen(str) - coeff] = '\0';
  } else {
    str[0] = '0';
    str[1] = '\0';
  }

  return str;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (NULL == dst || get_coeff(src) > 28) return CONVERTER_ERROR;
  *dst = 0;

  uint64_t temp = strtol(get_str_integer_part(src), NULL, 10);

  if (temp > INT_MAX) return CONVERTER_ERROR;
  *dst = (int)temp * get_sign(src);

  return CONVERTER_OK;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  copy_decimal(value, result);
  set_sign(result, get_sign(value) * -1);

  return 0;
}

int s21_is_equal(s21_decimal value_1, s21_decimal valus_2) {
  return memcmp(value_1.bits, valus_2.bits, sizeof(uint32_t) * 4) == 0;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}

// s21_decimal get_integer_part(s21_decimal src) {
//   uint8_t coeff = get_coeff(src);

//   if (NULL == dst || coeff > 28) return CONVERTER_ERROR;
//   *dst = 0;

//   long double num = 0;
//   char str[32];

//   for (uint8_t i = 0; i < 3; i++) num += src.bits[i] * pow(2, i * 32);

//   sprintf(str, "%.0Lf", num);
//   uint8_t str_len = strlen(str);
//   str_len -= coeff;
//   str[str_len] = '\0';
// }

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  uint8_t max_coeff = fmax(get_coeff(value_1), get_coeff(value_2));
  uint8_t min_coeff = fmin(get_coeff(value_1), get_coeff(value_2));

  if (min_coeff == 0) {
    printf("need to handle, return..\n");
    return 1;
  }

  for (uint8_t i = 0; i < 3; i++) {
    result->bits[i] = value_1.bits[i] + value_2.bits[i];
  }

  // printf("result: %d", result->bits[0]);

  set_coeff(result, max_coeff);
  printf("coeff1: %d\n", get_coeff(value_1));
  printf("coeff2: %d\n", get_coeff(value_2));
  printf("===========\n");
  printf("result coeff: %d\n\n", get_coeff(*result));

  // 5.05  // 2
  // 15.15 // 1
  //==========
  // 21.15

  // 0565
  // 1550
  //==========
  // 2115 // 2

  return ARITHMETIC_OK;
}
