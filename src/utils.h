#ifndef UTILS_H
#define UTILS_H

#include <inttypes.h>

#include "s21_decimal.h"

uint8_t get_bit(uint32_t value, uint8_t bit);
void set_bit(uint32_t *value, uint8_t bit, uint8_t state);

sign get_sign(s21_decimal value);
void set_sign(s21_decimal *value, sign _sign);

uint8_t get_coeff(s21_decimal value);
void set_coeff(s21_decimal *value, uint8_t coeff);

void copy_decimal(s21_decimal src, s21_decimal *dst);
void reset_decimal(s21_decimal *value);

#endif