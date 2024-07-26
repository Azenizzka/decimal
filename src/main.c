#include <check.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

__uint128_t str_to_uint128_t(const char *s) {
  const char *p = s;
  __uint128_t val = 0;

  while (isdigit(*p)) {
    val = (10 * val) + (*p - '0');
    p++;
  }

  return val;
}

void str_to_dec(char *str, s21_decimal *dec) {
  reset_decimal(dec);

  if (str[0] == '-') set_sign(dec, MINUS);

  uint8_t is_point = 0;
  char str_integer[32] = {0};

  for (uint8_t i = 0; i < strlen(str); i++) {
    if (str[i] == '.') is_point = 1;
    str_integer[i] = str[i + is_point];
    str_integer[i + 1] = '\0';
  }

  __uint128_t integer_part = str_to_uint128_t(str_integer);
  dec->bits[0] = (uint32_t)integer_part;
  dec->bits[1] = (uint32_t)(integer_part >> 32);
  dec->bits[2] = (uint32_t)(integer_part >> 64);

  uint8_t scale = 0;

  for (int8_t i = strlen(str) - 1; i >= 0; i--) {
    if (str[i] == '.') break;
    scale++;
  }

  if (!strchr(str, '.')) scale = 0;

  // printf("\n\nscale: %d\n\n", scale);

  set_scale(dec, scale);

  // print_decimal(*dec);
}

void assert_decimal(s21_decimal val_1, s21_decimal val_2,
                    arithmetic_result ar_res, arithmetic_result ar_exp) {
  uint8_t is_error = 0;

  if (!s21_is_equal(val_1, val_2)) is_error = 1;
  if (ar_res != ar_exp) is_error = 1;

  if (is_error) {
    fprintf(stdout, "\n\n-------------ERROR--------------\n\n");
    print_decimal(val_1);
    fprintf(stderr, "\n!=\n\n");
    print_decimal(val_2);
    fprintf(stderr, "\n");
    fprintf(stderr, "-----------------------------\n");
  }
}

START_TEST(tc_add_1) {
  s21_decimal val_1 = {0};
  s21_decimal val_2 = {0};

  s21_decimal expected = {0};
  s21_decimal res = {0};

  str_to_dec("3", &val_1);
  str_to_dec("2", &val_2);
  str_to_dec("5", &expected);

  arithmetic_result ar_res = s21_add(val_1, val_2, &res);

  assert_decimal(res, expected, ar_res, ARITHMETIC_OK);
}
END_TEST

START_TEST(tc_add_2) {
  s21_decimal val_1 = {0};
  s21_decimal val_2 = {0};

  s21_decimal expected = {0};
  s21_decimal res = {0};

  str_to_dec("0", &val_1);
  str_to_dec("0", &val_2);
  str_to_dec("0", &expected);

  arithmetic_result ar_res = s21_add(val_1, val_2, &res);

  assert_decimal(res, expected, ar_res, ARITHMETIC_OK);
}
END_TEST

void run_tests() {
  Suite *suite = suite_create("s21_decimal");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, tc_add_1);
  tcase_add_test(tc_core, tc_add_2);

  suite_add_tcase(suite, tc_core);
  SRunner *sr = srunner_create(suite);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
}

int main() {
  // s21_decimal decimal_1 = {0};
  // s21_decimal decimal_2 = {0};
  // s21_decimal result = {0};

  run_tests();

  // str_to_dec("3.1415977777777777265", &decimal_1);

  // print_decimal(decimal_1);

  return 0;
}