#ifndef SRC_s21_STRING_H_
#define SRC_s21_STRING_H_

#define s21_INF 1.0 / 0.0

#define s21_NULL \
  ((void *)0)  // Мы кастуем 0 в тип void* (пустой указатель), таким образом
               // указатель не имеет тип (т.к. он void) и указывает на ноль.
typedef long unsigned s21_size_t;
#define MAX_PRECISION (10)

#define s21_NAN 0.0 / 0.0
#define s21_INF 1.0 / 0.0

#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

#include "s21_sprintf.h"
#include "s21_sscanf.h"
#include "s21_string.h"

typedef long unsigned int s21_size_t;
typedef long long int s21_int64_t;

#define BUFF_SIZE 2094

// *string.h функции
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strcat(char *dest, const char *src);
// char *s21_strncat(char *dest, const char *src, int n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);

char *s21_strchr(const char *str, int c);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strcpy(char *dest, const char *src);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
s21_size_t s21_strspn(const char *str1, const char *str2);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

// Спец. ф-ии обработки строк (вдохновленные классом String в языке C#)
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

#endif  // SRC_s21_STRING_H_