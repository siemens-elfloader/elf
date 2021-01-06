// master string
// jared bruni
// my string algorithims :)

#include "masterstring.h"

// string copy
void stringcopy(char* input,char* output)
{
	strcpy(input,output);
}

// string attach
void stringattach(char* input,char* output)
{
	strcat(input,output);
}

// left copy
void leftcopy(char* input,char* output,int pos)
{
	int index = 0;
	for(int i = 0; i < pos; i++)
	{
		output[index] = input[i];
		index++;
	}
	output[index] = 0;
}
// right copy
void rightcopy(char* input,char* output,int pos)
{
	int index = 0;
	int len = strlen(input);
	for(int i = pos; i < len; i++)
	{
		output[index] = input[i];
		index++;
	}
	output[index] = 0;

}
// mid copy
void midcopy(char* input,char* output,int start_pos, int stop_pos)
{
	int index = 0;
	for(int i = start_pos; i < stop_pos; i++)
	{
		output[index] = input[i];
		index++;
	}

	output[index] = 0;
}

// trim the space
void trimspace(char* buffer)
{
	int len;
	len = strlen(buffer);
	char* ptemp;
	ptemp = new char[len+1];
	strcpy(ptemp,buffer);

	int index = 0;
	for(int z = 0; z < len; z++)
	{
		if(ptemp[z] != ' ')
		{
			buffer[index] = ptemp[z];
			index++;
		}
	}
	buffer[index] = 0;

	delete [] ptemp;
}

int findstr(char* body,char* search)
{
	int len = strlen(body);
	int len2 = strlen(search); // search len

	for(int i = 0; i < len; i++)
	{
		if(body[i] == search[0])
		{
			bool ichk = true;

			for(int z = 0; z < len2; z++)
			{
				if(body[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
				return i;
			}
		}
	}

	return -1; // failure
}

int ifindstr(int startx,char* body,char* search)
{
	int len = strlen(body);
	int len2 = strlen(search); // search len

	for(int i = startx+1; i < len; i++)
	{
		if(body[i] == search[0])
		{
			bool ichk = true;

			for(int z = 0; z < len2; z++)
			{
				if(body[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
				return i;
			}
		}
	}

	return -1; // failure
}

int findstrb(char* body,char* search)
{
	int len = strlen(body);
	int len2 = strlen(search);

	for(int i = len; i > 0; i--)
	{
		if(body[i] == search[0])
		{
			bool ichk = true;
			for(int z = 0; z < len2; z++)
			{
				if(body[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
				return i; // found it
			}
		}

	}
	return -1; // failure
}
// find inside backwards string loop
int ifindstrb(int startx, char* body,char* search)
{
	int len = strlen(body);
	int len2 = strlen(search);

	for(int i = startx-1; i > 0; i--)
	{
		if(body[i] == search[0])
		{
			bool ichk = true;
			for(int z = 0; z < len2; z++)
			{
				if(body[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
				return i; // found it
			}
		}

	}
	return -1; // failure
}
// forward search string (controled range) 
int fsearchstr(int start,int stop,char* buff,char* search)
{
	int len = strlen(buff);
	int len2 = strlen(search);

	for(int i = start; i < stop; i++)
	{
		if(buff[i] == search[0])
		{
			bool ichk = true;

			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
			  return i; // found it
			}
		}
	}

	return -1; // failure
}

// backward search string (controled range)
int bsearchstr(int start,int stop,char* buff,char* search)
{
	int len = strlen(buff);
	int len2 = strlen(search);

	for(int i = start; i > stop; i--)
	{
		if(buff[i] == search[0])
		{
			bool ichk = true;

			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ichk = false;
				}
			}

			if(ichk == true)
			{
				return i; // found it;
			}
		}
	}

	return -1;// failure
}
// getting length
int getlen(char* buff)
{
	return strlen(buff);// use strlen :)
}
// lower case
void lcase(char* buffer)
{
	int len = getlen(buffer);

	for(int i = 0; i < len; i++)
	{
		buffer[i] = tolower(buffer[i]);
	}
}
// upercase
void ucase(char* buffer)
{
	int len = getlen(buffer);

	for(int i = 0; i < len; i++)
	{
		buffer[i] = toupper(buffer[i]);
	}
}
// uppercase letter
int ucasel(char c)
{
	return tolower(c);
}

// lowercase letter
int lcasel(char c)
{
	return tolower(c);
}

// find string location algorithims
bool findstrloc(char* buff,char* search,MasStrDataLoc* dloc)
{
	int len = strlen(buff);
	int len2 = strlen(search);
	int* f;
	int  f_i = 0;
	f = new int[len+1];// big just in case

	for(int i = 0; i < len; i++)
	{
		if(buff[i] == search[0])
		{
			bool ic = true;
				
			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{

				}
				else
				{
					ic = false;
				}
			}

			if(ic == true)
			{
				f[f_i] = i;
				f_i++;
			}
		}
	}

	dloc->create_array(f_i);
	dloc->setstr(buff);
	dloc->setsearchstr(search);
	for(int p = 0; p < f_i; p++)
	{
		dloc->dindex[p] = f[p];
	}
	delete [] f;

	if(f_i != 0)
	{
		dloc->setstatus(true);
		return true; // we got some locations
	}
	else
	{
		dloc->setstatus(false); 
		return false; // not found
	}
}
// find string location forward search
bool findstrlocf(char* buff,char* search,MasStrDataLoc* dloc)
{
	return findstrloc(buff,search,dloc);
}
// find string location backwards search
bool findstrlocb(char* buff,char* search,MasStrDataLoc* dloc)
{
	int len = strlen(buff);
	int len2 = strlen(search);
	int* f;
	int  f_i = 0;
	f = new int[len+1];// big just in case

	for(int i = len; i > 0; i--)
	{
		if(buff[i] == search[0])
		{
			bool ic = true;
				
			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{

				}
				else
				{
					ic = false;
				}
			}

			if(ic == true)
			{
				f[f_i] = i;
				f_i++;
			}
		}
	}

	dloc->create_array(f_i);
	dloc->setstr(buff);
	dloc->setsearchstr(search);
	for(int p = 0; p < f_i; p++)
	{
		dloc->dindex[p] = f[p];
	}
	delete [] f;

	if(f_i != 0)
	{
		dloc->setstatus(true);
		return true; // we got some locations
	}
	else
	{
		dloc->setstatus(false);
		return false; // not found
	}
}

// string ( range based ) manipulation algorithims
bool searchrange(char* buff,char* search,MasStrRange* mrang)
{
	int len;
	int len2;
	len = strlen(buff);
	len2 = strlen(search);

	for(int i = 0; i < len; i++)
	{
		if(buff[i] == search[0])
		{
			bool ik = true;

			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ik = false;
				}
			}

			if(ik == true)
			{
				mrang->SetRange(i,i+len2);
				return true;
			}
		}
	}
	mrang->SetRange(0,0);
	return false;
}
// string range manipluation ex (i)
bool isearchrange(int startx, char* buff,char* search,MasStrRange* mrang)
{
	int len;
	int len2;
	len = strlen(buff);
	len2 = strlen(search);

	for(int i = startx+1; i < len; i++)
	{
		if(buff[i] == search[0])
		{
			bool ik = true;

			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ik = false;
				}
			}

			if(ik == true)
			{
				mrang->SetRange(i,i+len2);
				return true;
			}
		}
	}
	mrang->SetRange(0,0);
	return false;
}

// find the occourance amount of a specific string
int findoccourance(char* buff,char* search)
{
	int len;
	int len2;
	len = strlen(buff);
	len2 = strlen(search);

	int occ = 0;

	for(int i = 0; i < len; i++)
	{
		if(buff[i] == search[0])
		{
			bool ic = true;

			for(int z = 0; z < len2; z++)
			{
				if(buff[i+z] == search[z])
				{
				}
				else
				{
					ic = false;
				}
			}

			if(ic == true)
			{
				occ++;
			}

		}
	}

	if(occ == 0)
	{

	return -1; // failure

	}
	else
	{
		return occ;
	}
}

// string range manipulation copy left range
void copyleftrange(char* input,char* output,MasStrRange* mrang,int hi_lo)
{
	if(hi_lo == MRANGE_HI)
	{
		leftcopy(input,output,mrang->GetRangeHI());
	}
	else
	{
		leftcopy(input,output,mrang->GetRangeLO());
	}
}
// string range manipulation copy right range
void copyrightrange(char* input,char* output,MasStrRange* mrang,int hi_lo)
{
	if(hi_lo == MRANGE_HI)
	{
		rightcopy(input,output,mrang->GetRangeHI());
	}
	else
	{
		rightcopy(input,output,mrang->GetRangeLO());
	}
}
// string range manipulation mid copy
void copymidrange(char* input,char* output,MasStrRange* mrang, int hi_lo,MasStrRange* mrangx, int hi_lox)
{
	int cx;
	int cy;

	if(hi_lo == MRANGE_HI)
	{
		cx = mrang->GetRangeHI();
	}
	else
	{
		cx = mrang->GetRangeLO();
	}

	if(hi_lox == MRANGE_HI)
	{
		cy = mrangx->GetRangeHI();
	}
	else
	{
		cy =mrangx->GetRangeLO();
	}

	midcopy(input,output,cx,cy);
}

// create a list from string data
void createstrlist(char* buff,char* search,MasStrList* list)
{
	int occ;
	occ = findoccourance(buff,search);

	if(occ == -1)
	{
		return; // failure
	}
	list->create(occ);

	int occ_i = 0;

	MasStrDataLoc dloc;

	if(findstrloc(buff,search,&dloc))
	{
		int pre_pos = 0;

		for(int z = 0; z < dloc.getmaxpoint(); z++)
		{
			int cur = 0;
			cur = dloc.dindex[z];
			charwrap cwrap(buff);
			cwrap.strclearn();
			midcopy(buff,cwrap.get(),pre_pos,cur);
			list->strings[occ_i].set(cwrap.get());
			occ_i++;
			pre_pos = cur;
		}

		charwrap cwrapx(buff,true);
		rightcopy(buff,cwrapx.get(),pre_pos);
		list->strings[occ_i].set(cwrapx.get());
		occ_i++;
		}

	return;
}
// conversion of integers
void convertinteger(int integer,char* buff,int base)
{
	itoa(integer,buff,base);
}
// conversion of strings
int convertstring(char* buff)
{
	return atoi(buff);
}
// could this be a hexidecimal digit?
bool ishexc(char c)
{
	c = lcasel(c);
	switch(c)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
		return true;
		break;
	}
	return false;
}
// does this string contain a non-hexidecimal digit?
bool ishex(char* buff)
{
	int len;
	len = strlen(buff);

	for(int i = 0; i < len; i++)
	{
		if(ishexc(buff[i]) == false)
		{
			return false;
		}
	}
	return true;
}

// hexidecimal digit to integer value
int hextointc(char c)
{
	if(ishexc(c) == false)
	{
		return -1; // failure, not a hex digit
	}

	c = lcasel(c);

	switch(c)
	{
	case '0':
		return 0;
		break;
	case '1':
		return 1;
		break;
	case '2':
		return 2;
		break;
	case '3':
		return 3;
		break;
	case '4':
		return 4;
		break;
	case '5':
		return 5;
		break;
	case '6':
		return 6;
		break;
	case '7':
		return 7;
		break;
	case '8':
		return 8;
		break;
	case '9':
		return 9;
		break;
	case 'a':
		return 10;
		break;
	case 'b':
		return 11;
	case 'c':
		return 12;
	case 'd':
		return 13;
	case 'e':
		return 14;
	case 'f':
		return 15;
	}

	return -1; // failure ? never would get here
}

// convert hex value into a integer
int hextoint(char* buff)
{
	int rt = 0;

	if(buff[1] == 0)
	{
		return hextointc(buff[0]);
	}

	int len = strlen(buff);
	int* hexval;
	hexval = new int[len+1];
	int  hexvali = 0;

	for(int i = 0; i < len; i++)
	{
		hexval[hexvali] = hextointc(buff[i]);
		hexvali++;
	}

    int index = 0;

	for(int z = hexvali-1; z >= 0; z--)
	{
		int cur;
		if(index == 0)
		{
			cur = hexval[z];
			index = 16;
		}
		else
		{

		cur = hexval[z] * index;
		index = index * 16;
		}
		
		rt = rt + cur;
	}

	delete [] hexval;

	return rt;
} 


void tripcharup(char* buff, int up)
{
	int len;
	len = strlen(buff);

	for(int i = 0; i < len; i++)
	{
		if(buff[i] != 0)
		{

		buff[i] = buff[i] + up;

		}
	}
}

void tripchardown(char* buff,int up)
{
	int len;
	len = strlen(buff);

	for(int i = 0; i < len; i++)
	{
		if(buff[i] != 0)
		{

		buff[i] = buff[i] - up;

		}
	}
}
// replace single instance of a character
void replacechar(char* buff,char findchr,char replace)
{
	int len;
	len = strlen(buff);

	for(int z = 0; z < len; z++)
	{
		if(buff[z] == findchr)
		{
			buff[z] = replace;
		}
	}
}

void rmvinst(char* buff,char* findstr,char* replacex,char* output)
{

	int xt = ifindstr(NOPREV,buff,findstr);


	char* temp;
	temp = new char[strlen(buff)+1];
	stringcopy(temp,buff);

	char* ltemp;
	char* rtemp;

	ltemp = new char[strlen(buff)+1];
	rtemp = new char[strlen(buff)+1];

	leftcopy(buff,ltemp,xt);
	rightcopy(buff,rtemp,xt+strlen(findstr));


	cout << "\n#: " << ltemp << replacex << rtemp << endl;

	
	strcpy(output,ltemp);
	strcat(output,replacex);
	strcat(output,rtemp);

	delete [] temp;
	delete [] ltemp;
	delete [] rtemp;
}


// replace string
void replacestr(char* buff,char* findstr,char* replacex,char* output)
{
	int xt;
	xt = ifindstr(0,buff,findstr);

	if(xt == -1)
	{
		return; // failure no string to replace
	}

	char* ptemp;
	char* outtemp;
	ptemp = new char[strlen(buff) + 500];
	outtemp = new char[strlen(buff) + 500];
	stringcopy(ptemp,buff);

	while(1)
	{
		int xr;
		xr = ifindstr(0,ptemp,findstr);
		if(xr == -1)
		{
			break;
		}
		else
		{
			rmvinst(ptemp,findstr,replacex,outtemp);
			stringcopy(ptemp,outtemp);
		}
	}

	stringcopy(output,ptemp);

	delete [] ptemp;
	delete [] outtemp;

}

// random char
char randomchar(int max)
{
	int x;
	x = rand()%max;
	char c;
	c = x;
	return c;
}
// random char + up
char randomchar(int max,int up)
{
	int x;
	x = rand()%max+up;
	char c;
	c = x;
	return c;
}
// random string
void randomstr(char* buff,int max, int size)
{
	for(int i = 0; i < size; i++)
	{
		if(rand()%2)
		{
			buff[i] = randomchar(max);
		}
		else
		{
			buff[i] = randomchar(max,rand()%10);
		}
	}
}
// remove char
void removechar(char* in,char* out,char c)
{
	int len;
	len = strlen(in);
	int ic = 0;
	for(int i = 0; i < len; i++)
	{
		if(in[i] != c)
		{
			out[ic] = in[i];
			ic++;
		}
	}
	out[ic] = 0;
}

// find single character in string
int findchar(char* str,char c)
{
	int len = strlen(str);
	for(int i = 0; i < len; i++)
	{
		if(str[i] == c)
		{
			return i;
		}
	}

	return -1; // failure
}
// find char ex (inside)
int ifindchar(int start,char* str,char c)
{
	int len = strlen(str);
	for(int i = start+1; i < len; i++)
	{
		if(str[i] == c)
		{
			return i;
		}
	}

	return -1;
}
// find single char backward
int findcharb(char* str,char c)
{
	int len;
	len = strlen(str);
	for(int i = len; i > 0; i--)
	{
		if(str[i] == c)
		{
			return i;
		}
	}

	return -1;
}
// find single char backward
int ifindcharb(int start,char* str,char c)
{
	int len;
	len = strlen(str);
	for(int i = start-1; i > 0; i--)
	{
		if(str[i] == c)
		{
			return i;
		}
	}
	return -1;
}

int  findcharcf(char* str,int start,int stop,char c)
{
	for(int i = start; i < stop; i++)
	{
		if(str[i] == c)
		{
			return i;
		}
	}

	return -1; // failure
}
int  findcharcb(char* str,int start,int stop,char c)
{
	for(int i = stop; i > start; i--)
	{
		if(str[i] == c)
		{
			return i;
		}
	}
	return -1;// failure
}
// remove instances of string
void removestr(char* input,char* output,char* string)
{

	char* buff = input;
	char* findstr = string;

	int xt;
	xt = ifindstr(NULLPOS,buff,findstr);

	if(xt == -1)
	{
		return; // failure no string to replace
	}

	char* ptemp;
	char* outtemp;
	ptemp = new char[strlen(buff) + 500];
	outtemp = new char[strlen(buff) + 500];
	stringcopy(ptemp,buff);

	while(1)
	{
		int xr;
		xr = ifindstr(0,ptemp,findstr);
		if(xr == -1)
		{
			break;
		}
		else
		{
			rmvstrx(ptemp,findstr,outtemp);
			stringcopy(ptemp,outtemp);
		}
	}

	stringcopy(output,ptemp);

	delete [] ptemp;
	delete [] outtemp;

}

void rmvstrx(char* buff,char* output,char* string)
{
	int xt = ifindstr(NOPREV,buff,string);

	char* temp;
	temp = new char[strlen(buff)+1];
	stringcopy(temp,buff);

	char* ltemp;
	char* rtemp;

	ltemp = new char[strlen(buff)+1];
	rtemp = new char[strlen(buff)+1];

	leftcopy(buff,ltemp,xt);
	rightcopy(buff,rtemp,xt+strlen(string));
	
	strcpy(output,ltemp);
	strcat(output,rtemp);

	delete [] temp;
	delete [] ltemp;
	delete [] rtemp;
}

void strsavefile(char* filename,char* buff)
{
	ofstream fout(filename);

	fout << buff;

	fout.close();
}

int getfilestringlength(char* filename)
{
	int count = 0;
	ifstream fin(filename);
	if(fin)
	{
		char ch;
		while(fin.get(ch))
		{
			count++;
		}

		fin.close();
		return count;

	} else { return -1; } // failure

	return -1;
}

bool strloadfile(char* file,char* output)
{
	int count = 0;
	ifstream fin(file);
	if(fin)
	{
		char ch;
		int str_i = 0;
		while(fin.get(ch))
		{
			output[str_i] = ch;
			str_i++;
		}

		output[str_i] = 0;
		return true;
	}
	else
	{
		return false;
	}

	return false;
}

void reversestring(char* input,char* output)
{
	int len;
	len = strlen(input);
	int fcount = 0;

	for(int i = len; i > 0; i--)
	{
		output[fcount] = input[i];
		fcount++;
	}
	
	output[fcount] = 0;
}

bool isstrvalid(char* string)
{
	int len = strlen(string);
	for(int i = 0; i < len; i++)
	{
		if(string[i] == 0)
		{
			return true; // true it is a null terminated string!
		}
	}

	return false;
}

// Save Master INI
bool SaveMasterINI(char* filename,MasterINI* mini)
{
	ofstream fout(filename,ios::binary);

	if(fout)
	{


	fout.write((char*)&mini,sizeof(mini));

	fout.close();

	return true;

	}
	fout.close();
	return false;
}
// Load master INI
bool LoadMasterINI(char* filename,MasterINI* mini)
{
	ifstream fin(filename,ios::binary);

	if(fin)
	{
		fin.read((char*)&mini,sizeof(mini));
	}
	
	fin.close();
	return false;
}

// string compare (case sensitive)
bool mstrcmp(char* buff1,char* buff2)
{
	int len;
	int len2;
	len = strlen(buff1);
	len2 = strlen(buff2);

	if(len != len2)
	{
		return false; // not equal length
	}

	for(int i = 0; i < len; i++)
	{
		if(buff1[i] != buff2[i])
		{
			return false;
		}
	}

	return true;
}

// string compare (not case sensitive)
bool mstrcmpx(char* buff1,char* buff2)
{
	int len;
	int len2;
	len = strlen(buff1);
	len2 = strlen(buff2);

	if(len != len2)
	{
		return false; // not equal length
	}

	for(int i = 0; i < len; i++)
	{
		if(tolower(buff1[i]) != tolower(buff2[i]))
		{
			return false;
		}
	}

	return true;
}

bool insidestr(char* buff1,char* buff2)
{
	int chk;
	chk = findstr(buff1,buff2);

	if(chk == -1)
	{
		return false;
	}
	
	return true;
}

bool insidestrx(char* buff1,char* buff2)
{
	char* pbuff1;
	char* pbuff2;

	pbuff1 = new char[strlen(buff1)+1];
	pbuff2 = new char[strlen(buff2)+1];

	stringcopy(pbuff1,buff1);
	stringcopy(pbuff2,buff2);

	lcase(pbuff1);
	lcase(pbuff2);

	int chk;
	chk = findstr(pbuff1,buff2);

	delete [] pbuff1;
	delete [] pbuff2;
	pbuff1 = 0;
	pbuff2 = 0;

	if(chk == -1)
	{
		return false;
	}
	
	return true;
}
// string seperation from 2 points
void strsep(char* str, char* sleft, int go_left, char* sright, int go_right)
{
	leftcopy(str,sleft,go_left);
	rightcopy(str,sright,go_right);
}
void strsetnull(char* str,int pos)
{
	str[pos] = 0;
}

void rmvnullset(char* str)
{
	int len;
	len = strlen(str);
	for(int i = 0; i < len; i++)
	{
		if(str[i] == 0)
		{
			str[i] = ' ';
		}
	}
}

int getnullpos(char* str)
{
	int len = strlen(str);
	for(int i = 0; i < len; i++)
	{
		if(str[i] == 0)
		{
			return i;
		}
	}

	return -1; // failure to find 0
}
// trim commented characters () 
void trimcom(char* str, char* output,char start_c,char stop_c)
{
	int len = strlen(str);
	int index = 0;

	bool iadd = true;

	for(int z = 0; z < len; z++)
	{
		if(str[z] == start_c)
		{
			iadd = false; 
		}

		if(str[z] == stop_c)
		{
			iadd = true;
		}

		if(iadd == true)
		{
			output[index] = str[z];
			index++;
		}
	}
	
	output[index] = 0;
}

// trim comments to an assembly language source file
void asmtrim(char* input,char* output)
{
	trimcom(input,output,';','\n');
}

// count the number of lines exisitng within the source
int countlines(char* buffer)
{
	return findoccourance(buffer,"\n");
}
// get the first letter thats not a space
int getfirstletter(char* buff)
{
	int len = strlen(buff);
	
	for(int i = 0; i < len; i++)
	{
		if(buff[i] != ' ')
		{
			return i;
		}
	}
	return -1; // failure! no letters
}
