#ifndef UTILS_H
#define UTILS_H

#include <inttypes.h>

#include "s21_decimal.h"

uint8_t get_bit(uint32_t value, uint8_t bit);
void set_bit(uint32_t *value, uint8_t bit, uint8_t state);

uint8_t get_dbit(s21_decimal value, uint8_t bit_pos);
void set_dbit(s21_decimal *value, uint8_t bit, uint8_t state);

uint8_t get_ldbit(ldecimal value, uint8_t bit_pos);
void set_ldbit(ldecimal *value, uint8_t bit, uint8_t state);

sign get_sign(s21_decimal value);
void set_sign(s21_decimal *value, sign _sign);

uint8_t get_scale(s21_decimal value);
void set_scale(s21_decimal *value, uint8_t coeff);

void copy_decimal(s21_decimal src, s21_decimal *dst);
void reset_decimal(s21_decimal *value);

void print_decimal(s21_decimal src);
void print_ldecimal(ldecimal value);

void print_binary(uint32_t value);

arithmetic_result simple_add(ldecimal value_1, ldecimal value_2,
                             ldecimal *result);

void dec_to_ldec(s21_decimal src, ldecimal *dst);

void lshift(ldecimal *value, uint8_t shift);

arithmetic_result mul_by_10(ldecimal *val);

void normalize(ldecimal *min_sc_ldec, ldecimal *max_sc_ldec, uint8_t min_sc,
               uint8_t max_sc);

#endif