#include "s21_sprintf.h"

// Вычисляет длину строки str, не включая завершающий нулевой символ.

s21_size_t s21_strlen(const char *str) {
  s21_size_t lengsth = 0;
  for (; *(str + lengsth); lengsth++) {
  }
  return lengsth;
}

// Копирует до n символов из строки, на которую указывает src, в dest.
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i;
  for (i = 0; src[i] != '\0' && i < n; i++) {
    dest[i] = src[i];
  }
  if (src[i] == '\0' && n > 0 && n > s21_strlen(src)) {
    dest[i] = '\0';
  }
  return dest;
}

// Вычисляет длину начального сегмента str1, который полностью состоит из
// символов, не входящих в str2.
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  int flag = 1;
  s21_size_t len_str1 = s21_strlen(str1);
  s21_size_t len_str2 = s21_strlen(str2);
  s21_size_t result = len_str1;
  for (s21_size_t i = 0; i < len_str1 && flag; i++) {
    for (s21_size_t j = 0; j < len_str2 && flag; j++) {
      if (str1[i] == str2[j]) {
        result = i;
        flag = 0;
      }
    }
  }
  return result;
}

// Находит первый символ в строке str1, который соответствует любому символу,
// указанному в str2.
char *s21_strpbrk(const char *str1, const char *str2) {
  s21_size_t i, j, position, flag = 0;
  for (i = 0; str1[i] != '\0'; i++) {
  }
  position = i;
  for (i = 0; str2[i] != '\0'; i++) {
    for (j = 0; str1[j] != '\0'; j++) {
      if (str2[i] == str1[j]) {
        if (j <= position) {
          position = j;
          flag = 1;
        }
      }
    }
  }
  if (flag == 1) {
    return (char *)&str1[position];
  } else {
    return s21_NULL;
  }
}

// Выполняет поиск последнего вхождения символа c (беззнаковый тип) в строке,
// на которую указывает аргумент str.
char *s21_strrchr(const char *str, int c) {
  char *returning = 0;
  do {
    if (*str == c) {
      returning = (char *)str;
    }
  } while (*str++);
  return returning;
}

// Выполняет поиск первого вхождения символа c (беззнаковый тип) в строке, на
// которую указывает аргумент str.
char *s21_strchr(const char *str, int c) {
  int strLength = s21_strlen(str) + 1;
  const char *result = s21_NULL;

  for (int x = 0; x < strLength && result == s21_NULL; x += 1)
    if (str[x] == c) result = (str + x);

  return (char *)result;
}

// Вычисляет длину начального сегмента str1, который полностью состоит из
// символов str2.
s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t result = 0;
  s21_size_t len_str1 = s21_strlen(str1);
  s21_size_t len_str2 = s21_strlen(str2);
  for (s21_size_t i = 0; i < len_str1; i++) {
    int flag = 0;
    for (s21_size_t j = 0; j < len_str2 && !flag; j++) {
      if (str1[i] == str2[j]) {
        flag = 1;
        result++;
      }
    }
    if (!flag) {
      break;
    }
  }
  return result;
}

// Находит первое вхождение всей строки needle (не включая завершающий нулевой
// символ), которая появляется в строке haystack.
char *s21_strstr(const char *haystack, const char *needle) {
  char *result = s21_NULL;
  if (needle[0] == '\0') {
    result = (char *)haystack;
  } else {
    int found = 0;
    for (int i = 0; haystack[i] && !found; i++) {
      int flag = 1;
      if (haystack[i] == needle[0]) {
        for (int j = 0; needle[j] && flag; j++) {
          if (haystack[i + j] != needle[j]) {
            flag = 0;
          } else if (needle[j + 1] == '\0') {
            result = (char *)(haystack + i);
            found = 1;
          }
        }
      }
    }
  }
  return result;
}

// strtok разбивает строку str на ряд токенов, разделенных delim.

int is_one_of_delims(char c, const char *delim) {
  int delim_i = 0;
  int result = 0;
  while (delim[delim_i]) {
    if (delim[delim_i] == c) {
      result = 1;
    }
    delim_i++;
  }
  return result;
}

char *remove_delims_in_the_beginning(char *str_copy, const int *str_pointer,
                                     const char *delim) {
  if (*str_pointer == 0) {
    while (is_one_of_delims(str_copy[*str_pointer], delim)) {
      str_copy[*str_pointer] = 0;
      str_copy = str_copy + 1;
    }
  }
  return str_copy;
}

void clear_variables(int *function_call_no, char **str_copy, char **str_next,
                     int *str_pointer) {
  *function_call_no = 1;
  *str_copy = s21_NULL;
  *str_next = s21_NULL;
  *str_pointer = 0;
}

char *s21_strtok(char *str, const char *delim) {
  static int str_pointer = 0;
  static int function_call_no = 1;
  static char *str_copy = s21_NULL;
  static char *str_next = s21_NULL;
  if (function_call_no != 1 && str != s21_NULL) {
    clear_variables(&function_call_no, &str_copy, &str_next, &str_pointer);
  }
  int result_is_null = 0;
  if (function_call_no == 1) {
    str_copy = str;
  } else if (str == s21_NULL) {
    if (str_next != s21_NULL) {
      str_copy = str_next;
      str_pointer = 0;
    } else {
      str_copy = s21_NULL;
      result_is_null = 1;
    }
  }
  if (!result_is_null && s21_strlen(delim) > 0) {
    int not_stopped = 1;
    str_copy = remove_delims_in_the_beginning(str_copy, &str_pointer, delim);
    while (str_copy[str_pointer] && not_stopped) {
      if (is_one_of_delims(str_copy[str_pointer], delim)) {
        str_copy[str_pointer] = 0;
        str_next = str_copy + str_pointer + 1;
        not_stopped = 0;
      }
      str_pointer++;
    }
    if (str_next != s21_NULL &&
        (s21_strcmp(str_next, str_copy) == 0 || s21_strcmp(str_next, "") == 0))
      str_next = s21_NULL;
    if (s21_strcmp(str_copy, "") == 0) str_copy = s21_NULL;
  }
  function_call_no++;
  return str_copy;
}

// Сравнивает первые n байтов str1 и str2.
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int isFindedDiff = 0;
  int result = 0;
  for (s21_size_t i = 0; i < n && !isFindedDiff; i++) {
    if (*(unsigned char *)(str1 + i) != *(unsigned char *)(str2 + i)) {
      isFindedDiff = 1;
      result = *(unsigned char *)(str1 + i) - *(unsigned char *)(str2 + i);
    }
  }
  return result;
}

// Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n
// байтах строки, на которую указывает аргумент str.
void *s21_memchr(const void *str, int c, s21_size_t n) {
  void *res = s21_NULL;
  unsigned char *p = (unsigned char *)str;
  int flag = 1;
  for (s21_size_t i = 0; i < n && flag; i++) {
    if (*p == (unsigned char)c) {
      flag = 0;
      res = p;
    } else
      p++;
  }
  return res;
}

// Копирует n символов из src в dest.
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *destCopy = (char *)dest;
  const char *srcCopy = (const char *)src;

  while (n != 0) {
    *destCopy = *srcCopy;
    destCopy++, srcCopy++;
    n--;
  }
  return dest;
}

// Копирует символ c (беззнаковый тип) в первые n символов строки, на которую
// указывает аргумент str.
void *s21_memset(void *str, int c, s21_size_t n) {
  char *strCopy = (char *)str;

  if (n != 0) {
    for (s21_size_t i = 0; i < n; i++) {
      *strCopy = c;
      strCopy++;
    }
  }
  return str;
}

// Еще одна функция для копирования n символов из src в dest.
void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  void *result = dest;
  if (dest <= src || (unsigned char *)dest >= ((unsigned char *)src + n)) {
    for (s21_size_t i = 0; i < n; i++) {
      *(unsigned char *)dest = *(unsigned char *)src;
      dest = (unsigned char *)dest + 1;
      src = (unsigned char *)src + 1;
    }
  } else {
    dest = (unsigned char *)dest + n - 1;
    src = (unsigned char *)src + n - 1;
    for (s21_size_t i = 0; i < n; i++) {
      *(unsigned char *)dest = *(unsigned char *)src;
      dest = (unsigned char *)dest - 1;
      src = (unsigned char *)src - 1;
    }
  }
  return result;
}

// Добавляет строку, на которую указывает src, в конец строки, на которую
// указывает dest.

char *s21_strcat(char *dest, const char *src) {
  char *ptr = dest + s21_strlen(dest);
  while (*src != '\0') {
    *ptr++ = *src++;
  }
  *ptr = '\0';
  return dest;
}

// Добавляет строку, на которую указывает src, в конец строки, на которую
// указывает dest, длиной до n символов.

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  long unsigned int src_len = s21_strlen(src);
  long unsigned int dest_len = s21_strlen(dest);
  char *ptr = dest + dest_len;
  long unsigned int counter = 1;
  while ((counter <= n && counter <= src_len) && *src != '\0') {
    *ptr++ = *src++;
    counter++;
  }
  *ptr = '\0';
  return dest;
}

// Сравнивает строку, на которую указывает str1, со строкой, на которую
// указывает str2.
int s21_strcmp(const char *str1, const char *str2) {
  int flag = 1;
  while (*str1 != '\0' && flag) {
    if (*str1 == *str2) {
      str1++, str2++;
    } else {
      flag = 0;
    }
  }
  return *(unsigned char *)str1 - *(unsigned char *)str2;
}

// Сравнивает не более первых n байтов str1 и str2.
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0, flag = 1;
  if (!n) flag = 0;
  while (--n && *str1 != '\0' && *str1 == *str2) {
    str1++;
    str2++;
  }
  if (flag) result = *(char *)str1 - *(char *)str2;
  return result;
}

// Копирует строку, на которую указывает src, в dest.
char *s21_strcpy(char *dest, const char *src) {
  char *temp = dest;
  if (dest != s21_NULL) {
    while (*src != '\0') {
      *dest = *src;
      dest++;
      src++;
    }
  }
  *dest = '\0';
  return temp;
}

// Возвращает копию строки (str), преобразованной в нижний регистр. В случае
// какой-либо ошибки следует вернуть значение NULL
void *s21_to_lower(const char *str) {
  char *scopy = s21_NULL;

  if (str != s21_NULL) {
    scopy = calloc((s21_strlen(str) + 1), sizeof(char));
    if (scopy != s21_NULL) {
      s21_strcpy(scopy, str);
      for (s21_size_t i = 0; i <= s21_strlen(str); i++) {
        if (scopy[i] >= 65 && scopy[i] <= 90) {
          scopy[i] = scopy[i] + 32;
        }
      }
    }
    scopy[s21_strlen(str)] = '\0';
  }
  return scopy;
}

// Возвращает копию строки (str), преобразованной в верхний регистр. В случае
// какой-либо ошибки следует вернуть значение NULL
void *s21_to_upper(const char *str) {
  char *temp_str = s21_NULL;
  if (str != s21_NULL) {
    temp_str = calloc((s21_strlen(str) + 1), sizeof(char));
    if (temp_str != s21_NULL) {
      s21_strcpy(temp_str, str);
      for (s21_size_t i = 0; i <= s21_strlen(str); i++) {
        if (temp_str[i] >= 97 && temp_str[i] <= 122) {
          temp_str[i] = temp_str[i] - 32;
        }
      }
    }
    temp_str[s21_strlen(str)] = '\0';
  }
  return temp_str;
}

// Возвращает новую строку, в которой указанная строка (str) вставлена в
// указанную позицию (start_index) в данной строке (src). В случае какой-либо
// ошибки следует вернуть значение NULL
// возвращаем УКАЗАТЕЛЬ на строку
// создаём новую стр, перезапис. в нее поданную и в процессе перезаписи
// вставить элементы
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *result = s21_NULL;
  if (src && str && start_index <= (s21_strlen(src))) {
    result =
        (char *)calloc(s21_strlen(src) + s21_strlen(str) + 1, sizeof(char));
    if (result) {
      s21_strncpy(result, src, start_index);
      s21_strcat(result, str);
      s21_strcat(result, src + start_index);
    }
  }
  return result;
}

// Возвращает новую строку, в которой удаляются все начальные и конечные
// вхождения набора заданных символов (trim_chars) из данной строки (src). В
// случае какой-либо ошибки следует вернуть значение NULL
// Обрезает указанные символы (или стандартные, если не указаны) по краям (и
// только по краям) строки.
// возвращаем УКАЗАТЕЛЬ на строку
void *s21_trim(const char *src, const char *trim_chars) {
  char *result = s21_NULL;
  if (src != s21_NULL) {
    if (trim_chars == NULL || trim_chars[0] == '\0') {
      trim_chars = " ";
    }
    int size = (int)s21_strlen(src);
    if (size != 0) {
      int start = -1, end = -1;
      int flag_i = 1, flag_j = 1;
      for (int i = 0, j = size - 1; i < size; i++, j--) {
        if (s21_strchr(trim_chars, src[i]) == s21_NULL && flag_i) {
          start = i;
          flag_i = 0;
        }
        if (s21_strchr(trim_chars, src[j]) == s21_NULL && flag_j) {
          end = j;
          flag_j = 0;
        }
        if (!flag_i && !flag_j) {
          break;
        }
      }
      result = calloc(end - start + 2, sizeof(char));
      if (result != s21_NULL) {
        for (int i = start, j = 0; i <= end; i++, j++) {
          result[j] = src[i];
        }
      }
    } else {
      result = calloc(2, sizeof(char));
      result[0] = '\0';
    }
  }
  return result;
}

#define ERRLEN 50
#if defined(__APPLE__) || defined(__MACH__)
#define UNKNOWN "Unknown error:"
#define ERRCOUNT 107
#else
#define UNKNOWN "No error information"
#define ERRCOUNT 134
#endif

#if defined(__APPLE__) || defined(__MACH__)
static const char s21_errlist[ERRCOUNT][ERRLEN] = {
    "Undefined error: 0",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "Device not configured",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource deadlock avoided",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Resource busy",
    "File exists",
    "Cross-device link",
    "Operation not supported by device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Result too large",
    "Resource temporarily unavailable",
    "Operation now in progress",
    "Operation already in progress",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol family",
    "Address already in use",
    "Can't assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Socket is already connected",
    "Socket is not connected",
    "Can't send after socket shutdown",
    "Too many references: can't splice",
    "Operation timed out",
    "Connection refused",
    "Too many levels of symbolic links",
    "File name too long",
    "Host is down",
    "No route to host",
    "Directory not empty",
    "Too many processes",
    "Too many users",
    "Disc quota exceeded",
    "Stale NFS file handle",
    "Too many levels of remote in path",
    "RPC struct is bad",
    "RPC version wrong",
    "RPC prog. not avail",
    "Program version wrong",
    "Bad procedure for program",
    "No locks available",
    "Function not implemented",
    "Inappropriate file type or format",
    "Authentication error",
    "Need authenticator",
    "Device power is off",
    "Device error",
    "Value too large to be stored in data type",
    "Bad executable (or shared library)",
    "Bad CPU type in executable",
    "Shared library version mismatch",
    "Malformed Mach-o file",
    "Operation canceled",
    "Identifier removed",
    "No message of desired type",
    "Illegal byte sequence",
    "Attribute not found",
    "Bad message",
    "EMULTIHOP (Reserved)",
    "No message available on STREAM",
    "ENOLINK (Reserved)",
    "No STREAM resources",
    "Not a STREAM",
    "Protocol error",
    "STREAM ioctl timeout",
    "Operation not supported on socket",
    "Policy not found",
    "State not recoverable",
    "Previous owner died",
    "Interface output queue is full"};
#endif
#if defined(__linux__)
static const char s21_errlist[ERRCOUNT][ERRLEN] = {
    "No error information",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "I/O error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child process",
    "Resource temporarily unavailable",
    "Out of memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Resource busy",
    "File exists",
    "Cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "No file descriptors available",
    "Not a tty",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Invalid seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Domain error",
    "Result not representable",
    "Resource deadlock would occur",
    "Filename too long",
    "No locks available",
    "Function not implemented",
    "Directory not empty",
    "Symbolic link loop",
    "No error information",
    "No message of desired type",
    "Identifier removed",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "Device not a stream",
    "No data available",
    "Device timeout",
    "Out of streams resources",
    "No error information",
    "No error information",
    "No error information",
    "Link has been severed",
    "No error information",
    "No error information",
    "No error information",
    "Protocol error",
    "Multihop attempted",
    "No error information",
    "Bad message",
    "Value too large for data type",
    "No error information",
    "File descriptor in bad state",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "Illegal byte sequence",
    "No error information",
    "No error information",
    "No error information",
    "Not a socket",
    "Destination address required",
    "Message too large",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Not supported",
    "Protocol family not supported",
    "Address family not supported by protocol",
    "Address in use",
    "Address not available",
    "Network is down",
    "Network unreachable",
    "Connection reset by network",
    "Connection aborted",
    "Connection reset by peer",
    "No buffer space available",
    "Socket is connected",
    "Socket not connected",
    "Cannot send after socket shutdown",
    "No error information",
    "Operation timed out",
    "Connection refused",
    "Host is down",
    "Host is unreachable",
    "Operation already in progress",
    "Operation in progress",
    "Stale file handle",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "Remote I/O error",
    "Quota exceeded",
    "No medium found",
    "Wrong medium type",
    "Operation canceled",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "Previous owner died",
    "State not recoverable",
    "No error information",
    "No error information"};
#endif
char *s21_strerror(int errnum) {
  static char res[BUFF_SIZE] = {'\0'};
  if (errnum < 0 || errnum >= ERRCOUNT) {
#ifdef APPLE
    s21_sprintf(res, "%s %d", UNKNOWN, errnum);
#elif linux
    s21_sprintf(res, "%s", UNKNOWN);
#endif
  } else
    s21_strcpy(res, s21_errlist[errnum]);

  return res;
}
