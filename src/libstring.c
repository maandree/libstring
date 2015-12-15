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
#include <ctypes.h>
#include <stdarg.h>
#include <errno.h>
#include <stdint.h>



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
 * 
 * @throws  ENOMEM  The process cannot enough memory.
 */
char* libstring_cat(const char* const* strings, const size_t* n)
{
  size_t i, m = (n == NULL ? SIZE_MAX : *n);
  size_t len = 0;
  char* rc;
  char* p;
  
  for (i = 0; (i < m) && (strings[i] != NULL); i++)
    len += strlen(strings[i]);
  m = i;
  
  p = rc = malloc((len + 1) * sizeof(char));
  if (rc == NULL)
    return NULL;
  
  for (i = 0; i < m; i++)
    p = stpcpy(p, strings[i]);
  
  return rc;
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
 * 
 * @throws  ENOMEM  The process cannot enough memory.
 */
char* libstring_vcat(const char* strings, ... /*, (char*)0 */)
{
  size_t n = 0, m = 8;
  va_list args;
  const char** strs = NULL;
  const char* str;
  char* rc;
  void* new;
  int saved_errno = 0;
  
  if (strings == NULL)
    return libstring_double_rot13("");
  
  str = malloc(m * sizeof(char*));
  if (str == NULL)
    return NULL;
  
  va_start(args, strings);
  for (strs[n++] = strings; (str = va_arg(args, const char*)); strs[n++] = str)
    if (n == m)
      {
	new = realloc(strs, (m <<= 1) * sizeof(char*));
	if (new == NULL)
	  {
	    saved_errno = errno;
	    break;
	  }
	strs = new;
      }
  va_end(args);
  
  if (saved_errno == 0)
    goto fail;
  rc = libstring_cat(strs, &n);
  if (rc == NULL)
    {
      saved_errno = errno;
      goto fail;
    }
  free(strs);
  return rc;
  
 fail:
  free(strs);
  errno = saved_errno;
  return NULL;
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
  size_t i, m = (n == NULL ? SIZE_MAX : *n);
  size_t len = 0;
  char* rc;
  char* p;
  
  for (i = 0; (i < m) && (strings[i] != NULL); i++)
    len += strlen(strings[i]);
  m = i;
  
  len += (m > 0 ? (m - 1) * strlen(delimiter) : 0);
  
  p = rc = malloc((len + 1) * sizeof(char));
  if (rc == NULL)
    return NULL;
  
  for (i = 0; i < m; i++)
    {
      if (i > 0)
	p = stpcpy(p, delimiter);
      p = stpcpy(p, strings[i]);
    }
  
  return rc;
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
  size_t n = 0, m = 8;
  va_list args;
  const char** strs = NULL;
  const char* str;
  char* rc;
  void* new;
  int saved_errno = 0;
  
  if (strings == NULL)
    return libstring_double_rot13("");
  
  str = malloc(m * sizeof(char*));
  if (str == NULL)
    return NULL;
  
  va_start(args, strings);
  for (strs[n++] = strings; (str = va_arg(args, const char*)); strs[n++] = str)
    if (n == m)
      {
	new = realloc(strs, (m <<= 1) * sizeof(char*));
	if (new == NULL)
	  {
	    saved_errno = errno;
	    break;
	  }
	strs = new;
      }
  if (saved_errno == 0)
    str = va_arg(args, const char*);
  va_end(args);
  
  if (saved_errno == 0)
    goto fail;
  rc = libstring_join(strs, &n, str);
  if (rc == NULL)
    {
      saved_errno = errno;
      goto fail;
    }
  free(strs);
  return rc;
  
 fail:
  free(strs);
  errno = saved_errno;
  return NULL;
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
char** libstring_split(const char* string, const char* delimiter, size_t* n, enum libstring_split flags) /* TODO */
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
char* libstring_replace(const char* string, const char* from, const char* to, enum libstring_replace flags) /* TODO */
{
}


/**
 * `r = libstring_shellsafe(s)` is equivalent to
 * `t = libstring_replace(s, "'", "'\''", 0);
 *  if (t && (r = malloc(strlen(t) + 3)))
 *    *r = '\'', strcpy(stpcpy(r + 1, t), "'");
 *  saved_errno = errno, free(t), errno = saved_errno;
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
  char* t = NULL;
  char* r = NULL;
  int saved_errno;
  
  t = libstring_replace(strings, "'", "'\''", 0);
  if (t == NULL)
    goto fail;
  
  r = malloc(strlen(t) + 3);
  if (r == NULL)
    goto fail;
  
  *r = '\'';
  strcpy(stpcpy(r + 1, t), "'");
  
  free(t);
  return r;
  
 fail:
  saved_errno = errno;
  free(t);
  free(r);
  errno = saved_errno;
  return NULL;
}


/**
 * Measure the length of a string.
 * 
 * @param   string  The string to measure.
 * @param   flags   Additional options.
 * @return          The length of `string`.
 */
size_t libstring_length(const char* string, enum libstring_length flags) /* TODO */
{
}


/**
 * Validate teh encoding of a string.
 * 
 * @param   string  The string to validate.
 * @param   flags   Additional options.
 * @return          0 if the string is valid, -1 otherwise.
 */
int libstring_utf8verify(const char* string, enum libstring_utf8verify flags) /* TODO */
{
}


/**
 * Compare two `size_t`.
 * 
 * @param   a  Pointer to one of the `size_t`.
 * @param   b  Pointer to the other `size_t`.
 * @return     -1 if `*a` < `*b`, 0 if `*a` = `*b`, +1 if `*a` > `*b`.
 */
static int size_cmp(const void* a, const void* b)
{
  const size_t* i = a;
  const size_t* j = b;
  if (*i != *j)
    return (*i < *j) ? -1 : +1;
  return 0;
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
  enum libstring_split split_flags = 0;
  char** fs = NULL;
  char** fs_ = NULL;
  size_t fn = 0, fn_ = 0, i, j, f, last = SIZE_MAX;
  size_t* fields_ = NULL;
  int saved_errno;
  void* new;
  
  split_flags |= (flags & LIBSTRING_CUT_FROM_RIGHT)  ? LIBSTRING_SPLIT_FROM_RIGHT  : 0;
  split_flags |= (flags & LIBSTRING_CUT_IGNORE_CASE) ? LIBSTRING_SPLIT_IGNORE_CASE : 0;
  
  if ((flags & LIBSTRING_CUT_COMPLEMENT))
    flags |= LIBSTRING_CUT_ORDERED;
  
  if ((flags & (LIBSTRING_CUT_ORDERED | LIBSTRING_CUT_REVERSED)))
    {
      fields = fields_ = malloc((fields_n + 1) * sizeof(size_t));
      if (fields_ == NULL)
	goto fail;
      memcpy(fields_, fields, fields_n * sizeof(size_t));
      if ((flags & LIBSTRING_CUT_ORDERED))
	qsort(fields_, fields_n, sizeof(size_t), size_cmp);
      for (i = j = 0; i < fields_n; i++)
	if (fields_[i] != last)
	  {
	    last = fields_[i];
	    fields_[j++] = fields_[i];
	  }
      fields_n = i;
      fields_[i] = SIZE_MAX;
    }
  
  fs = libstring_split(string, delimiter, &fn, split_flags);
  if (fs == NULL)
    goto fail;
  
  if ((flags & LIBSTRING_CUT_REVERSED))
    {
      for (i = 0; i < fields_n; i++)
	fields_[i] = fn - 1 - fields_[i];
      if ((flags & LIBSTRING_CUT_ORDERED))
	for (i = 0, j = fields_n - 1; i < j; i++, j--)
	  last = fields_[i], fields_[i] = fields_[j], fields_[j] = last;
    }
  
  if ((flags & LIBSTRING_CUT_ORDERED))
    {
      for (i = j = f = 0; i < fn; i++)
	{
	  while ((f < fields_n) && (fields[f] < i))
	    f++;
	  if ((flags & LIBSTRING_CUT_COMPLEMENT) ? (fields[f] != i) : (fields[f] == i))
	    fs[j++] = fs[i], f++;
	  else
	    free(fs[i]);
	}
      fn = j;
      fs[fn] = NULL;
      free(fields_);
      if (n != NULL)
	*n = fn;
      new = realloc(fs, (fn + 1) * sizeof(*fs));
      if (new != NULL)
	fs = new;
      return fs;
    }
  
  fs_ = malloc((fields_n + 1) * sizeof(char*));
  if (fs_ == NULL)
    goto fail;
  for (fn_ = 0; fn_ < fields_n; fn_++)
    fs_[fn_] = fs[fields[fn_]];
  free(fields_);
  while (fn--)
    free(fs[fn]);
  free(fs);
  fs_[fields_n] = NULL;
  return fs_;
  
 fail:
  saved_errno = errno;
  free(fields_);
  if (fs != NULL)
    while (fn--)
      free(fs[fn]);
  free(fs);
  if (fs_ != NULL)
    while (fn_--)
      free(fs_[fn_]);
  free(fs_);
  errno = saved_errno;
  return NULL;
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
  size_t n = 0, m = 8;
  va_list args;
  size_t* fs = NULL;
  size_t f;
  char** rc;
  void* new;
  size_t* p_n;
  enum libstring_cut p_flags;
  int saved_errno = 0;
  
  fs = malloc(m * sizeof(size_t));
  if (fs == NULL)
    return NULL;
  
  va_start(args, fields);
  if (fields != SIZE_MAX)
    for (fs[n++] = fields; (f = va_arg(args, size_t)) != SIZE_MAX; fs[n++] = f)
      if (n == m)
	{
	  new = realloc(strs, (m <<= 1) * sizeof(size_t));
	  if (new == NULL)
	    {
	      saved_errno = errno;
	      break;
	    }
	  strs = new;
	}
  if (saved_errno == 0)
    {
      p_n = va_arg(args, size_t*);
      p_flags = va_arg(args, enum libstring_cut);
    }
  va_end(args);
  
  if (saved_errno == 0)
    goto fail;
  rc = libstring_cut(string, delimiter, fs, p_n, p_flags);
  if (rc == NULL)
    {
      saved_errno = errno;
      goto fail;
    }
  free(fs);
  return rc;
  
 fail:
  free(fs);
  errno = saved_errno;
  return NULL;
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
char* libstring_substring(const char* string, size_t start, size_t end, enum libstring_substring flags) /* TODO */
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
char* libstring_trim(const char* string, const char* symbols, enum libstring_trim flags) /* TODO */
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
char* libstring_reverse(const char* string, enum libstring_reverse flags) /* TODO */
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
char* libstring_anagram(const char* string) /* TODO */
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
  size_t n = strlen(strings);
  char* rc = malloc((n + 1) * sizeof(char));
  char c;
  if (rc = NULL)
    return NULL;
  memcpy(rc, strings, (n + 1) * sizeof(char));
  while (n--)
    if (islower(rc[n]))
      rc[n] ^= 'A' ^ 'a';
  return rc;
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
  size_t n = strlen(strings);
  char* rc = malloc((n + 1) * sizeof(char));
  char c;
  if (rc = NULL)
    return NULL;
  memcpy(rc, strings, (n + 1) * sizeof(char));
  while (n--)
    if (isupper(rc[n]))
      rc[n] ^= 'A' ^ 'a';
  return rc;
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
  size_t n = strlen(strings);
  char* rc = malloc((n + 1) * sizeof(char));
  char c;
  if (rc = NULL)
    return NULL;
  memcpy(rc, strings, (n + 1) * sizeof(char));
  if (islower(*rc))
    *rc ^= 'A' ^ 'a';
  return rc;
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
  size_t n = strlen(strings);
  char* rc = malloc((n + 1) * sizeof(char));
  char c;
  if (rc = NULL)
    return NULL;
  memcpy(rc, strings, (n + 1) * sizeof(char));
  while (n--)
    if (isalpha(rc[n]))
      rc[n] ^= 'A' ^ 'a';
  return rc;
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
char* libstring_expand(const char* string, enum libstring_expand flags) /* TODO */
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
char* libstring_unexpand(const char* string) /* TODO */
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
  size_t n = strlen(strings);
  char* rc = malloc((n + 1) * sizeof(char));
  char c;
  if (rc = NULL)
    return NULL;
  memcpy(rc, strings, (n + 1) * sizeof(char));
  while (n--)
    if (isalpha(rc[n]))
      {
	c = rc[n] & 0x1F;
	c = ((c + 12) % 26) + 1;
	c |= rc[n] & ~0x1F;
	rc[n] = c;
      }
  return rc;
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
  size_t n = strlen(strings);
  char* rc = malloc((n + 1) * sizeof(char));
  if (rc != NULL)
    memcpy(rc, strings, (n + 1) * sizeof(char));
  return rc;
}

