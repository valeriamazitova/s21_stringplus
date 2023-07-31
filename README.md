# s21_stringplus
Implementation of the string.h library with additions.

Functions of the string.h library:

- `void *memchr(const void *str, int c, size_t n)`

- `int memcmp(const void *str1, const void *str2, size_t n)`

- `void *memcpy(void *dest, const void *src, size_t n)`

- `void *memmove(void *dest, const void *src, size_t n)`

- `void *memset(void *str, int c, size_t n)`

- `char *strcat(char *dest, const char *src)`

- `char *strncat(char *dest, const char *src, size_t n)`

- `char *strchr(const char *str, int c)`

- `int strcmp(const char *str1, const char *str2)`

- `int strncmp(const char *str1, const char *str2, size_t n)`

- `char *strcpy(char *dest, const char *src)`

- `char *strncpy(char *dest, const char *src, size_t n)`

- `size_t strcspn(const char *str1, const char *str2)`

- `char *strerror(int errnum)`

- `size_t strlen(const char *str)`

- `char *strpbrk(const char *str1, const char *str2)`

- `char *strrchr(const char *str, int c)`

- `size_t strspn(const char *str1, const char *str2)`

- `char *strstr(const char *haystack, const char *needle)`

- `char *strtok(char *str, const char *delim)`

Bonus part:

- `int sscanf(const char *str, const char *format, ...)` - reads formatted input from a string.

- `int sprintf(char *str, const char *format, ...)` - sends formatted output to a string pointed to, by str.

- `void *to_upper(const char *str)`

- `void *to_lower(const char *str)`

- `void *insert(const char *src, const char *str, size_t start_index)`

- `void *trim(const char *src, const char *trim_chars)`
