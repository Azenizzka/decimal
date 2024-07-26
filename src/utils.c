#include "utils.h"

#include <stdio.h>
#include <string.h>

void print_binary(uint32_t value) {
  for (int8_t i = 31; i >= 0; i--) putchar(value & (1 << i) ? '1' : '0');
}

void print_decimal(s21_decimal value) {
  puts("============DECIMAL=============\n");
  printf("SCALE: %hhd\n\n", get_scale(value));
  for (uint8_t i = 0; i < 3; i++) {
    printf("bits[%d]: ", i);
    print_binary(value.bits[i]);
    putchar('\n');
  }

  puts("\n================================");
}

void print_ldecimal(ldecimal value) {
  puts("==========LONG DECIMAL==========\n");
  printf("BASE SCALE: %hhd\n\n", value.base_scale);
  for (uint8_t i = 0; i < 3; i++) {
    printf("bits[%d]: ", i);
    print_binary(value.bits[i]);
    putchar('\n');
  }

  puts("\n================================");
}

uint8_t get_bit(uint32_t value, uint8_t bit_pos) {
  return (value >> bit_pos) & 1;
}

void set_bit(uint32_t *value, uint8_t bit, uint8_t state) {
  *value = state ? (*value | (1 << bit)) : (*value & ~(1 << bit));
}

uint8_t get_dbit(s21_decimal value, uint8_t bit_pos) {
  return value.bits[bit_pos / 32] >> (bit_pos % 32) & 1;
}

void set_dbit(s21_decimal *value, uint8_t bit, uint8_t state) {
  state ? (value->bits[bit / 32] |= (1 << (bit % 32)))
        : (value->bits[bit / 32] &= ~(1 << (bit % 32)));
}

uint8_t get_ldbit(ldecimal value, uint8_t bit_pos) {
  return value.bits[bit_pos / 32] >> (bit_pos % 32) & 1;
}

void set_ldbit(ldecimal *value, uint8_t bit, uint8_t state) {
  state ? (value->bits[bit / 32] |= (1 << (bit % 32)))
        : (value->bits[bit / 32] &= ~(1 << (bit % 32)));
}

void set_sign(s21_decimal *value, sign _sign) {
  set_bit(&value->bits[3], SIGN_BIT_POS, _sign == MINUS);
}

sign get_sign(s21_decimal value) {
  return get_bit(value.bits[3], SIGN_BIT_POS) ? MINUS : PLUS;
}

void set_scale(s21_decimal *value, uint8_t coeff) {
  value->bits[3] &= 0x0000FFFF;
  value->bits[3] |= (uint32_t)coeff << 16;
}

uint8_t get_scale(s21_decimal value) { return value.bits[3] >> 16; }

void reset_decimal(s21_decimal *value) {
  memset(value, 0, sizeof(uint32_t) * 4);
}

void copy_decimal(s21_decimal src, s21_decimal *dst) {
  memcpy(dst->bits, src.bits, sizeof(uint32_t) * 4);
}

void copy_ldecimal(ldecimal src, ldecimal *dst) {
  memcpy(dst->bits, src.bits, sizeof(uint32_t) * 8);
}

uint8_t word_add(uint32_t *result, uint32_t value_1, uint32_t value_2,
                 uint8_t carry) {
  *result = value_1 + value_2 + carry;
  (value_1 < value_2) ? (value_1 += carry) : (value_2 += carry);

  return __builtin_uadd_overflow(value_1, value_2, result);
}

arithmetic_result simple_add(ldecimal value_1, ldecimal value_2,
                             ldecimal *result) {
  uint8_t overflow = 0;

  for (uint8_t i = 0; i < 8; i++) {
    overflow =
        word_add(&result->bits[i], value_1.bits[i], value_2.bits[i], overflow);
  }

  return overflow ? TOO_LARGE : ARITHMETIC_OK;
}

arithmetic_result simple_sub(ldecimal value_1, ldecimal value_2,
                             ldecimal *result) {
  for (uint8_t i = 0; i < 8; i++)
    word_add(&result->bits[i], value_1.bits[i], value_2.bits[i], 0);
  return ARITHMETIC_OK;
}

void dec_to_ldec(s21_decimal src, ldecimal *dst) {
  memcpy(dst, &src, sizeof(uint32_t) * 3);
}

int8_t ldec_to_dec(ldecimal src, s21_decimal *dst) {
  for (uint8_t i = 3; i < 8; i++)
    if (src.bits[i] != 0) return -1;

  memcpy(dst->bits, src.bits, sizeof(uint32_t) * 3);
  set_scale(dst, src.base_scale);

  return 0;
}

void lshift(ldecimal *value, uint8_t shift) {
  for (uint8_t i = 0; i < shift; i++) {
    for (int16_t bit = sizeof(uint32_t) * 8 - 1; bit > 0; bit--)
      set_ldbit(value, bit, get_ldbit(*value, bit - 1));

    set_ldbit(value, 0, 0);
  }
}

arithmetic_result mul_by_10(ldecimal *val) {
  ldecimal twice_ldecimal;
  ldecimal thrice_ldecimal;
  ldecimal result_ld;

  copy_ldecimal(*val, &twice_ldecimal);
  copy_ldecimal(*val, &thrice_ldecimal);

  lshift(&twice_ldecimal, 1);
  lshift(&thrice_ldecimal, 3);

  arithmetic_result result_code =
      simple_add(twice_ldecimal, thrice_ldecimal, &result_ld);

  if (result_code == ARITHMETIC_OK) *val = result_ld;

  return result_code;
}

// testme
void div_by_10(ldecimal *value) {
  for (uint8_t i = 0; i < 8; i++) {
    value->bits[i] = value->bits[i] / 10;
  }
}

// TESTME
uint8_t is_div_by_10(ldecimal val) {
  for (uint8_t i = 0; i < 8; i++)
    if (val.bits[i] % 10) return 0;

  return 1;
}

// TESTME
void cut_ldecimal(ldecimal *value) {
  while (value->base_scale > 0 && is_div_by_10(*value)) {
    value->base_scale--;
    div_by_10(value);
  }
}

uint8_t normalize(ldecimal *val_1, ldecimal *val_2) {
  uint8_t max_scale = fmax(val_1->base_scale, val_2->base_scale);
  uint8_t min_scale = fmin(val_1->base_scale, val_2->base_scale);
  uint8_t scale_diff = max_scale - min_scale;

  ldecimal *min_scale_ldecimal;

  if (val_1->base_scale == min_scale)
    min_scale_ldecimal = val_1;
  else
    min_scale_ldecimal = val_2;

  for (uint8_t i = 0; i < scale_diff; i++) {
    mul_by_10(min_scale_ldecimal);
  }

  return max_scale;
}