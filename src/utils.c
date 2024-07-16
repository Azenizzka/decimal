#include "utils.h"

#include <stdio.h>
#include <string.h>

uint8_t get_bit(uint32_t value, uint8_t bit_pos) {
  return (value >> bit_pos) & 1;
}

void set_bit(uint32_t *value, uint8_t bit, uint8_t state) {
  *value = state ? (*value | bit) : (*value & ~bit);
}

void set_sign(s21_decimal *value, sign _sign) {
  set_bit(&value->bits[3], SIGN_BIT_POS, _sign == MINUS);
}

sign get_sign(s21_decimal value) {
  return get_bit(value.bits[3], SIGN_BIT_POS) == 0 ? PLUS : MINUS;
}

void set_coeff(s21_decimal *value, uint8_t coeff) {
  value->bits[3] &= 0x0000FFFF;
  value->bits[3] |= ((uint32_t)coeff << 16);
}

uint8_t get_coeff(s21_decimal value) { return value.bits[3] >> 16; }

void reset_decimal(s21_decimal *value) {
  memset(value, 0, sizeof(uint32_t) * 4);
}

void copy_decimal(s21_decimal src, s21_decimal *dst) {
  memcpy(dst->bits, src.bits, sizeof(uint32_t) * 4);
}