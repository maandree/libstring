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
#include "libstring.h"
#include <string.h>
#include <stdlib.h>



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
char* libstring_cat(const char* const* strings, const size_t* n)
{
}


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
char* libstring_vcat(const char* strings, ... /*, (char*)0 */)
{
}


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
char* libstring_join(const char* const* strings, const size_t* n, const char* delimiter)
{
}


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
char* libstring_vjoin(const char* strings, ... /*, (char*)0, const char* delimiter */)
{
}


/**
 * Split a string at each occurrence of a selected delimiter.
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
char** libstring_split(const char* string, const char* delimiter, size_t* n, enum libstring_split flags)
{
}


/**
 * Replace a substrings in a string.
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
char* libstring_replace(const char* string, const char* from, const char* to, enum libstring_replace flags)
{
}


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
char* libstring_shellsafe(const char* string)
{
}


/**
 * Measure the length of a string.
 * 
 * @param   string  The string to measure.
 * @param   flags   Additional options.
 * @return          The length of `string`.
 */
size_t libstring_length(const char* string, enum libstring_length flags)
{
}


/**
 * Validate teh encoding of a string.
 * 
 * @param   string  The string to validate.
 * @param   flags   Additional options.
 * @return          0 if the string is valid, -1 otherwise.
 */
int libstring_utf8verify(const char* string, enum libstring_utf8verify flags)
{
}


/**
 * Split a string at each occurrence of a selected delimiter,
 * but retain only select fields.
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
char** libstring_cut(const char* string, const char* delimiter, const size_t* fields,
		     size_t fields_n, size_t* n, enum libstring_cut flags)
{
}


/**
 * Split a string at each occurrence of a selected delimiter,
 * but retain only select fields.
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
char** libstring_vcut(const char* string, const char* delimiter, size_t fields,
		      ... /*, SIZE_MAX, size_t* n, enum libstring_cut flags */)
{
}


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
char* libstring_substring(const char* string, size_t start, size_t end, enum libstring_substring flags)
{
}


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
char* libstring_trim(const char* string, const char* symbols, enum libstring_trim flags)
{
}


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
char* libstring_reverse(const char* string, enum libstring_reverse flags)
{
}


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
char* libstring_anagram(const char* string)
{
}


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
char* libstring_lcase(const char* string)
{
}


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
char* libstring_ucase(const char* string)
{
}


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
char* libstring_capitalise(const char* string)
{
}


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
char* libstring_swapcase(const char* string)
{
}


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
char* libstring_expand(const char* string, enum libstring_expand flags)
{
}


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
char* libstring_unexpand(const char* string)
{
}


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
char* libstring_rot13(const char* string)
{
}


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
char* libstring_double_rot13(const char* string)
{
}

