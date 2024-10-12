#include "s21_decimal.h"

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "s21_helpers.h"

/* Signs are should be handled only inside of these functions !!! */

/*
  0 - OK
  1 - число слишком велико или равно бесконечности
  2 - число слишком мало или равно отрицательной бесконечности
  3 - деление на 0
*/
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal result_ = *result;
  int rv = 0;
  big_decimal bigValue1 = {}, bigValue2 = {}, bigResult = {};
  toBigDecimal(value_1, &bigValue1);
  toBigDecimal(value_2, &bigValue2);
  /* Need to truncate, if the values has view - 12.20 or 1.40,
   * but should has the - 12.2 and 1.4.
   * Or the view - 0.00 with an excess exponent */
  truncateZeroesAtTheEndAfterExp(&bigValue1);
  truncateZeroesAtTheEndAfterExp(&bigValue2);
  alignmentExp(&bigValue1, &bigValue2);

  helperSummSub(bigValue1, bigValue2, &bigResult);

  truncateZeroesAtTheEndAfterExp(&bigResult);
  rv = fromBigDecimal(bigResult, &result_);
  if (!rv) *result = result_;
  return rv;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal result_ = *result;
  int rv = 0;
  big_decimal bigValue1 = {}, bigValue2 = {}, bigResult = {};
  toBigDecimal(value_1, &bigValue1);
  toBigDecimal(value_2, &bigValue2);
  setSign(&bigValue1, !getSign(bigValue2));
  alignmentExp(&bigValue1, &bigValue2);
  helperSummSub(bigValue1, bigValue2, &bigResult);
  truncateZeroesAtTheEndAfterExp(&bigResult);
  rv = fromBigDecimal(bigResult, &result_);
  if (!rv) *result = result_;
  return rv;
}
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal result_ = *result;
  int error = 0, scale = 0;
  big_decimal v1 = {0}, v2 = {0}, r = {0};
  toBigDecimal(value_1, &v1);
  toBigDecimal(value_2, &v2);
  toBigDecimal(result_, &r);
  if (getSign(v1) != getSign(v2)) s21_set_sign(result);
  scale = s21_get_scale(value_1) + s21_get_scale(value_2);
  error = mulToBigDecimal(v1, v2, &r);
  scale = s21_post_normalization(&r, scale);
  if (scale >= 0) {
    s21_set_scale(result, scale);
    s21_import_to_small_decimal(result, r);
  } else {
    error = 1;
  }
  if (error == 1 && s21_get_sign(*result)) error = 2;
  if (error) s21_zero_decimal(result);
  return error;
}
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  if (s21_is_decimal_no_empty(value_2)) {
    int scale = 0, res_scale = 0;
    big_decimal v1 = {0}, v2 = {0}, r = {0};
    toBigDecimal(value_1, &v1);
    toBigDecimal(value_2, &v2);
    if (s21_get_sign(value_1) != s21_get_sign(value_2)) s21_set_sign(result);
    scale = longDivision(v1, v2, &r);
    s21_set_scale(&value_1, s21_get_scale(value_1) + scale);
    res_scale = s21_get_scale(value_1) - s21_get_scale(value_2);
    if (res_scale > 0) {
      res_scale = s21_post_normalization(&r, res_scale);
    } else if (res_scale < 0) {
      shiftRight(&r, abs(res_scale));
      res_scale = s21_post_normalization(&r, 0);
    }
    if (res_scale >= 0) {
      s21_import_to_small_decimal(result, r);
      s21_set_scale(result, res_scale);
    } else {
      error = 1;
    }
  } else {
    error = 3;
  }
  if (error == 1 && s21_get_sign(*result)) error = 2;
  if (error) s21_zero_decimal(result);
  return error;
}
/// @brief Пост нормализация для big decimal
/// @param result
/// @param scale
/// @return Число больше, равно или меньше нуля
int s21_post_normalization(big_decimal *result, int scale) {
  int dop = 0;
  while ((result->bits[3] || result->bits[4] || result->bits[5] ||
          result->bits[6] || result->bits[7]) &&
         scale > 0) {
    if (scale == 1 && result->bits[3]) dop = 1;
    shiftLeft(result, 1);
    scale--;
  }
  if (dop && scale == 0 && result->bits[3] == 0 && getBit(*result, 0))
    setBit(result, 0, 0);
  if ((result->bits[3] || result->bits[4] || result->bits[5] ||
       result->bits[6] || result->bits[7]))
    scale = -1;
  return scale;
}

int s21_get_sign(s21_decimal dst) { return (dst.bits[3] & 1u << 31) != 0; }