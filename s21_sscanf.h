#ifndef SRC_S21_SSCANF_H
#define SRC_S21_SSCANF_H

#include "s21_sprintf.h"
#include "s21_sscanf.h"
#include "s21_string.h"

struct format_modifier {
  int star;
  int width;
  int lenght;
  char specifier;
};

// scanf
int s21_sscanf(const char *str, const char *format, ...);
// ----- s21_sscanf additional functions -----
int is_number(char c);
long long int s21_atoi(char *s);
long double s21_atof(char *s);
void get_int_from_string(const char *str, int *pos, va_list args,
                         int *n_specifier, int *scanned_variables,
                         int *no_error, struct format_modifier fm);
int case_science_notation(const char *str, int *str_i, int *end_pos,
                          int *no_error);
void write_to_float(va_list args, const long double *base, int is_notation,
                    int n, int is_negative);
void write_to_double(va_list args, const long double *base, int is_notation,
                     int n, int is_negative);
void write_to_long_double(va_list args, const long double *base,
                          int is_notation, int n, int is_negative);
void get_float_from_string(const char *str, int *str_i, int pos,
                           struct format_modifier fm, char *tmp, int *end_pos);
char to_lower_(char c);
long double is_nan_or_inf(char *tmp, const char *str, int *str_i, int *end_pos);
void float_specifier(const char *str, int *pos, va_list args, int *n_specifier,
                     int *scanned_variables, int *no_error,
                     struct format_modifier fm);
wchar_t *strcopy_to_wchar(wchar_t *dest, char *src);
void get_string_from_str(const char *str, int *pos, va_list args,
                         int *n_specifier, int *scanned_variables,
                         struct format_modifier fm);
int is_suitable_for_16(char c);
char to_upper_(char c);
long long int hex_to_decimal(char *number_to_convert);
long long int octal_to_decimal(char *number_to_convert);
void write_scanned_variable_to_int(struct format_modifier fm, va_list args,
                                   long long int scanned_variable,
                                   int is_negative);
void get_hex_or_octal_from_string(char mode, const char *str, int *pos,
                                  va_list args, int *n_specifier,
                                  int *scanned_variables,
                                  struct format_modifier fm, int *no_error);
void get_16_int_from_string(const char *str, int *str_i,
                            struct format_modifier fm, char *tmp, int *end_pos,
                            int *no_error);
void get_8_int_from_string(const char *str, int *str_i,
                           struct format_modifier fm, char *tmp, int *end_pos,
                           int *no_error);
char is_hexadecimal_or_octal(const char *str, int str_i);
void get_char_from_str(struct format_modifier fm, va_list args,
                       const char *str_copy, int *str_i, int *n_specifier,
                       int *scanned_variables);
void create_struct(struct format_modifier *formatModifier, const char *format,
                   int i, int *no_error);
int is_an_empty_string(const char *str);
void skip_spaces(const char *str, int *str_i);
void process_specifier(const char *str_copy, struct format_modifier fm,
                       va_list args, int *n_specifier, int *str_i,
                       int *scanned_variables, int *no_error);

#endif  // SRC_S21_SSCANF_H
