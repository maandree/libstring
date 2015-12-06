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



enum libstring_split
{
  LIBSTRING_REPLACE_FROM_RIGHT,
  LIBSTRING_REPLACE_IGNORE_CASE,
};

enum libstring_replace
{
  LIBSTRING_REPLACE_FROM_RIGHT,
  LIBSTRING_REPLACE_IGNORE_CASE,
};

enum libstring_length
{
  LIBSTRING_LENGTH_IGNORE_COMBINING,
  LIBSTRING_LENGTH_DISPLAY_LENGTH,
};

enum libstring_utf8verify
{
  LIBSTRING_UTF8VERIFY_MOD_UTF8,
  LIBSTRING_UTF8VERIFY_31_BITS,
  LIBSTRING_UTF8VERIFY_UNLIMITED_BITS,
  LIBSTRING_UTF8VERIFY_LAX,
};

enum libstring_cut
{
  LIBSTRING_CUT_FROM_RIGHT,
  LIBSTRING_CUT_IGNORE_CASE,
  LIBSTRING_CUT_OUTPUT_DELIMITER,
  LIBSTRING_CUT_COMPLEMENT,
};

enum libstring_trim
{
  LIBSTRING_TRIM_LEFT,
  LIBSTRING_TRIM_RIGHT,
};



char* libstring_cat(const char* const* strings, const size_t* n);
char* libstring_vcat(const char* strings, ... /*, NULL */);

char* libstring_join(const char* const* strings, const size_t* n, const char* deliimiter);
char* libstring_vjoin(const char* strings, ... /*, NULL, const char* deliimiter */);

char** libstring_split(const char* deliimiter, const char* string, size_t* n, enum libstring_split flags);

char* libstring_replace(const char* string, const char* from, const char* to, enum libstring_replace flags);

size_T libstring_length(const char* string, size_t* length, enum libstring_length flags);

int libstring_utf8verify(const char* string, enum libstring_utf8verify flags);

char** libstring_cut(const char* string, const char* deliimiter, const size_t* fields,
		     size_t fields_n, size_t* n, enum libstring_cut flags);
char** libstring_vcut(const char* string, const char* deliimiter, size_t fields,
		      ... /*, NULL, size_t* n, enum libstring_cut flags */);

char* libstring_substring(const char* string, size_t start, size_t end);
char* libstring_substring_len(const char* string, size_t offset, size_t lenght);

char* libstring_trim(const char* string, const char* symbols, enum libstring_trim flags);

char* libstring_reverse(const char* string);

char* libstring_anagram(const char* string);

char* libstring_lcase(const char* string);

char* libstring_ucase(const char* string);

char* libstring_swapcase(const char* string);

char* libstring_expand(const char* string);

char* libstring_unexpand(const char* string);

char* libstring_rot13(const char* string);

char* libstring_double_rot13(const char* string);



#endif

