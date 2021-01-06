
/*-
 * Copyright (c) 1999, 2000, 2001, 2002, 2003 Lev Walkin <vlm@lionet.info>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $Id: sf_mime.h,v 1.3 2005/05/25 21:55:10 vlm Exp $
 */

#ifndef __SF_MIME_H__
#define __SF_MIME_H__

//#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */


/**********************/
/*** MIME encodings ***/
/**********************/

/*
 * Encode or decode the given string using the base64 decoder.
 * If size is not specified, strlen(str) will be used.
 * The resulting data size will be placed into *size.
 */
char *base64_encode(const void *data,   size_t *size);	/* leak-safe */
char *base64_decode(const char *string, size_t *size);	/* leak-safe */
void *base64_detach(size_t *size);		/* Detach the internal buffer */

char *quoted_printable_decode(const char *string, size_t *size);/* leak-safe */
char *mime_word_decode(const char *string, size_t *size);		/* leak-safe */


#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* __SF_MIME_H__ */
