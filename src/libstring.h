/**
 * libstring — String manipulation library
 * 
 * Copyright © 2015  Mattias Andrée (maandree@member.fsf.org)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LIBSTRING_H
#define LIBSTRING_H

#include <stddef.h>


#ifdef __GNUC__
# define LIBSTRING_GCC_ONLY(...)  __VA_ARGS__
# define LIBSTRING_COMMON         __malloc__, __warn_unused_result__, __nonnull__
# define LIBSTRING_LEAF           __leaf__, LIBSTRING_COMMON
#else
# define LIBSTRING_GCC_ONLY(...)  /* ignore */
#endif



/**
 * Flags for `libstring_split`.
 */
enum libstring_split
{
  /**
   * Match from right to left, rather
   * than from left to right.
   */
  LIBSTRING_SPLIT_FROM_RIGHT = 1,
  
  /**
   * Ignore case when matching.
   */
  LIBSTRING_SPLIT_IGNORE_CASE = 2,
};


/**
 * Flags for `libstring_replace`.
 */
enum libstring_replace
{
  /**
   * Match from right to left, rather
   * than from left to right.
   */
  LIBSTRING_REPLACE_FROM_RIGHT = 1,
  
  /**
   * Ignore case when matching.
   */
  LIBSTRING_REPLACE_IGNORE_CASE = 2,
};


/**
 * Flags for `libstring_length`.
 */
enum libstring_length
{
  /**
   * Do not count combining diacritical
   * marks as contributing to the length
   * of the string.
   */
  LIBSTRING_LENGTH_IGNORE_COMBINING = 1,
  
  /**
   * Guess how many columns will be used
   * when displayed in a terminal. Unless
   * `LIBSTRING_LENGTH_IGNORE_COMBINING`
   * is also used, combining diacritical
   * marks ware assumed to not combine.
   */
  LIBSTRING_LENGTH_DISPLAY_LENGTH = 2,
};


/**
 * Flags for `libstring_utf8verify`.
 */
enum libstring_utf8verify
{
  /**
   * Accept 0xC0 0x80 as a valid
   * byte sequence.
   */
  LIBSTRING_UTF8VERIFY_MOD_UTF8 = 1,
  
  /**
   * Do not require that characters are
   * encoded with as short byte sequence
   * as possible. This implies
   * `LIBSTRING_UTF8VERIFY_MOD_UTF8`.
   */
  LIBSTRING_UTF8VERIFY_LAX = 2,
  
  /**
   * Use the old specification: characters
   * are at most 31 bits, rather than the
   * new standard: 10FFFF is the highest
   * character (end if plane 16.)
   */
  LIBSTRING_UTF8VERIFY_31_BITS = 4,
  
  /**
   * Implies `LIBSTRING_UTF8VERIFY_31_BITS`
   * but extends to one additional bits,
   * allowing negative code points for
   * private use.
   */
  LIBSTRING_UTF8VERIFY_32_BITS = 8,
  
  /**
   * Implies `LIBSTRING_UTF8VERIFY_32_BITS` 
   * but extend to allow 8 bytes (42 bits),
   * which is the highest that can be encoded
   * with only one byte that specifies the
   * width of the sequence.
   */
  LIBSTRING_UTF8VERIFY_8_BYTES = 16,
};


/**
 * Flags for `libstring_cut` and `libstring_vcut`.
 */
enum libstring_cut
{
  /**
   * Match from right to left, rather than
   * from left to right.
   */
  LIBSTRING_CUT_FROM_RIGHT = 1,
  
  /**
   * Ignore case when matching.
   */
  LIBSTRING_CUT_IGNORE_CASE = 2,
  
  /**
   * Fields are returned in sorted order,
   * rather than the specified order.
   */
  LIBSTRING_CUT_ORDERED = 4,
  
  /**
   * The all fields except the specified
   * fields shall be returned. This
   * implies `LIBSTRING_CUT_ORDERED`.
   */
  LIBSTRING_CUT_COMPLEMENT = 8,
};


/**
 * Flags for `libstring_substring`.
 */
enum libstring_substring
{
  /**
   * The third parameter is the length
   * rather than the end.
   */
  LIBSTRING_SUBSTRING_LENGTH = 1,
  
  /**
   * Count from the end rather than from
   * the beginning.
   */
  LIBSTRING_SUBSTRING_FROM_END = 2,
  
  /**
   * Indicies are of bytes rather than
   * of characters.
   */
  LIBSTRING_SUBSTRING_BYTES = 4,
};


/**
 * Flags for `libstring_trim`.
 * 
 * If neither `LIBSTRING_TRIM_LEFT`,
 * `LIBSTRING_TRIM_RIGHT`, nor
 * `LIBSTRING_TRIM_DUPLICATES` is specified,
 * `LIBSTRING_TRIM_LEFT` and `LIBSTRING_TRIM_RIGHT`
 * will be used.
 */
enum libstring_trim
{
  /**
   * Trim the beginning.
   */
  LIBSTRING_TRIM_LEFT = 1,
  
  /**
   * Trim the end.
   */
  LIBSTRING_TRIM_RIGHT = 2,
  
  /**
   * Deduplicate characters.
   */
  LIBSTRING_TRIM_DUPLICATES = 4,
};


/**
 * Flags for `libstring_reverse`.
 */
enum libstring_reverse
{
  /**
   * Treat combining diacritical marks
   * as part of the letters it is on.
   */
  LIBSTRING_REVERSE_KEEP_COMBINING = 1,
};


enum libstring_expand
{
  /**
   * Do not count combining diacritical
   * marks as contributing to the length
   * of the string.
   */
  LIBSTRING_EXPAND_IGNORE_COMBINING = 1,
  
  /**
   * Guess how many columns will be used
   * when displayed in a terminal. Unless
   * `LIBSTRING_LENGTH_IGNORE_COMBINING`
   * is also used, combining diacritical
   * marks ware assumed to not combine.
   */
  LIBSTRING_EXPAND_DISPLAY_LENGTH = 2,
  
  /**
   * Do not count backspaces as
   * contributing negatively to the length
   * of the string.
   */
  LIBSTRING_EXPAND_IGNORE_BACKSPACE = 4,
  
  /**
   * Only expand beginning of the line,
   * stop at any other character space
   * and tab space. This implies
   * `LIBSTRING_EXPAND_IGNORE_BACKSPACE`.
   */
  LIBSTRING_EXPAND_INITIAL_ONLY = 8,
};



/**
 * Concatenate strings.
 * 
 * Example:
 *   const char* strings[] = {"alpha", "bet", "s", NULL};
 *   s = libstring_cat(strings, NULL);
 *   # s is "alphabets"
 *   free(s);
 * 
 * Example:
 *   const char* strings[] = {"alpha", "bet", "s"};
 *   size_t n = 3;
 *   s = libstring_cat(strings, &n);
 *   # s is "alphabets"
 *   free(s);
 * 
 * @param   strings  List of strings to concatenate, must
 *                   not be `NULL` or contain `NULL`:s.
 * @param   n        Either a pointer the number of strings
 *                   stored in `strings`, or `NULL` if
 *                   `strings` is `NULL`-terminated.
 * @return           A string with all strings in `strings`
 *                   concatenated in order, without any
 *                   delimiter. `NULL` on error.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_COMMON(1))))
char* libstring_cat(const char* const*, const size_t*);
#ifdef LIBSTRING_SHORT_NAMES
# define strmulcat  libstring_cat
#endif


/**
 * Concatenate strings.
 * 
 * Example:
 *   s = libstring_vcat("alpha", "bet", "s", NULL);
 *   # s is "alphabets"
 *   free(s);
 * 
 * @param   strings...  List of strings to concatenate, end
 *                      with a `NULL`.
 * @return              A string with all strings in `strings`
 *                      concatenated in order, without any
 *                      delimiter. `NULL` on error.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF, __sentinel__(0))))
char* libstring_vcat(const char*, ... /*, (char*)0 */);
#ifdef LIBSTRING_SHORT_NAMES
# define vstrmulcat  libstring_vcat
#endif


/**
 * Concatenate strings and insert a delimiter between the strings.
 * 
 * Example:
 *   const char* strings[] = {"alpha", "bet", "s", NULL};
 *   s = libstring_join(strings, NULL, "--");
 *   # s is "alpha--bet--s"
 *   free(s);
 * 
 * Example:
 *   const char* strings[] = {"alpha", "bet", "s"};
 *   size_t n = 3;
 *   s = libstring_join(strings, &n, "--");
 *   # s is "alpha--bet--s"
 *   free(s);
 * 
 * @param   strings    List of strings to join, must
 *                     not be `NULL` or contain `NULL`:s.
 * @param   n          Either a pointer the number of strings
 *                     stored in `strings`, or `NULL` if
 *                     `strings` is `NULL`-terminated.
 * @param   delimiter  A string to insert between all strings.
 * @return             A string with all strings in `strings`
 *                     concatenated in order, with the
 *                     delimiter `delimiter`. `NULL` on error.
 * 
 * @throws  ENOMEM  The process cannot enough memory.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_COMMON(1, 3))))
char* libstring_join(const char* const*, const size_t*, const char*);
#ifdef LIBSTRING_SHORT_NAMES
# define strjoin  libstring_join
#endif


/**
 * Concatenate strings and insert a delimiter between the strings.
 * 
 * Example:
 *   s = libstring_vjoin("alpha", "bet", "s", NULL, "--");
 *   # s is "alpha--bet--s"
 *   free(s);
 * 
 * @param   strings...  List of strings to concatenate, end
 *                      with a `NULL`.
 * @param   delimiter   A string to insert between all strings.
 * @return              A string with all strings in `strings`
 *                      concatenated in order, with the
 *                      delimiter `delimiter`. `NULL` on error.
 * 
 * @throws  ENOMEM  The process cannot enough memory.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF, __sentinel__(1))))
char* libstring_vjoin(const char*, ... /*, (char*)0, const char* */);
#ifdef LIBSTRING_SHORT_NAMES
# define vstrjoin  libstring_vjoin
#endif


/**
 * TODO
 * 
 * @param   string     String to split.
 * @param   delimiter  The delimiter.
 * @param   n          Output parameter for the number of
 *                     strings in the returned list. May be `NULL`.
 * @param   flags      Additional options.
 * @return             `NULL`-terminated list of the substrings in
 *                     `string` which had `delimiter` between them.
 *                     `NULL` on error.
 * 
 * @throws  ENOMEM  The process cannot enough memory.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF(1, 2))))
char** libstring_split(const char*, const char*, size_t*, enum libstring_split);
#ifdef LIBSTRING_SHORT_NAMES
# define strsplit  libstring_split
#endif


/**
 * TODO
 * 
 * @param   string  The string to manipulate.
 * @param   from    Substring to replace.
 * @param   to      String to substitute for `from`.
 * @param   flags   Additional options.
 * @return          `string` with `to` substituted for `from`.
 *                  `NULL` on error.
 * 
 * @throws  ENOMEM  The process cannot enough memory.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF)))
char* libstring_replace(const char*, const char*, const char*, enum libstring_replace);
#ifdef LIBSTRING_SHORT_NAMES
# define strreplace  libstring_replace
#endif


/**
 * `r = libstring_shellsafe(s)` is equivalent to
 * `t = libstring_replace(s, "'", "'\''", 0);
 *  if ((r = malloc(strlen(t) + 3)))
 *    *r = '\'', strcpy(stpcpy(r + 1, t), "'");
 *  r;`.
 * You guess what it does, and why.
 * 
 * @param   string  The string to manipulate.
 * @return          The result. `NULL` on error.
 * 
 * @throws  ENOMEM  The process cannot enough memory.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF)))
char* libstring_shellsafe(const char*);
#ifdef LIBSTRING_SHORT_NAMES
# define strshsafe  libstring_shellsafe
#endif


/**
 * Measure the length of a string.
 * 
 * @param   string  The string to measure.
 * @param   flags   Additional options.
 * @return          The length of `string`.
 */
LIBSTRING_GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __leaf__)))
size_t libstring_length(const char*, enum libstring_length);
#ifdef LIBSTRING_SHORT_NAMES
# define strdisplen  libstring_length
#endif


/**
 * Validate teh encoding of a string.
 * 
 * @param   string  The string to validate.
 * @param   flags   Additional options.
 * @return          0 if the string is valid, -1 otherwise.
 */
LIBSTRING_GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __leaf__)))
int libstring_utf8verify(const char*, enum libstring_utf8verify);
#ifdef LIBSTRING_SHORT_NAMES
# define strverify  libstring_utf8verify
#endif


/**
 * TODO
 * 
 * @param   string     The string to cut.
 * @param   delimiter  The delimiter.
 * @param   fields     List of fields to return.
 * @param   fields_n   The number of elements in `fields`.
 * @param   n          Output parameter for the number of
 *                     returned fields. May be `NULL`.
 * @param   flags      Additional options.
 * @return             `NULL`-terminated list of the
 *                     found fields. `NULL` on error.
 * 
 * @throws  ENOMEM  The process cannot enough memory.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_COMMON(1, 2, 3))))
char** libstring_cut(const char*, const char*, const size_t*, size_t, size_t*, enum libstring_cut);
#ifdef LIBSTRING_SHORT_NAMES
# define strcut  libstring_cut
#endif


/**
 * TODO
 * 
 * @param   string     The string to cut.
 * @param   delimiter  The delimiter.
 * @param   fields...  List of fields to return.
 *                     End with `SIZE_MAX`.
 * @param   n          Output parameter for the number of
 *                     returned fields. May be `NULL`.
 * @param   flags      Additional options.
 * @return             `NULL`-terminated list of the
 *                     found fields. `NULL` on error.
 * 
 * @throws  ENOMEM  The process cannot enough memory.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF(1, 2))))
char** libstring_vcut(const char*, const char*, size_t, ... /*, SIZE_MAX, size_t*, enum libstring_cut */);
#ifdef LIBSTRING_SHORT_NAMES
# define vstrcut  libstring_vcut
#endif


/**
 * Retrieve a substring.
 * 
 * @param   string  The string.
 * @param   start   The position in `string` of the
 *                  beginning of the substring.
 * @param   end     The position in `string` of the
 *                  end of the substring.
 * @param   flags   Additional options.
 * @return          The selected substring of `string`.
 *                  `NULL` on error.
 * 
 * @throws  ENOMEM  The process cannot enough memory.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF)))
char* libstring_substring(const char*, size_t, size_t, enum libstring_substring);
#ifdef LIBSTRING_SHORT_NAMES
# define strsub  libstring_substring
#endif


/**
 * Remove unnecessary whitespace in string.
 * 
 * Example:
 *   s = libstring_trim("  hello   world!  ", NULL, 0);
 *   # s is "hello   world!"
 *   free(s);
 * 
 * @param   string   The string to manipulate.
 * @param   symbols  Symbols to remove.
 * @param   flags    Additional options.
 * @return           Trimmed version of `string`.
 *                   `NULL` on error.
 * 
 * @throws  ENOMEM  The process cannot enough memory.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF(1))))
char* libstring_trim(const char*, const char*, enum libstring_trim);
#ifdef LIBSTRING_SHORT_NAMES
# define strtrim  libstring_trim
#endif


/**
 * Reverse the order of the characters in a string.
 * 
 * Example:
 *   s = libstring_reverse("hello world!", 0);
 *   # s is "!dlrow olleh"
 *   free(s);
 * 
 * @param   string  The string to reverse.
 * @param   flags   Additional options.
 * @return          String reversed. `NULL` on error.
 * 
 * @throws  ENOMEM  The process cannot enough memory.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF)))
char* libstring_reverse(const char*, enum libstring_reverse);
#ifdef LIBSTRING_SHORT_NAMES
# define strrev  libstring_reverse
#endif


/**
 * Shuffle the order of the characters in a string.
 * 
 * You should have called `srand` before calling
 * this function.
 * 
 * Example:
 *   s = libstring_anagram("hello world!");
 *   # s is "oh!owerld ll", or something else.
 *   free(s);
 *   s = libstring_anagram("hello world!");
 *   # s is "olw! lordlhe", or something else.
 *   free(s);
 *   s = libstring_anagram("hello world!");
 *   # s is "hell row old!", or something else.
 *   free(s);
 * 
 * @param   string  Anagram of the returned string.
 * @return          An anagram of `string`.
 *                  `NULL` on error.
 * 
 * @throws  ENOMEM  The process cannot enough memory.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF)))
char* libstring_anagram(const char*);
#ifdef LIBSTRING_SHORT_NAMES
# define stranagram  libstring_anagram
#endif


/**
 * Replace lowercase letters with uppercase letters.
 * 
 * Example:
 *   s = libstring_lcase("Hello World!");
 *   # s is "hello world!"
 *   free(s);
 * 
 * @param   string  The string to manipulate.
 * @return          Lowercase version of `string`.
 *                  `NULL` on error.
 * 
 * @throws  ENOMEM  The process cannot enough memory.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF)))
char* libstring_lcase(const char*);
#ifdef LIBSTRING_SHORT_NAMES
# define strlcase  libstring_lcase
#endif


/**
 * Replace uppercase letters with lowercase letters.
 * 
 * Example:
 *   s = libstring_ucase("Hello World!");
 *   # s is "HELLO WORLD!"
 *   free(s);
 * 
 * @param   string  The string to manipulate.
 * @return          Uppercase version of `string`.
 *                  `NULL` on error.
 * 
 * @throws  ENOMEM  The process cannot enough memory.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF)))
char* libstring_ucase(const char*);
#ifdef LIBSTRING_SHORT_NAMES
# define strucase  libstring_ucase
#endif


/**
 * Replace the first letter with its lovercase
 * variant if it is in upper case.
 * 
 * Example:
 *   s = libstring_capitalise("hello world!");
 *   # s is "Hello world!"
 *   free(s);
 * 
 * @param   string  The string to manipulate.
 * @return          Capitalised version of `string`.
 *                  `NULL` on error.
 * 
 * @throws  ENOMEM  The process cannot enough memory.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF)))
char* libstring_capitalise(const char*);
#ifdef LIBSTRING_SHORT_NAMES
# define strcap  libstring_capitalise
#endif


/**
 * Replace lowercase letters with uppercase letters,
 * and uppercase letters with lowercase letters.
 * 
 * Example:
 *   s = libstring_swapcase("Hello World!");
 *   # s is "hELLO wORLD!"
 *   free(s);
 * 
 * @param   string  The string to manipulate.
 * @return          `string` with swapped cased for
 *                  all letters. `NULL` on error.
 * 
 * @throws  ENOMEM  The process cannot enough memory.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF)))
char* libstring_swapcase(const char*);
#ifdef LIBSTRING_SHORT_NAMES
# define strscase  libstring_swapcase
#endif


/**
 * Replace tabs with spaces.
 * 
 * @param   string  The string to manipulate.
 * @param   flags   Additional options.
 * @return          `string` with 8 spaces substituted
 *                  tabs for tab space. `NULL` on error.
 * 
 * @throws  ENOMEM  The process cannot enough memory.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF)))
char* libstring_expand(const char*, enum libstring_expand);
#ifdef LIBSTRING_SHORT_NAMES
# define strexp  libstring_expand
#endif


/**
 * Replace initial spaces of groups of 8 with tabs.
 * 
 * @param   string  The string to manipulate.
 * @return          `string` with initial spaces of
 *                  groups of 8, replaced with tab
 *                  spaces. `NULL` on error.
 * 
 * @throws  ENOMEM  The process cannot enough memory.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF)))
char* libstring_unexpand(const char*);
#ifdef LIBSTRING_SHORT_NAMES
# define strunexp  libstring_unexpand
#endif


/**
 * ROT13: Offensive joke and spoiler masker.
 * 
 * Example:
 *   s = libstring_rot13("An offensive joke");
 *   # s is "Na bssrafvir wbxr"
 *   z = libstring_rot13(s);
 *   # z is "An offensive joke"
 *   free(s), free(z);
 * 
 * @param   string  The string to manipulate.
 * @return          `string` with all ASCII letters
 *                  substituted for the corresponding
 *                  letter in the alphabet whose position
 *                  is offset from that letter by 13.
 *                  `NULL` on error.
 * 
 * @throws  ENOMEM  The process cannot enough memory.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF)))
char* libstring_rot13(const char*);
#ifdef LIBSTRING_SHORT_NAMES
# define strrot13  libstring_rot13
#endif


/**
 * Double ROT13: terrorist-grade encryption.
 * 
 * Example:
 *   s = libstring_rot13("Secret message");
 *   # s is "Secret message"
 *   free(s);
 * 
 * @param   string  The string to copy.
 * @return          A copy of `string`. `NULL` on error.
 * 
 * @throws  ENOMEM  The process cannot enough memory.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF)))
char* libstring_double_rot13(const char*);
#ifdef LIBSTRING_SHORT_NAMES
# define str2rot13  libstring_double_rot13
#endif



#undef LIBSTRING_GCC_ONLY
#ifdef LIBSTRING_COMMON
# undef LIBSTRING_COMMON
#endif
#ifdef LIBSTRING_LEAF
# undef LIBSTRING_LEAF
#endif

#endif

