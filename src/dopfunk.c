#include "s21_sprintf.h"

int s21_atoi_sprintf(char *number) {
  int a = 0, b = 0, res = 0, length = s21_strlen(number);
  while (length--) {
    a = number[b++] - '0';
    res += a;
    if (length != 0) res *= 10;
  }
  return res;
}

uint64_t dex_To_Octal(uint64_t numb) {
  uint64_t currentChar = 0, res = 0;
  int k = 1;
  while (numb > 0) {
    currentChar = numb % 8;
    numb /= 8;
    res += currentChar * pow(10, k++ - 1);
  }
  return res;
}

char *dev_To_Hex(uint64_t num, char *dest, int lettercase) {
  char *c = dest;
  int arr[30], i = 0;
  uint64_t currentChar = 0;
  while (num > 15) {
    arr[i] = num % 16;
    currentChar = num / 16;
    num = currentChar;
    i++;
  }
  arr[i] = num;
  for (int j = i, k = 0; j >= 0; j--, k++) {
    if (arr[j] == 1) {
      c[k] = '1';
    } else if (arr[j] == 2) {
      c[k] = '2';
    } else if (arr[j] == 3) {
      c[k] = '3';
    } else if (arr[j] == 4) {
      c[k] = '4';
    } else if (arr[j] == 5) {
      c[k] = '5';
    } else if (arr[j] == 6) {
      c[k] = '6';
    } else if (arr[j] == 7) {
      c[k] = '7';
    } else if (arr[j] == 8) {
      c[k] = '8';
    } else if (arr[j] == 9) {
      c[k] = '9';
    } else if (arr[j] == 10 && lettercase == 1) {
      c[k] = 'a';
    } else if (arr[j] == 10 && lettercase == 0) {
      c[k] = 'A';
    } else if (arr[j] == 11 && lettercase == 1) {
      c[k] = 'b';
    } else if (arr[j] == 11 && lettercase == 0) {
      c[k] = 'B';
    } else if (arr[j] == 12 && lettercase == 1) {
      c[k] = 'c';
    } else if (arr[j] == 12 && lettercase == 0) {
      c[k] = 'C';
    } else if (arr[j] == 13 && lettercase == 1) {
      c[k] = 'd';
    } else if (arr[j] == 13 && lettercase == 0) {
      c[k] = 'D';
    } else if (arr[j] == 14 && lettercase == 1) {
      c[k] = 'e';
    } else if (arr[j] == 14 && lettercase == 0) {
      c[k] = 'E';
    } else if (arr[j] == 15 && lettercase == 1) {
      c[k] = 'f';
    } else if (arr[j] == 15 && lettercase == 0) {
      c[k] = 'F';
    } else if (arr[j] == 0) {
      c[k] = '0';
    }
  }
  return c;
}

// функция для счета количества знаков целой части в числе %g
int count_char_specificator_G(double numb) {
  int count = 0, left = 0;
  if (numb < 0) {
    numb *= -1;
  }
  left = (int)numb;
  while (left > 0) {
    left = left / 10;
    count++;
  }
  return count;
}

// функция для счета количества знаков в числе %d
int count_character_numb(long long int numb) {
  int count = 1;
  if (numb < 0) {
    count++;
    numb = numb * -1;
  }
  while (numb > 9) {
    numb = numb / 10;
    count++;
  }
  return count;
}

// функция для счета количества знаков в целой части double при спецификаторе e
int count_char_specificator_E(double *numb) {
  int count = 0;
  if (*numb < 0) {
    *numb = *numb * -1;
  }
  if (*numb > 1) {
    while (*numb > 9) {
      *numb = *numb / 10;
      count++;
    }
  } else {
    while (*numb < 1) {
      *numb = *numb * 10;
      count--;
    }
  }
  return count;
}

// перевод int в char
char *int_to_char(int64_t n, char *dest) {
  char *c = dest;
  int v = 0;
  char t;
  if (n < 0) n = n * -1;
  while (n > 9) {
    c[v++] = (n % 10) + '0';
    n = n / 10;
  }
  c[v++] = n + '0';
  c[v] = '\0';

  for (int i = 0; i < v / 2; i++) {
    t = c[i];
    c[i] = c[v - 1 - i];
    c[v - 1 - i] = t;
  }
  return c;
}

// перевод unsigned int в char
char *int_to_char_unsigned(uint64_t n, char *dest) {
  char *c = dest;
  int v = 0;
  char t;
  while (n > 9) {
    c[v++] = (n % 10) + '0';
    n = n / 10;
  }
  c[v++] = n + '0';
  c[v] = '\0';
  for (int i = 0; i < v / 2; i++) {
    t = c[i];
    c[i] = c[v - 1 - i];
    c[v - 1 - i] = t;
  }
  return c;
}

void parser(char *fmt, char *tmp, va_list *ap, flag *num) {
  int star = 0;
  switch (*fmt) {
    case 'c':
      charToBuffer(tmp, *ap, num);
      break;
    case 'd':
      print_flags(tmp, *ap, num);
      break;
    case 'i':
      print_flags_unsigned(tmp, *ap, num);
      break;
    case 'o':
      num->spec_o = 1;
      print_flags_unsigned(tmp, *ap, num);
      break;
    case 'x':
      num->spec_x = 1;
      print_flags_unsigned(tmp, *ap, num);
      break;
    case 'X':
      num->spec_X = 1;
      print_flags_unsigned(tmp, *ap, num);
      break;
    case 'f':
      print_flags_double(tmp, *ap, num);
      break;
    case 'e':
      num->spec_e = 1;
      print_flags_double(tmp, *ap, num);
      break;
    case 'E':
      num->spec_E = 1;
      print_flags_double(tmp, *ap, num);
      break;
    case 'g':
      num->spec_g = 1;
      print_flags_double(tmp, *ap, num);
      break;
    case 'G':
      num->spec_G = 1;
      print_flags_double(tmp, *ap, num);
      break;
    case 's':
      str_to_buffer(tmp, *ap, num);
      break;
    case 'u':
      print_flags_unsigned(tmp, *ap, num);
      break;
    case 'p':
      num->spec_p = 1;
      print_flags_pointer(tmp, *ap, num);
      break;
    case 'h':
      num->length_h++;
      break;
    case 'l':
      num->length_l++;
      break;
    case 'L':
      num->length_L++;
      break;
    case '+':
      num->flagPlus = 1;
      break;
    case '-':
      num->flagMinus = 1;
      break;
    case '0':
      flag_null(fmt, num);
      break;
    case 'n':
      specificator_n(tmp, *ap, num);
      break;
    case '*':
      star = va_arg(*ap, int);
      if (num->flag_precision) {
        num->precision = star;
      } else {
        num->flag_width = 1;
        num->width = star;
      }
      break;
    case '.':
      flag_precision(fmt, num);
      break;
    case '#':
      num->flagSharp = 1;
      break;
    case ' ':
      tmp[num->posBuff++] = ' ';
      break;
  }
}