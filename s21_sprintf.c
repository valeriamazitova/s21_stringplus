#include "s21_sprintf.h"

int s21_sprintf(char *s, char *fmt, ...) {
  va_list ap;
  flag num = {0};
  int t = 0, length = s21_strlen(fmt);
  char tmp[500] = {'\0'};
  va_start(ap, fmt);
  for (int j = 0; j < length; j++, fmt++) {
    if (*fmt == '%') {
      num.process++;
    }
    if (num.process) {
      parser(fmt, tmp, &ap, &num);
      if (!num.flag_precision) {
        flag_width(fmt, &num);
      }
    }
    if ((*fmt != '\0' && *fmt != '%' && !num.process) || num.process == 2) {
      tmp[num.posBuff++] = *fmt;
      num.flagReset = 1;
    }
    if (num.flagReset) {
      int posBuff = num.posBuff;
      s21_memset(&num, 0, sizeof(num));
      num.posBuff = posBuff;
    }
  }
  va_end(ap);
  int lengthStr = s21_strlen(tmp);
  while (lengthStr--) {
    s[t] = tmp[t];
    t++;
  }
  s[t] = '\0';
  return (int)s21_strlen(s);
}

void flag_null(char *fmt, flag *num) {
  char ch[40] = {'\0'};
  int i = 0, numbNull = 0;
  if (!num->flag_width && !num->flag_null && !num->flag_precision) {
    while ((*fmt > 47 && *fmt < 58) || *fmt == '#') {
      if (*fmt > 47 && *fmt < 58) {
        ch[i] = *fmt;
        i++;
      }
      fmt++;
    }
    numbNull = s21_atoi_sprintf(ch);
    num->amountNull = numbNull;
    num->flag_null = 1;
  }
}

int round_int(int numb, int charRound) {
  int lastChar = 0, temp = numb;
  int countChar = 0, countDiff = 0;
  if (numb < 0) {
    numb *= -1;
  }
  while (temp > 0) {
    temp = temp / 10;
    countChar++;
  }
  if (countChar > charRound) {
    countDiff = countChar - charRound;
    while (countDiff) {
      if (countDiff == 1) {
        lastChar = numb % 10;
      }
      numb /= 10;
      countDiff--;
    }
  }
  if (lastChar > 4) {
    numb += 1;
  }
  if (charRound < countChar) {
    countDiff = countChar - charRound;
    while (countDiff) {
      numb *= 10;
      countDiff--;
    }
  }
  return numb;
}

char *double_to_char(double numb, char *dest, flag *num) {
  char *c = dest;
  int v = 0, numZero = 6, n = 0;
  long double right = 0, left = 0, rRight = 0;
  long long int leftInt = 0, rightInt = 0;
  left = (long int)numb;
  right = numb - (long int)numb;
  if (num->flag_precision) {
    flag_precision1(num, &n, &right);
  } else if (!num->flag_precision) {
    for (int i = 0; i < numZero; i++) {
      right *= 10;
    }
  }
  rRight = round(right);
  if (numb < 0) {
    rRight *= -1;
    left *= -1;
  }
  leftInt = (long int)left;
  rightInt = (long long int)rRight;
  if ((num->spec_G || num->spec_g) && num->amountСharNumbG > 6 &&
      !num->flag_precision) {
    rightInt = round_int(rightInt, 5);
    rightInt /= 10;
  }
  int amount = count_character_numb(rightInt);
  int copyAmount = amount;
  double_to_char3(num, &rightInt, &copyAmount, amount);
  if (rightInt == 0) {
    double_to_charcpek1(num, amount, &v, c, copyAmount);
  } else {
    double_to_charcpek2(num, amount, &v, c, &rightInt, numZero);
  }
  if ((!(num->flag_precision && num->precision == 0 && !num->flagSharp) &&
       !(num->amountСharNumbG == 6 && (num->spec_g || num->spec_G)) &&
       num->precision != 1) ||
      (!(num->flag_precision && num->precision == 0 && !num->flagSharp) &&
       !(num->spec_g || num->spec_G)) ||
      ((num->spec_g_low || num->spec_g || num->spec_E) && rightInt == 0 &&
       num->flagSharp) ||
      (num->spec_g && num->flag_precision &&
       num->amountСharNumbG < num->precision)) {
    c[v++] = '.';
  }
  while (leftInt > 9) {
    c[v++] = (leftInt % 10) + '0';
    leftInt = leftInt / 10;
  }
  c[v++] = leftInt + '0';
  c[v] = '\0';
  char t;
  for (int i = 0; i < v / 2; i++) {
    t = c[i];
    c[i] = c[v - 1 - i];
    c[v - 1 - i] = t;
  }
  return c;
}

void double_to_char3(flag *num, long long int *rightInt, int *copyAmount,
                     int amount) {
  if ((num->spec_g || num->spec_G) && !num->flag_precision &&
      num->amountСharNumbG < 7 && num->amountСharNumbG >= 1) {
    int count = num->amountСharNumbG;
    while (count) {
      *rightInt = *rightInt / 10;
      count--;
    }
  } else if (((num->spec_g || num->spec_G) && !num->spec_e &&
              !num->flag_precision && num->amountСharNumbG != 0) ||
             (num->spec_g_low && !num->flag_precision)) {
    while (*rightInt % 10 == 0 && *copyAmount) {
      *rightInt = *rightInt / 10;
      *copyAmount = *copyAmount - 1;
    }
  } else if ((num->spec_g || num->spec_G) && num->flag_precision &&
             (num->amountСharNumbG + amount) > num->precision && !num->spec_e &&
             !num->spec_E) {
    int count = num->amountСharNumbG + amount - num->precision;
    while (count) {
      *rightInt = *rightInt / 10;
      count--;
    }
  } else if ((num->spec_g || num->spec_G) && num->spec_g_low &&
             !num->flag_precision) {
    while (*rightInt % 10 == 0 && *copyAmount) {
      *rightInt = *rightInt / 10;
      *copyAmount = *copyAmount - 1;
    }
  } else if ((num->spec_g || num->spec_G) && num->spec_g_low &&
             num->flag_precision && !num->flagSharp) {
    while (*rightInt % 10 == 0 && *copyAmount) {
      *rightInt = *rightInt / 10;
      *copyAmount = *copyAmount - 1;
    }
  }
}

void double_to_charcpek2(flag *num, int amount, int *v, char *c,
                         long long int *rightInt, int numZero) {
  if ((!num->spec_g && !num->spec_G && num->flag_precision &&
       amount != num->precision && !num->spec_g_low) ||
      (!num->spec_g && !num->spec_G &&
       !(amount == numZero && num->spec_g_low))) {
    int d = 0;
    if (amount != numZero &&
        !(num->flag_precision && !num->spec_g && !num->spec_G)) {
      d = numZero - amount;
    } else if (num->spec_g_low && !num->flag_precision) {
      d = 5;
    }
    while (d--) {
      c[*v] = '0';
      *v = *v + 1;
    }
  }
  while (*rightInt > 9) {
    c[*v] = (*rightInt % 10) + '0';
    *v = *v + 1;
    *rightInt = *rightInt / 10;
  }
  if (!(num->spec_g_low && *rightInt == 0) &&
      !(num->spec_g && *rightInt == 0) && !(num->spec_G && *rightInt == 0)) {
    c[*v] = *rightInt + '0';
    *v = *v + 1;
  }
  if (num->flag_precision && !num->spec_g && !num->spec_G) {
    int n = num->precision - amount;
    while (n--) {
      c[*v] = '0';
      *v = *v + 1;
    }
  }
}

void double_to_charcpek1(flag *num, int amount, int *v, char *c,
                         int copyAmount) {
  if ((num->spec_g_low || num->spec_g || num->spec_G) && num->flagSharp) {
    int b = 6;
    if (num->flag_precision) {
      b = num->precision - amount;
    } else if ((num->spec_g_low || num->spec_g || num->spec_G) &&
               num->flagSharp) {
      b = 4;
    } else if (num->spec_g_low && copyAmount == 0) {
      b = 0;
    }
    if (b > 0) {
      while (b--) {
        c[*v] = '0';
        *v = *v + 1;
      }
    }
  }
}

void flag_precision1(flag *num, int *n, long double *right) {
  if (num->spec_g_low) {
    *n = -1;
  } else if ((num->spec_g || num->spec_G) && !num->spec_e && !num->spec_E) {
    *n = -2;
  } else if ((num->spec_g || num->spec_G) && (num->spec_e || num->spec_E)) {
    *n = -1;
  }
  for (int i = 0; i < num->precision + *n; i++) {
    *right = *right * 10;
  }
}

void print_flags(char *buffer, va_list ap, flag *num) {
  long long int numb = 0;
  if (num->length_l == 1) {
    numb = va_arg(ap, long int);
  } else if (num->length_l == 2) {
    numb = va_arg(ap, long long int);
  } else {
    numb = va_arg(ap, int);
  }
  int k = 0, addNull = 0, addSpace = 0, addNullPoint = 0;
  char number[30] = {'\0'};
  int_to_char(numb, number);
  if (num->flagPlus) k = 1;
  if (num->precision > (int)s21_strlen(number))
    addNullPoint = num->precision - (int)s21_strlen(number);
  addSpace = num->width - (int)s21_strlen(number) - k - addNullPoint;
  addNull = num->amountNull - (int)s21_strlen(number) - k;
  print_flags_now(num, numb, number, addSpace, buffer, addNull, addNullPoint);
  num->flagReset = 1;
}

void print_flags_now(flag *num, int numb, char *number, int addSpace,
                     char *buffer, int addNull, int addNullPoint) {
  if (num->flag_width && !num->flag_null && !num->flagMinus &&
      (int)s21_strlen(number) < num->width) {
    for (int i = 0; i < addSpace; i++) {
      buffer[num->posBuff++] = ' ';
    }
  }
  if (numb >= 0 && num->flagPlus) {
    buffer[num->posBuff++] = '+';
  } else if (numb < 0) {
    buffer[num->posBuff++] = '-';
  }
  if ((int)s21_strlen(number) < num->amountNull) {
    for (int i = 0; i < addNull; i++) {
      buffer[num->posBuff++] = '0';
    }
  }
  if ((int)s21_strlen(number) < num->precision) {
    for (int i = 0; i < addNullPoint; i++) {
      buffer[num->posBuff++] = '0';
    }
  }
  if (num->spec_o && num->flagSharp) {
    buffer[num->posBuff++] = '0';
  }
  for (int i = 0; i < (int)s21_strlen(number); i++) {
    buffer[num->posBuff++] = number[i];
  }
  if (num->flagMinus && (int)s21_strlen(number) < num->width) {
    for (int i = 0; i < addSpace; i++) {
      buffer[num->posBuff++] = ' ';
    }
  }
}

void print_flags_unsigned(char *buffer, va_list ap, flag *num) {
  uint64_t numb = va_arg(ap, uint64_t);
  if (num->length_h) {
    numb = (uint16_t)numb;
  } else if (num->length_l || num->spec_o) {
    numb = (uint64_t)numb;
  } else {
    numb = (uint32_t)numb;
  }
  int k = 0, addNull = 0, addSpace = 0, addNullPoint = 0, prefix = 0;
  char number[15] = {'\0'};
  if (num->spec_o) {
    numb = dex_To_Octal(numb);
    int_to_char_unsigned(numb, number);
  } else if (num->spec_x) {
    dev_To_Hex(numb, number, 1);
  } else if (num->spec_X) {
    dev_To_Hex(numb, number, 0);
  } else {
    int_to_char_unsigned(numb, number);
  }
  if (num->flagPlus) k = 1;
  if (num->flagSharp && num->spec_o) {
    prefix = 1;
  } else {
    prefix = 2;
  }
  if (num->flagSharp && num->spec_o &&
      num->precision > (int)s21_strlen(number) + k) {
    addNullPoint = num->precision - k - (int)s21_strlen(number) - prefix;
  } else if (num->precision > (int)s21_strlen(number)) {
    addNullPoint = num->precision - (int)s21_strlen(number) - k;
  }
  if (num->flagSharp && (num->spec_o || num->spec_X || num->spec_x)) {
    addSpace = num->width - (int)s21_strlen(number) - k - prefix - addNullPoint;
  } else {
    addSpace = num->width - (int)s21_strlen(number) - k - addNullPoint;
  }
  addNull = num->amountNull - (int)s21_strlen(number) - k;
  print_flags_unsignednow(num, number, addSpace, buffer, addNull, addNullPoint);
  num->flagReset = 1;
}

void print_flags_unsignednow(flag *num, char *number, int addSpace,
                             char *buffer, int addNull, int addNullPoint) {
  if (num->flag_width && !num->flag_null && !num->flagMinus &&
      (int)s21_strlen(number) < num->width) {
    for (int i = 0; i < addSpace; i++) {
      buffer[num->posBuff++] = ' ';
    }
  }
  if (num->flagPlus) {
    buffer[num->posBuff++] = '+';
  }
  if (num->spec_x && num->flagSharp) {
    buffer[num->posBuff++] = '0';
    buffer[num->posBuff++] = 'x';
  }
  if (num->spec_X && num->flagSharp) {
    buffer[num->posBuff++] = '0';
    buffer[num->posBuff++] = 'X';
  }
  if ((int)s21_strlen(number) < num->amountNull) {
    for (int i = 0; i < addNull; i++) {
      buffer[num->posBuff++] = '0';
    }
  }
  if ((int)s21_strlen(number) < num->precision) {
    for (int i = 0; i < addNullPoint; i++) {
      buffer[num->posBuff++] = '0';
    }
  }
  if (num->spec_o && num->flagSharp) {
    buffer[num->posBuff++] = '0';
  }
  for (int i = 0; i < (int)s21_strlen(number); i++) {
    buffer[num->posBuff++] = number[i];
  }
  if (num->flagMinus && (int)s21_strlen(number) < num->width) {
    for (int i = 0; i < addSpace; i++) {
      buffer[num->posBuff++] = ' ';
    }
  }
}

void print_flags_pointer(char *buffer, va_list ap, flag *num) {
  int addSpace = 0;
  char number[50] = {'\0'};
  void *numb = va_arg(ap, void *);
  dev_To_Hex((uint64_t)numb, number, 1);
  addSpace = num->width - (int)s21_strlen(number) - 2;
  if (num->flag_width && !num->flag_null && !num->flagMinus &&
      (int)s21_strlen(number) + 2 < num->width) {
    for (int i = 0; i < addSpace; i++) {
      buffer[num->posBuff++] = ' ';
    }
  }
  buffer[num->posBuff++] = '0';
  buffer[num->posBuff++] = 'x';
  for (int i = 0; i < (int)s21_strlen(number); i++) {
    buffer[num->posBuff++] = number[i];
  }
  if (num->flagMinus && (int)s21_strlen(number) + 2 < num->width) {
    for (int i = 0; i < addSpace; i++) {
      buffer[num->posBuff++] = ' ';
    }
  }
  num->flagReset = 1;
}

void print_flags_double(char *buffer, va_list ap, flag *num) {
  long double numb = 0;
  if (num->length_L) {
    numb = va_arg(ap, long double);
  } else {
    numb = va_arg(ap, double);
  }
  num->amountСharNumbG = count_char_specificator_G(numb);
  int addNull = 0, addSpace = 0, flagNegative = 0, k = 0;
  char number[100] = {'\0'};
  specificator_g_search(num, numb);
  if (numb < 0) {
    flagNegative = 1;
    k = 1;
  }
  if ((num->spec_g || num->spec_G || num->spec_g_low) && num->flag_precision &&
      num->precision < 2) {
    num->spec_e = 1;
  }
  if (num->spec_e || num->spec_E) {
    double numbSpecE = numb;
    num->degree_spec_e = count_char_specificator_E(&numbSpecE);
    if (num->flag_precision && num->precision == 0) {
      int temp = (int)(numbSpecE * 10);
      temp = round_int(temp, 1) / 10;
      number[0] = temp + '0';
      if (num->flagSharp) number[1] = '.';
    } else {
      double_to_char(numbSpecE, number, num);
    }
  } else {
    double_to_char(numb, number, num);
  }
  if (num->flagPlus && !(numb < 0)) k += 1;
  if ((num->spec_e || num->spec_E)) {
    addSpace = num->width - (int)s21_strlen(number) - k - 4;
  } else {
    addSpace = num->width - (int)s21_strlen(number) - k;
  }
  print_flags_double_e(num, &addNull, buffer, number, addSpace, k, numb,
                       flagNegative);

  num->flagReset = 1;
}

void specificator_g_search(flag *num, long double numb) {
  if (num->spec_g && numb < 0.0001 && numb > 0) {
    num->spec_e = 1;
    num->spec_g_low = 1;
  } else if (num->spec_G && numb < 0.0001 && numb > 0) {
    num->spec_E = 1;
    num->spec_g_low = 1;
  } else if (num->spec_g && num->amountСharNumbG > 6 && !num->flag_precision) {
    num->spec_e = 1;
  } else if (num->spec_g && num->amountСharNumbG > num->precision &&
             num->flag_precision) {
    num->spec_e = 1;
  } else if (num->spec_G && num->amountСharNumbG > 6 && !num->flag_precision) {
    num->spec_E = 1;
  } else if (num->spec_G && num->amountСharNumbG > num->precision &&
             num->flag_precision) {
    num->spec_E = 1;
  }
}

void flag_double_specificator_g(flag *num, char *number, char *buffer) {
  int count = (int)s21_strlen(number);
  if (count > 7 && !num->flag_precision && num->amountСharNumbG != 0) {
    count = 7;
  } else if (num->flag_precision && (int)s21_strlen(number) > num->precision) {
    count = num->precision + 1;
  }
  for (int i = 0; i < count; i++) {
    buffer[num->posBuff++] = number[i];
    if (!num->flagSharp && num->amountСharNumbG == 6 && i == 5 &&
        num->precision < 7) {
      i++;
    }
  }
}

void print_flags_double_e(flag *num, int *addNull, char *buffer, char *number,
                          int addSpace, int k, long double numb,
                          int flagNegative) {
  if (num->spec_e || num->spec_E) {
    *addNull = num->amountNull - (int)s21_strlen(number) - k - 4;
  } else if ((num->spec_g || num->spec_G) && num->amountСharNumbG < 7 &&
             num->amountСharNumbG >= 1 && !num->flag_precision) {
    *addNull = num->amountNull - 7 - k;
  } else {
    *addNull = num->amountNull - (int)s21_strlen(number) - k;
  }
  if (num->flag_width && !num->flag_null && !num->flagMinus) {
    if ((int)s21_strlen(number) + k < num->width) {
      for (int i = 0; i < addSpace; i++) {
        buffer[num->posBuff++] = ' ';
      }
    }
  }
  if (numb >= 0 && num->flagPlus) {
    buffer[num->posBuff++] = '+';
  } else if (numb < 0 || flagNegative) {
    buffer[num->posBuff++] = '-';
  }
  if (0 < num->amountNull) {
    for (int i = 0; i < *addNull; i++) {
      buffer[num->posBuff++] = '0';
    }
  }
  if (!num->spec_e && !num->spec_E && !num->spec_g && !num->spec_G) {
    for (int i = 0; i < (int)s21_strlen(number); i++) {
      buffer[num->posBuff++] = number[i];
    }
  }
  if ((num->spec_g || num->spec_G) && !num->spec_e && !num->spec_E) {
    flag_double_specificator_g(num, number, buffer);
  }
  if (num->spec_e || num->spec_E) {
    flag_double_specificator_e(num, number, buffer);
  }
  if (num->flagMinus && addSpace < num->width) {
    for (int i = 0; i < addSpace; i++) {
      buffer[num->posBuff++] = ' ';
    }
  }
}

void flag_double_specificator_e(flag *num, char *number, char *buffer) {
  int amount = (int)s21_strlen(number);
  if ((num->spec_g || num->spec_G) && num->amountСharNumbG > 6 &&
      !num->flag_precision && (int)s21_strlen(number) > 7) {
    amount = 7;
  } else if ((num->spec_g || num->spec_G) && num->flag_precision &&
             !num->flagSharp && (int)s21_strlen(number) > num->precision &&
             !num->spec_g_low) {
    amount = num->precision;
  } else if ((num->spec_g || num->spec_G) && num->flag_precision &&
             num->flagSharp && (int)s21_strlen(number) > num->precision) {
    amount = num->precision + 1;
    if (num->precision == 0) amount = 2;
  }
  for (int i = 0; i < amount; i++) {
    buffer[num->posBuff] = number[i];
    num->posBuff = num->posBuff + 1;
  }
  if (num->spec_E) {
    buffer[num->posBuff] = 'E';
    num->posBuff = num->posBuff + 1;
  } else if (num->spec_e) {
    buffer[num->posBuff] = 'e';
    num->posBuff = num->posBuff + 1;
  }
  if (num->degree_spec_e >= 0) {
    buffer[num->posBuff] = '+';
    num->posBuff = num->posBuff + 1;
    if (num->degree_spec_e < 10) {
      buffer[num->posBuff] = '0';
      num->posBuff = num->posBuff + 1;
    }
  } else {
    num->degree_spec_e *= -1;
    buffer[num->posBuff] = '-';
    num->posBuff = num->posBuff + 1;
    if (num->degree_spec_e < 10) {
      buffer[num->posBuff] = '0';
      num->posBuff = num->posBuff + 1;
    }
  }
  buffer[num->posBuff] = num->degree_spec_e + '0';
  num->posBuff = num->posBuff + 1;
}

void flag_width(char *fmt, flag *num) {
  if (!num->flag_width && !num->flag_null && !num->flag_precision &&
      *fmt > 48 && *fmt < 58) {
    char ch[40] = {'\0'};
    int width = 0, i = 0;
    while (*fmt > 47 && *fmt < 58) {
      ch[i] = *fmt;
      i++;
      fmt++;
    }
    width = s21_atoi_sprintf(ch);
    num->width = width;
    num->flag_width = 1;
  }
}

void flag_precision(char *fmt, flag *num) {
  char ch[40] = {'\0'};
  int i = 0, precision = 0;
  if (*fmt++ != '*') {
    while (*fmt > 47 && *fmt < 58) {
      ch[i] = *fmt;
      i++;
      fmt++;
    }
  }
  precision = s21_atoi_sprintf(ch);
  num->precision = precision;
  num->flag_precision = 1;
}

void specificator_n(char *buffer, va_list ap, flag *num) {
  int *n = va_arg(ap, int *);
  *n = (int)s21_strlen(buffer);
  num->flagReset = 1;
}

void charToBuffer(char *buffer, va_list ap, flag *num) {
  char c[6] = {'\0'};
  if (num->length_l) {
    wchar_t wh = va_arg(ap, wchar_t);
    wctomb(c, wh);
  } else {
    c[0] = (char)va_arg(ap, int);
  }
  int ind = num->posBuff, addSpace = 0;
  if (num->flagMinus) {
    buffer[ind] = c[0];
    num->posBuff++;
    ind++;
  }
  if (num->flag_width) {
    addSpace = num->width - 1;
    for (int i = 0; i < addSpace; i++) {
      buffer[ind] = ' ';
      ind++;
      num->posBuff++;
    }
  }
  if (!num->flagMinus) {
    buffer[ind] = c[0];
    num->posBuff++;
  }
  num->flagReset = 1;
}

void str_to_buffer(char *buffer, va_list ap, flag *num) {
  char temp[200] = {'\0'};
  char *s = temp;
  if (num->length_l) {
    wchar_t *wTemp = va_arg(ap, wchar_t *);
    wcstombs(temp, wTemp, sizeof(temp));
  } else {
    s = va_arg(ap, char *);
  }
  int ind = num->posBuff, addSpace = 0, length = s21_strlen(s);
  if (num->flag_precision && length > num->precision) {
    length = num->precision;
  }
  if (num->flagMinus) {
    for (int i = 0; i < length; i++) {
      buffer[ind] = s[i];
      num->posBuff++;
      ind++;
    }
  }
  if (num->flag_width) {
    addSpace = num->width - length;
    for (int i = 0; i < addSpace; i++) {
      buffer[ind] = ' ';
      ind++;
      num->posBuff++;
    }
  }
  if (!num->flagMinus) {
    for (int i = 0; i < length; i++) {
      buffer[ind] = s[i];
      num->posBuff++;
      ind++;
    }
  }
  num->flagReset = 1;
}
