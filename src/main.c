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
  // run_tests();

  printf("\n\n");

  s21_decimal decimal_1 = {0};
  s21_decimal decimal_2 = {0};
  s21_decimal result = {0};

  int res = 0;

  // 3.1
  // 1.5
  // ========
  // 4

  // decimal_1.bits[2] = 0b0;
  // decimal_1.bits[1] = 0b0;
  // decimal_1.bits[0] = 0b01111;
  // decimal_1.bits[3] = 0b00000000000000010000000000000000;

  // decimal_2.bits[2] = 0b0;
  // decimal_2.bits[1] = 0b0;
  // decimal_2.bits[0] = 0b11111;
  // decimal_2.bits[3] = 0b00000000000000010000000000000000;

  // 3.1
  // 1.5
  // ========
  // 4

  decimal_1.bits[2] = 0b0;
  decimal_1.bits[1] = 0b0;
  decimal_1.bits[0] = 0b11111;
  decimal_1.bits[3] = 0b00000000000000110000000000000000;

  decimal_2.bits[2] = 0b0;
  decimal_2.bits[1] = 0b0;
  decimal_2.bits[0] = 0b11111;
  decimal_2.bits[3] = 0b00000000000000010000000000000000;

  // s21_add(decimal_1, decimal_2, &result);

  // printf("dec1: %d\n", decimal_1.bits[0]);
  // printf("dec2: %d\n", decimal_2.bits[0]);
  // printf("=========\n");
  // printf("res:  %d\n", result.bits[0]);

  // 1.5 / 1
  // 7   / 0
  //=======
  // 8.5

  // 1.5 /
  // 0.7
  //

  int ret = s21_from_decimal_to_int(decimal_1, &res);
  printf("res: %d\n", res);

  // printf("ret: %d", ret);

  return 0;
}