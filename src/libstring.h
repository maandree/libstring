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
 * @param   strings  List of strings to concatenate, must
 *                   not be `NULL` or contain `NULL`:s.
 * @param   n        Either a pointer the number of strings
 *                   stored in `strings`, or `NULL` if
 *                   `strings` is `NULL`-terminated.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_COMMON(1))))
char* libstring_cat(const char* const*, const size_t*);


/**
 * @param   strings...  List of strings to concatenate, end
 *                      with a `NULL`.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF, __sentinel__(0))))
char* libstring_vcat(const char*, ... /*, (char*)0 */);


/**
 * @param   strings    List of strings to join, must
 *                     not be `NULL` or contain `NULL`:s.
 * @param   n          Either a pointer the number of strings
 *                     stored in `strings`, or `NULL` if
 *                     `strings` is `NULL`-terminated.
 * @param   delimiter  A string to insert between all strings.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_COMMON(1, 3))))
char* libstring_join(const char* const*, const size_t*, const char*);


/**
 * @param   strings...  List of strings to concatenate, end
 *                      with a `NULL`.
 * @param   delimiter   A string to insert between all strings.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF, __sentinel__(1))))
char* libstring_vjoin(const char*, ... /*, (char*)0, const char* */);


/**
 * @param   string     String to split.
 * @param   delimiter  The delimiter.
 * @param   n          Output parameter for the number of
 *                     strings in the returned list. May be `NULL`.
 * @param   flags      Additional options.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF(1, 2))))
char** libstring_split(const char*, const char*, size_t*, enum libstring_split);


/**
 * @param   string  The string to manipulate.
 * @param   from    Substring to replace.
 * @param   to      String to substitute for `from`.
 * @param   flags   Additional options.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF)))
char* libstring_replace(const char*, const char*, const char*, enum libstring_replace);


/**
 * @param   string  The string to measure.
 * @param   flags   Additional options.
 */
LIBSTRING_GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __leaf__)))
size_t libstring_length(const char*, enum libstring_length);


/**
 * @param   string  The string to validate.
 * @param   flags   Additional options.
 */
LIBSTRING_GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __leaf__)))
int libstring_utf8verify(const char*, enum libstring_utf8verify);


/**
 * @param   string     The string to cut.
 * @param   delimiter  The delimiter.
 * @param   fields     List of fields to return.
 * @param   fields_n   The number of elements in `fields`.
 * @param   n          Output parameter for the number of
 *                     returned fields. May be `NULL`.
 * @param   flags      Additional options.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_COMMON(1, 2, 3))))
char** libstring_cut(const char*, const char*, const size_t*, size_t, size_t*, enum libstring_cut);


/**
 * @param   string     The string to cut.
 * @param   delimiter  The delimiter.
 * @param   fields...  List of fields to return.
 *                     End with `SIZE_MAX`.
 * @param   n          Output parameter for the number of
 *                     returned fields. May be `NULL`.
 * @param   flags      Additional options.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF(1, 2))))
char** libstring_vcut(const char*, const char*, size_t, ... /*, SIZE_MAX, size_t*, enum libstring_cut */);


/**
 * @param   string  The string.
 * @param   start   The position in `string` of the
 *                  beginning of the substring.
 * @param   end     The position in `string` of the
 *                  end of the substring.
 * @param   flags   Additional options.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF)))
char* libstring_substring(const char*, size_t, size_t, enum libstring_substring);


/**
 * @param   string   The string to manipulate.
 * @param   symbols  Symbols to remove.
 * @param   flags    Additional options.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF(1))))
char* libstring_trim(const char*, const char*, enum libstring_trim);


/**
 * @param   string  The string to reverse.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF)))
char* libstring_reverse(const char*);


/**
 * @param   string  Anagram of the returned string.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF)))
char* libstring_anagram(const char*);


/**
 * @param   string  The string to manipulate.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF)))
char* libstring_lcase(const char*);


/**
 * @param   string  The string to manipulate.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF)))
char* libstring_ucase(const char*);


/**
 * @param   string  The string to manipulate.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF)))
char* libstring_capitalise(const char*);


/**
 * @param   string  The string to manipulate.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF)))
char* libstring_swapcase(const char*);


/**
 * @param   string  The string to manipulate.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF)))
char* libstring_expand(const char*);


/**
 * @param   string  The string to manipulate.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF)))
char* libstring_unexpand(const char*);


/**
 * @param   string  The string to manipulate.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF)))
char* libstring_rot13(const char*);


/**
 * @param   string  The string to copy.
 */
LIBSTRING_GCC_ONLY(__attribute__((LIBSTRING_LEAF)))
char* libstring_double_rot13(const char*);



#undef LIBSTRING_GCC_ONLY
#ifdef LIBSTRING_COMMON
# undef LIBSTRING_COMMON
#endif
#ifdef LIBSTRING_LEAF
# undef LIBSTRING_LEAF
#endif

#endif

