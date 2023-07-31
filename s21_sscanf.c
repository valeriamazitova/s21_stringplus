
#include "s21_string.h"

int is_number(char c) {
  int answer = 0;
  char numbers[] = "0123456789\0";
  int i = 0;
  int not_stopped = 1;
  while (numbers[i] != '\0' && not_stopped) {
    if (c == numbers[i]) {
      answer = 1;
      not_stopped = 0;
    }
    i++;
  }
  return answer;
}

long long int s21_atoi(char *s) {
  long long int i, n = 0;
  for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i) n = 10 * n + (s[i] - '0');
  return n;
}

long double s21_atof(char *s) {
  long double a = 0.0;
  int e = 0;
  int c;
  while ((c = *s++) != '\0' && is_number(c)) {
    a = a * 10.0 + (c - '0');
  }
  if (c == '.') {
    while ((c = *s++) != '\0' && is_number(c)) {
      a = a * 10.0 + (c - '0');
      e = e - 1;
    }
  }
  if (c == 'e' || c == 'E') {
    int sign = 1;
    int i = 0;
    c = *s++;
    if (c == '+')
      c = *s++;
    else if (c == '-') {
      c = *s++;
      sign = -1;
    }
    while (is_number(c)) {
      i = i * 10 + (c - '0');
      c = *s++;
    }
    e += i * sign;
  }
  while (e > 0) {
    a *= 10.0;
    e--;
  }
  while (e < 0) {
    a *= 0.1;
    e++;
  }
  return a;
}

void get_int_from_string(const char *str, int *pos, va_list args,
                         int *n_specifier, int *scanned_variables,
                         int *no_error, struct format_modifier fm) {
  char tmp[BUFF_SIZE] = {0};
  int tmp_i = 0;
  int end_pos = *pos;
  int str_i = *pos + tmp_i;
  int is_negative = 0;
  skip_spaces(str, &str_i);
  int w_count = 0;
  if (str[str_i] == '+' || str[str_i] == '-') {
    if (str[str_i] == '-') is_negative = 1;
    str_i++;
    w_count++;
  }
  while (is_number(str[str_i]) && (fm.width == -1 || w_count < fm.width)) {
    w_count++;
    tmp[tmp_i] = str[str_i++];
    tmp_i++;
    end_pos = str_i;
  }
  if (s21_strcmp(tmp, "") == 0 || (str_i == *pos && !is_negative) ||
      (str_i == *pos + 1 && is_negative)) {
    *no_error = 0;
  } else {
    if (fm.star != 1) {
      long long int lld = s21_atoi(tmp);
      write_scanned_variable_to_int(fm, args, lld, is_negative);
      (*scanned_variables)++;
    }
    *pos = *n_specifier = end_pos;
  }
}

int case_science_notation(const char *str, int *str_i, int *end_pos,
                          int *no_error) {
  int n = 0;
  // после Е должна быть степень 10
  int start_pos = *str_i;
  char exponent[10] = {0};
  int exp_i = 0;
  int is_negative = 0;
  if (str[*str_i] == '-') {
    is_negative = 1;
    (*str_i)++;
  }
  while (is_number(str[*str_i]) || str[*str_i] == '+') {
    if (str[*str_i] == '+')
      (*str_i)++;
    else {
      exponent[exp_i] = str[(*str_i)++];
      exp_i++;
      *end_pos = *str_i;
    }
  }
  if ((*str_i == start_pos && !is_negative) ||
      (*str_i == start_pos + 1 && is_negative))
    *no_error = 0;
  else {
    n = s21_atoi(exponent);
    if (is_negative) n = -n;
  }
  return n;
}

void write_to_float(va_list args, const long double *base, int is_notation,
                    int n, int is_negative) {
  float *f = va_arg(args, float *);
  if (is_notation) {
    *f = (float)(*base) * pow(10, n);
  } else
    *f = (float)(*base);
  if (is_negative) *f = -(*f);
}

void write_to_double(va_list args, const long double *base, int is_notation,
                     int n, int is_negative) {
  double *d = va_arg(args, double *);
  if (is_notation) {
    *d = (double)(*base) * pow(10, n);
  } else
    *d = (double)(*base);
  if (is_negative) *d = -(*d);
}

void write_to_long_double(va_list args, const long double *base,
                          int is_notation, int n, int is_negative) {
  long double *ld = va_arg(args, long double *);
  if (is_notation) {
    *ld = *base * pow(10, n);
  } else
    *ld = *base;
  if (is_negative) *ld = -(*ld);
}

void get_float_from_string(const char *str, int *str_i, int pos,
                           struct format_modifier fm, char *tmp, int *end_pos) {
  int tmp_i = 0;
  while ((is_number(str[*str_i]) || (str[*str_i] == '.' && *str_i != pos)) &&
         (fm.width == -1 || tmp_i < fm.width)) {
    tmp[tmp_i] = str[*str_i];
    tmp_i++;
    (*str_i)++;
    *end_pos = *str_i;
  }
}

char to_lower_(char c) {
  char new_c;
  if (c >= 'A' && c <= 'Z') {
    new_c = (int)c + 32;
  } else {
    new_c = c;
  }
  return new_c;
}

long double is_nan_or_inf(char *tmp, const char *str, int *str_i,
                          int *end_pos) {
  long double result = 0;
  int tmp_i = 0;
  while ((s21_strchr("nNaAiIFf", str[*str_i]) != s21_NULL) &&
         (str[*str_i] != '\0')) {
    tmp[tmp_i] = str[*str_i];
    tmp_i++;
    (*str_i)++;
    *end_pos = *str_i;
  }
  tmp[tmp_i] = '\0';
  for (int i = 0; tmp[i] != '\0'; i++) {
    if (tmp[i] != '\0') tmp[i] = to_lower_(tmp[i]);
  }
  if (s21_strcmp(tmp, "nan") == 0) {
    result = s21_NAN;
  } else if (s21_strcmp(tmp, "inf") == 0)
    result = s21_INF;
  return result;
}

void float_specifier(const char *str, int *pos, va_list args, int *n_specifier,
                     int *scanned_variables, int *no_error,
                     struct format_modifier fm) {
  char tmp[BUFF_SIZE] = {0};
  int end_pos = *pos;
  int str_i = *pos;
  int is_negative = 0;
  skip_spaces(str, &str_i);
  long double base = 0;
  int is_notation = 0;
  int n = 0;
  if ((base = is_nan_or_inf(tmp, str, &str_i, &end_pos)) == 0) {
    if (str[str_i] == '-' || str[str_i] == '+') {
      if (str[str_i] == '-') is_negative = 1;
      str_i++;
    }
    get_float_from_string(str, &str_i, *pos, fm, tmp, &end_pos);
    if (s21_strcmp(tmp, "") == 0 || (str_i == *pos && !is_negative) ||
        (str_i == *pos + 1 && is_negative))
      *no_error = 0;
    else {
      if (str[str_i] == 'E' || str[str_i] == 'e') {  // значит у нас нотация
        str_i++;  // переходим к следующему символу
        is_notation = 1;
        n = case_science_notation(str, &str_i, &end_pos, no_error);
      }
    }
  }
  if (*no_error) {
    if (fm.star != 1) {
      if (base == 0) base = s21_atof(tmp);
      if (fm.lenght == -1)
        write_to_float(args, &base, is_notation, n, is_negative);
      else if (fm.lenght == 2)
        write_to_double(args, &base, is_notation, n, is_negative);
      else if (fm.lenght == 3)
        write_to_long_double(args, &base, is_notation, n, is_negative);
      (*scanned_variables)++;
    }
    *pos = *n_specifier = end_pos;
  }
}

wchar_t *strcopy_to_wchar(wchar_t *dest, char *src) {
  for (int i = 0; src[i]; i++) {
    dest[i] = (unsigned char)src[i];
  }
  dest[s21_strlen(src)] = '\0';
  return dest;
}

void get_string_from_str(const char *str, int *pos, va_list args,
                         int *n_specifier, int *scanned_variables,
                         struct format_modifier fm) {
  char tmp[BUFF_SIZE] = {0};
  int tmp_i = 0;
  int end_pos = *pos;
  int str_i = *pos + tmp_i;
  skip_spaces(str, &str_i);
  while (str[str_i] != ' ' && str[str_i] != '\0' && str[str_i] != '\n' &&
         str[str_i] != '\t' && (fm.width == -1 || tmp_i < fm.width)) {
    tmp[tmp_i] = str[str_i++];
    tmp_i++;
    end_pos = str_i;
  }
  if (fm.star != 1) {
    char *s = s21_NULL;
    wchar_t *ls = s21_NULL;
    if (fm.lenght == -1) {
      s = va_arg(args, char *);
      s21_strcpy(s, tmp);
      s[s21_strlen(tmp)] = '\0';
    } else if (fm.lenght == 2) {
      ls = va_arg(args, wchar_t *);
      strcopy_to_wchar(ls, tmp);
    }
    (*scanned_variables)++;
  }
  *pos = *n_specifier = end_pos;
}

int is_suitable_for_16(char c) {
  int answer = 0;
  char numbers_in_16[] = "xAaBbCcDdEeFf\0";
  int i = 0;
  int not_stopped = 1;
  while (numbers_in_16[i] != '\0' && not_stopped) {
    if (c == numbers_in_16[i]) {
      answer = 1;
      not_stopped = 0;
    }
    i++;
  }
  return answer;
}

char to_upper_(char c) {
  char new_c;
  if (c >= 'a' && c <= 'z') {
    new_c = (int)c - 32;
  } else {
    new_c = c;
  }
  return new_c;
}

long long int hex_to_decimal(char *number_to_convert) {
  long long int s = 0;
  int k, p;
  p = (int)s21_strlen(number_to_convert) - 1;
  for (int i = 0; number_to_convert[i] != '\0'; i++) {
    switch (to_upper_(number_to_convert[i])) {
      case 'A':
        k = 10;
        break;
      case 'B':
        k = 11;
        break;
      case 'C':
        k = 12;
        break;
      case 'D':
        k = 13;
        break;
      case 'E':
        k = 14;
        break;
      case 'F':
        k = 15;
        break;
      case '0':
        k = 0;
        break;
      case '1':
        k = 1;
        break;
      case '2':
        k = 2;
        break;
      case '3':
        k = 3;
        break;
      case '4':
        k = 4;
        break;
      case '5':
        k = 5;
        break;
      case '6':
        k = 6;
        break;
      case '7':
        k = 7;
        break;
      case '8':
        k = 8;
        break;
      case '9':
        k = 9;
        break;
    }
    s += k * pow(16, p);
    p--;
  }
  return s;
}

long long int octal_to_decimal(char *number_to_convert) {
  long long int result = 0;
  int k;
  int size = (int)s21_strlen(number_to_convert) - 1;
  for (int i = 0; number_to_convert[i] != '\0'; i++) {
    //        int num = number_to_convert[i] - 48;
    switch (number_to_convert[i]) {
      case '0':
        k = 0;
        break;
      case '1':
        k = 1;
        break;
      case '2':
        k = 2;
        break;
      case '3':
        k = 3;
        break;
      case '4':
        k = 4;
        break;
      case '5':
        k = 5;
        break;
      case '6':
        k = 6;
        break;
      case '7':
        k = 7;
        break;
    }
    result += k * pow(8, size);
    size--;
  }
  return result;
}

void get_16_int_from_string(const char *str, int *str_i,
                            struct format_modifier fm, char *tmp, int *end_pos,
                            int *no_error) {
  int start_pos = *str_i;
  int tmp_i = 0;
  int w_count = 0;
  int x_count = 0;
  while ((is_number(str[*str_i]) || is_suitable_for_16(str[*str_i])) &&
         (fm.width == -1 || w_count < fm.width) && x_count <= 1) {
    w_count++;
    if (str[*str_i] == 'x') {
      (*str_i)++;
      x_count++;
    } else {
      tmp[tmp_i] = str[(*str_i)++];
      tmp_i++;
      *end_pos = *str_i;
    }
  }
  if (*end_pos == start_pos) *no_error = 0;
}

void write_scanned_variable_to_int(struct format_modifier fm, va_list args,
                                   long long int scanned_variable,
                                   int is_negative) {
  int *res = s21_NULL;
  long int *long_res = s21_NULL;
  long long int *ll_res = s21_NULL;
  if (fm.lenght == 1) {
    short int *tmp_short_d = va_arg(args, short int *);
    res = (int *)tmp_short_d;
  } else if (fm.lenght == -1) {
    int *tmp_int_d = va_arg(args, int *);
    res = (int *)tmp_int_d;
  } else if (fm.lenght == 2) {
    long int *tmp_long = va_arg(args, long int *);
    long_res = tmp_long;
  } else if (fm.lenght == 4) {
    long long *tmp_ll = va_arg(args, long long int *);
    ll_res = tmp_ll;
  }
  if ((fm.specifier == 'x' || fm.specifier == 'o') && is_negative) {
    if (fm.lenght == 4)
      *ll_res = (unsigned long long int)(-scanned_variable);
    else if (fm.lenght == 2)
      *long_res = (unsigned long int)(-scanned_variable);
    else
      *res = (unsigned int)(-scanned_variable);
  } else {
    if (fm.lenght == 4) {
      *ll_res = scanned_variable;
      if (is_negative) *ll_res = -(*ll_res);
    } else if (fm.lenght == 2) {
      *long_res = (long)scanned_variable;
      if (is_negative) *long_res = -(*long_res);
    } else {
      *res = (int)scanned_variable;
      if (is_negative) *res = -(*res);
      if (scanned_variable < -INT_MAX || scanned_variable > INT_MAX) *res = -1;
    }
  }
}

void get_hex_or_octal_from_string(char mode, const char *str, int *pos,
                                  va_list args, int *n_specifier,
                                  int *scanned_variables,
                                  struct format_modifier fm, int *no_error) {
  char tmp[BUFF_SIZE] = {0};
  int end_pos = *pos;
  int str_i = *pos;
  int is_negative = 0;
  skip_spaces(str, &str_i);
  if (str[str_i] == '-') {
    is_negative = 1;
    str_i++;
  }
  if (mode == 'h')
    get_16_int_from_string(str, &str_i, fm, tmp, &end_pos, no_error);
  else if (mode == 'o')
    get_8_int_from_string(str, &str_i, fm, tmp, &end_pos, no_error);
  if (*no_error) {
    if (fm.star != 1) {
      long long int d = 0;
      if (mode == 'h')
        d = hex_to_decimal(tmp);
      else if (mode == 'o')
        d = octal_to_decimal(tmp);
      write_scanned_variable_to_int(fm, args, d, is_negative);
      (*scanned_variables)++;
    }
    *pos = *n_specifier = end_pos;
  }
}

void get_8_int_from_string(const char *str, int *str_i,
                           struct format_modifier fm, char *tmp, int *end_pos,
                           int *no_error) {
  int start_pos = *str_i;
  int tmp_i = 0;
  while (is_number(str[*str_i]) && str[*str_i] >= 48 && str[*str_i] <= 55 &&
         (fm.width == -1 || tmp_i < fm.width)) {
    // принимаем здесь числа только от 0 до 7
    tmp[tmp_i] = str[(*str_i)++];
    tmp_i++;
  }
  *end_pos = *str_i;
  if (*end_pos == start_pos) *no_error = 0;
}

char is_hexadecimal_or_octal(const char *str, int str_i) {
  int is_hexadecimal = 0;
  int is_octal = 0;
  skip_spaces(str, &str_i);
  if (str[str_i] == '0') {
    is_octal = 1;
    if (str[str_i + 1] == 'x' || str[str_i + 1] == 'X') {
      is_hexadecimal = 1;
      is_octal = 0;
    }
  }
  char res = '\0';
  if (is_octal)
    res = 'o';
  else if (is_hexadecimal)
    res = 'h';
  return res;
}

void get_char_from_str(struct format_modifier fm, va_list args,
                       const char *str_copy, int *str_i, int *n_specifier,
                       int *scanned_variables) {
  if (fm.star != 1) {
    char *tmp_c = s21_NULL;
    wchar_t *tmp_lc = s21_NULL;
    if (fm.lenght == -1) {
      tmp_c = (char *)va_arg(args, char *);
      *tmp_c = str_copy[(*str_i)++];
    } else if (fm.lenght == 2) {
      tmp_lc = va_arg(args, wchar_t *);
      *tmp_lc = (unsigned char)str_copy[(*str_i)++];
    }
    *n_specifier = *str_i;
    (*scanned_variables)++;
  } else
    *n_specifier = (*str_i)++;
  if (fm.width != -1) {
    int count = 0;
    while (count < fm.width) {
      *n_specifier = *str_i;
      (*str_i)++;
      count++;
    }
  }
}

void process_specifier(const char *str_copy, struct format_modifier fm,
                       va_list args, int *n_specifier, int *str_i,
                       int *scanned_variables, int *no_error) {
  if (fm.specifier == 'c') {
    get_char_from_str(fm, args, str_copy, str_i, n_specifier,
                      scanned_variables);
  } else if (fm.specifier == 'd' || fm.specifier == 'u') {
    get_int_from_string(str_copy, str_i, args, n_specifier, scanned_variables,
                        no_error, fm);
  } else if ((s21_strchr("feEgG", fm.specifier) != s21_NULL)) {
    float_specifier(str_copy, str_i, args, n_specifier, scanned_variables,
                    no_error, fm);
  } else if (fm.specifier == 's') {
    get_string_from_str(str_copy, str_i, args, n_specifier, scanned_variables,
                        fm);
  } else if (fm.specifier == 'i') {
    char variable_case = is_hexadecimal_or_octal(str_copy, *str_i);
    if (variable_case == 'h' || variable_case == 'o') {
      get_hex_or_octal_from_string(variable_case, str_copy, str_i, args,
                                   n_specifier, scanned_variables, fm,
                                   no_error);
    } else
      get_int_from_string(str_copy, str_i, args, n_specifier, scanned_variables,
                          no_error, fm);
  } else if (fm.specifier == 'o') {  // Беззнаковое восьмеричное число
    get_hex_or_octal_from_string('o', str_copy, str_i, args, n_specifier,
                                 scanned_variables, fm, no_error);
  } else if (s21_strchr("xXp", fm.specifier) != s21_NULL) {
    get_hex_or_octal_from_string('h', str_copy, str_i, args, n_specifier,
                                 scanned_variables, fm, no_error);
  } else if (fm.specifier == 'n') {
    int *res = va_arg(args, int *);
    *res = *n_specifier;
  }
}

void create_struct(struct format_modifier *formatModifier, const char *format,
                   int i, int *no_error) {
  if (format[++i] == '*') {
    formatModifier->star = 1;
    i++;
  }
  if (!is_number(format[i]) &&
      s21_strchr("hlLcdieEfgGosuxXpn", format[i]) == s21_NULL)
    *no_error = 0;
  else {
    if (is_number(format[i])) {
      char tmp[BUFF_SIZE] = {0};
      int tmp_i = 0;
      while (is_number(format[i])) {
        tmp[tmp_i] = format[i];
        tmp_i++;
        i++;
      }
      tmp[tmp_i] = '\0';
      formatModifier->width = s21_atoi(tmp);
    }
    if (formatModifier->width == 0) *no_error = 0;
    if (format[i] == 'h') {
      formatModifier->lenght = 1;
      i++;  // short
    } else if (format[i] == 'l') {
      formatModifier->lenght = 2;
      i++;  // long
      if (format[i] == 'l') {
        formatModifier->lenght = 4;
        i++;  // long long
      }
    } else if (format[i] == 'L') {
      formatModifier->lenght = 3;
      i++;  // long double
    }
    if (s21_strchr("cdieEfgGosuxXpn", format[i]) != s21_NULL)
      formatModifier->specifier = format[i];
    else
      *no_error = 0;
    if ((formatModifier->lenght == 1 &&
         s21_strchr("idouxX", formatModifier->specifier) == s21_NULL) ||
        (formatModifier->lenght == 2 &&
         s21_strchr("csfidouxX", formatModifier->specifier) == s21_NULL) ||
        (formatModifier->lenght == 3 &&
         s21_strchr("eEfgG", formatModifier->specifier) == s21_NULL))
      *no_error = 0;
  }
}

int is_an_empty_string(const char *str) {
  int is_empty = 0;
  if (s21_strcmp(str, "") == 0)
    is_empty = 1;
  else {
    int i = 0;
    while (str[i] == ' ') i++;
    if (str[i] == '\0') is_empty = 1;
  }
  return is_empty;
}

void skip_spaces(const char *str, int *str_i) {
  while (str[*str_i] == ' ' || str[*str_i] == '\n' || str[*str_i] == '\t')
    (*str_i)++;
}

void remove_repetitions(const char *format, const char *str_copy, int *i,
                        int *str_i, int *no_error) {
  while (format[*i] == str_copy[*str_i]) {
    (*i)++;
    (*str_i)++;
  }
  if (is_number(str_copy[*str_i]) && format[*i] != '%') *no_error = 0;
  (*i)--;
}

int s21_sscanf(const char *str, const char *format, ...) {
  char str_copy[BUFF_SIZE] = {0};
  s21_strcpy(str_copy, str);
  int num_args = s21_strlen(format);
  va_list args;
  va_start(args, format);
  int scanned_variables = 0;
  int no_error = 1;
  int str_i = 0;
  int n_specifier = 0;
  if (is_an_empty_string(str_copy)) {
    scanned_variables = -1;
  } else {
    for (int i = 0; i < num_args && no_error; i++) {
      if (format[i] == '%') {
        if (format[i + 1] != '%') {
          struct format_modifier fm = {-1, -1, -1, '\0'};
          create_struct(&fm, format, i, &no_error);
          process_specifier(str, fm, args, &n_specifier, &str_i,
                            &scanned_variables, &no_error);
        } else {
          remove_repetitions(format, str_copy, &i, &str_i, &no_error);
          if (format[i + 1] != '%')
            i += 2;
          else
            i++;
        }
      } else if (format[i] == ' ') {
        skip_spaces(str_copy, &str_i);
        n_specifier = str_i;
      } else if (format[i] == str_copy[str_i] &&
                 s21_strchr("%*", format[i - 1]) == s21_NULL) {
        remove_repetitions(format, str_copy, &i, &str_i, &no_error);
      }
    }
  }
  va_end(args);
  return scanned_variables;
}
