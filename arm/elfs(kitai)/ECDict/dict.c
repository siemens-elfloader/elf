#include "..\inc\swilib.h"
#include "..\inc\zlib.h"
#include <stdbool.h>

#define MAX_UNICODE_STR 512


extern const char dict_dir[128];
extern const char modidx_dir[128];

extern char **index;
extern bool m_f_err;                //memory or file error;

char* err_msg;               //error msg string;
int dict;
const int idxbuf_size = 694718;
char *indexbuf = NULL;
const int wordcount = 51214;

void SetError(char* msg)
{
    m_f_err = true;
    err_msg = msg;
}

//====== str functions ========//
#pragma inline=forced
int tolower(int c)
{
	if ((c>='A')&&(c<='Z')) c+='a'-'A';
	return(c);
}

#pragma inline
int strcmp_nocase(const char *s1, const char *s2)
{
	int i;
	int c;
	while(!(i=(c=tolower(*s1++))-tolower(*s2++))) if (!c) break;
	return(i);
}

int strmatch_nocase(const char *s1, const char *s2)
{
  //return the matched length. '\0'='\0' also match
  int c;
	int i = 0;
  while( (c=tolower(*s1++))==tolower(*s2++) )
  {
      i++;
      if( !c )    break;
  }
  return i;
}

//unicode must be a pointer to zero-terminated unicode string.
void copy_unicode_2ws(WSHDR* ws, unsigned short* unicode)
{
	int i = 0;
	for (; unicode[i]!=0 && i<=MAX_UNICODE_STR; i++ )
	{
		ws->wsbody[i+1] = unicode[i];
	}
	ws->wsbody[0] = i;                  // set ws length
}


//====== dict functions ========//

int lookup(char* word)
{
    int start = 0;
    int end = wordcount - 1;
    int mid = 0;
    bool found = false;
    int result;
    
    if( m_f_err )   return -1;
    
    // some ugly magic to avoid showing words before "a"
    mid = 9;
    
    if ( word[0]!=0 && word[0]!='(' &&word[0]!='\'')       //¼´(strlen(word)!=0)
    {
        //find lowerbound, that is word>=index[mid];
        while (start <= end)
        {   
            mid = (start + end) / 2;
            
            if( start == mid )
            {
                break;
            }
            
            result = strcmp_nocase(word, index[mid]);
            if ( result < 0 )
            {
                end = mid;          //find lowerbound, don't minus 1;
            }
            else if ( result > 0 )
            {
                start = mid;        //find lowerbound, don't add 1;
            }
            else// if (result == 0)
            {
                found = true;
                break;
            }
        }
        
        if( !found && (mid+1)<wordcount )    //if not exactly match, find a similar one.
        {   
            if( strmatch_nocase(word, index[mid+1])>=strmatch_nocase(word, index[mid]) )
            {
                mid ++;
            }
        }
    }
    
    
    return mid;
}

void construct_entry_text(WSHDR* word_entry_text, char* word, int show_word, int show_phonetic, int show_meaning)
{
    unsigned int errcode;
    int word_len = strlen(word);
    char* pos = word + word_len + 1;
    unsigned long int offset = (pos[0]<<16) | (pos[1]<<8) | pos[2];
    //pos += 4;
    unsigned long int size = pos[3];
    
    lseek(dict, offset, S_SET, &errcode, &errcode);
    
    //µ¥´Ê
    if( show_word )
    {
        str_2ws(word_entry_text, word, word_len);
        wsAppendChar(word_entry_text, '\n');
    }
    else
    {
        str_2ws(word_entry_text, "", strlen(""));
    }
    
    char buf[MAX_UNICODE_STR];
    if( (fread(dict, buf, size, &errcode)) != size )
    {
        SetError("Can't read dict file!");
        return;
    }
    
    //char aa[100];
    //sprintf(aa, "off=%d, size=%d, err=%X\0", offset, size, errcode);
    //str_2ws(ec2.pWS, aa, strlen(aa));
    
    //Òô±ê
    WSHDR *ws = AllocWS(MAX_UNICODE_STR);
    int phonetic_len = strlen(buf);
    if( show_phonetic )
    {
        utf8_2ws(ws, buf, phonetic_len);
        wsInsertChar(ws, '[', 1);
        wsAppendChar(ws, ']');
        wsAppendChar(ws, '\n');
        wstrcat(word_entry_text, ws);
    }
    
    //½âÊÍ
    if( show_meaning )
    {
        utf8_2ws(ws, buf+phonetic_len+1, size-phonetic_len-1);
        wstrcat(word_entry_text, ws);
    }
    
    FreeWS(ws);
}

void LoadDictIndex()
{
	//char fname[40];
	//sprintf(fname, "0:\\ZBin\\dict\\stardict1.3.idx.gz");

	//gzFile f;
	//f=gzopen(fname, "rb");

	int f;
	unsigned int errcode;
    
	f = fopen(modidx_dir, A_ReadOnly+A_BIN, P_READ, &errcode);
  //  f = fopen("0:\\ZBin\\dict\\stardict1.3.mod.idx", A_ReadOnly+A_BIN, P_READ, &errcode);
	if( f<0 )
	{
	//	f = fopen("4:\\ZBin\\dict\\stardict1.3.mod.idx", A_ReadOnly+A_BIN, P_READ, &errcode);
	//	if( f<0 )
		{
			SetError("Can't open index file!");
			return;
		}
	}

	if ((indexbuf = malloc(idxbuf_size))==0)
	{
		SetError("Can't malloc indexbuf!");
		return;
	}

	//if (gzread(f, index, idx_size)!=idx_size)
	if( (fread(f, indexbuf, idxbuf_size, &errcode)) != idxbuf_size )
	{
		SetError("Can't read index file!");
		fclose(f, &errcode);

		return;
	}
	//gzclose(f);
	fclose(f, &errcode);

	index = malloc( wordcount*sizeof(char*) );
	if( index == NULL )
	{
		SetError("Can't malloc index!");
		return;
	}

	char *pos=indexbuf;
	int i = 0;
	while (pos < indexbuf+idxbuf_size)
	{
		index[i++] = pos;
		pos += strlen(pos) + 1 + 4; /*sizeof(long)*2;*/
	}
}

void UnloadDictIndex()
{
	if (indexbuf != NULL)
	    mfree(indexbuf);

	if (index != NULL )
	    mfree(index);
}

void OpenDict()
{   
	unsigned int errcode;
  dict = fopen(dict_dir, A_ReadOnly+A_BIN, P_READ, &errcode);
	//dict = fopen("0:\\ZBin\\dict\\stardict1.3.dict", A_ReadOnly+A_BIN, P_READ, &errcode);
	if( dict <= 0 )
	{
		//dict = fopen("4:\\ZBin\\dict\\stardict1.3.dict", A_ReadOnly+A_BIN, P_READ, &errcode);
		//if( dict <= 0 )
		{
			SetError("Can't open dict file!");
		}
	}
}

void CloseDict()
{
	unsigned int errcode;
	if ( dict > 0 )
	{
		fclose(dict, &errcode);
	}
}
