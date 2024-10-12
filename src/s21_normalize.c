#include "s21_decimal.h"
#include "s21_helpers.h"
/// @brief Копирование d2 в d1
/// @param d1
/// @param d2
void s21_copy_decimal(s21_decimal *d1, s21_decimal d2) {
    s21_decimal first = *d1;
    big_decimal bigValue1 = {}, bigValue2 = {};
    toBigDecimal(first, &bigValue1);
    toBigDecimal(d2, &bigValue2);
  for (int i = 127; i >= 0; i--) {
    setBit(&bigValue1, i, getBit(bigValue2, i));
  }
}

/// @brief Повышение scale на norm
/// @param d
/// @param norm
void s21_normalize_scale_upper(s21_decimal *d, int norm) {
  s21_decimal _norm = {0};
  s21_decimal _res = {0};
  s21_from_float_to_decimal(pow(10, norm), &_norm);
  s21_mul(*d, _norm, &_res);
  s21_set_scale(&_res, s21_get_scale(*d) + norm);
  s21_copy_decimal(d, _res);
}

/// @brief Нормализация d1 d2 путем уравнения их scale
/// @param d1
/// @param d2
void s21_normalize(s21_decimal *d1, s21_decimal *d2) {
  int norm = s21_get_scale(*d1) - s21_get_scale(*d2);
  if (norm > 0) {
    s21_normalize_scale_upper(d2, norm);
  } else if (norm < 0) {
    s21_normalize_scale_upper(d1, -norm);
  }
}