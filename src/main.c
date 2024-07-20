#include <check.h>
#include <stdio.h>

#include "s21_decimal.h"

START_TEST(test_s21_strlen) {
  s21_decimal decimal_1 = {0};

  int ret = s21_from_int_to_decimal(INT_MAX, &decimal_1);
  ck_assert_int_eq(ret, 0);
}
END_TEST

void run_tests() {
  Suite *suite = suite_create("s21_string");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strlen);

  SRunner *sr = srunner_create(suite);

  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}

int main() {
  s21_decimal decimal_1 = {0};
  s21_decimal decimal_2 = {0};
  s21_decimal result = {0};

  decimal_1.bits[0] = 0b00000000000000000000000000000000;
  decimal_1.bits[1] = 0b00000000000000000000000000000000;
  decimal_1.bits[2] = 0b00000000000000000000000000001111;

  decimal_2.bits[0] = 0b00000000000000000000000000000000;
  decimal_2.bits[1] = 0b00000000000000000000000000000000;
  decimal_2.bits[2] = 0b00000000000000000000000000000000;

  s21_add(decimal_1, decimal_2, &result);

  print_decimal(decimal_1);
  putchar('\n');
  print_decimal(decimal_2);
  putchar('\n');
  print_decimal(result);
  putchar('\n');

  return 0;
}