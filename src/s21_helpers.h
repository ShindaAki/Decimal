#ifndef S21_HELPERS_H
#define S21_HELPERS_H

#include "s21_decimal.h"
#define DECIMALTEN                   \
  (big_decimal) {                    \
    .bits = { 10, 0, 0, 0, 0, 0, 0 } \
  }
#define MAX_DEC powf(2.0f, 96.0f) - 1.0
#define MIN_DEC -powf(2.0f, 96.0f) + 1.0

#define INTMAX 0x7fffffff
#define TRUE 1
#define FALSE 0
#define UINTMAX 0xffffffff
#define EXPMASK (0b00000000111111110000000000000000)

typedef unsigned bit_t;

/*------------------------ Operations with bits ------------------------- */

bit_t getBit(big_decimal value, unsigned num);
void setBit(big_decimal *value, unsigned num, bit_t bitValue);
int s21_get_scale(s21_decimal dst);

void helperSummSub(big_decimal value1, big_decimal value2, big_decimal *result);
unsigned getExp(big_decimal value);
void setExp(big_decimal *value, unsigned exp);
bit_t getSign(big_decimal value);
void setSign(big_decimal *value, bit_t sign);
void print_binary(unsigned int number);
int shiftLeft(big_decimal *num, int shift);
void print_decimal(big_decimal num);
int bigDecimalIsLess(big_decimal value1, big_decimal value2);
int bigDecimalIsGreater(big_decimal value1, big_decimal value2);
int mulToBigDecimal(big_decimal value1, big_decimal value2,
                     big_decimal *result);
void alignmentExp(big_decimal *value1, big_decimal *value2);
void toBigDecimal(s21_decimal value1, big_decimal *bigValue1);
bit_t fromBigDecimal(big_decimal bigValue, s21_decimal *value);
void truncateZeroesAtTheEndAfterExp(big_decimal *value);
int shiftRight(big_decimal *num, int shift);
int longDivision(big_decimal value1, big_decimal value2, big_decimal *result);
void s21_set_sign(s21_decimal *dst);
void setSign_(s21_decimal *value, bit_t sign);
void s21_set_scale(s21_decimal *dst, int scale);
/*------------------------------- Decimal  ------------------------------ */

void s21_zero_decimal(s21_decimal *dst);
float s21_rand_r(float a, float b);
int s21_is_decimal_no_empty(s21_decimal dst);
void s21_zero_decimal(s21_decimal *dst);
void s21_import_to_small_decimal(s21_decimal *value_1, big_decimal value_2);
void s21_add_big_decimal(big_decimal value_1, big_decimal value_2, big_decimal *result);
void s21_set_bit(s21_decimal *dst, int index, int bit);


#endif