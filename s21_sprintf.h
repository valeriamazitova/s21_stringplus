#ifndef SRC_S21_SPRINTF_H
#define SRC_S21_SPRINTF_H

#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>

#include "s21_sprintf.h"
#include "s21_sscanf.h"
#include "s21_string.h"

typedef struct {
  int amountNull;      // количество нулей в флаге Null
  int width;           // ширина во флаге
  int precision;       // точность положение точки
  int flag_null;       // флаг 0
  int flagMinus;       // флаг -
  int flagPlus;        // флаг +
  int flag_width;      // флаг ширина (число)
  int flag_precision;  // флаг точность
  int flagSharp;       // флаг #
  int spec_e;          // спецификатор е
  int spec_E;          // спецификатор Е
  int spec_g;          // спецификатор g
  int spec_g_low;  // маленькое число при спецификаторе G
  int spec_G;         // спецификатор G
  int spec_o;         // спецификатор o
  int spec_x;         // спецификатор x
  int spec_X;         // спецификатор X
  int spec_p;         // спецификатор p
  int length_h;       // длина h
  int length_l;       // длина l
  int length_L;       // длина L
  int degree_spec_e;  // степень флага Е
  int process;        // отработка печати
  int flagReset;  // флаг разрешения обнуления флагов
  int posBuff;    // позиция буффера
  int amountСharNumbG;
} flag;

// main
int s21_sprintf(char *str, char *fmt, ...);

// парсер
void parser(char *fmt, char *tmp, va_list *ap, flag *num);

// вспомогательная функция для отработки спецификатора g
void specificator_g_search(flag *num, long double numb);

// функция для отработки спецификатора g
void flag_double_specificator_g(flag *num, char *number, char *buffer);

// функция для отработки спецификатора e
void flag_double_specificator_e(flag *num, char *number, char *buffer);

void flag_precision1(flag *num, int *n, long double *right);

// перевод из char в int
int s21_atoi_sprintf(char *number);

// считывание количества нулей из форматной строки
void flag_null(char *fmt, flag *num);

// функция для счета количества знаков в целом числе
int count_character_numb(long long int numb);

// функция для счета количества знаков в целой части double при спецификаторе g
int count_char_specificator_G(double numb);

// функция для счета количества знаков в целой части double при спецификаторе e
int count_char_specificator_E(double *numb);

// перевод int в char
char *int_to_char(int64_t n, char *dest);

// перевод unsigned int в char
char *int_to_char_unsigned(uint64_t n, char *dest);

// функция для округления целого числа по заданной точности
int round_int(int numb, int charRound);

// перевод double в char
char *double_to_char(double numb, char *dest, flag *num);

// вспомогательные функции
void double_to_charcpek1(flag *num, int amount, int *v, char *c,
                         int copyAmount);

// вспомогательные функции
void double_to_charcpek2(flag *num, int amount, int *v, char *c,
                         long long int *rightInt, int numZero);

// вспомогательные функции
void double_to_char3(flag *num, long long int *rightInt, int *copyAmount,
                     int amount);

// перевод числа из дестиричной системы в восьмиричную
uint64_t dex_To_Octal(uint64_t numb);

// перевод числа из дестиричной системы в шестнадцетиричную
char *dev_To_Hex(uint64_t num, char *dest, int lettercase);

// подготовка для записи в буфер целого числа
void print_flags(char *buffer, va_list ap, flag *num);

// запись в буфер целого числа
void print_flags_now(flag *num, int numb, char *number, int addSpace,
                     char *buffer, int addNull, int addNullPoint);

// подготовка для записи в буфер беззнакового целого числа
void print_flags_unsigned(char *buffer, va_list ap, flag *num);

// запись в буфер беззнакового целого числа
void print_flags_unsignednow(flag *num, char *number, int addSpace,
                             char *buffer, int addNull, int addNullPoint);

// запись в буфер указателя
void print_flags_pointer(char *buffer, va_list ap, flag *num);

// запись в буфер числа c плавающей точкой
void print_flags_double(char *buffer, va_list ap, flag *num);

// запись в буфер числа c плавающей точкой флаг е
void print_flags_double_e(flag *num, int *addNull, char *buffer, char *number,
                          int addSpace, int k, long double numb,
                          int flagNegative);

// считывание ширины из форматной строки
void flag_width(char *fmt, flag *num);

// считывание точности из форматной строки
void flag_precision(char *fmt, flag *num);

// отработка спецификатора n
void specificator_n(char *buffer, va_list ap, flag *num);

// запись в буфер char
void charToBuffer(char *buffer, va_list ap, flag *num);

// запись в буфер string
void str_to_buffer(char *buffer, va_list ap, flag *num);

#endif  // SRC_S21_SPRINTF_H
