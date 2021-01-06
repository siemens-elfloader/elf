#include "..\inc\swilib.h"
#include "url_utils.h"

/* URL handling.
   Copyright (C) 2005 Free Software Foundation, Inc.

This file is part of GNU Wget.

GNU Wget is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or (at
your option) any later version.

GNU Wget is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Wget; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

In addition, as a special exception, the Free Software Foundation
gives permission to link the code of its release of Wget with the
OpenSSL project's "OpenSSL" library (or with modified versions of it
that use the same license as the "OpenSSL" library), and distribute
the linked executables.  You must obey the GNU General Public License
in all respects for all of the code used other than "OpenSSL".  If you
modify this file, you may extend this exception to your version of the
file, but you are not obligated to do so.  If you do not wish to do
so, delete this exception statement from your version.  */

/* Character classification.  */
const unsigned short _sch_istable[256] =
{
  Z,  C,  C,  C,   C,  C,  C,  C,   /* NUL SOH STX ETX  EOT ENQ ACK BEL */
  C,  T,  V,  M,   M,  V,  C,  C,   /* BS  HT  LF  VT   FF  CR  SO  SI  */
  C,  C,  C,  C,   C,  C,  C,  C,   /* DLE DC1 DC2 DC3  DC4 NAK SYN ETB */
  C,  C,  C,  C,   C,  C,  C,  C,   /* CAN EM  SUB ESC  FS  GS  RS  US  */
  S,  P,  P,  P,   P,  P,  P,  P,   /* SP  !   "   #    $   %   &   '   */
  P,  P,  P,  P,   P,  P,  P,  P,   /* (   )   *   +    ,   -   .   /   */
  D,  D,  D,  D,   D,  D,  D,  D,   /* 0   1   2   3    4   5   6   7   */
  D,  D,  P,  P,   P,  P,  P,  P,   /* 8   9   :   ;    <   =   >   ?   */
  P, XU, XU, XU,  XU, XU, XU,  U,   /* @   A   B   C    D   E   F   G   */
  U,  U,  U,  U,   U,  U,  U,  U,   /* H   I   J   K    L   M   N   O   */
  U,  U,  U,  U,   U,  U,  U,  U,   /* P   Q   R   S    T   U   V   W   */
  U,  U,  U,  P,   P,  P,  P,  _,   /* X   Y   Z   [    \   ]   ^   _   */
  P, XL, XL, XL,  XL, XL, XL,  L,   /* `   a   b   c    d   e   f   g   */
  L,  L,  L,  L,   L,  L,  L,  L,   /* h   i   j   k    l   m   n   o   */
  L,  L,  L,  L,   L,  L,  L,  L,   /* p   q   r   s    t   u   v   w   */
  L,  L,  L,  P,   P,  P,  P,  C,   /* x   y   z   {    |   }   ~   DEL */

  /* high half of unsigned char is locale-specific, so all tests are
     false in "C" locale */
  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,

  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
};

const unsigned char _sch_tolower[256] =
{
   0,  1,  2,  3,   4,  5,  6,  7,   8,  9, 10, 11,  12, 13, 14, 15,
  16, 17, 18, 19,  20, 21, 22, 23,  24, 25, 26, 27,  28, 29, 30, 31,
  32, 33, 34, 35,  36, 37, 38, 39,  40, 41, 42, 43,  44, 45, 46, 47,
  48, 49, 50, 51,  52, 53, 54, 55,  56, 57, 58, 59,  60, 61, 62, 63,
  64,

  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
  'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',

  91, 92, 93, 94, 95, 96,

  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
  'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',

 123,124,125,126,127,

 128,129,130,131, 132,133,134,135, 136,137,138,139, 140,141,142,143,
 144,145,146,147, 148,149,150,151, 152,153,154,155, 156,157,158,159,
 160,161,162,163, 164,165,166,167, 168,169,170,171, 172,173,174,175,
 176,177,178,179, 180,181,182,183, 184,185,186,187, 188,189,190,191,

 192,193,194,195, 196,197,198,199, 200,201,202,203, 204,205,206,207,
 208,209,210,211, 212,213,214,215, 216,217,218,219, 220,221,222,223,
 224,225,226,227, 228,229,230,231, 232,233,234,235, 236,237,238,239,
 240,241,242,243, 244,245,246,247, 248,249,250,251, 252,253,254,255,
};

const unsigned char _sch_toupper[256] =
{
   0,  1,  2,  3,   4,  5,  6,  7,   8,  9, 10, 11,  12, 13, 14, 15,
  16, 17, 18, 19,  20, 21, 22, 23,  24, 25, 26, 27,  28, 29, 30, 31,
  32, 33, 34, 35,  36, 37, 38, 39,  40, 41, 42, 43,  44, 45, 46, 47,
  48, 49, 50, 51,  52, 53, 54, 55,  56, 57, 58, 59,  60, 61, 62, 63,
  64,

  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
  'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',

  91, 92, 93, 94, 95, 96,

  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
  'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',

 123,124,125,126,127,

 128,129,130,131, 132,133,134,135, 136,137,138,139, 140,141,142,143,
 144,145,146,147, 148,149,150,151, 152,153,154,155, 156,157,158,159,
 160,161,162,163, 164,165,166,167, 168,169,170,171, 172,173,174,175,
 176,177,178,179, 180,181,182,183, 184,185,186,187, 188,189,190,191,

 192,193,194,195, 196,197,198,199, 200,201,202,203, 204,205,206,207,
 208,209,210,211, 212,213,214,215, 216,217,218,219, 220,221,222,223,
 224,225,226,227, 228,229,230,231, 232,233,234,235, 236,237,238,239,
 240,241,242,243, 244,245,246,247, 248,249,250,251, 252,253,254,255,
};

#define _sch_test(c, bit) (_sch_istable[(c) & 0xff] & (unsigned short)(bit))

/* Support for escaping and unescaping of URL strings.  */

/* Table of "reserved" and "unsafe" characters.  Those terms are
   rfc1738-speak, as such largely obsoleted by rfc2396 and later
   specs, but the general idea remains.

   A reserved character is the one that you can't decode without
   changing the meaning of the URL.  For example, you can't decode
   "/foo/%2f/bar" into "/foo///bar" because the number and contents of
   path components is different.  Non-reserved characters can be
   changed, so "/foo/%78/bar" is safe to change to "/foo/x/bar".  The
   unsafe characters are loosely based on rfc1738, plus "$" and ",",
   as recommended by rfc2396, and minus "~", which is very frequently
   used (and sometimes unrecognized as %7E by broken servers).

   An unsafe character is the one that should be encoded when URLs are
   placed in foreign environments.  E.g. space and newline are unsafe
   in HTTP contexts because HTTP uses them as separator and line
   terminator, so they must be encoded to %20 and %0A respectively.
   "*" is unsafe in shell context, etc.

   We determine whether a character is unsafe through static table
   lookup.  This code assumes ASCII character set and 8-bit chars.  */

enum {
  /* rfc1738 reserved chars + "$" and ",".  */
  urlchr_reserved = 1,
  /* rfc1738 unsafe chars, plus non-printables.  */
  urlchr_unsafe   = 2
};

#define urlchr_test(c, mask) (urlchr_table[(unsigned char)(c)] & (mask))
#define URL_RESERVED_CHAR(c) urlchr_test(c, urlchr_reserved)
#define URL_UNSAFE_CHAR(c) urlchr_test(c, urlchr_unsafe)

/* Shorthands for the table: */
#define RE  urlchr_reserved
#define UN  urlchr_unsafe
#define RU RE|UN

static const unsigned char urlchr_table[256] =
{
  UN, UN, UN, UN, UN, UN, UN, UN,   /* NUL SOH STX ETX  EOT ENQ ACK BEL */
  UN, UN, UN, UN, UN, UN, UN, UN,   /* BS  HT  LF  VT   FF  CR  SO  SI  */
  UN, UN, UN, UN, UN, UN, UN, UN,   /* DLE DC1 DC2 DC3  DC4 NAK SYN ETB */
  UN, UN, UN, UN, UN, UN, UN, UN,   /* CAN EM  SUB ESC  FS  GS  RS  US  */
  UN,  0, UN, RU, RE, UN, RE,  0,   /* SP  !   "   #    $   %   &   '   */
   0,  0,  0, RE, RE,  0,  0, RE,   /* (   )   *   +    ,   -   .   /   */
   0,  0,  0,  0,  0,  0,  0,  0,   /* 0   1   2   3    4   5   6   7   */
   0,  0, RU, RE, UN, RE, UN, RE,   /* 8   9   :   ;    <   =   >   ?   */
  RU,  0,  0,  0,  0,  0,  0,  0,   /* @   A   B   C    D   E   F   G   */
   0,  0,  0,  0,  0,  0,  0,  0,   /* H   I   J   K    L   M   N   O   */
   0,  0,  0,  0,  0,  0,  0,  0,   /* P   Q   R   S    T   U   V   W   */
   0,  0,  0, RU, UN, RU, UN,  0,   /* X   Y   Z   [    \   ]   ^   _   */
  UN,  0,  0,  0,  0,  0,  0,  0,   /* `   a   b   c    d   e   f   g   */
   0,  0,  0,  0,  0,  0,  0,  0,   /* h   i   j   k    l   m   n   o   */
   0,  0,  0,  0,  0,  0,  0,  0,   /* p   q   r   s    t   u   v   w   */
   0,  0,  0, UN, UN, UN,  0, UN,   /* x   y   z   {    |   }   ~   DEL */

  UN, UN, UN, UN,  UN, UN, UN, UN,  UN, UN, UN, UN,  UN, UN, UN, UN,
  UN, UN, UN, UN,  UN, UN, UN, UN,  UN, UN, UN, UN,  UN, UN, UN, UN,
  UN, UN, UN, UN,  UN, UN, UN, UN,  UN, UN, UN, UN,  UN, UN, UN, UN,
  UN, UN, UN, UN,  UN, UN, UN, UN,  UN, UN, UN, UN,  UN, UN, UN, UN,

  UN, UN, UN, UN,  UN, UN, UN, UN,  UN, UN, UN, UN,  UN, UN, UN, UN,
  UN, UN, UN, UN,  UN, UN, UN, UN,  UN, UN, UN, UN,  UN, UN, UN, UN,
  UN, UN, UN, UN,  UN, UN, UN, UN,  UN, UN, UN, UN,  UN, UN, UN, UN,
  UN, UN, UN, UN,  UN, UN, UN, UN,  UN, UN, UN, UN,  UN, UN, UN, UN,
};
#undef RE
#undef UN
#undef RU

/* URL-unescape the string S.

   This is done by transforming the sequences "%HH" to the character
   represented by the hexadecimal digits HH.  If % is not followed by
   two hexadecimal digits, it is inserted literally.

   The transformation is done in place.  If you need the original
   string intact, make a copy before calling this function.  */

void URL_unescape (char *s)
{
  char *t = s;			/* t - tortoise */
  char *h = s;			/* h - hare     */

  for (; *h; h++, t++)
    {
      if (*h != '%')
	{
	copychar:
	  *t = *h;
	}
      else
	{
	  char c;
	  /* Do nothing if '%' is not followed by two hex digits. */
	  if (!h[1] || !h[2] || !(ISXDIGIT (h[1]) && ISXDIGIT (h[2])))
	    goto copychar;
	  c = X2DIGITS_TO_NUM (h[1], h[2]);
	  /* Don't unescape %00 because there is no way to insert it
	     into a C string without effectively truncating it. */
	  if (c == '\0')
	    goto copychar;
	  *t = c;
	  h += 2;
	}
    }
  *t = '\0';
}

/* Decide whether the char at position P needs to be encoded.  (It is
   not enough to pass a single char *P because the function may need
   to inspect the surrounding context.)

   Return 1 if the char should be escaped as %XX, 0 otherwise.  */

int CharNeedsEscaping(const char *p)
{
  if (*p == '%')
    {
      if (ISXDIGIT (*(p + 1)) && ISXDIGIT (*(p + 2)))
	return 0;
      else
	/* Garbled %.. sequence: encode `%'. */
	return 1;
    }
  else if (URL_UNSAFE_CHAR (*p) && !URL_RESERVED_CHAR (*p))
    return 1;
  else
    return 0;
}

/* Translate a %-escaped (but possibly non-conformant) input string S
   into a %-escaped (and conformant) output string.  If no characters
   are encoded or decoded, return the same string S; otherwise, return
   a freshly allocated string with the new contents.

   After a URL has been run through this function, the protocols that
   use `%' as the quote character can use the resulting string as-is,
   while those that don't can use urlUNnescape to get to the intended
   data.  This function is stable: once the input is transformed,
   further transformations of the result yield the same output.

   Let's discuss why this function is needed.

   Imagine Wget is asked to retrieve `http://abc.xyz/abc def'.  Since
   a raw space character would mess up the HTTP request, it needs to
   be quoted, like this:

       GET /abc%20def HTTP/1.0

   It would appear that the unsafe chars need to be quoted, for
   example with url_escape.  But what if we're requested to download
   `abc%20def'?  url_escape transforms "%" to "%25", which would leave
   us with `abc%2520def'.  This is incorrect -- since %-escapes are
   part of URL syntax, "%20" is the correct way to denote a literal
   space on the Wget command line.  This leads to the conclusion that
   in that case Wget should not call url_escape, but leave the `%20'
   as is.  This is clearly contradictory, but it only gets worse.

   What if the requested URI is `abc%20 def'?  If we call url_escape,
   we end up with `/abc%2520%20def', which is almost certainly not
   intended.  If we don't call url_escape, we are left with the
   embedded space and cannot complete the request.  What the user
   meant was for Wget to request `/abc%20%20def', and this is where
   reencode_escapes kicks in.

   Wget used to solve this by first decoding %-quotes, and then
   encoding all the "unsafe" characters found in the resulting string.
   This was wrong because it didn't preserve certain URL special
   (reserved) characters.  For instance, URI containing "a%2B+b" (0x2b
   == '+') would get translated to "a%2B%2Bb" or "a++b" depending on
   whether we considered `+' reserved (it is).  One of these results
   is inevitable because by the second step we would lose information
   on whether the `+' was originally encoded or not.  Both results
   were wrong because in CGI parameters + means space, while %2B means
   literal plus.  reencode_escapes correctly translates the above to
   "a%2B+b", i.e. returns the original string.

   This function uses a modified version of the algorithm originally
   proposed by Anon Sricharoenchai:

   * Encode all "unsafe" characters, except those that are also
     "reserved", to %XX.  See urlchr_table for which characters are
     unsafe and reserved.

   * Encode the "%" characters not followed by two hex digits to
     "%25".

   * Pass through all other characters and %XX escapes as-is.  (Up to
     Wget 1.10 this decoded %XX escapes corresponding to "safe"
     characters, but that was obtrusive and broke some servers.)

   Anon's test case:

   "http://abc.xyz/%20%3F%%36%31%25aa% a?a=%61+a%2Ba&b=b%26c%3Dc"
   ->
   "http://abc.xyz/%20%3F%25%36%31%25aa%25%20a?a=%61+a%2Ba&b=b%26c%3Dc"

   Simpler test cases:

   "foo bar"         -> "foo%20bar"
   "foo%20bar"       -> "foo%20bar"
   "foo %20bar"      -> "foo%20%20bar"
   "foo%%20bar"      -> "foo%25%20bar"       (0x25 == '%')
   "foo%25%20bar"    -> "foo%25%20bar"
   "foo%2%20bar"     -> "foo%252%20bar"
   "foo+bar"         -> "foo+bar"            (plus is reserved!)
   "foo%2b+bar"      -> "foo%2b+bar"  */

char * URL_reencode_escapes(const char * url)
{
  const char * p1;
  char * p2;
  char * new_url;
  int old_len, new_len;

  int encode_count = 0;

  /* First pass: inspect the string to see if there's anything to do,
     and to calculate the new length.  */
  for (p1 = url; *p1; p1++)
    if (CharNeedsEscaping(p1))
      ++encode_count;

  if (!encode_count)
  {
    /* The string is good as it is. */
    new_url = (char *)malloc(strlen(url) + 1);
    strcpy(new_url, url);
    return new_url;		/* C const model sucks. */
  }

  old_len = p1 - url;
  /* Each encoding adds two characters (hex digits).  */
  new_len = old_len + 2 * encode_count;
  new_url = (char *)malloc(new_len + 1);

  /* Second pass: copy the string to the destination address, encoding
     chars when needed.  */
  p1 = url;
  p2 = new_url;

  while (*p1)
    if (CharNeedsEscaping(p1))
      {
	unsigned char c = *p1++;
	*p2++ = '%';
	*p2++ = XNUM_TO_DIGIT (c >> 4);
	*p2++ = XNUM_TO_DIGIT (c & 0xf);
      }
    else
      *p2++ = *p1++;

  *p2 = '\0';
  return new_url;
}
