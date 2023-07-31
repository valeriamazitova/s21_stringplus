#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_sprintf.h"
#include "s21_sscanf.h"
#include "s21_string.h"

START_TEST(s21_memchr_test_1) {
  s21_size_t n_byte = 0;
  char str[10] = {""};
  int find_byte = '\0';
  ck_assert_ptr_eq(s21_memchr(str, find_byte, n_byte),
                   memchr(str, find_byte, n_byte));
}
END_TEST

START_TEST(s21_memchr_test_2) {
  s21_size_t n_byte = 7;
  char str[10] = {"string"};
  int find_byte = '\0';
  ck_assert_ptr_eq(s21_memchr(str, find_byte, n_byte),
                   memchr(str, find_byte, n_byte));
}
END_TEST

START_TEST(s21_memchr_test_3) {
  char str[50] = {"Hello w\0orld\0"};
  ck_assert_pstr_eq(memchr(str, 'r', 5), s21_memchr(str, 'r', 5));
}

END_TEST

START_TEST(s21_memchr_test_5) {
  char str3[50] = {'q', 'r', 's', 't', 'w', '\0'};
  ck_assert_pstr_eq(memchr(str3, 's', 5), s21_memchr(str3, 's', 5));
}
END_TEST

START_TEST(s21_memchr_test_6) {
  s21_size_t n_byte = 6;
  char str[10] = {"Atring"};
  int find_byte = 'A';
  ck_assert_ptr_eq(s21_memchr(str, find_byte, n_byte),
                   memchr(str, find_byte, n_byte));
}
END_TEST

START_TEST(s21_memchr_test_7) {
  s21_size_t n_byte = 7;
  char str[10] = {"StringA"};
  int find_byte = 'A';
  ck_assert_ptr_eq(s21_memchr(str, find_byte, n_byte),
                   memchr(str, find_byte, n_byte));
}
END_TEST

START_TEST(s21_memchr_test_8) {
  s21_size_t n_byte = 15;
  char str[16] = {"Str55333222ingA"};
  int find_byte = '3';
  ck_assert_ptr_eq(s21_memchr(str, find_byte, n_byte),
                   memchr(str, find_byte, n_byte));
}
END_TEST

START_TEST(s21_memcmp_test_1) {
  char test_str[50][20] = {"Hello, World!", "Hello", "Hello\0World!"};
  s21_size_t num[50] = {0, 1, 2, 10, 20};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 5; k++) {
        ck_assert_int_eq(s21_memcmp(test_str[i], test_str[j], num[k]),
                         memcmp(test_str[i], test_str[j], num[k]));
      }
}
END_TEST

START_TEST(s21_memcmp_test_2) {
  int test_int[50] = {0, 1, -21, -42, 1234567};
  s21_size_t num[50] = {0, 1};
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      for (int k = 0; k < 2; k++) {
        ck_assert_int_eq(s21_memcmp(&test_int[i], &test_int[j], num[k]),
                         memcmp(&test_int[i], &test_int[j], num[k]));
      }
}
END_TEST

START_TEST(s21_memcmp_test_3) {
  char str1[50] = {"aboba"};
  char str2[50] = {"aboba"};
  int n = 0;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(s21_memcmp_test_4) {
  char str1[50] = {"aboba"};
  char str2[50] = {"aboba"};
  int n = 3;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(s21_memcmp_test_5) {
  char str1[50] = {"aboba"};
  char str2[50] = {"Aboba"};
  int n = 1;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(s21_memcmp_test_6) {
  char str1[50] = {"1"};
  char str2[50] = {"1"};
  int n = 0;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(s21_memcmp_test_7) {
  char str1[50] = {"1"};
  char str2[50] = {"1234"};
  int n = 1;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(s21_memcmp_test_8) {
  char str1[50] = {"1234"};
  char str2[50] = {"1234"};
  int n = 2;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(s21_memcmp_test_10) {
  char str1[100] = {
      "111111111111111111112312312312312312434524563567adsfe 4rafa "
      "ewfseASDASD"};
  char str2[100] = {
      "111111111111111111112312312312312312434524563567adsfe 4rafa "
      "ewfseASDASd"};
  int n = 71;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(s21_memcpy_test_1) {
  char test_str[50][20] = {"Hello, World!", "Hello\0World!\0", "", "\0"};
  s21_size_t num[50] = {0, 1, 2, 10, 20};
  char str_s21[2048] = {""};
  char str_original[2048] = {""};
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 5; j++) {
      ck_assert_pstr_eq(s21_memcpy(str_s21, test_str[i], num[j]),
                        memcpy(str_original, test_str[i], num[j]));
      ck_assert_mem_eq(str_s21, str_original, num[j]);
    }
}
END_TEST

START_TEST(s21_memcpy_test_2) {
  s21_size_t n1 = 3;
  char b1[1024] = {""};
  char b11[1024] = {""};
  char str_1_2[1024] = {"ABOBA THE BEST!"};
  ck_assert_pstr_eq(memcpy(b1, str_1_2, n1), s21_memcpy(b11, str_1_2, n1));
}
END_TEST

START_TEST(s21_memcpy_test_3) {
  s21_size_t n2 = 5;
  char b2[1024] = {""};
  char b22[1024] = {""};
  char str_2_2[1024] = {"THE OF \0BEST!!"};
  ck_assert_pstr_eq(memcpy(b2, str_2_2, n2), s21_memcpy(b22, str_2_2, n2));
}
END_TEST

START_TEST(s21_memcpy_test_4) {
  s21_size_t n3 = 4;
  char b3[1024] = {"777 "};
  char b33[1024] = {"777 "};
  char str_3_2[1024] = {"ABOBA!"};
  ck_assert_pstr_eq(memcpy(b3, str_3_2, n3), s21_memcpy(b33, str_3_2, n3));
}
END_TEST

START_TEST(s21_memcpy_test_5) {
  s21_size_t n4 = 4;
  char b4[1024] = {"ABOBA! 777 "};
  char b44[1024] = {"ABOBA! 777 "};
  ck_assert_pstr_eq(memcpy(b4, b4 + 7, n4), s21_memcpy(b44, b44 + 7, n4));
}
END_TEST

START_TEST(s21_memmove_test_1) {
  char test_str[50][20] = {"Hello, World!", "Hello\0World!\0", "", "\0"};
  s21_size_t num[50] = {0, 1, 2, 10, 20};
  char str_s21[2048] = {""};
  char str_original[2048] = {""};
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 5; j++) {
      ck_assert_pstr_eq(s21_memmove(str_s21, test_str[i], num[j]),
                        memmove(str_original, test_str[i], num[j]));
      ck_assert_mem_eq(str_s21, str_original, num[j]);
    }
}
END_TEST

START_TEST(s21_memmove_test_2) {
  char test_str[50][20] = {"Hello, World!", "Hello\0World!\0", "", "\0"};
  s21_size_t num[50] = {0, 1, 2, 10, 20};
  int split = 2;
  char str_s21[2048] = {""};
  char str_original[2048] = {""};
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 5; j++) {
      memcpy(str_s21, test_str[i], strlen(test_str[i]) + 1);
      memcpy(str_original, test_str[i], strlen(test_str[i]) + 1);
      ck_assert_pstr_eq(s21_memmove(str_s21 + split, str_s21, num[j]),
                        memmove(str_original + split, str_original, num[j]));
      ck_assert_mem_eq(str_s21 + split, str_original + split, num[j]);
    }
}
END_TEST

START_TEST(s21_memmove_test_3) {
  s21_size_t n1 = 3;
  char b1[1024] = {"ABOBA THE BEST!"};
  char b11[1024] = {"ABOBA THE BEST!"};
  ck_assert_pstr_eq(memmove(b1, b1 + 5, n1), s21_memmove(b11, b1 + 5, n1));
}
END_TEST

START_TEST(s21_memmove_test_4) {
  s21_size_t n2 = 4;
  char b2[1024] = {"777 9999999"};
  char b22[1024] = {"777 9999999"};
  ck_assert_pstr_eq(memmove(b2, b2, n2), s21_memmove(b22, b2, n2));
}
END_TEST

START_TEST(s21_memmove_test_5) {
  s21_size_t n3 = 4;
  char b3[1024] = {"777 ABOBA!"};
  char b33[1024] = {"777 ABOBA!"};
  ck_assert_pstr_eq(memmove(b3, b3, n3), s21_memmove(b33, b33, n3));
}
END_TEST

START_TEST(s21_memset_test_1) {
  char str_s21[50] = {"Hello, World!"};
  char str_original[50] = {"Hello, World!"};
  char v = '1';
  int n = 5;
  ck_assert_pstr_eq(s21_memset(str_s21, v, n), memset(str_original, v, n));
  ck_assert_mem_eq(str_s21, str_original, n);
}
END_TEST

START_TEST(s21_memset_test_2) {
  char str_s21[50] = {"Hello, World!"};
  char str_original[50] = {"Hello, World!"};
  char v = '2';
  int n = 0;
  ck_assert_pstr_eq(s21_memset(str_s21, v, n), memset(str_original, v, n));
  ck_assert_mem_eq(str_s21, str_original, n);
}
END_TEST

START_TEST(s21_memset_test_3) {
  char str_s21[50] = {""};
  char str_original[50] = {""};
  char v = '3';
  int n = 0;
  ck_assert_pstr_eq(s21_memset(str_s21, v, n), memset(str_original, v, n));
  ck_assert_mem_eq(str_s21, str_original, n);
}
END_TEST

START_TEST(s21_memset_test_4) {
  char str_s21[50] = {"Hello, World!"};
  char str_original[50] = {"Hello, World!"};
  char v = '/';
  int n = 4;
  ck_assert_pstr_eq(s21_memset(str_s21, v, n), memset(str_original, v, n));
  ck_assert_mem_eq(str_s21, str_original, n);
}
END_TEST

START_TEST(s21_memset_test_5) {
  char res[50] = {"aboba"};
  char expected[50] = {"aboba"};
  char replace = 'A';
  s21_size_t n_byte = 3;
  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(s21_memset_test_6) {
  char res[50] = {"a1obA"};
  char expected[50] = {"a1obA"};
  char replace = '1';
  s21_size_t n_byte = 5;
  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(s21_memset_test_7) {
  char res[100] = {
      "a1oas[pifjaosidfj oapisjdfpoi asjdfoij ouh12oi3 uh12i3 "
      "hiajhIOUAHSDiouAHSdu1).bA"};
  char expected[100] = {
      "a1oas[pifjaosidfj oapisjdfpoi asjdfoij ouh12oi3 uh12i3 "
      "hiajhIOUAHSDiouAHSdu1).bA"};
  char replace = '1';
  s21_size_t n_byte = 5;
  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(s21_memset_test_8) {
  char res[50] = {"aboba"};
  char expected[50] = {"aboba"};
  char replace = 'g';
  s21_size_t n_byte = 0;
  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(s21_memset_test_9) {
  char res[50] = {""};
  char expected[50] = {""};
  char replace = '\0';
  s21_size_t n_byte = 0;
  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(s21_memset_test_10) {
  char res[50] = {"aboba"};
  char expected[50] = {"aboba"};
  char replace = 'g';
  s21_size_t n_byte = 5;
  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(s21_strcat_test_1) {
  char test_str[50] = {"Hello, World!"};
  char str_s21[2048] = {""};
  char str_original[2048] = {""};
  ck_assert_pstr_eq(s21_strcat(str_s21, test_str),
                    strcat(str_original, test_str));
  ck_assert_pstr_eq(str_s21, str_original);
}
END_TEST

START_TEST(s21_strcat_test_2) {
  char test_str[50] = {"Hello\0World!\0"};
  char str_s21[2048] = {""};
  char str_original[2048] = {""};
  ck_assert_pstr_eq(s21_strcat(str_s21, test_str),
                    strcat(str_original, test_str));
  ck_assert_pstr_eq(str_s21, str_original);
}
END_TEST

START_TEST(s21_strcat_test_3) {
  char test_str[50] = {""};
  char str_s21[2048] = {""};
  char str_original[2048] = {""};
  ck_assert_pstr_eq(s21_strcat(str_s21, test_str),
                    strcat(str_original, test_str));
  ck_assert_pstr_eq(str_s21, str_original);
}
END_TEST

START_TEST(s21_strcat_test_4) {
  char test_str[50] = {"Hello"};
  char str_s21[2048] = {"\0"};
  char str_original[2048] = {"\0"};
  ck_assert_pstr_eq(s21_strcat(str_s21, test_str),
                    strcat(str_original, test_str));
  ck_assert_pstr_eq(str_s21, str_original);
}
END_TEST

START_TEST(s21_strcat_test_5) {
  char test_str[50] = {""};
  char str_s21[2048] = {"World"};
  char str_original[2048] = {"World"};
  ck_assert_pstr_eq(s21_strcat(str_s21, test_str),
                    strcat(str_original, test_str));
  ck_assert_pstr_eq(str_s21, str_original);
}
END_TEST

START_TEST(s21_strncat_test_1) {
  char test_str[50][64] = {"Hello, World!", "Hello\0World!\0", "", "\0"};
  char str_s21[50][64] = {"Hello, World!", "Hello\0World!\0", "", "\0"};
  char str_original[50][64] = {"Hello, World!", "Hello\0World!\0", "", "\0"};
  size_t num[50] = {0, 1, 10, 30};
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      for (int k = 0; k < 2; k++) {
        ck_assert_pstr_eq(s21_strncat(str_s21[i], test_str[j], num[k]),
                          strncat(str_original[i], test_str[j], num[k]));
        ck_assert_pstr_eq(str_s21[i], str_original[i]);
      }
}
END_TEST

START_TEST(s21_strncat_test_2) {
  s21_size_t n1 = 2;
  char b1[1024] = {""};
  char b11[1024] = {""};
  char str_1_2[1024] = {"VLASTELINI UTROBI THE BEST!"};
  ck_assert_pstr_eq(strncat(b1, str_1_2, n1), s21_strncat(b11, str_1_2, n1));
}
END_TEST

START_TEST(s21_strncat_test_3) {
  s21_size_t n3 = 2;
  char b3[1024] = {"777"};
  char b33[1024] = {"777"};
  char str_3_2[1024] = {" VLASTELINI UTROBI!"};
  ck_assert_pstr_eq(strncat(b3, str_3_2, n3), s21_strncat(b33, str_3_2, n3));
}
END_TEST

START_TEST(strncat_BIGFLOPPA) {
  char src[] = "BIGFLOPPA";
  char res[25] = "BIGFLOPPA";
  char expected[25] = "BIGFLOPPA";
  s21_size_t n_byte = 5;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(strncat_BIGFLOPPA2) {
  char src[] = "BIGFLOPPA";
  char res[25] = "BIGFLOPPA";
  char expected[25] = "BIGFLOPPA";
  s21_size_t n_byte = 0;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(strncat_BIGFLOPPA3) {
  char src[] = "BIGFLOPPA";
  char res[25] = "BIGFLOPPA";
  char expected[25] = "BIGFLOPPA";
  s21_size_t n_byte = 1;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(strncat_BIGFLOPPA4) {
  char src[] = "BIGFLOPPA";
  char res[25] = "BIGFLOPPA";
  char expected[25] = "BIGFLOPPA";
  s21_size_t n_byte = 10;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(strncat_zero_char) {
  char src[] = "\0";
  char res[25] = "BIGFLOPPA";
  char expected[25] = "BIGFLOPPA";
  s21_size_t n_byte = 1;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(s21_strncat_1) {
  char s1[50] = "Hello world\0";
  char s2[50] = " world\0";
  char s3[50] = "Hello world\0";
  ck_assert_str_eq(s21_strncat(s1, s2, 3), strncat(s3, s2, 3));
}
END_TEST

START_TEST(s21_strncat_2) {
  char s1[50] = "a\n\0";
  char s2[50] = " \n\0";
  char s3[50] = "a\n\0";
  ck_assert_str_eq(s21_strncat(s1, s2, 3), strncat(s3, s2, 3));
}
END_TEST

START_TEST(s21_strncat_3) {
  char s1[50] = " \0";
  char s2[50] = "\n\0";
  char s3[50] = " \0";
  ck_assert_str_eq(s21_strncat(s1, s2, 1), strncat(s3, s2, 1));
}
END_TEST

START_TEST(s21_strncat_4) {
  char s1[50] = "\0";
  char s2[50] = "\n\0";
  char s3[50] = "\0";
  ck_assert_str_eq(s21_strncat(s1, s2, 1), strncat(s3, s2, 1));
}
END_TEST

START_TEST(s21_strchr_test_1) {
  char s1[50] = {"asdf\0"};
  char s3[50] = {"asdf\0"};
  ck_assert_str_eq(s21_strchr(s1, 'a'), strchr(s3, 'a'));
}
END_TEST

START_TEST(s21_strchr_test_2) {
  char src[50] = {"abobasaaaa"};
  char find = 'a';
  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(s21_strchr_test_3) {
  char src[50] = {"abobasAsa"};
  char find = 'A';
  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(s21_strchr_test_4) {
  char src[50] = {"abobasA1sa"};
  char find = '1';
  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(s21_strcmp_test_1) {
  char *str_1_1 = {"ABOBA!"};
  char *str_1_2 = {"ABOBA!"};
  int s21_c = s21_strcmp(str_1_1, str_1_2);
  int s_c = strcmp(str_1_1, str_1_2);
  ck_assert_int_eq(s21_c, s_c);
}
END_TEST

START_TEST(s21_strcmp_test_2) {
  char *str_2_1 = {"ABOBA THE BEST!"};
  char *str_2_2 = {"ABOBA OF THE BEST!"};
  int s21_c = s21_strcmp(str_2_1, str_2_2);
  int s_c = strcmp(str_2_1, str_2_2);
  if (s21_c > 0) s21_c = 1;
  if (s_c > 0) s_c = 1;
  ck_assert_int_eq(s21_c, s_c);
}
END_TEST

START_TEST(s21_strcmp_test_3) {
  char *str_3_1 = {"ABOBA OF THE BEST!!!!!"};
  char *str_3_2 = {"ABOBA!"};
  int s21_c = s21_strcmp(str_3_1, str_3_2);
  int s_c = strcmp(str_3_1, str_3_2);
  if (s21_c > 0) s21_c = 1;
  if (s_c > 0) s_c = -1;
  ck_assert_int_eq(s21_c, s_c);
}
END_TEST

START_TEST(s21_strncmp_test_1) {
  char test_str[50][20] = {"Hello, World!", "Hello", "", "\0", "Hello\0World!"};
  s21_size_t num[50] = {0, 1, 2, 10, 20};
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      for (int k = 0; k < 5; k++) {
        int s21_c = s21_strncmp(test_str[i], test_str[j], num[k]);
        int s_c = strncmp(test_str[i], test_str[j], num[k]);
        if (s21_c > 0)
          s21_c = 1;
        else if (s21_c < 0)
          s21_c = -1;
        if (s_c > 0)
          s_c = 1;
        else if (s_c < 0)
          s_c = -1;
        ck_assert_int_eq(s21_c, s_c);
      }
}
END_TEST

START_TEST(s21_strncmp_test_2) {
  s21_size_t n = 3;
  char *str_1_1 = {"ABOBA!"};
  char *str_1_2 = {"ABOBA!"};
  int s21_c = s21_strncmp(str_1_1, str_1_2, n);
  int s_c = strncmp(str_1_1, str_1_2, n);
  if (s21_c > 0) ck_assert_int_eq(s21_c, s_c);
}
END_TEST

START_TEST(s21_strcpy_test_1) {
  char test_str[50][20] = {"Hello, World!", "", "Hello\0World!\0", "\0"};
  char str_s21[2048] = {""};
  char str_original[2048] = {""};
  for (int i = 0; i < 4; i++) {
    ck_assert_str_eq(s21_strcpy(str_s21, test_str[i]),
                     strcpy(str_original, test_str[i]));
    ck_assert_str_eq(str_s21, str_original);
  }
}
END_TEST

START_TEST(s21_strcpy_test_2) {
  char b1[1024] = {""};
  char b11[1024] = {""};
  char str_1_2[1024] = {"ABOBA THE BEST!"};
  ck_assert_pstr_eq(strcpy(b1, str_1_2), s21_strcpy(b11, str_1_2));
}
END_TEST

START_TEST(s21_strcpy_test_3) {
  char b2[1024] = {""};
  char b22[1024] = {""};
  char str_2_2[1024] = {"THE OF \0BEST!!"};
  ck_assert_pstr_eq(strcpy(b2, str_2_2), s21_strcpy(b22, str_2_2));
}
END_TEST

START_TEST(s21_strcpy_test_4) {
  char b3[1024] = {"777 "};
  char b33[1024] = {"777 "};
  char str_3_2[1024] = {"ABOBA!"};
  ck_assert_pstr_eq(strcpy(b3, str_3_2), s21_strcpy(b33, str_3_2));
}
END_TEST

START_TEST(s21_strncpy_test_1) {
  char test_str[50][20] = {"Hello, World!", "Hello\0World!\0", "", "\0"};
  s21_size_t num[50] = {0, 1, 2, 10, 20};
  char str_s21[2048] = {""};
  char str_original[2048] = {""};
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 5; j++) {
      ck_assert_pstr_eq(s21_strncpy(str_s21, test_str[i], num[j]),
                        strncpy(str_original, test_str[i], num[j]));
      ck_assert_str_eq(str_s21, str_original);
    }
}
END_TEST

START_TEST(s21_strncpy_test_2) {
  s21_size_t n1 = 3;
  char b1[1024] = {"1111111111"};
  char b11[1024] = {"1111111111"};
  char str_1_2[1024] = {"123\0"};
  ck_assert_pstr_eq(strncpy(b1, str_1_2, n1), s21_strncpy(b11, str_1_2, n1));
}
END_TEST

START_TEST(s21_strncpy_test_3) {
  s21_size_t n2 = 5;
  char b2[1024] = {"1111111111"};
  char b22[1024] = {"1111111111"};
  char str_2_2[1024] = {"12345\0006789"};
  ck_assert_pstr_eq(strncpy(b2, str_2_2, n2), s21_strncpy(b22, str_2_2, n2));
}
END_TEST

START_TEST(s21_strncpy_test_4) {
  s21_size_t n3 = 5;
  char b3[1024] = {"11"};
  char b33[1024] = {"11"};
  char str_3_2[1024] = {"12345\0006789"};
  ck_assert_pstr_eq(strncpy(b3, str_3_2, n3), s21_strncpy(b33, str_3_2, n3));
}
END_TEST

START_TEST(s21_strncpy_test_5) {
  s21_size_t n3 = 7;
  char b3[1024] = {"228"};
  char b33[1024] = {"228"};
  char str_3_2[1024] = {"12345\0006789"};
  ck_assert_pstr_eq(strncpy(b3, str_3_2, n3), s21_strncpy(b33, str_3_2, n3));
}
END_TEST

START_TEST(s21_strcspn_test_1) {
  char test_str[50][20] = {"Hello, World!", "Hell", "q+=", "do", "", "\0",
                           "Hello\0World!"};
  for (int i = 0; i < 7; i++)
    for (int j = 0; j < 7; j++)
      ck_assert_int_eq(s21_strcspn(test_str[i], test_str[j]),
                       strcspn(test_str[i], test_str[j]));
}
END_TEST

START_TEST(s21_strcspn_test_2) {
  char str1[50] = {"this is a test"};
  ck_assert_int_eq(strcspn(str1, "ab"), s21_strcspn(str1, "ab"));
}
END_TEST

START_TEST(s21_strcspn_test_3) {
  char str2[50] = {"LOST: 4-8-15-16-23-42"};
  ck_assert_int_eq(strcspn(str2, "1234567890"),
                   s21_strcspn(str2, "1234567890"));
}
END_TEST

START_TEST(s21_strcspn_test_4) {
  char str3[50] = {'q', 'r', 's', 't', 'w', 's', 'a', 's', '\0'};
  ck_assert_int_eq(strcspn(str3, "zx"), s21_strcspn(str3, "zx"));
}
END_TEST

START_TEST(s21_strcspn_test_5) {
  char str3[50] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', '\0'};
  ck_assert_int_eq(strcspn(str3, "ZX"), s21_strcspn(str3, "ZX"));
}
END_TEST

START_TEST(s21_strerror_test_1) {
  char *str11 = s21_strerror(10);
  char *str21 = strerror(10);
  ck_assert_str_eq(str11, str21);

  char *str12 = s21_strerror(0);
  char *str22 = strerror(0);
  ck_assert_str_eq(str12, str22);

  char *str14 = s21_strerror(30);
  char *str24 = strerror(30);
  ck_assert_str_eq(str14, str24);

  char *str15 = s21_strerror(11);
  char *str25 = strerror(11);
  ck_assert_str_eq(str15, str25);
}
END_TEST

START_TEST(s21_strerror_test_2) {
  int err_num = 7;
  ck_assert_pstr_eq(strerror(err_num), s21_strerror(err_num));
}
END_TEST

START_TEST(s21_strerror_test_3) {
  int err_num2 = 1;
  ck_assert_pstr_eq(strerror(err_num2), s21_strerror(err_num2));
}
END_TEST

START_TEST(s21_strerror_test_4) {
  int err_num3 = 20;
  ck_assert_pstr_eq(strerror(err_num3), s21_strerror(err_num3));
}
END_TEST

START_TEST(s21_strerror_test_5) {
  int err_num4 = 0;
  ck_assert_pstr_eq(strerror(err_num4), s21_strerror(err_num4));
}
END_TEST

START_TEST(s21_strlen_test_1) {
  char test_str[50][20] = {"Hello, World!", "Hello\0World!\0", "", "\0"};
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(s21_strlen(test_str[i]), strlen(test_str[i]));
}
END_TEST

START_TEST(s21_strlen_test_2) {
  char src[50] = {""};
  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(s21_strlen_test_3) {
  char src[50] = {"christik"};
  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(s21_strlen_test_4) {
  char src[50] = {"987623456124678"};
  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(s21_strlen_test_5) {
  char src[100] = {
      "987623456124678qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"};
  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(s21_strlen_test_6) {
  char src[50] = {"mama\0ne_ponojet"};
  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(s21_strlen_test_7) {
  char src[50] = {"dai_mne_pen(321321)...123...123"};
  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(s21_strlen_test_8) {
  char src[50] = {"Spasibo_papasha"};
  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(s21_strlen_test_9) {
  char src[50] = {"Pelmeni_eto_vkusno"};
  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(s21_strlen_test_10) {
  char src[50] = {"floppa"};
  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(s21_strpbrk_test_1) {
  char test_str[50][20] = {"Hello, World!", "Hell", "q+=", "do", "", "\0",
                           "Hello\0World!"};
  for (int i = 0; i < 7; i++)
    for (int j = 0; j < 7; j++)
      ck_assert_pstr_eq(s21_strpbrk(test_str[i], test_str[j]),
                        strpbrk(test_str[i], test_str[j]));
}
END_TEST

START_TEST(s21_strpbrk_test_2) {
  char str1[50] = {""};
  char str2[50] = {""};
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(s21_strpbrk_test_3) {
  char str1[50] = {"floppa"};
  char str2[50] = {""};
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(s21_strpbrk_test_4) {
  char str1[50] = {""};
  char str2[50] = {"floppa"};
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(s21_strpbrk_test_5) {
  char str1[50] = {"poki doki"};
  char str2[50] = {"o"};
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(s21_strpbrk_test_6) {
  char str1[50] = {"poki doki"};
  char str2[50] = {"i"};
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(s21_strpbrk_test_7) {
  char str1[50] = {"poki doki"};
  char str2[50] = {"p"};
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(s21_strpbrk_test_8) {
  char str1[50] = {"ppppppppppppP"};
  char str2[50] = {"P"};
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(s21_strpbrk_test_9) {
  char str1[50] = {"ppppppppppppP"};
  char str2[50] = {"\0"};
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(s21_strrchr_test_1) {
  char test_str[50][20] = {"Hello, World!", "Hello\0World!\0", "", "\0"};
  int test_char[50] = {'l', '!', '/', '\0', 'q'};
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 5; j++)
      ck_assert_pstr_eq(s21_strrchr(test_str[i], test_char[j]),
                        strrchr(test_str[i], test_char[j]));
}
END_TEST

START_TEST(s21_strrchr_test_2) {
  char str[50] = {"0163456769"};
  ck_assert_pstr_eq(strrchr(str, '6'), s21_strrchr(str, '6'));
}
END_TEST

START_TEST(s21_strrchr_test_3) {
  char str2[50] = {"mcgalinka@gmail.com"};
  ck_assert_pstr_eq(strrchr(str2, 'o'), s21_strrchr(str2, 'o'));
}
END_TEST

START_TEST(s21_strrchr_test_4) {
  char str3[50] = {"mcgalinka@gmail.com"};
  ck_assert_pstr_eq(strrchr(str3, 'h'), s21_strrchr(str3, 'h'));
}
END_TEST

START_TEST(s21_strrchr_test_5) {
  char str4[50] = {""};
  ck_assert_pstr_eq(strrchr(str4, 'd'), s21_strrchr(str4, 'd'));
}
END_TEST

START_TEST(s21_strrchr_test_6) {
  char str5[50] = {""};
  ck_assert_pstr_eq(strrchr(str5, 'z'), s21_strrchr(str5, 'z'));
}
END_TEST

START_TEST(s21_strspn_test_1) {
  char test_str[50][20] = {"Hello, World!", "Hell", "q+=", "d!", "", "\0",
                           "Hello\0World!"};
  for (int i = 0; i < 7; i++)
    for (int j = 0; j < 7; j++)
      ck_assert_int_eq(s21_strspn(test_str[i], test_str[j]),
                       strspn(test_str[i], test_str[j]));
}
END_TEST

START_TEST(s21_strspn_test_2) {
  char str[50] = {"12-years"};
  ck_assert_int_eq(strspn(str, "1234567890"), s21_strspn(str, "1234567890"));
}
END_TEST

START_TEST(s21_strspn_test_3) {
  char str2[50] = {"this is a test"};
  ck_assert_int_eq(strspn(str2, "shit "), s21_strspn(str2, "shit "));
}
END_TEST

START_TEST(s21_strspn_test_4) {
  char str3[50] = {'q', 'r', 's', 't', 'w', 's', 'a', 's'};
  ck_assert_int_eq(strspn(str3, "01234"), s21_strspn(str3, "01234"));
}
END_TEST

START_TEST(s21_strspn_test_5) {
  char str3[50] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'I', 'O'};
  ck_assert_int_eq(strspn(str3, "01234"), s21_strspn(str3, "01234"));
}
END_TEST

START_TEST(s21_strstr_test_1) {
  char test_str[50][20] = {"Hello, World!", "Hell", "q+=", "d!", "", "\0",
                           "Hello\0World!"};
  for (int i = 0; i < 7; i++)
    for (int j = 0; j < 7; j++)
      ck_assert_pstr_eq(s21_strstr(test_str[i], test_str[j]),
                        strstr(test_str[i], test_str[j]));
}
END_TEST

START_TEST(s21_strstr_test_2) {
  char str[50] = {""};
  ck_assert_pstr_eq(strstr(str, ""), s21_strstr(str, ""));
}
END_TEST

START_TEST(s21_strstr_test_3) {
  char str2[50] = {"john.smith@mic\0rosoft.com"};
  ck_assert_pstr_eq(strstr(str2, "sm"), s21_strstr(str2, "sm"));
}
END_TEST

START_TEST(s21_strstr_test_4) {
  char str3[50] = {'q', 'r', 's', 't', 'w', 's', 'a', 's', '\0'};
  ck_assert_pstr_eq(strstr(str3, "woo"), s21_strstr(str3, "woo"));
}
END_TEST

START_TEST(s21_strtok_test_1) {
  char input_s21_strtok_str[50] = {"Тут была christik - абоба."};
  char input_original_strtok_str[50] = {"Тут была christik - абоба."};
  char delim[50] = {",.-"};
  char *out_s21_strtok_pch = s21_strtok(input_s21_strtok_str, delim);
  char *out_original_strtok_pch = strtok(input_original_strtok_str, delim);
  while ((out_s21_strtok_pch != NULL) || (out_original_strtok_pch != NULL)) {
    ck_assert_pstr_eq(out_s21_strtok_pch, out_original_strtok_pch);
    out_original_strtok_pch = strtok(NULL, delim);
    out_s21_strtok_pch = s21_strtok(NULL, delim);
  }
  ck_assert_ptr_null(out_s21_strtok_pch);
  ck_assert_ptr_null(out_original_strtok_pch);
}
END_TEST

START_TEST(s21_strtok_test_2) {
  char input_s21_strtok_str[50] = {"Тут была christik - абоба."};
  char input_original_strtok_str[50] = {"Тут была christik - абоба."};
  char delim[50] = {"%_+="};
  char *out_s21_strtok_pch = s21_strtok(input_s21_strtok_str, delim);
  char *out_original_strtok_pch = strtok(input_original_strtok_str, delim);
  while ((out_s21_strtok_pch != NULL) || (out_original_strtok_pch != NULL)) {
    ck_assert_pstr_eq(out_s21_strtok_pch, out_original_strtok_pch);
    out_original_strtok_pch = strtok(NULL, delim);
    out_s21_strtok_pch = s21_strtok(NULL, delim);
  }
  ck_assert_ptr_null(out_s21_strtok_pch);
  ck_assert_ptr_null(out_original_strtok_pch);
}
END_TEST

START_TEST(s21_strtok_test_3) {
  char input_s21_strtok_str[50] = {"$$$$$$$$$$"};
  char input_original_strtok_str[50] = {"$$$$$$$$$$"};
  char delim[50] = {"$"};
  char *out_s21_strtok_pch = s21_strtok(input_s21_strtok_str, delim);
  char *out_original_strtok_pch = strtok(input_original_strtok_str, delim);
  while ((out_s21_strtok_pch != NULL) || (out_original_strtok_pch != NULL)) {
  }
  ck_assert_ptr_null(out_s21_strtok_pch);
  ck_assert_ptr_null(out_original_strtok_pch);
}
END_TEST

START_TEST(s21_strtok_test_4) {
  char input_s21_strtok_str[50] = {""};
  char input_original_strtok_str[50] = {""};
  char delim[50] = {"%_+="};
  char *out_s21_strtok_pch = s21_strtok(input_s21_strtok_str, delim);
  char *out_original_strtok_pch = strtok(input_original_strtok_str, delim);
  while ((out_s21_strtok_pch != NULL) || (out_original_strtok_pch != NULL)) {
  }
  ck_assert_ptr_null(out_s21_strtok_pch);
  ck_assert_ptr_null(out_original_strtok_pch);
}
END_TEST

START_TEST(s21_strtok_test_5) {
  char input_s21_strtok_str[50] = {"Тут была christik\0 - абоба."};
  char input_original_strtok_str[50] = {"Тут была christik\0 - абоба."};
  char delim[50] = {",.-"};
  char *out_s21_strtok_pch = s21_strtok(input_s21_strtok_str, delim);
  char *out_original_strtok_pch = strtok(input_original_strtok_str, delim);
  while ((out_s21_strtok_pch != NULL) || (out_original_strtok_pch != NULL)) {
    ck_assert_pstr_eq(out_s21_strtok_pch, out_original_strtok_pch);
    out_original_strtok_pch = strtok(NULL, delim);
    out_s21_strtok_pch = s21_strtok(NULL, delim);
  }
  ck_assert_ptr_null(out_s21_strtok_pch);
  ck_assert_ptr_null(out_original_strtok_pch);
}
END_TEST

START_TEST(s21_strtok_test_6) {
  char input_s21_strtok_str[50] = {"Тут была christik\\абоба\\абобус."};
  char input_original_strtok_str[50] = {"Тут была christik\\абоба\\абобус."};
  char delim[50] = {"\\"};
  char *out_s21_strtok_pch = s21_strtok(input_s21_strtok_str, delim);
  char *out_original_strtok_pch = strtok(input_original_strtok_str, delim);
  while ((out_s21_strtok_pch != NULL) || (out_original_strtok_pch != NULL)) {
    ck_assert_pstr_eq(out_s21_strtok_pch, out_original_strtok_pch);
    out_original_strtok_pch = strtok(NULL, delim);
    out_s21_strtok_pch = s21_strtok(NULL, delim);
  }
  ck_assert_ptr_null(out_s21_strtok_pch);
  ck_assert_ptr_null(out_original_strtok_pch);
}
END_TEST

START_TEST(s21_strtok_test_7) {
  char input_s21_strtok_str[50] = {"Тут была christik - абоба."};
  char input_original_strtok_str[50] = {"Тут была christik - абоба."};
  char delim[50] = {""};
  char *out_s21_strtok_pch = s21_strtok(input_s21_strtok_str, delim);
  char *out_original_strtok_pch = strtok(input_original_strtok_str, delim);
  while ((out_s21_strtok_pch != NULL) || (out_original_strtok_pch != NULL)) {
    ck_assert_pstr_eq(out_s21_strtok_pch, out_original_strtok_pch);
    out_original_strtok_pch = strtok(NULL, delim);
    out_s21_strtok_pch = s21_strtok(NULL, delim);
  }
  ck_assert_ptr_null(out_s21_strtok_pch);
  ck_assert_ptr_null(out_original_strtok_pch);
}
END_TEST

START_TEST(s21_strtok_test_8) {
  char str4_1[50] = {"/testing/with/original/string.h/"};
  char str4_2[50] = {"/testing/with/original/string.h/"};
  char del4[3] = {"/"};
  char *nstr_1, *nstr_2;
  nstr_1 = strtok(str4_1, del4);
  nstr_2 = s21_strtok(str4_2, del4);
  while (nstr_1 != s21_NULL) {
    ck_assert_pstr_eq(nstr_1, nstr_2);
    nstr_1 = strtok(s21_NULL, del4);
    nstr_2 = s21_strtok(s21_NULL, del4);
  }
}
END_TEST

START_TEST(s21_strtok_test_9) {
  char str4_1[50] = {". . testing with original string.h"};
  char str4_2[50] = {". . testing with original string.h"};
  char del4[3] = {". "};
  char *nstr_1, *nstr_2;
  nstr_1 = strtok(str4_1, del4);
  nstr_2 = s21_strtok(str4_2, del4);
  while (nstr_1 != s21_NULL) {
    ck_assert_pstr_eq(nstr_1, nstr_2);
    nstr_1 = strtok(s21_NULL, del4);
    nstr_2 = s21_strtok(s21_NULL, del4);
  }
}
END_TEST

START_TEST(s21_strtok_test_10) {
  char str4_1[50] = {"testing with original string.h"};
  char str4_2[50] = {"testing with original string.h"};
  char del4[3] = {". "};
  char *nstr_1, *nstr_2;
  nstr_1 = strtok(str4_1, del4);
  nstr_2 = s21_strtok(str4_2, del4);
  while (nstr_1 != s21_NULL) {
    ck_assert_pstr_eq(nstr_1, nstr_2);
    nstr_1 = strtok(s21_NULL, del4);
    nstr_2 = s21_strtok(s21_NULL, del4);
  }
}
END_TEST

START_TEST(s21_to_upper_test_1) {
  char test_str[100] = {
      "Hello, World! ABCabc..XYZxyz 0123456789 ±!@#$%^&*()_+-=*/"};
  char out_expected[100] = {
      "HELLO, WORLD! ABCABC..XYZXYZ 0123456789 ±!@#$%^&*()_+-=*/"};
  char *out_s21 = s21_to_upper(test_str);
  ck_assert_str_eq(out_s21, out_expected);
  free(out_s21);
}
END_TEST

START_TEST(s21_to_upper_test_2) {
  char test_str[50] = {""};
  char out_expected[50] = {""};
  char *out_s21 = s21_to_upper(test_str);
  ck_assert_str_eq(out_s21, out_expected);
  free(out_s21);
}
END_TEST

START_TEST(s21_to_lower_test_1) {
  char test_str[70] = {
      "Hello, World! ABCabc..XYZxyz 0123456789 ±!@#$%^&*()_+-=*/"};
  char out_expected[70] = {
      "hello, world! abcabc..xyzxyz 0123456789 ±!@#$%^&*()_+-=*/"};
  char *out_s21 = s21_to_lower(test_str);
  ck_assert_str_eq(out_s21, out_expected);
  free(out_s21);
}
END_TEST

START_TEST(s21_to_lower_test_2) {
  char test_str[50] = {""};
  char out_expected[50] = {""};
  char *out_s21 = s21_to_lower(test_str);
  ck_assert_str_eq(out_s21, out_expected);
  free(out_s21);
}
END_TEST

START_TEST(s21_insert_test_1) {
  char test_str[50] = {"Hello, World!"};
  char ins[50] = {"_hop-hey lalaley_"};
  s21_size_t index = 0;
  char out_expected[50] = {"_hop-hey lalaley_Hello, World!"};
  char *out_s21 = (char *)s21_insert(test_str, ins, index);
  ck_assert_str_eq(out_s21, out_expected);
  if (out_s21) free(out_s21);
}
END_TEST

START_TEST(s21_insert_test_2) {
  char test_str[50] = {"Hello, World!"};
  char ins[50] = {"_hop-hey lalaley_"};
  s21_size_t index = 6;
  char out_expected[50] = {"Hello,_hop-hey lalaley_ World!"};
  char *out_s21 = (char *)s21_insert(test_str, ins, index);
  ck_assert_str_eq(out_s21, out_expected);
  if (out_s21) free(out_s21);
}
END_TEST

START_TEST(s21_insert_test_3) {
  char test_str[50] = {"Hello, World!"};
  char ins[50] = {"_hop-hey lalaley_"};
  s21_size_t index = 50;
  char *out_expected = s21_NULL;
  char *out_s21 = (char *)s21_insert(test_str, ins, index);
  ck_assert_pstr_eq(out_s21, out_expected);
  if (out_s21) free(out_s21);
}
END_TEST

START_TEST(s21_insert_test_5) {
  char *test_str = s21_NULL;
  char *ins = s21_NULL;
  s21_size_t index = 10;
  char *out_expected = s21_NULL;
  char *out_s21 = (char *)s21_insert(test_str, ins, index);
  ck_assert_pstr_eq(out_s21, out_expected);
  if (out_s21) free(out_s21);
}
END_TEST

START_TEST(s21_trim_test_1) {
  char test_str[50] = {""};
  char trims[50] = {""};
  char out_expected[50] = {""};
  char *out_s21 = s21_trim(test_str, trims);
  ck_assert_pstr_eq(out_s21, out_expected);
  if (out_s21) free(out_s21);
}
END_TEST

START_TEST(s21_trim_test_2) {
  char test_str[50] = {""};
  char trims[50] = {"@#$<fuck up>$%^"};
  char out_expected[50] = {""};
  char *out_s21 = s21_trim(test_str, trims);
  ck_assert_pstr_eq(out_s21, out_expected);
  if (out_s21) free(out_s21);
}
END_TEST

START_TEST(s21_trim_test_3) {
  char test_str[50] = {"  <^ u%p>   Hello, World!c $ #@ k  "};
  char trims[50] = {""};
  char out_expected[50] = {"<^ u%p>   Hello, World!c $ #@ k"};
  char *out_s21 = s21_trim(test_str, trims);
  ck_assert_pstr_eq(out_s21, out_expected);
  if (out_s21) free(out_s21);
}
END_TEST

START_TEST(sscanf_only_chars1) {
  char fstr[] = "%c %c %c %c";
  char str[] = "   a     b c d";
  int32_t a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);

  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_only_chars2) {
  char fstr[] = "%c%c%c%c";
  char str[] = "abcd";
  int32_t a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);

  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_only_chars3) {
  char fstr[] = "%c %c %c      %c";
  char str[] = "1 a 3   c           ";
  int32_t a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_only_chars4) {
  char fstr[] = "%c %c %c %c";
  char str[] = "   000 0    ";
  int32_t a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);

  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_only_chars5) {
  char fstr[] = "%c %c %c %c";
  char str[] = "tttt";
  int32_t a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);

  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_special_symbols_as_chars1) {
  char fstr[] = "%c%c%c%c";
  char str[] = "\\\n\t\t\t";
  int32_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_special_symbols_as_chars2) {
  char fstr[] = "%c %c %c %c";
  char str[] = "z ' ' /";
  int32_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_special_symbols_as_chars3) {
  char fstr[] = "%c%*c%c%c";
  char str[] = "ABCD";
  int32_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1);

  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}

END_TEST

START_TEST(sscanf_chars_flags1) {
  char fstr[] = "%c %c %c %c";
  char str[] = "z *'@";
  int32_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_chars_flags2) {
  char fstr[] = "%1c %c %c %0c";
  char str[] = "z *'@";
  int32_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_chars_flags3) {
  char fstr[] = "%c %c %c %c";
  char str[] = "z *'@";
  int32_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_chars_aster1) {
  char fstr[] = "%*c%*c%*c%*c";
  char str[] = "   c ";
  int32_t a1 = 0, a2 = 0;

  int32_t res1 = s21_sscanf(str, fstr, &a1);
  int32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_chars_aster2) {
  char fstr[] = "%*c%*c%*c%c";
  char str[] = "abcd ";
  int32_t a1 = 0, a2 = 0;

  int32_t res1 = s21_sscanf(str, fstr, &a1);
  int32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_only_ints1) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char fstr[] = "%ld %ld %ld %ld";
  const char str[] = "555 666 777 888";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_only_ints2) {
  int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "1337 21 5008 3000";
  const char fstr[] = "%hd %hd %hd %hd";

  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_only_ints3) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "1337 21 5008 300004";
  const char fstr[] = "%lld %lld %lld %lld";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_ints_nwidth4) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "1337";
  const char fstr[] = "%15lld %1lld %1lld %1lld";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_ints_astwidth1) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  const char str[] = "1337123123 1 123412341234 1 999999 0";
  const char fstr[] = "%*d %lld %*d %lld %*d %lld";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}

END_TEST

START_TEST(sscanf_ints_astwidth2) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "1337";
  const char fstr[] = "%15lld %1lld %1lld %1lld";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_ints_astwidth3) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "1337";
  const char fstr[] = "%15lld %1lld %1lld %1lld";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_ints_astwidth4) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "1337";
  const char fstr[] = "%15lld %1lld %1lld %1lld";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_signed_ints1) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "11337 ++3 -5 ------4";
  const char fstr[] = "%lld %lld %lld %lld";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

END_TEST

START_TEST(sscanf_signed_ints4) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "1 01 10 0";
  const char fstr[] = "%lld %lld %lld %lld";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_spec_i_int1) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "300 500 -600 +700";
  const char fstr[] = "%lli %lli %lli %lli";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_spec_i_int2) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "300500-600+700 111";
  const char fstr[] = "%lli %lld %lld %lli";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_spec_i_int3) {
  long long a1 = 0, a2 = 0, c1 = 0, c2 = 0;
  char b1 = 0, b2 = 0, d1 = 0, d2 = 0;
  const char str[] = "300500-600+700+400";
  const char fstr[] = "%lli%c%lli%c";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(c1, c2);
}

END_TEST

START_TEST(sscanf_spec_i_int4) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "  55555 f f f5555555 ddd   4    3    1 ";
  const char fstr[] = "%lli %lld %lld %lli";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_spec_i_hex1) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "0xFFF 0xA123123 0x123123 0x0";
  const char fstr[] = "%lli %lld %lld %lli";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

// [%s] //
START_TEST(sscanf_strings1) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};

  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};
  char s8[BUFF_SIZE] = {'\0'};

  const char str[] = "Aboba Floppa Keppa Shleppa Anuroba";
  const char fstr[] = "%s %s %s %s";

  int32_t res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
  int32_t res2 = sscanf(str, fstr, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}

END_TEST

START_TEST(sscanf_strings_mixed3) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};

  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};
  char s8[BUFF_SIZE] = {'\0'};

  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char str[] = "Aboba 123 Floppa -3 Keppa 4444Shleppa 333Anuroba 3";
  const char fstr[] = "%s%ld%s%d%s%d%s";

  int32_t res1 = s21_sscanf(str, fstr, s1, &a1, s2, &b1, s3, &c1, s4, &d1);
  int32_t res2 = s21_sscanf(str, fstr, s5, &a2, s6, &b2, s7, &c2, s8, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}

END_TEST

START_TEST(sscanf_strings2) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};

  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};
  char s8[BUFF_SIZE] = {'\0'};

  const char str[] = "aboba\tshlepa\tasdfasdf\tasdfasdf";
  const char fstr[] = "%s%s%s%s";

  int32_t res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
  int32_t res2 = sscanf(str, fstr, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}

END_TEST

START_TEST(sscanf_strings3) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};

  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};
  char s8[BUFF_SIZE] = {'\0'};

  const char str[] = "aboba\tkepaboba floppa shleppa koooppa ap p p p p";
  const char fstr[] = "%*s%*s%*s%*s";

  int32_t res1 = s21_sscanf(str, fstr);
  int32_t res2 = sscanf(str, fstr);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}

END_TEST

START_TEST(sscanf_strings4) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};

  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};
  char s8[BUFF_SIZE] = {'\0'};

  const char str[] = "aboba\tshlepa\tasdfasdf\tasdfasdf";
  const char fstr[] = "%1s%1s%1s%1s";

  int32_t res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
  int32_t res2 = sscanf(str, fstr, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}

END_TEST

START_TEST(sscanf_strings5) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};

  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};
  char s8[BUFF_SIZE] = {'\0'};

  const char str[] = "aboba\tshlepa\tasdfasdf\tasdfasdf";
  const char fstr[] = "%3s%3s%3s%3s";

  int32_t res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
  int32_t res2 = sscanf(str, fstr, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}

END_TEST

START_TEST(sscanf_strings6) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};

  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};
  char s8[BUFF_SIZE] = {'\0'};

  const char str[] = "aboba\tshlepa\tasdfasdf\tasdfasdf";
  const char fstr[] = "%150s%1s%1s\t%3s";

  int32_t res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
  int32_t res2 = sscanf(str, fstr, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}

END_TEST

START_TEST(sscanf_strings_mixed2) {
  int d1 = 0, d2 = 0, b1 = 0, b2 = 0, a1 = 0, a2 = 0;
  long long v1, v2;

  const char str[] = "1 1 1 1 1 -1";
  const char fstr[] = "%1s %5d %1s %1s %d %lld %d";

  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};
  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};

  int32_t res1 = s21_sscanf(str, fstr, s1, &a1, s2, s3, &b1, &v1, &d1);
  int32_t res2 = sscanf(str, fstr, s4, &a2, s5, s6, &b2, &v2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(s1, s2);
  ck_assert_str_eq(s3, s4);
  ck_assert_str_eq(s5, s6);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

// [%n] //
START_TEST(sscanf_n1) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int32_t n1 = 0, n2 = 5;

  const char str[BUFF_SIZE] = "50 160 70 80";
  const char fstr[BUFF_SIZE] = "%lli %lli %n %lli %lli";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &n1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &n2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_n2) {
  int n1 = 1, n2 = 5;

  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};

  const char str[] = "cbobErobM fl? asdfasdflkasdf asdfasdf asdfasdf 88888";
  const char fstr[] = "%s %s %n %s";

  int32_t res1 = s21_sscanf(str, fstr, s1, s2, &n1, s3);
  int32_t res2 = sscanf(str, fstr, s5, s6, &n2, s7);

  ck_assert_int_eq(res1, res2);

  ck_assert_int_eq(n1, n2);
  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
}

END_TEST

START_TEST(sscanf_n3) {
  int n1 = 0, n2 = 5;

  const char str[BUFF_SIZE] = "50 60 70 80";
  const char fstr[BUFF_SIZE] = "%n";

  int32_t res1 = s21_sscanf(str, fstr, &n1);
  int32_t res2 = sscanf(str, fstr, &n2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
}

END_TEST

START_TEST(sscanf_n4) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int32_t n1 = 0, n2 = 5;

  const char str[] = "50 60 70 80";
  const char fstr[] = "%lli %lli %n %lli %lli";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &n1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &n2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_n5) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int n1 = 0, n2 = 5;

  const char str[] = "50 60 70 80";
  const char fstr[] = "%lli %lli %n %lli %lli";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &n1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &n2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}

END_TEST

// [%f] / [%g] / %[%G] //
START_TEST(sscanf_floats1) {
  long double a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0, d1 = 1, d2 = 0;

  const char str[] = "53.1 -4.1135 41.3333 +2.0001";
  const char fstr[] = "%Lf %Lf %Lf %Lf";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq_tol(a1, a2, 1e-6);
  ck_assert_double_eq_tol(b1, b2, 1e-6);
  ck_assert_double_eq_tol(c1, c2, 1e-6);
  ck_assert_double_eq_tol(d1, d2, 1e-6);
}

END_TEST

START_TEST(sscanf_floats2) {
  double a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char str[] = "0.00001 -4123123 4. .";
  const char fstr[] = "%lf %lf %lf %lf";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq_tol(a1, a2, 1e-6);
  ck_assert_double_eq_tol(b1, b2, 1e-6);
  ck_assert_double_eq_tol(c1, c2, 1e-6);
  ck_assert_double_eq_tol(d1, d2, 1e-6);
}

END_TEST

START_TEST(sscanf_floats3) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char str[] = ". . . .";
  const char fstr[] = "%f %f %f %f";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_floats4) {
  long double a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char str[] = "513.41 -4.14135 414.3333 +112.0001";
  const char fstr[] = "%Lf %Lf %Lf %Lf";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq_tol(a1, a2, 1e-6);
  ck_assert_double_eq_tol(b1, b2, 1e-6);
  ck_assert_double_eq_tol(c1, c2, 1e-6);
  ck_assert_double_eq_tol(d1, d2, 1e-6);
}

END_TEST

START_TEST(sscanf_floats_sci3) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char str[] = "inF InF inF INF";
  const char fstr[] = "%G %G %G %G";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_floats_sci1) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char str[] = " 1.4441 1.31e+4 -3.31e-4 0.444e-5";
  const char fstr[] = "%G %G %G %G";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_uint3) {
  unsigned long long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  long long d1 = 0, d2 = 0;
  long double v1, v2;

  const char str[] =
      "\t\t\t\t\t\n 3      adsfdfa%$$$$`adfasdfasdfaszcvzcxvcv -1337 "
      "anurobich+ 21 -5008 -33000 0.3333";
  const char fstr[] = "%*s %*s %llu %s %llu %llu %lld %Lf";

  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};

  int32_t res1 = s21_sscanf(str, fstr, &a1, s1, &b1, &c1, &d1, &v1);
  int32_t res2 = sscanf(str, fstr, &a2, s2, &b2, &c2, &d2, &v2);

  ck_assert_uint_eq(res1, res2);
  ck_assert_str_eq(s1, s2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_ldouble_eq_tol(v1, v2, 0.0001);
}

END_TEST

START_TEST(sscanf_upeer_hex_base_version) {
  uint32_t a1, a2;
  const char str[] = "F";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_upeer_hex_overflow) {
  uint32_t a1, a2;
  const char str[] = "0xFFFFFFFF";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_upeer_hex_0X) {
  uint32_t a1, a2;
  const char str[] = "A";
  const char fstr[] = "%X";
  s21_sscanf(str, fstr, &a1);
  sscanf(str, fstr, &a2);

  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_upeer_hex_fail) {
  uint32_t a1, a2;
  const char str[] = "qF";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
}

END_TEST

START_TEST(sscanf_upeer_hex_short) {
  uint16_t a1, a2;
  const char str[] = "F";
  const char fstr[] = "%hX";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_upeer_hex_long) {
  unsigned long int a1, a2;
  const char str[] = "F";
  const char fstr[] = "%lX";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_upeer_hex_longlong) {
  unsigned long long int a1, a2;
  const char str[] = "F";
  const char fstr[] = "%llX";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_upeer_hex_2x) {
  uint32_t a1, a2;
  const char str[] = "0xFF0x0xFFF 0xFFxFF";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_upeer_hex_star) {
  const char str[] = "0xFF0x0xFFF 0xFFxFF";
  const char fstr[] = "%*X";
  uint32_t res1 = s21_sscanf(str, fstr);
  uint32_t res2 = sscanf(str, fstr);

  ck_assert_int_eq(res1, res2);
}

END_TEST

START_TEST(sscanf_upeer_hex_nohex) {
  uint32_t a1, a2;
  const char str[] = "tqwqpl";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
}

END_TEST

START_TEST(sscanf_upeer_hex_lower) {
  uint32_t a1, a2;
  const char str[] = "abcdef";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_upeer_hex_sign) {
  uint32_t a1, a2;
  const char str[] = "-f";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_lower_hex_base_version) {
  uint32_t a1, a2;
  const char str[] = "f";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_lower_hex_overflow) {
  uint32_t a1, a2;
  const char str[] = "0xfffffffffffffffffff";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_lower_hex_0x) {
  uint32_t a1, a2;
  const char str[] = "a";
  const char fstr[] = "%x";
  s21_sscanf(str, fstr, &a1);
  sscanf(str, fstr, &a2);

  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_lower_hex_fail) {
  uint32_t a1, a2;
  const char str[] = "qF";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
}

END_TEST

START_TEST(sscanf_lower_hex_short) {
  uint16_t a1, a2;
  const char str[] = "ff";
  const char fstr[] = "%hx";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_lower_hex_long) {
  unsigned long int a1, a2;
  const char str[] = "ff";
  const char fstr[] = "%lx";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_lower_hex_2x) {
  uint32_t a1, a2;
  const char str[] = "0xFF0x0xFFF 0xFFxFF";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_lower_hex_star) {
  const char str[] = "0xFF0x0xFFF 0xFFxFF";
  const char fstr[] = "%*x";
  uint32_t res1 = s21_sscanf(str, fstr);
  uint32_t res2 = sscanf(str, fstr);

  ck_assert_int_eq(res1, res2);
}

END_TEST

START_TEST(sscanf_lower_hex_nohex) {
  uint32_t a1, a2;
  const char str[] = "tqwqpl";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
}

END_TEST

START_TEST(sscanf_lower_hex_lower) {
  uint32_t a1, a2;
  const char str[] = "abcdef";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_lower_hex_sign) {
  uint32_t a1, a2;
  const char str[] = "-f";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_octal_base_version) {
  uint32_t a1, a2;
  const char str[] = "777";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_octal_overflow) {
  uint32_t a1, a2;
  const char str[] = "0x7777777777777777777777";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_octal_0x) {
  uint32_t a1, a2;
  const char str[] = "0x";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_octal_0X) {
  uint32_t a1, a2;
  const char str[] = "0X";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_octal_fail) {
  uint32_t a1, a2;
  const char str[] = "q1";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
}

END_TEST

START_TEST(sscanf_octal_short) {
  uint16_t a1, a2;
  const char str[] = "12";
  const char fstr[] = "%ho";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_octal_long) {
  unsigned long int a1, a2;
  const char str[] = "57234";
  const char fstr[] = "%lo";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_octal_longlong) {
  unsigned long long int a1, a2;
  const char str[] = "12356226137";
  const char fstr[] = "%llo";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_octal_2x) {
  uint32_t a1, a2;
  const char str[] = "0x12320x213x123213";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_octal_star) {
  const char str[] = "521561612";
  const char fstr[] = "%*o";
  uint32_t res1 = s21_sscanf(str, fstr);
  uint32_t res2 = sscanf(str, fstr);

  ck_assert_int_eq(res1, res2);
}

END_TEST

START_TEST(sscanf_octal_nohex) {
  uint32_t a1, a2;
  const char str[] = "tqwqpl";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
}

END_TEST

START_TEST(sscanf_octal_lower) {
  uint32_t a1, a2;
  const char str[] = "01234567";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_octal_sign) {
  uint32_t a1, a2;
  const char str[] = "-66";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(sscanf_buff1) {
  int32_t a1, a2;
  int32_t b1, b2;
  const char str[] = "12 keppa 12";
  const char fstr[] = "%d keppa %d";
  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}

END_TEST

START_TEST(sscanf_buff2) {
  int32_t a1, a2;
  int32_t b1, b2;
  const char str[] = "12keppa12";
  const char fstr[] = "%dkeppa%d";
  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}

END_TEST

START_TEST(sscanf_pointer1) {
  void *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;
  const char str[] = "0xFFFF 0xAAAA 0x7123 0xBBC1FF";
  const char fstr[] = "%p %p %p %p";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_perc1) {
  const char str[] = "%%%";
  const char fstr[] = "%%%%%%";
  int32_t res1 = s21_sscanf(str, fstr);
  int32_t res2 = sscanf(str, fstr);

  ck_assert_int_eq(res1, res2);
}

END_TEST

START_TEST(sscanf_mixed_ptrs1) {
  void *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;

  const char str[] = "0x4 0x3 0x2 0x1";
  const char fstr[] = "%p %p %p %p";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}

END_TEST

START_TEST(sscanf_hard1) {
  int a1 = 0, a2 = 5, a3 = 3, a4 = 9;
  int32_t n1 = 500, n2 = 10000;

  const char str[] = "123123SkipMePlease!!!!123";
  const char fstr[] = "%dSkipMePlease!!!!%d %n";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &a3, &n1);
  int32_t res2 = sscanf(str, fstr, &a2, &a4, &n2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(a3, a4);
  ck_assert_int_eq(n1, n2);
}

END_TEST

START_TEST(s21_sprintf_test1) {
  char str1[100];
  char str2[100];
  void *p = (void *)0x3456;
  int n1, n2;
  int r1 = sprintf(str1, "%d%o%s%c%i%e%f%E%g%u%x%G%X%n%p%%%s", 25, 342, "aboba",
                   'a', 123, 25.34, 4325.23434, 0.0000000123, 2.12345, 12345u,
                   8342, 0.0000456, 1235, &n1, p, "hello my friend");
  int r2 =
      s21_sprintf(str2, "%d%o%s%c%i%e%f%E%g%u%x%G%X%n%p%%%s", 25, 342, "aboba",
                  'a', 123, 25.34, 4325.23434, 0.0000000123, 2.12345, 12345u,
                  8342, 0.0000456, 1235, &n2, p, "hello my friend");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test2) {
  char str1[100];
  char str2[100];
  int r1 = sprintf(str1, "%+-25.3d%25.15o%#10.f%015d", 252, 243, 256.34, 15);
  int r2 =
      s21_sprintf(str2, "%+-25.3d%25.15o%#10.f%015d", 252, 243, 256.34, 15);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test3) {
  char str1[100];
  char str2[100];
  int r1 = sprintf(str1, "%#+34.10g%#.10x%#15.1o%25.10s", 25.3456, 1234, 4567,
                   "HELLOMYDEARFRIEND");
  int r2 = s21_sprintf(str2, "%#+34.10g%#.10x%#15.1o%25.10s", 25.3456, 1234,
                       4567, "HELLOMYDEARFRIEND");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test4) {
  char str1[100];
  char str2[100];
  void *p = (void *)43252342;
  int r1 = sprintf(str1, "%#24.e%-15.20i%20p%020u", 43253242.4342, 4567899, p,
                   43252342u);
  int r2 = s21_sprintf(str2, "%#24.e%-15.20i%20p%020u", 43253242.4342, 4567899,
                       p, 43252342u);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
  char str3[50];
  char str4[100];
  int r3 = sprintf(str3, "%*.0f", 25, 25432.34345);
  int r4 = s21_sprintf(str4, "%*.0f", 25, 25432.34345);
  ck_assert_str_eq(str3, str4);
  ck_assert_int_eq(r3, r4);
}
END_TEST

START_TEST(s21_sprintf_test_d) {
  char str1[1000];
  char str2[1000];
  short h = 34;
  int r1 = sprintf(
      str1, "%-25.10d%-30.2d%10.12d%11d%*d%*.*d%+-25.*d%+10.2ld%-11.*hd", 253,
      335, 1234, 34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, h);
  int r2 = s21_sprintf(
      str2, "%-25.10d%-30.2d%10.12d%11d%*d%*.*d%+-25.*d%+10.2ld%-11.*hd", 253,
      335, 1234, 34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, h);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_i) {
  char str1[1000];
  char str2[1000];
  short h = 34;
  long l = 2353423523424;
  int r1 = sprintf(str1, "%+50.i%-10.20i%10.i%012i%*.*i%-10.*i%+10.1li%*.25hi",
                   34567, 225, 5230, 125, 10, 5, 456, 10, 377, l, 12, h);
  int r2 =
      s21_sprintf(str2, "%+50.i%-10.20i%10.i%012i%*.*i%-10.*i%+10.1li%*.25hi",
                  34567, 225, 5230, 125, 10, 5, 456, 10, 377, l, 12, h);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_f) {
  char str1[1000];
  char str2[1000];
  int r1 = sprintf(
      str1, "%+-10.5f%+10.2f%15.16f%+*.10f%*.16f%-10.*f%25.*f%25.f%#+10.f%*.*f",
      2546.4324, 3452.4325, 5678.43256, 25, 456789.243242, 10, 3456789123.43245,
      2, 12345.6788, 1, 34.4325432, 4325678.43242, 34567.2345432, 10, 2,
      34567.43244);
  int r2 = s21_sprintf(
      str2, "%+-10.5f%+10.2f%15.16f%+*.10f%*.16f%-10.*f%25.*f%25.f%#+10.f%*.*f",
      2546.4324, 3452.4325, 5678.43256, 25, 456789.243242, 10, 3456789123.43245,
      2, 12345.6788, 1, 34.4325432, 4325678.43242, 34567.2345432, 10, 2,
      34567.43244);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_o) {
  char str1[1000];
  char str2[1000];
  unsigned short h = 253;
  unsigned long l = 4325234324242l;
  int r1 = sprintf(str1, "%-25.10o%-10o%#-30.2o%#*.10o%#*.*o%25.*o%#.10ho%*lo",
                   12345, 6532, 43522, 10, 64342, 15, 2, 343, 6, 678, h, 10, l);
  int r2 =
      s21_sprintf(str2, "%-25.10o%-10o%#-30.2o%#*.10o%#*.*o%25.*o%#.10ho%*lo",
                  12345, 6532, 43522, 10, 64342, 15, 2, 343, 6, 678, h, 10, l);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_x) {
  char str1[1000];
  char str2[1000];
  unsigned short h = 345;
  unsigned long l = 52342353242l;
  int r1 = sprintf(str1,
                   "%x%-25x%#10x%#-10x%#10.5x%-25.34x%#-10.2x%*.*x%#*.10x%20.*"
                   "x%#10.*x%*.5hx%10.25lx",
                   235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15, 3452,
                   8, 23452, 10, 34254, 3, 33334, 10, h, l);
  int r2 = s21_sprintf(str2,
                       "%x%-25x%#10x%#-10x%#10.5x%-25.34x%#-10.2x%*.*x%#*.10x%"
                       "20.*x%#10.*x%*.5hx%10.25lx",
                       235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15,
                       3452, 8, 23452, 10, 34254, 3, 33334, 10, h, l);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_X) {
  char str1[1000];
  char str2[1000];
  unsigned short h = 234;
  unsigned long l = 4325243132l;
  int r1 = sprintf(str1,
                   "%X%-10X%15X%#-15X%#20.3X%-30.12X%#-12.3X%*.*X%#*.15X%21.*X%"
                   "#12.*X%*.8hx%14.12lX",
                   235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15, 3452,
                   8, 23452, 10, 34254, 3, 33334, 10, h, l);
  int r2 = s21_sprintf(str2,
                       "%X%-10X%15X%#-15X%#20.3X%-30.12X%#-12.3X%*.*X%#*.15X%"
                       "21.*X%#12.*X%*.8hx%14.12lX",
                       235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15,
                       3452, 8, 23452, 10, 34254, 3, 33334, 10, h, l);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_u) {
  char str1[1000];
  char str2[1000];
  unsigned short h = 115;
  unsigned long l = 123325242342l;
  int r1 =
      sprintf(str1, "%u%15u%-20u%010u%-15.10u%20.*u%*.*u%*.10u%-20.12lu%19hu",
              4321u, 34567u, 2342u, 12346u, 234542u, 10, 234523u, 10, 5, 2345u,
              20, 2432u, l, h);
  int r2 = s21_sprintf(
      str2, "%u%15u%-20u%010u%-15.10u%20.*u%*.*u%*.10u%-20.12lu%19hu", 4321u,
      34567u, 2342u, 12346u, 234542u, 10, 234523u, 10, 5, 2345u, 20, 2432u, l,
      h);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_s) {
  char str1[1000];
  char str2[1000];
  wchar_t s[10] = {'h', 'e', 'l', 'l', 'o'};
  // wchar_t s[10] = {'п', 'р', 'и', 'в', 'е', 'т'};
  int r1 = sprintf(str1, "%s%23s%-15s%10.s%15.2s%16.*s%*.*s%*s%15ls%15.3ls",
                   "aboba", "helloworld", "ABOBA", "ABOBBAAA", "AAABOBA", 10,
                   "QWERTY", 15, 4, "AAAAABOOOOOBAAA", 10, "ABOBAAAAA", s, s);
  int r2 =
      s21_sprintf(str2, "%s%23s%-15s%10.s%15.2s%16.*s%*.*s%*s%15ls%15.3ls",
                  "aboba", "helloworld", "ABOBA", "ABOBBAAA", "AAABOBA", 10,
                  "QWERTY", 15, 4, "AAAAABOOOOOBAAA", 10, "ABOBAAAAA", s, s);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_p) {
  char str1[1000];
  char str2[1000];
  void *p1 = (void *)0x123456789;
  void *p2 = (void *)4325234;
  void *p3 = (void *)0x123f324b;
  void *p4 = (void *)432520;
  int r1 = sprintf(str1, "%p%20p%-15p%10p%-15p%*p%10p%*p", p1, p2, p3, p4, p2,
                   10, p3, p1, 10, p4);
  int r2 = s21_sprintf(str2, "%p%20p%-15p%10p%-15p%*p%10p%*p", p1, p2, p3, p4,
                       p2, 10, p3, p1, 10, p4);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_percent) {
  char str1[1000];
  char str2[1000];
  int r1 = sprintf(str1, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
  int r2 = s21_sprintf(str2, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_g) {
  char str1[1000];
  char str2[1000];
  int r1 = sprintf(
      str1, "%g%23g%-10g%015g%#10.5g%0#15.10g%+10.6g%#*.g%-10.*g%+#25.8g",
      2345.4324, 23445.2342, 1234.234242, 3456.3424, 0.00001234, -324234.234,
      2345.4234, 5, 23456.4324, 9, 234567.43242, 0.0000034);
  int r2 = s21_sprintf(
      str2, "%g%23g%-10g%015g%#10.5g%0#15.10g%+10.6g%#*.g%-10.*g%+#25.8g",
      2345.4324, 23445.2342, 1234.234242, 3456.3424, 0.00001234, -324234.234,
      2345.4234, 5, 23456.4324, 9, 234567.43242, 0.0000034);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_G) {
  char str1[1000];
  char str2[1000];
  int r1 = sprintf(
      str1,
      "%G%25G%#-15G%017G%#05.2G%#010.16G%+#8.6G%*.8G%#-10.*G%+#12.16G%*.*G",
      43242.43242, 123432.43242, 0000.1234, -34252.43242, 1234.5,
      111.432534243243242, 4324.43242, 25, -3213.43242, 16, -43.43242353242342,
      111.24324242, 25, 5, 0.000000342);
  int r2 = s21_sprintf(
      str2,
      "%G%25G%#-15G%017G%#05.2G%#010.16G%+#8.6G%*.8G%#-10.*G%+#12.16G%*.*G",
      43242.43242, 123432.43242, 0000.1234, -34252.43242, 1234.5,
      111.432534243243242, 4324.43242, 25, -3213.43242, 16, -43.43242353242342,
      111.24324242, 25, 5, 0.000000342);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

Suite *test_suite_s21_sprintf() {
  Suite *s = suite_create("test_suite_s21_sprintf");
  TCase *tc = tcase_create("test_case_s21_sprintf");

  tcase_add_test(tc, s21_sprintf_test1);
  tcase_add_test(tc, s21_sprintf_test2);
  tcase_add_test(tc, s21_sprintf_test3);
  tcase_add_test(tc, s21_sprintf_test4);
  tcase_add_test(tc, s21_sprintf_test_d);
  tcase_add_test(tc, s21_sprintf_test_i);
  tcase_add_test(tc, s21_sprintf_test_f);
  tcase_add_test(tc, s21_sprintf_test_o);
  tcase_add_test(tc, s21_sprintf_test_x);
  tcase_add_test(tc, s21_sprintf_test_X);
  tcase_add_test(tc, s21_sprintf_test_u);
  tcase_add_test(tc, s21_sprintf_test_s);
  tcase_add_test(tc, s21_sprintf_test_p);
  tcase_add_test(tc, s21_sprintf_test_percent);
  tcase_add_test(tc, s21_sprintf_test_g);
  tcase_add_test(tc, s21_sprintf_test_G);

  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_sscanf() {
  Suite *s = suite_create("test_suite_s21_sscanf");
  TCase *tc = tcase_create("test_suite_s21_sscanf");
  tcase_add_test(tc, sscanf_only_chars1);
  tcase_add_test(tc, sscanf_only_chars2);
  tcase_add_test(tc, sscanf_only_chars3);
  tcase_add_test(tc, sscanf_only_chars4);
  tcase_add_test(tc, sscanf_only_chars5);
  tcase_add_test(tc, sscanf_special_symbols_as_chars1);
  tcase_add_test(tc, sscanf_special_symbols_as_chars2);
  tcase_add_test(tc, sscanf_special_symbols_as_chars3);
  tcase_add_test(tc, sscanf_chars_flags1);
  tcase_add_test(tc, sscanf_chars_flags2);
  tcase_add_test(tc, sscanf_chars_flags3);
  tcase_add_test(tc, sscanf_chars_aster1);
  tcase_add_test(tc, sscanf_chars_aster2);
  tcase_add_test(tc, sscanf_only_ints1);
  tcase_add_test(tc, sscanf_only_ints2);
  tcase_add_test(tc, sscanf_only_ints3);

  tcase_add_test(tc, sscanf_ints_nwidth4);
  tcase_add_test(tc, sscanf_ints_astwidth1);
  tcase_add_test(tc, sscanf_ints_astwidth2);
  tcase_add_test(tc, sscanf_ints_astwidth3);
  tcase_add_test(tc, sscanf_ints_astwidth4);
  tcase_add_test(tc, sscanf_signed_ints1);

  tcase_add_test(tc, sscanf_signed_ints4);
  tcase_add_test(tc, sscanf_spec_i_int1);
  tcase_add_test(tc, sscanf_spec_i_int2);
  tcase_add_test(tc, sscanf_spec_i_int3);
  tcase_add_test(tc, sscanf_spec_i_int4);

  tcase_add_test(tc, sscanf_spec_i_hex1);

  tcase_add_test(tc, sscanf_strings1);
  tcase_add_test(tc, sscanf_strings2);
  tcase_add_test(tc, sscanf_strings3);
  tcase_add_test(tc, sscanf_strings4);
  tcase_add_test(tc, sscanf_strings5);
  tcase_add_test(tc, sscanf_strings6);

  tcase_add_test(tc, sscanf_uint3);

  tcase_add_test(tc, sscanf_strings_mixed2);
  tcase_add_test(tc, sscanf_strings_mixed3);
  tcase_add_test(tc, sscanf_floats1);
  tcase_add_test(tc, sscanf_floats2);
  tcase_add_test(tc, sscanf_floats3);
  tcase_add_test(tc, sscanf_floats4);
  tcase_add_test(tc, sscanf_floats_sci3);
  tcase_add_test(tc, sscanf_floats_sci1);
  tcase_add_test(tc, sscanf_n1);
  tcase_add_test(tc, sscanf_n2);
  tcase_add_test(tc, sscanf_n3);
  tcase_add_test(tc, sscanf_n4);
  tcase_add_test(tc, sscanf_n5);
  tcase_add_test(tc, sscanf_upeer_hex_base_version);
  tcase_add_test(tc, sscanf_upeer_hex_overflow);
  tcase_add_test(tc, sscanf_upeer_hex_0X);
  tcase_add_test(tc, sscanf_upeer_hex_fail);

  tcase_add_test(tc, sscanf_upeer_hex_short);
  tcase_add_test(tc, sscanf_upeer_hex_long);
  tcase_add_test(tc, sscanf_upeer_hex_longlong);
  tcase_add_test(tc, sscanf_upeer_hex_2x);
  tcase_add_test(tc, sscanf_upeer_hex_star);
  tcase_add_test(tc, sscanf_upeer_hex_nohex);
  tcase_add_test(tc, sscanf_upeer_hex_lower);
  tcase_add_test(tc, sscanf_upeer_hex_sign);

  tcase_add_test(tc, sscanf_lower_hex_base_version);
  tcase_add_test(tc, sscanf_lower_hex_overflow);
  tcase_add_test(tc, sscanf_lower_hex_0x);

  tcase_add_test(tc, sscanf_lower_hex_fail);

  tcase_add_test(tc, sscanf_lower_hex_short);
  tcase_add_test(tc, sscanf_lower_hex_long);
  tcase_add_test(tc, sscanf_lower_hex_2x);
  tcase_add_test(tc, sscanf_lower_hex_star);
  tcase_add_test(tc, sscanf_lower_hex_nohex);
  tcase_add_test(tc, sscanf_lower_hex_lower);
  tcase_add_test(tc, sscanf_lower_hex_sign);
  tcase_add_test(tc, sscanf_octal_base_version);
  tcase_add_test(tc, sscanf_octal_overflow);
  tcase_add_test(tc, sscanf_octal_0x);
  tcase_add_test(tc, sscanf_octal_0X);

  tcase_add_test(tc, sscanf_octal_fail);

  tcase_add_test(tc, sscanf_octal_short);
  tcase_add_test(tc, sscanf_octal_long);
  tcase_add_test(tc, sscanf_octal_longlong);
  tcase_add_test(tc, sscanf_octal_2x);
  tcase_add_test(tc, sscanf_octal_star);
  tcase_add_test(tc, sscanf_octal_nohex);
  tcase_add_test(tc, sscanf_octal_lower);
  tcase_add_test(tc, sscanf_octal_sign);
  tcase_add_test(tc, sscanf_pointer1);
  tcase_add_test(tc, sscanf_buff1);
  tcase_add_test(tc, sscanf_buff2);
  tcase_add_test(tc, sscanf_perc1);
  tcase_add_test(tc, sscanf_mixed_ptrs1);
  tcase_add_test(tc, sscanf_hard1);

  suite_add_tcase(s, tc);

  return s;
}

Suite *test_suite_s21_memchr() {
  Suite *s = suite_create("test_suite_s21_memchr");
  TCase *tc = tcase_create("test_case_s21_memchr");
  tcase_add_test(tc, s21_memchr_test_1);
  tcase_add_test(tc, s21_memchr_test_2);
  tcase_add_test(tc, s21_memchr_test_3);
  tcase_add_test(tc, s21_memchr_test_5);
  tcase_add_test(tc, s21_memchr_test_6);
  tcase_add_test(tc, s21_memchr_test_7);
  tcase_add_test(tc, s21_memchr_test_8);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_memcmp() {
  Suite *s = suite_create("test_suite_s21_memcmp");
  TCase *tc = tcase_create("test_case_s21_memcmp");
  tcase_add_test(tc, s21_memcmp_test_1);
  tcase_add_test(tc, s21_memcmp_test_2);
  tcase_add_test(tc, s21_memcmp_test_3);
  tcase_add_test(tc, s21_memcmp_test_4);
  tcase_add_test(tc, s21_memcmp_test_5);
  tcase_add_test(tc, s21_memcmp_test_6);
  tcase_add_test(tc, s21_memcmp_test_7);
  tcase_add_test(tc, s21_memcmp_test_8);
  tcase_add_test(tc, s21_memcmp_test_10);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_memcpy() {
  Suite *s = suite_create("test_suite_s21_memcpy");
  TCase *tc = tcase_create("test_case_s21_memcpy");
  tcase_add_test(tc, s21_memcpy_test_1);
  tcase_add_test(tc, s21_memcpy_test_2);
  tcase_add_test(tc, s21_memcpy_test_3);
  tcase_add_test(tc, s21_memcpy_test_4);
  tcase_add_test(tc, s21_memcpy_test_5);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_memmove() {
  Suite *s = suite_create("test_suite_s21_memmove");
  TCase *tc = tcase_create("test_case_s21_memmove");
  tcase_add_test(tc, s21_memmove_test_1);
  tcase_add_test(tc, s21_memmove_test_2);
  tcase_add_test(tc, s21_memmove_test_3);
  tcase_add_test(tc, s21_memmove_test_4);
  tcase_add_test(tc, s21_memmove_test_5);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_memset() {
  Suite *s = suite_create("test_suite_s21_memset");
  TCase *tc = tcase_create("test_case_s21_memset");
  tcase_add_test(tc, s21_memset_test_1);
  tcase_add_test(tc, s21_memset_test_2);
  tcase_add_test(tc, s21_memset_test_3);
  tcase_add_test(tc, s21_memset_test_4);
  tcase_add_test(tc, s21_memset_test_5);
  tcase_add_test(tc, s21_memset_test_6);
  tcase_add_test(tc, s21_memset_test_7);
  tcase_add_test(tc, s21_memset_test_8);
  tcase_add_test(tc, s21_memset_test_9);
  tcase_add_test(tc, s21_memset_test_10);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_strcat() {
  Suite *s = suite_create("test_suite_s21_strcat");
  TCase *tc = tcase_create("test_case_s21_strcat");
  tcase_add_test(tc, s21_strcat_test_1);
  tcase_add_test(tc, s21_strcat_test_2);
  tcase_add_test(tc, s21_strcat_test_3);
  tcase_add_test(tc, s21_strcat_test_4);
  tcase_add_test(tc, s21_strcat_test_5);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_strncat() {
  Suite *s = suite_create("test_suite_s21_strncat");
  TCase *tc = tcase_create("test_case_s21_strncat");
  tcase_add_test(tc, s21_strncat_test_1);
  tcase_add_test(tc, s21_strncat_test_2);
  tcase_add_test(tc, s21_strncat_test_3);
  tcase_add_test(tc, s21_strncat_1);
  tcase_add_test(tc, s21_strncat_2);
  tcase_add_test(tc, s21_strncat_3);
  tcase_add_test(tc, s21_strncat_4);
  tcase_add_test(tc, strncat_zero_char);
  tcase_add_test(tc, strncat_BIGFLOPPA4);
  tcase_add_test(tc, strncat_BIGFLOPPA3);
  tcase_add_test(tc, strncat_BIGFLOPPA2);
  tcase_add_test(tc, strncat_BIGFLOPPA);

  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_strchr() {
  Suite *s = suite_create("test_suite_s21_strchr");
  TCase *tc = tcase_create("test_case_s21_strchr");
  tcase_add_test(tc, s21_strchr_test_1);
  tcase_add_test(tc, s21_strchr_test_2);
  tcase_add_test(tc, s21_strchr_test_3);
  tcase_add_test(tc, s21_strchr_test_4);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_strcmp() {
  Suite *s = suite_create("test_suite_s21_strcmp");
  TCase *tc = tcase_create("test_case_s21_strcmp");
  tcase_add_test(tc, s21_strcmp_test_1);
  tcase_add_test(tc, s21_strcmp_test_2);
  tcase_add_test(tc, s21_strcmp_test_3);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_strncmp() {
  Suite *s = suite_create("test_suite_s21_strncmp");
  TCase *tc = tcase_create("test_case_s21_strncmp");
  tcase_add_test(tc, s21_strncmp_test_1);
  tcase_add_test(tc, s21_strncmp_test_2);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_strcpy() {
  Suite *s = suite_create("test_suite_s21_strcpy");
  TCase *tc = tcase_create("test_case_s21_strcpy");
  tcase_add_test(tc, s21_strcpy_test_1);
  tcase_add_test(tc, s21_strcpy_test_2);
  tcase_add_test(tc, s21_strcpy_test_3);
  tcase_add_test(tc, s21_strcpy_test_4);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_strncpy() {
  Suite *s = suite_create("test_suite_s21_strncpy");
  TCase *tc = tcase_create("test_case_s21_strncpy");
  tcase_add_test(tc, s21_strncpy_test_1);
  tcase_add_test(tc, s21_strncpy_test_2);
  tcase_add_test(tc, s21_strncpy_test_3);
  tcase_add_test(tc, s21_strncpy_test_4);
  tcase_add_test(tc, s21_strncpy_test_5);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_strcspn() {
  Suite *s = suite_create("test_suite_s21_strcspn");
  TCase *tc = tcase_create("test_case_s21_strcspn");
  tcase_add_test(tc, s21_strcspn_test_1);
  tcase_add_test(tc, s21_strcspn_test_2);
  tcase_add_test(tc, s21_strcspn_test_3);
  tcase_add_test(tc, s21_strcspn_test_4);
  tcase_add_test(tc, s21_strcspn_test_5);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_strerror() {
  Suite *s = suite_create("test_suite_s21_strerror");
  TCase *tc = tcase_create("test_case_s21_strerror");
  tcase_add_test(tc, s21_strerror_test_1);
  tcase_add_test(tc, s21_strerror_test_2);
  tcase_add_test(tc, s21_strerror_test_3);
  tcase_add_test(tc, s21_strerror_test_4);
  tcase_add_test(tc, s21_strerror_test_5);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_strlen() {
  Suite *s = suite_create("test_suite_s21_strlen");
  TCase *tc = tcase_create("test_case_s21_strlen");
  tcase_add_test(tc, s21_strlen_test_1);
  tcase_add_test(tc, s21_strlen_test_2);
  tcase_add_test(tc, s21_strlen_test_3);
  tcase_add_test(tc, s21_strlen_test_4);
  tcase_add_test(tc, s21_strlen_test_5);
  tcase_add_test(tc, s21_strlen_test_6);
  tcase_add_test(tc, s21_strlen_test_7);
  tcase_add_test(tc, s21_strlen_test_8);
  tcase_add_test(tc, s21_strlen_test_9);
  tcase_add_test(tc, s21_strlen_test_10);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_strpbrk() {
  Suite *s = suite_create("test_suite_s21_strpbrk");
  TCase *tc = tcase_create("test_case_s21_strpbrk");
  tcase_add_test(tc, s21_strpbrk_test_1);
  tcase_add_test(tc, s21_strpbrk_test_2);
  tcase_add_test(tc, s21_strpbrk_test_3);
  tcase_add_test(tc, s21_strpbrk_test_4);
  tcase_add_test(tc, s21_strpbrk_test_5);
  tcase_add_test(tc, s21_strpbrk_test_6);
  tcase_add_test(tc, s21_strpbrk_test_7);
  tcase_add_test(tc, s21_strpbrk_test_8);
  tcase_add_test(tc, s21_strpbrk_test_9);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_strrchr() {
  Suite *s = suite_create("test_suite_s21_strrchr");
  TCase *tc = tcase_create("test_case_s21_strrchr");
  tcase_add_test(tc, s21_strrchr_test_1);
  tcase_add_test(tc, s21_strrchr_test_2);
  tcase_add_test(tc, s21_strrchr_test_3);
  tcase_add_test(tc, s21_strrchr_test_4);
  tcase_add_test(tc, s21_strrchr_test_5);
  tcase_add_test(tc, s21_strrchr_test_6);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_strspn() {
  Suite *s = suite_create("test_suite_s21_strspn");
  TCase *tc = tcase_create("test_case_s21_strspn");
  tcase_add_test(tc, s21_strspn_test_1);
  tcase_add_test(tc, s21_strspn_test_2);
  tcase_add_test(tc, s21_strspn_test_3);
  tcase_add_test(tc, s21_strspn_test_4);
  tcase_add_test(tc, s21_strspn_test_5);

  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_strstr() {
  Suite *s = suite_create("test_suite_s21_strstr");
  TCase *tc = tcase_create("test_case_s21_strstr");
  tcase_add_test(tc, s21_strstr_test_1);
  tcase_add_test(tc, s21_strstr_test_2);
  tcase_add_test(tc, s21_strstr_test_3);
  tcase_add_test(tc, s21_strstr_test_4);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_strtok() {
  Suite *s = suite_create("test_suite_s21_strtok");
  TCase *tc = tcase_create("test_suite_s21_strtok");
  tcase_add_test(tc, s21_strtok_test_1);
  tcase_add_test(tc, s21_strtok_test_2);
  tcase_add_test(tc, s21_strtok_test_3);
  tcase_add_test(tc, s21_strtok_test_4);
  tcase_add_test(tc, s21_strtok_test_5);
  tcase_add_test(tc, s21_strtok_test_6);
  tcase_add_test(tc, s21_strtok_test_7);
  tcase_add_test(tc, s21_strtok_test_8);
  tcase_add_test(tc, s21_strtok_test_9);
  tcase_add_test(tc, s21_strtok_test_10);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_to_upper() {
  Suite *s = suite_create("test_suite_s21_to_upper");
  TCase *tc = tcase_create("test_case_s21_to_upper");
  tcase_add_test(tc, s21_to_upper_test_1);
  tcase_add_test(tc, s21_to_upper_test_2);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_to_lower() {
  Suite *s = suite_create("test_suite_s21_to_lower");
  TCase *tc = tcase_create("test_case_s21_to_lower");
  tcase_add_test(tc, s21_to_lower_test_1);
  tcase_add_test(tc, s21_to_lower_test_2);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_insert() {
  Suite *s = suite_create("test_suite_s21_insert");
  TCase *tc = tcase_create("test_case_s21_insert");
  tcase_add_test(tc, s21_insert_test_1);
  tcase_add_test(tc, s21_insert_test_2);
  tcase_add_test(tc, s21_insert_test_3);
  tcase_add_test(tc, s21_insert_test_5);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_trim() {
  Suite *s = suite_create("test_suite_s21_trim");
  TCase *tc = tcase_create("test_case_s21_trim");
  tcase_add_test(tc, s21_trim_test_1);
  tcase_add_test(tc, s21_trim_test_2);
  tcase_add_test(tc, s21_trim_test_3);
  suite_add_tcase(s, tc);
  return s;
}

int main() {
  int no_failed = 0;
  Suite *test_suites[50] = {test_suite_s21_memchr(),
                            test_suite_s21_memcmp(),
                            test_suite_s21_memcpy(),
                            test_suite_s21_memmove(),
                            test_suite_s21_memset(),
                            test_suite_s21_strcat(),
                            test_suite_s21_strncat(),
                            test_suite_s21_strchr(),
                            test_suite_s21_strcmp(),
                            test_suite_s21_strncmp(),
                            test_suite_s21_strcpy(),
                            test_suite_s21_strncpy(),
                            test_suite_s21_strcspn(),
                            test_suite_s21_strerror(),
                            test_suite_s21_strlen(),
                            test_suite_s21_strpbrk(),
                            test_suite_s21_strrchr(),
                            test_suite_s21_strspn(),
                            test_suite_s21_strstr(),
                            test_suite_s21_strtok(),
                            test_suite_s21_to_upper(),
                            test_suite_s21_to_lower(),
                            test_suite_s21_insert(),
                            test_suite_s21_trim(),
                            test_suite_s21_sscanf(),
                            test_suite_s21_sprintf(),

                            NULL};
  for (Suite **suite = test_suites; *suite != NULL; suite++) {
    SRunner *runner = srunner_create(*suite);
    srunner_run_all(runner, CK_NORMAL);
    no_failed += srunner_ntests_failed(runner);
    srunner_free(runner);
  }
  return no_failed;
}
