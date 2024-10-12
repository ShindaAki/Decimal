#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H
#define START_INFO 96

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
  unsigned bits[4];
} s21_decimal;

typedef struct {
  unsigned bits[7];
} big_decimal;

typedef union {
  int ui;
  float fl;
} floatbits;

/* bits[3] [31] [30...24] [23...16] [15...0]
 *        |sign|null     |exp      |null    | */

/*------------------------ Ariphmetic operators ------------------------*/

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/*------------------------ Comparison operators ------------------------*/
void s21_comparison_reverse(int *flag);
int s21_comparison_bits(s21_decimal d1, s21_decimal d2);
int s21_greater_num(int a, int b);
int s21_comparison(s21_decimal d1, s21_decimal d2);
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

/*------------------------ Convertors and parsers ------------------------*/

int s21_get_exp(double src);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_decimal_to_double(s21_decimal src, long double *dst);

/*------------------------  Another functions   ------------------------- */

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

/*------------------------       Normalize      ------------------------- */

void s21_normalize(s21_decimal *d1, s21_decimal *d2);
void s21_normalize_scale_upper(s21_decimal *d, int norm);
void s21_copy_decimal(s21_decimal *d1, s21_decimal d2);
int s21_post_normalization(big_decimal *result, int scale);
int s21_get_sign(s21_decimal dst);
float s21_rand_r(float a, float b);
#endif /* S21_DECIMAL_H */