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



LIBSTRING_GCC_ONLY(__attribute__((__malloc__, __warn_unused_result__, __nonnull__(1))))
char* libstring_cat(const char* const* strings, const size_t* n);

LIBSTRING_GCC_ONLY(__attribute__((__malloc__, __warn_unused_result__, __nonnull__, __sentinel__(0), __leaf__)))
char* libstring_vcat(const char* strings, ... /*, (char*)0 */);

LIBSTRING_GCC_ONLY(__attribute__((__malloc__, __warn_unused_result__, __nonnull__(1, 3))))
char* libstring_join(const char* const* strings, const size_t* n, const char* delimiter);

LIBSTRING_GCC_ONLY(__attribute__((__malloc__, __warn_unused_result__, __nonnull__, __sentinel__(1), __leaf__)))
char* libstring_vjoin(const char* strings, ... /*, (char*)0, const char* delimiter */);

LIBSTRING_GCC_ONLY(__attribute__((__malloc__, __warn_unused_result__, __nonnull__(1, 2), __leaf__)))
char** libstring_split(const char* delimiter, const char* string, size_t* n, enum libstring_split flags);

LIBSTRING_GCC_ONLY(__attribute__((__malloc__, __warn_unused_result__, __nonnull__, __leaf__)))
char* libstring_replace(const char* string, const char* from, const char* to, enum libstring_replace flags);

LIBSTRING_GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __leaf__)))
size_t libstring_length(const char* string, size_t* length, enum libstring_length flags);

LIBSTRING_GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __leaf__)))
int libstring_utf8verify(const char* string, enum libstring_utf8verify flags);

LIBSTRING_GCC_ONLY(__attribute__((__malloc__, __warn_unused_result__, __nonnull__(1, 2, 3))))
char** libstring_cut(const char* string, const char* delimiter, const size_t* fields,
		     size_t fields_n, size_t* n, enum libstring_cut flags);

LIBSTRING_GCC_ONLY(__attribute__((__malloc__, __warn_unused_result__, __nonnull__(1, 2), __sentinel__(2), __leaf__)))
char** libstring_vcut(const char* string, const char* delimiter, size_t fields,
		      ... /*, (char*)0, size_t* n, enum libstring_cut flags */);

LIBSTRING_GCC_ONLY(__attribute__((__malloc__, __warn_unused_result__, __nonnull__, __leaf__)))
char* libstring_substring(const char* string, size_t start, size_t end, enum libstring_substring flags);

LIBSTRING_GCC_ONLY(__attribute__((__malloc__, __warn_unused_result__, __nonnull__(1), __leaf__)))
char* libstring_trim(const char* string, const char* symbols, enum libstring_trim flags);

LIBSTRING_GCC_ONLY(__attribute__((__malloc__, __warn_unused_result__, __nonnull__, __leaf__)))
char* libstring_reverse(const char* string);

LIBSTRING_GCC_ONLY(__attribute__((__malloc__, __warn_unused_result__, __nonnull__, __leaf__)))
char* libstring_anagram(const char* string);

LIBSTRING_GCC_ONLY(__attribute__((__malloc__, __warn_unused_result__, __nonnull__, __leaf__)))
char* libstring_lcase(const char* string);

LIBSTRING_GCC_ONLY(__attribute__((__malloc__, __warn_unused_result__, __nonnull__, __leaf__)))
char* libstring_ucase(const char* string);

LIBSTRING_GCC_ONLY(__attribute__((__malloc__, __warn_unused_result__, __nonnull__, __leaf__)))
char* libstring_swapcase(const char* string);

LIBSTRING_GCC_ONLY(__attribute__((__malloc__, __warn_unused_result__, __nonnull__, __leaf__)))
char* libstring_expand(const char* string);

LIBSTRING_GCC_ONLY(__attribute__((__malloc__, __warn_unused_result__, __nonnull__, __leaf__)))
char* libstring_unexpand(const char* string);

LIBSTRING_GCC_ONLY(__attribute__((__malloc__, __warn_unused_result__, __nonnull__, __leaf__)))
char* libstring_rot13(const char* string);

LIBSTRING_GCC_ONLY(__attribute__((__malloc__, __warn_unused_result__, __nonnull__, __leaf__)))
char* libstring_double_rot13(const char* string);



#undef LIBSTRING_GCC_ONLY

#endif

