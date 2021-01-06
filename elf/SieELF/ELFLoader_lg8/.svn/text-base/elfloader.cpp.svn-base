//#define wintel	//§Ü§à§Þ§á§Ö§Ý§Ú§Þ §á§à§Õ §Ó§Ú§ß§Õ§å

#define MAX_PHNUM	10	//§Þ§Ñ§Ü§ã§Ú§Þ§Ñ§Ý§î§ß§à§Ö §Ü§à§Ý§Ú§é§Ö§ã§ä§Ó§à §á§â§à§Ô§â§Ñ§Þ§ß§í§ç §ã§Ö§Ô§Þ§Ö§ß§ä§à§Ó

#ifdef wintel
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#define _CRT_SECURE_NO_DEPRECATE
#include "stdlib.h"
#include "stdio.h"
#include <iostream>
using namespace std;
#define mfree free
#endif

#ifndef wintel
#include "..\inc\swilib.h"
#include "conf_loader.h"
#endif

typedef unsigned long  Elf32_Addr;	//Unsigned program address 4
typedef unsigned short Elf32_Half;	//Unsigned medium integer  2
typedef unsigned long  Elf32_Off; 	//Unsigned file offset     4
typedef          long  Elf32_Sword; 	//Signed large integer     4
typedef unsigned long  Elf32_Word; 	//Unsigned large integer   4

//ELF Header
//e_ident[] Identification Indexes
#define EI_MAG0    0  //File identification
#define EI_MAG1    1  //File identification
#define EI_MAG2    2  //File identification
#define EI_MAG3    3  //File identification
#define EI_CLASS   4  //File class
#define EI_DATA    5  //Data encoding
#define EI_VERSION 6  //File version
#define EI_PAD     7  //Start of padding bytes
#define EI_NIDENT  16 //Size of e_ident[]

typedef struct{
  unsigned char e_ident[EI_NIDENT]; //The initial bytes mark the file as an object file and provide machine-independent data with which to decode and interpret the file¡¯s contents.
  Elf32_Half e_type;      //This member identifies the object file type.
  Elf32_Half e_machine;   //This member¡¯s value specifies the required architecture for an individual file.
  Elf32_Word e_version;   //This member identifies the object file version.
  Elf32_Addr e_entry;     //This member gives the virtual address to which the system first transfers control, thus starting the process. If the file has no associated entry point, this member holds zero.
  Elf32_Off  e_phoff;     //This member holds the program header table¡¯s file offset in bytes. If the file has no program header table, this member holds zero.
  Elf32_Off  e_shoff;     //This member holds the section header table¡¯s file offset in bytes. If the file has no section header table, this member holds zero.
  Elf32_Word e_flags;     //This member holds processor-specific flags associated with the file. Flag names take the form EF_machine_flag.
  Elf32_Half e_ehsize;    //This member holds the ELF header¡¯s size in bytes.
  Elf32_Half e_phentsize; //This member holds the size in bytes of one entry in the file¡¯s program header table; all entries are the same size.
  Elf32_Half e_phnum;     //This member holds the number of entries in the program header table. Thus the product of e_phentsize and e_phnum gives the table¡¯s size in bytes. If a file has no program header table, e_phnum holds the value zero.
  Elf32_Half e_shentsize; //This member holds a section header¡¯s size in bytes. A section header is one entry in the section header table; all entries are the same size.
  Elf32_Half e_shnum;     //shnum¡ªThis member holds the number of entries in the section header table. Thus the product of e_shentsize and e_shnum gives the section header table¡¯s size in bytes. If a file has no section header table, e_shnum holds the value zero.
  Elf32_Half e_shstrndx;  //This member holds the section header table index of the entry associated with the section name string table. If the file has no section name string table, this member holds the value SHN_UNDEF.
} Elf32_Ehdr;

//E_type¡ªThis member identifies the object file type.
#define ET_NONE   0        //No file type
#define ET_REL    1        //Re-locatable file
#define ET_EXEC   2        //Executable file
#define ET_DYN    3        //Shared object file
#define ET_CORE   4        //Core file
#define ET_LOPROC 0xFF00   //Processor-specific
#define ET_HIPROC 0xFFFF   //Processor-specific

//E_machine¡ªThis member¡¯s value specifies the required architecture for an individual file.
#define EM_NONE        0  //No machine
#define EM_M32         1  //AT&T WE 32100
#define EM_SPARC       2  //SPARC
#define EM_386         3  //Intel Architecture
#define EM_68K         4  //Motorola 68000
#define EM_88K         5  //Motorola 88000
#define EM_860         7  //Intel 80860
#define EM_MIPS        8  //MIPS RS3000 Big-Endian
#define EM_MIPS_RS4_BE 10 //MIPS RS4000 Big-Endian
#define EM_ARM         40 //ARM/Thumb Architecture

//E_version¡ªThis member identifies the object file version.
#define EV_NONE    0 //Invalid version
#define EV_CURRENT 1 //Current version

//EI_MAG0 0 to EI_MAG3¡ªA file¡¯s first 4 bytes hold a magic number, identifying the file as an ELF object file. Name Value Meaning
#define ELFMAG0 0x7f //e_ident[EI_MAG0]
#define ELFMAG1 'E' //e_ident[EI_MAG1]
#define ELFMAG2 'L' //e_ident[EI_MAG2]
#define ELFMAG3 'F' //e_ident[EI_MAG3]

//EI_CLASS¡ªThe next byte, e_ident[EI_CLASS], identifies the file¡¯s class, or capacity. Name Value Meaning
#define ELFCLASSNONE 0 //Invalid class
#define ELFCLASS32   1 //32-bit objects
#define ELFCLASS64   2 //64-bit objects

//EI_DATA¡ªByte e_ident[EI_DATA]specifies the data encoding of all data1 in the object file. The following encodings are currently defined. Name Value Meaning
#define ELFDATANONE 0 //Invalid data encoding
#define ELFDATA2LSB 1 //See Data encodings ELFDATA2LSB, below
#define ELFDATA2MSB 2 //See Data encodings ELFDATA2MSB, below

//Sections
//Section Header
typedef struct{
  Elf32_Word sh_name;      //This member specifies the name of the section. Its value is an index into the section header string table section [see section 3.4, String Table below], giving the location of a null-terminated string.
  Elf32_Word sh_type;      //type¡ªThis member categorizes the section¡¯s contents and semantics. Section types and their descriptions appear in Figure 3-9 below.
  Elf32_Word sh_flags;     //Sections support 1-bit flags that describe miscellaneous attributes. Flag definitions appear in Figure 3-11, below.
  Elf32_Addr sh_addr;      //If the section will appear in the memory image of a process, this member gives the address at which the section¡¯s first byte should reside. Otherwise, the member contains 0.
  Elf32_Off  sh_offset;    //This member¡¯s value gives the byte offset from the beginning of the file to the first byte in the section. One section type, SHT_NOBITS described in Figure 3-9 below, occupies no space in the file, and its sh_offset member locates the conceptual placement in the file.
  Elf32_Word sh_size;      //This member gives the section¡¯s size in bytes. Unless the section type is SHT_NOBITS, the section occupies sh_size bytes in the file. A section of type SHT_NOBITS may have a non-zero size, but it occupies no space in the file.
  Elf32_Word sh_link;      //This member holds a section header table index link, whose interpretation depends on the section type. Figure 3-12 below describes the values.
  Elf32_Word sh_info;      //This member holds extra information, whose interpretation depends on the section type. Figure 3-12 below describes the values.
  Elf32_Word sh_addralign; //Some sections have address alignment constraints. For example, if a section holds a doubleword, the system must ensure double-word alignment for the entire section. That is, the value of sh_addr must be congruent to 0, modulo the value of sh_addralign. Currently, only 0 and positive integral powers of two are allowed. Values 0 and 1 mean the section has no alignment constraints.
  Elf32_Word sh_entsize;   //Some sections hold a table of fixed-size entries, such as a symbol table. For such a section, this member gives the size in bytes of each entry. The member contains 0 if the section does not hold a table of fixedsize entries. A section header¡¯s sh_type member specifies the section¡¯s semantics.
} Elf32_Shdr;

//Special Section Indexes
#define SHN_UNDEF     0     //This value marks an undefined, missing, irrelevant, or otherwise meaningless section reference. For example, a symbol ¡°defined¡± relative to section number SHN_UNDEF is an undefined symbol.
#define SHN_LORESERVE 0xff00 //This value specifies the lower bound of the range of reserved indexes.
#define SHN_LOPROC    0xff00 //Values in this range are reserved for processor-specific semantics.
#define SHN_HIPROC    0xff1f //Values in this range are reserved for processor-specific semantics.
#define SHN_ABS       0xfff1 //This value specifies absolute values for the corresponding reference. For example, symbols defined relative to section number SHN_ABS have absolute values and are not affected by relocation.
#define SHN_COMMON    0xfff2 //Symbols defined relative to this section are common symbols, such as FORTRAN COMMON or unallocated C external variables.
#define SHN_HIRESERVE 0xffff //This value specifies the upper bound of the range of reserved indexes. The system reserves indexes between SHN_LORESERVE and SHN_HIRESERVE, inclusive; the values do not refer to the section header table. That is, the section header table does not contain entries for the reserved indexes.

//sh_type
#define SHT_NULL     0  //This value marks a section header that does not have an associated section. Other members of the section header have undefined values
#define SHT_PROGBITS 1  //The section holds information defined by the program, whose format and meaning are determined solely by the program.
#define SHT_SYMTAB   2  //The section holds a symbol table.
#define SHT_STRTAB   3  //The section holds a string table.
#define SHT_RELA     4  //The section holds relocation entries with explicit addends, such as type Elf32_Rela for the 32-bit class of object files. An object file may have multiple relocation sections. See Relocation below for details.
#define SHT_HASH     5  //The section holds a symbol hash table.
#define SHT_DYNAMIC  6  //The section holds information for dynamic linking.
#define SHT_NOTE     7  //This section holds information that marks the file in some way.
#define SHT_NOBITS   8  //A section of this type occupies no space in the file but otherwise resembles SHT_PROGBITS. Although this section contains no bytes, the sh_offset member contains the conceptual file offset.
#define SHT_REL      9  //The section holds relocation entries without explicit addends, such as type Elf32_Rel for the 32-bit class of object files. An object file may have multiple relocation sections. See Relocation below for details.
#define SHT_SHLIB    10 //This section type is reserved but has unspecified semantics.
#define SHT_DYNSYM   11 //The section holds a symbol table.
#define SHT_LOPROC   0x70000000
#define SHT_HIPROC   0x7fffffff //Values in this inclusive range are reserved for processor-specific semantics.
#define SHT_LOUSER   0x80000000
#define SHT_HIUSER   0xffffffff //Values in this inclusive range are reserved for application programs. Types between SHT_LOUSER and SHT_HIUSER may be used by an application,without conflicting with current or future system-defined section types.

//Section Attribute Flags, sh_flags
#define SHF_WRITE     1          //The section contains data that should be writable during process execution
#define SHF_ALLOC     2          //The section occupies memory during process execution. Some control sections do not reside in the memory image of an object file; this attribute is off for those sections
#define SHF_EXECINSTR 4          //The section contains executable machine instructions.
#define SHF_MASKPROC  0xf0000000 //Bits in this mask are reserved for processor-specific semantics.

//Program
//Program Header
typedef struct{
  Elf32_Word p_type;   //This member tells what kind of segment this array element describes or how to interpret the array element's information. Type values and their meanings are given in Figure 3-21, below.
  Elf32_Off p_offset;  //This member gives the offset from the start of the file at which the first byte of the segment resides.
  Elf32_Addr p_vaddr;  //This member gives the virtual address at which the first byte of the segment resides in memory.
  Elf32_Addr p_paddr;  //On systems for which physical addressing is relevant, this member is reserved for the segment's physical address. This member requires operating system specific information.
  Elf32_Word p_filesz; //This member gives the number of bytes in the file image of the segment; it may be zero.
  Elf32_Word p_memsz;  //This member gives the number of bytes in the memory image of the segment; it may be zero.
  Elf32_Word p_flags;  //This member gives flags relevant to the segment. Defined flag values are given in Figure 3-22, below.
  Elf32_Word p_align;  //Loadable process segments must have congruent values for p_vaddr and p_offset, modulo the page size. This member gives the value to which the segments are aligned in memory and in the file. Values 0 and 1 mean that no alignment is required. Otherwise, p_align should be a positive, integral power of 2, and p_vaddr should equal p_offset, modulo p_align.
} Elf32_Phdr;

//Defined program header flags
#define PF_X 1 //The segment may be executed.
#define PF_W 2 //The segment may be written to.
#define PF_R 4 //The segment may be read.
#define PF_MASKPROC 0xf0000000 //Reserved for processor-specific purposes (see 4.6, Program headers).

//Segment Types, p_type
#define PT_NULL    0 //The array element is unused; other members' values are undefined. This type lets the program header table have ignored entries.
#define PT_LOAD    1 //The array element specifies a loadable segment, described by p_filesz and p_memsz (for additional explanation, see PT_LOAD below).
#define PT_DYNAMIC 2 //The array element specifies dynamic linking information. See subsection 4.7.
#define PT_INTERP  3 //The array element specifies the location and size of a null-terminated path name to invoke as an interpreter.
#define PT_NOTE    4 //The array element specifies the location and size of auxiliary information.
#define PT_SHLIB   5 //This segment type is reserved but has unspecified semantics.
#define PT_PHDR    6 //The array element, if present, specifies the location and size of the program header table itself (for additional explanation, see PT_ PHDR below).
#define PT_LOPROC  0x70000000 //Values in this inclusive range are reserved for processor-specific semantics.
#define PT_HIPROC  0x7fffffff

//The dynamic section
typedef struct{
  Elf32_Sword d_tag;
  Elf32_Word d_val;
} Elf32_Dyn;

//Dynamic section tags
#define DT_NULL     0  //Ignored. This entry marks the end of the dynamic array. mandatory
#define DT_NEEDED   1  //Index in the string table of the name of a needed library. multiple
#define DT_PLTRELSZ 2  //These entries are unused by versions 1-2 of the ARM EABI. unused
#define DT_PLTGOT   3
#define DT_HASH     4  //The offset of the hash table section in the dynamic segment. mandatory
#define DT_STRTAB   5  //The offset of the string table section in the dynamic segment. mandatory
#define DT_SYMTAB   6  //The offset of the symbol table section in the dynamic segment. mandatory
#define DT_RELA     7  //The offset in the dynamic segment of an SHT_RELA relocation section, Its byte size, and the byte size of an ARM RELA-type relocation entry. optional
#define DT_RELASZ   8
#define DT_RELAENT  9
#define DT_STRSZ    10 //The byte size of the string table section. mandatory
#define DT_SYMENT   11 //The byte size of an ARM symbol table entry¡ª16. mandatory
#define DT_INIT     12 //These entries are unused by versions 1-2 of the ARM EABI. unused
#define DT_FINI     13
#define DT_SONAME   14 //The Index in the string table of the name of this shared object. mandatory
#define DT_RPATH    15 //Unused by the ARM EABI. unused
#define DT_SYMBOLIC 16
#define DT_REL      17 //The offset in the dynamic segment of an SHT_REL relocation section, Its byte size, and the byte size of an ARM REL-type relocation entry optional
#define DT_RELSZ    18
#define DT_RELENT   19
#define DT_PLTREL   20 //These entries are unused by versions 1-2 of the ARM EABI. unused
#define DT_DEBUG    21
#define DT_TEXTREL  22
#define DT_JMPREL   23
#define DT_BIND_NOW 24
#define DT_LOPROC   0x70000000 //Values in this range are reserved to the ARM EABI. unused
#define DT_HIPROC   0x7fffffff

//Relocation Entries
typedef struct{
  Elf32_Addr r_offset;
  Elf32_Word r_info;
} Elf32_Rel;

typedef struct{
  Elf32_Addr  r_offset;
  Elf32_Word  r_info;
  Elf32_Sword r_addend;
} Elf32_Rela;

#define ELF32_R_SYM(i) ((i)>>8)
#define ELF32_R_TYPE(i) ((unsigned char)(i))
#define ELF32_R_INFO(s,t) (((s)<<8)+(unsigned char)(t))

//ARM relocation types
#define R_ARM_NONE            0   //Any No relocation. Encodes dependencies between sections.
#define R_ARM_PC24            1   //ARM B/BL S ¨C P + A
#define R_ARM_ABS32           2   //32-bit word S + A
#define R_ARM_REL32           3   //32-bit word S ¨C P + A
#define R_ARM_PC13            4   //ARM LDR r, [pc,¡­] S ¨C P + A
#define R_ARM_ABS16           5   //16-bit half-word S + A
#define R_ARM_ABS12           6   //ARM LDR/STR S + A
#define R_ARM_THM_ABS5        7   //Thumb LDR/STR S + A
#define R_ARM_ABS8            8   //8-bit byte S + A
#define R_ARM_SBREL32         9   //32-bit word S ¨C B + A
#define R_ARM_THM_PC22        10  //Thumb BL pair S ¨C P+ A
#define R_ARM_THM_PC8         11  //Thumb LDR r, [pc,¡­] S ¨C P + A
#define R_ARM_AMP_VCALL9      12  //AMP VCALL Obsolete¡ªSA-1500 only.
#define R_ARM_SWI24           13  //ARM SWI S + A
#define R_ARM_THM_SWI8        14  //Thumb SWI S + A
#define R_ARM_XPC25           15  //ARM BLX S ¨C P+ A
#define R_ARM_THM_XPC22       16  //Thumb BLX pair S ¨C P+ A
#define R_ARM_COPY            20  //32 bit word Copy symbol at dynamic link time.
#define R_ARM_GLOB_DAT        21  //32 bit word Create GOT entry.
#define R_ARM_JUMP_SLOT       22  //32 bit word Create PLT entry.
#define R_ARM_RELATIVE        23  //32 bit word Adjust by program base.
#define R_ARM_GOTOFF          24  //32 bit word Offset relative to start of GOT.
#define R_ARM_GOTPC           25  //32 bit word Insert address of GOT.
#define R_ARM_GOT32           26  //32 bit word Entry in GOT.
#define R_ARM_PLT32           27  //ARM BL Entry in PLT.
#define R_ARM_ALU_PCREL_7_0   32  //ARM ADD/SUB (S ¨C P + A) & 0x000000FF
#define R_ARM_ALU_PCREL_15_8  33  //ARM ADD/SUB (S ¨C P + A) & 0x0000FF00
#define R_ARM_ALU_PCREL_23_15 34  //ARM ADD/SUB (S ¨C P + A) & 0x00FF0000
#define R_ARM_LDR_SBREL_11_0  35  //ARM LDR/STR (S ¨C B + A) & 0x00000FFF
#define R_ARM_ALU_SBREL_19_12 36  //ARM ADD/SUB (S ¨C B + A) & 0x000FF000
#define R_ARM_ALU_SBREL_27_20 37  //ARM ADD/SUB (S ¨C B + A) & 0x0FF00000
#define R_ARM_GNU_VTENTRY     100 //32 bit word Record C++ vtable entry.
#define R_ARM_GNU_VTINHERIT   101 //32 bit word Record C++ member usage.
#define R_ARM_THM_PC11        102 //Thumb B S ¨C P + A
#define R_ARM_THM_PC9         103 //Thumb B<cond> S ¨C P + A
#define R_ARM_RXPC25          249 //ARM BLX (?S ¨C ?P) + A For calls between program segments.
#define R_ARM_RSBREL32        250 //Word (?S ¨C ?SB) + A For an offset from SB, the static base.
#define R_ARM_THM_RPC22       251 //Thumb BL/BLX pair (?S ¨C ?P) + A For calls between program segments.
#define R_ARM_RREL32          252 //Word (?S ¨C ?P) + A For on offset between two segments.
#define R_ARM_RABS32          253 //Word ?S + A For the address of a location in the target segment.
#define R_ARM_RPC24           254 //ARM B/BL (?S ¨C ?P) + A For calls between program segments.
#define R_ARM_RBASE           255 //None None¡ªIdentifies the segment being relocated by the following relocation directives.

typedef long TElfEntry(char *, void *,void *,void *);

#ifndef wintel
__arm zeromem_a(void *d, int l){zeromem(d,l);}
#else
void zeromem_a(void *d, int l){memset(d,0, l);}
#endif

long elfload(char *filename, void *param1, void *param2, void *param3){
  Elf32_Ehdr ehdr;				                        //§Ù§Ñ§Ô§à§Ý§à§Ó§à§Ü §Ö§Ý§î§æ§Ñ
  Elf32_Phdr phdrs[MAX_PHNUM];	                                        //§Ù§Ñ§Ô§à§Ý§à§Ó§Ü§Ú §á§â§à§Ô§â§Ñ§Þ
  Elf32_Word dyn[DT_BIND_NOW+1];	                                        //§ä§ï§Ô§Ú §Õ§Ú§ß§Ñ§Þ§Ú§é§Ö§ã§Ü§à§Û §ã§Ö§Ü§è§Ú§Ú
  char *reloc, *base;
  unsigned long minadr=(unsigned long)-1, maxadr=0;//, maxadrsize;
  int n,m;
  
  
  zeromem_a(dyn, sizeof(dyn));
  
  /////////////////////////////////////////
  //WINTEL
#ifdef wintel
  FILE *fin=NULL;
  if ((fin=fopen(filename,"rb"))==NULL) return -1;			//§ß§Ö §à§ä§Ü§â§í§Ó§Ñ§Ö§ä§ã§ñ §Ö§Ý§î§æ
  if (fread(&ehdr,sizeof(Elf32_Ehdr),1,fin)!=1) return -2;	        //§ß§Ö §é§Ú§ä§Ñ§Ö§ä§ã§ñ §Ö§Ý§î§æ
#endif
  
  //ARM
#ifndef wintel
  int fin;
  unsigned int iError, iError2;
  if ((fin=fopen(filename, A_ReadOnly+A_BIN, P_READ, &iError))<0) return -1;	//§ß§Ö §à§ä§Ü§â§í§Ó§Ñ§Ö§ä§ã§ñ §Ö§Ý§î§æ
  if (fread(fin, &ehdr, sizeof(Elf32_Ehdr), &iError)!=sizeof(Elf32_Ehdr))	//§ß§Ö §é§Ú§ä§Ñ§Ö§ä§ã§ñ §Ö§Ý§î§æ
  {fclose(fin, &iError); return -2;}
#endif
  /////////////////////////////////////////
  
  if (*((long *)ehdr.e_ident)!=0x464C457F){                               //§Õ§Ñ §Ú §ß§Ö §Ö§Ý§î§æ §ï§ä§à §Ó§à§Ó§ã§Ö
#ifndef wintel
    fclose(fin, &iError);
#endif
    return -3;
  }
  
#ifdef wintel
  cout << "Elf header"<<endl;
  cout << "ehdr.e_entry:"<<ehdr.e_entry<<endl;
  cout << "ehdr.e_phoff:"<<ehdr.e_phoff<<endl;
#endif
  
  //§á§â§à§é§Ú§ä§Ñ§Ö§Þ §Ó§ã§Ö §á§â§à§Ô§â§Ñ§Þ§ß§í§Ö §ã§Ö§Ô§Þ§Ö§ß§ä§í §Ú §Ó§í§é§Ú§ã§Ý§Ú§Þ §ß§Ö§à§Ò§ç§à§Õ§Ú§Þ§å§ð §à§Ò§Ý§Ñ§ã§ä§î §Ó §â§Ñ§Þ§Ö
  if (ehdr.e_phnum>MAX_PHNUM) return -9;					//§ã§Ý§Ú§ê§Ü§à§Þ §Þ§ß§à§Ô§à §á§â§à§Ô§â§Ñ§Þ§ß§í§ç §ã§Ö§Ô§Þ§Ö§ß§ä§à§Ó
  for(n=0;n<ehdr.e_phnum;n++){
    ////////////////////////////////////////////////////
    //WINTEL
#ifdef wintel
    if (fseek(fin,ehdr.e_phoff+n*ehdr.e_phentsize,SEEK_SET)!=0) return -4;	//§ß§Ö §ã§Ú§Ü§Ñ§Ö§ä§ã§ñ §á§â§à§Ô§â§Ñ§Þ§ß§í§Û §Ù§Ñ§Ô§à§Ý§à§Ó§à§Ü
    if (fread(&(phdrs[n]),sizeof(Elf32_Phdr),1,fin)!=1) return -5;		//§ß§Ö §é§Ú§ä§Ñ§Ö§ä§ã§ñ §á§â§à§Ô§â§Ñ§Þ§ß§í§Û §Ù§Ñ§Ô§à§Ý§à§Ó§à§Ü
#endif
    
    //ARM
#ifndef wintel
    if (lseek(fin, ehdr.e_phoff+n*ehdr.e_phentsize, S_SET, &iError, &iError2)!=ehdr.e_phoff+n*ehdr.e_phentsize)
    {fclose(fin, &iError); return -4;}				//§ß§Ö §ã§Ú§Ü§Ñ§Ö§ä§ã§ñ §á§â§à§Ô§â§Ñ§Þ§ß§í§Û §Ù§Ñ§Ô§à§Ý§à§Ó§à§Ü
    if (fread(fin, &phdrs[n], sizeof(Elf32_Phdr), &iError)!=sizeof(Elf32_Phdr))
    {fclose(fin, &iError); return -5;}				//§ß§Ö §é§Ú§ä§Ñ§Ö§ä§ã§ñ §á§â§à§Ô§â§Ñ§Þ§ß§í§Û §Ù§Ñ§Ô§à§Ý§à§Ó§à§Ü
#endif
    /////////////////////////////////////////////////////
    if (phdrs[n].p_type==PT_LOAD) {
      if (minadr>phdrs[n].p_vaddr) minadr=phdrs[n].p_vaddr;
      if (maxadr<(phdrs[n].p_vaddr+phdrs[n].p_memsz))
      {
	maxadr=phdrs[n].p_vaddr+phdrs[n].p_memsz;
      }
    }
#ifdef wintel
    cout << "minadr:"<<hex<<minadr<<endl;
    cout << "maxadr:"<<hex<<maxadr<<endl;
    cout << "Program header"<<endl;
    cout << "phdr.p_type:"<<phdrs[n].p_type<<endl;
    cout << "phdr.p_offset:"<<phdrs[n].p_offset<<endl;
    cout << "phdr.p_vaddr:"<<phdrs[n].p_vaddr<<endl;
    cout << "phdr.p_paddr:"<<phdrs[n].p_paddr<<endl;
    cout << "phdr.p_filesz:"<<phdrs[n].p_filesz<<endl;
    cout << "phdr.p_memsz:"<<phdrs[n].p_memsz<<endl;
#endif
  }
  
  //§Ó§í§Õ§Ö§Ý§Ú§Þ §ï§ä§å §à§Ò§Ý§Ñ§ã§ä§î §Ú §à§é§Ú§ã§ä§Ú§Þ §Ö§Ö
  if ((base=(char *)malloc(maxadr-minadr))==0){		//§ß§Ö §Ó§í§Õ§Ö§Ý§ñ§Ö§ä§î§ã§ñ §á§Ñ§Þ§ñ§ä§î §á§à§Õ §Ö§Ý§î§æ
#ifndef wintel
    fclose(fin, &iError);
#endif
    return -14;
  }
  //  t_zeromem(base,maxadr-minadr);
  zeromem_a(base,maxadr-minadr);
  for(n=0;n<ehdr.e_phnum;n++){ //  §à§Ò§ç§à§Õ §Ó§ã§Ö§ç §ã§Ö§Ô§Þ§Ö§ß§ä§à§Ó
    ////////////////////////////////////////////////////////////////////
    //WINTEL
#ifdef wintel
    if (fseek(fin,phdrs[n].p_offset,SEEK_SET)!=0) return -6;	//§ß§Ö §ã§Ú§Ü§Ñ§Ö§ä§ã§ñ §Õ§Ú§ß§Ñ§Þ§Ú§é§Ö§ã§Ü§Ú§Û §ã§Ö§Ô§Þ§Ö§ß§ä
#endif
    
    //ARM
#ifndef wintel
    if (lseek(fin, phdrs[n].p_offset, S_SET, &iError, &iError)!=phdrs[n].p_offset)
    {fclose(fin, &iError); mfree(base); return -6;}		//§ß§Ö §ã§Ú§Ü§Ñ§Ö§ä§ã§ñ §Õ§Ú§ß§Ñ§Þ§Ú§é§Ö§ã§Ü§Ú§Û §ã§Ö§Ô§Þ§Ö§ß§ä
#endif
    /////////////////////////////////////////////////////////////////////
    switch (phdrs[n].p_type){
    case PT_LOAD:
      //§Ù§Ñ§Ô§â§å§Ù§Ú§Þ §á§â§à§Ô§â§Ñ§Þ§ß§í§Ö §ã§Ö§Ô§Þ§Ö§ß§ä§í §ã §â§Ñ§Ù§Þ§Ö§â§à§Þ §Ò§à§Ý§î§ê§Ö 0
      if (phdrs[n].p_filesz!=0) {
	/////////////////////////////////////////////////////////////////////
	//WINTEL
#ifdef wintel
	if (fread((void *)&base[phdrs[n].p_vaddr-minadr],phdrs[n].p_filesz,1,fin)!=1) return -11;	//§ß§Ö §é§Ú§ä§Ñ§Ö§ä§ã§ñ §á§â§à§Ô§â§Ñ§Þ§ß§í§Û §ã§Ö§Ô§Þ§Ö§ß§ä
#endif
	
	//ARM
#ifndef wintel
	if (fread(fin, &base[phdrs[n].p_vaddr-minadr], phdrs[n].p_filesz, &iError)!= phdrs[n].p_filesz)
	{fclose(fin, &iError); mfree(base); return -11;}//§ß§Ö §é§Ú§ä§Ñ§Ö§ä§ã§ñ §á§â§à§Ô§â§Ñ§Þ§ß§í§Û §ã§Ö§Ô§Þ§Ö§ß§ä
#endif
	///////////////////////////////////////////////////////////////////////
      }
      break;
    case PT_DYNAMIC:
      //§á§â§à§é§ä§Ö§Þ §Õ§Ú§ß§Ñ§Þ§Ú§é§Ö§ã§Ü§å§ð §ã§Ö§Ü§è§Ú§ð
      if ((reloc=(char *)malloc(phdrs[n].p_filesz))==0) {//§ß§Ö §Ó§í§Õ§Ö§Ý§ñ§Ö§ä§ã§ñ §â§Ñ§Þ§Ñ §á§à§Õ §Õ§Ú§ß§Ñ§Þ§Ú§é§Ö§ã§Ü§Ú§Û §ã§Ö§Ô§Þ§Ö§ß§ä
#ifndef wintel
	fclose(fin, &iError);
#endif
	mfree(base);
	return -7;
      }
      ///////////////////////////////////////////////////////////////////////
      //WINTEL
#ifdef wintel
      cout << "dyn seg: off="<<hex<<phdrs[n].p_offset<<", sz="<<phdrs[n].p_filesz<<endl;
      if (fread(reloc,phdrs[n].p_filesz,1,fin)!=1) {mfree(reloc); return -8;} //§ß§Ö §é§Ú§ä§Ñ§Ö§ä§ã§ñ §Õ§Ú§ß§Ñ§Þ§Ú§é§Ö§ã§Ü§Ú§Û §ã§Ö§Ô§Þ§Ö§ß§ä
#endif
      
      //ARM
#ifndef wintel
      if (fread(fin, reloc, phdrs[n].p_filesz, &iError)!=phdrs[n].p_filesz)
      {fclose(fin, &iError); mfree(reloc); mfree (base); return -8;}	//§ß§Ö §é§Ú§ä§Ñ§Ö§ä§ã§ñ §Õ§Ú§ß§Ñ§Þ§Ú§é§Ö§ã§Ü§Ú§Û §ã§Ö§Ô§Þ§Ö§ß§ä
#endif
      ////////////////////////////////////////////////////////////////////////
      //				memset(dyn,0, sizeof(dyn));
      //§Ó§í§ä§Ñ§ë§Ú§Þ §Ó§ã§Ö §ä§ï§Ô§Ú §Ú§Ù §Õ§Ú§ß§Ñ§Þ§Ú§é§Ö§ã§Ü§à§Û §ã§Ö§Ü§è§Ú§Ú
      m=0;
      while (((Elf32_Dyn *)reloc)[m].d_tag!=DT_NULL){
	if (((Elf32_Dyn *)reloc)[m].d_tag<=DT_BIND_NOW) {
#ifdef wintel
          cout<<"d_tag="<<((Elf32_Dyn *)reloc)[m].d_tag;
          cout<<" d_val="<<((Elf32_Dyn *)reloc)[m].d_val<<endl;
#endif
	  dyn[((Elf32_Dyn *)reloc)[m].d_tag]=((Elf32_Dyn *)reloc)[m].d_val;
	}
	m++;
      }
#ifdef wintel
      cout << "Dynamic section" << endl;
      for (m = 0; m <= DT_BIND_NOW; m++) {
	cout << dec << m <<" = "<< hex << dyn[m]<<endl;
      }
      cout<<"dyn[DT_REL]="<<dyn[DT_REL]<<", dyn[DT_RELA]="<<dyn[DT_RELA]<<endl;
      cout<<"dyn[DT_RELSZ]="<<dyn[DT_RELSZ]<<", dyn[DT_RELASZ]="<<dyn[DT_RELASZ]<<endl;
#endif
      
      m=0;
      //§Ó§í§á§à§Ý§ß§Ú§Þ §â§Ö§Ý§à§Ü§Ñ§è§Ú§ð REL
      if (dyn[DT_RELSZ]!=0) {
	while (m*sizeof(Elf32_Rel)<dyn[DT_RELSZ]){
#ifdef wintel
	  cout<<"rel: of="<<hex<<((Elf32_Rel *)(reloc+dyn[DT_REL]-phdrs[n].p_vaddr))[m].r_offset
	    <<" , sym_idx="<<ELF32_R_SYM(((Elf32_Rel *)(reloc+dyn[DT_REL]-phdrs[n].p_vaddr))[m].r_info)
              <<" , rel_type="<<dec<<(int) ELF32_R_TYPE(((Elf32_Rel *)(reloc+dyn[DT_REL]-phdrs[n].p_vaddr))[m].r_info)<<endl;
#endif
          Elf32_Word ri=ELF32_R_TYPE(((Elf32_Rel *)(reloc+dyn[DT_REL]-phdrs[n].p_vaddr))[m].r_info);
          if (ri!=R_ARM_RBASE)
          {
            if (ri==R_ARM_RABS32)
            {
              *((long*)(base+((Elf32_Rel *)(reloc+dyn[DT_REL]-phdrs[n].p_vaddr))[m].r_offset))+=(long)base-minadr;
            }
            else
              switch(ri){
                
              case R_ARM_NONE: break; // §á§å§ã§ä§à§Û §â§Ö§Ý§à§Ü§Ö§Û§ê§Ö§ß
              
              case R_ARM_ABS32:
#ifdef wintel
                cout << "base="<<hex<<(long)base<< endl;
                cout << "of="<<hex<<((Elf32_Rel *)(reloc+dyn[DT_REL]-phdrs[n].p_vaddr))[m].r_offset-minadr<<endl;
#endif
                *((long*)(base+((Elf32_Rel *)(reloc+dyn[DT_REL]-phdrs[n].p_vaddr))[m].r_offset-minadr))+=(long)base;
                break;
                
              case R_ARM_RELATIVE: // §Ó§à§à§Ò§ë§Ö §Ô§à§Ó§à§â§ñ §ß§Ö minadr §Ñ §ß§Ñ§é§Ñ§Ý§à §ã§Ö§Ô§Þ§Ö§ß§ä§Ñ §ã§à§Õ§Ö§â§Ø§Ñ§ë§Ö§Ô§à §ã§Ú§Þ§Ó§à§Ý
                *((long*)(base+((Elf32_Rel *)(reloc+dyn[DT_REL]-phdrs[n].p_vaddr))[m].r_offset-minadr))+=(long)base-minadr;
                break; // ignore
                
                //	  case R_ARM_RABS32:
                //	    *((long*)(base+((Elf32_Rel *)(reloc+dyn[DT_REL]-phdrs[n].p_vaddr))[m].r_offset))+=(long)base-minadr;
                //            break;
                
                //              case R_ARM_RBASE: break;
              default: 	//§ß§Ö§Ú§Ù§Ó§Ö§ã§ä§ß§í§Û §ä§Ú§á §â§Ö§Ý§à§Ü§Ñ§è§Ú§Ú
#ifdef wintel
                cout << "Invalid reloc type: " <<dec<<(unsigned)ELF32_R_TYPE(((Elf32_Rel *)(reloc+dyn[DT_REL]-phdrs[n].p_vaddr))[m].r_info) << endl;
#else
                fclose(fin, &iError);
#endif
                mfree(base);
                mfree(reloc);
                return -13;
              }
          }
	  m++;
	}
      }
#ifdef wintel
      else
      {
        cout << "No relocation information dyn[DT_RELSZ]=0" << endl;
      }
#endif
      mfree(reloc);
      break;
    default:	//§ß§Ö§Ú§Ù§Ó§Ö§ã§ä§ß§í§Û §ä§Ú§á §á§â§à§Ô§â§Ñ§Þ§ß§à§Ô§à §ã§Ö§Ô§Þ§Ö§ß§ä§Ñ
#ifndef wintel
      fclose(fin, &iError);
#endif
      mfree(base);
      return -12;
    }
  }
#ifndef wintel
  fclose(fin, &iError);
  {
    extern __arm void ExecuteIMB(void);
    ExecuteIMB();	
  }
  ((TElfEntry *)(base+ehdr.e_entry-minadr))(filename,param1,param2,param3);
  //	mfree(base);
  return 0;
#endif
#ifdef wintel
  FILE fout;
  char foutbuff[11];
  sprintf(foutbuff,"0x%08x",base);
  if ((fin=fopen(foutbuff,"wb"))==NULL) return -1000;
  if (fwrite(base,maxadr-minadr,1,fin)!=1) return -1001; // vit
  return 0;
#endif
}

#ifdef wintel
int main(int argc, char* argv[]){
  if(argc<2)
  {
    cout << "no .elf specified"<<endl;
    return -1;
  }
  
  cout << elfload(argv[1],0,0,0);
  return 1;
}
#endif

#ifndef wintel
int elfloader_onload(WSHDR *filename, WSHDR *ext, void *param){
  char fn[128];
  ws_2str(filename,fn,126);
  if (elfload(fn,param,0,0)) return 0; else return 1;
}

//=======================================================================
//
//=======================================================================
extern void(*OldOnClose)(void *);
extern void(*OldOnCreate)(void *);
#ifdef NEWSGOLD
extern void(*OldShowMsg)(int, int);
#else
extern void(*OldTxtOpen)(WSHDR*, WSHDR*);
#endif

extern unsigned int DEFAULT_DISK_N;

//-----------------------------------------------------------------------

#ifdef NEWSGOLD
//#define HELPER_CEPID 0x4339
#define HELPER_CEPID 0x440A
#else
//#define HELPER_CEPID 0x4331
#define HELPER_CEPID 0x4407

#endif
#define MSG_HELPER_RUN 0x0001

__arm void proc_HELPER(void)
{
  GBS_MSG msg;
  if (GBS_RecActDstMessage(&msg))
  {
    if (msg.msg==MSG_HELPER_RUN)
    {
      if (msg.data0)
      {
	((void (*)(int, void *))(msg.data0))(msg.submess,msg.data1);
      }
    }
    else
    {
      GBS_SendMessage(MMI_CEPID,MSG_HELPER_TRANSLATOR,msg.pid_from,msg.msg,msg.submess);
    }
  }
}

__arm void CreateHELPER_PROC(void)
{
  static const char name[]="HELPER";
  CreateGBSproc(HELPER_CEPID, name, proc_HELPER, 0x80, 0);
}

__arm void REDRAW_impl(void)
{
  LockSched();
#ifdef NEWSGOLD
  PendedRedrawGUI();
#else
  PendedRedrawGUI();
  GBS_SendMessage(MMI_CEPID,0x90);
#endif
  UnlockSched();
}

__arm void SUBPROC_impl(void *f, int p2, void *p1)
{
  GBS_SendMessage(HELPER_CEPID,MSG_HELPER_RUN,p2,f,p1);
}

__thumb void SEQKILLER_impl(void *data, void(*next_in_seq)(void *), void *data_to_kill)
{
  next_in_seq(data);
  mfree(data_to_kill);
}

__arm void MyIDLECSMonClose(void *data)
{
  extern BXR1(void *, void (*)(void *));
  KillGBSproc(HELPER_CEPID);
  BXR1(data,OldOnClose);
  //  OldOnClose(data);
  //  asm("NOP\n");
}


__arm void LoadDaemons(void)
{
  DIR_ENTRY de;
  unsigned int err;
  unsigned int pathlen;
  char name[256];
  strcpy(name+1,":\\ZBin\\Daemons\\");
  name[0]=DEFAULT_DISK_N+'0';
  pathlen=strlen(name);
  strcat(name,"*.elf");
  if (FindFirstFile(&de,name,&err))
  {
    do
    {
      //strcpy(name,path);
      name[pathlen]=0;
      strcat(name,de.file_name);
      elfload(name,0,0,0);
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
}


__no_init void *(*pLIB_TOP)[];
extern void *Library[];

int get_file_size(const char * fname)
{
  FSTATS fs;
  unsigned int err;
  if (GetFileStats(fname,&fs,&err)==-1) return (-1);
  else return (fs.size);
}

__arm void LoadLibrary(void)
{
  void *(*lt)[]=pLIB_TOP;
#define LIB_EMPTY ((void *)-1L)
  unsigned int ul;
  int sz;
  int f;
  char fn[64];
  strcpy(fn+1,":\\Zbin\\swi.blib");
  fn[0]=DEFAULT_DISK_N+'0';
  if (lt)
  {
    pLIB_TOP=NULL;
    mfree(lt);
    lt=NULL;
  }
  if ((sz=get_file_size(fn))==-1) return;
  if (sz!=16384)
  {
    ShowMSG(1,(int)"Illegal library size!");
    return;
  }
  f=fopen(fn,A_ReadOnly+A_BIN, P_READ, &ul);
  if (f==-1) return;
  lt=malloc(16384);
  if (fread(f,lt,sz,&ul)!=sz)
  {
    fclose(f,&ul);
    ShowMSG(1,(int)"Can't read library!");
  LERR:
    mfree(lt);
    return;
  }
  fclose(f,&ul);
  f=0;
  do
  {
    if (((*lt)[f]!=LIB_EMPTY)&&(Library[f]!=LIB_EMPTY))
    {
      if ((*lt)[f]!=Library[f])
      {
	char s[50];
	sprintf(s,"Function %d conflict!",f);
	ShowMSG(1,(int)s);
	goto LERR;
      }
    }
    if ((*lt)[f]==LIB_EMPTY)
    {
      (*lt)[f]=Library[f];
    }
    f++;
  }
  while(f<4096);
  pLIB_TOP=lt;
#undef LIB_EMPTY
}
extern void InitPngBitMap(void);

__no_init char smallicons_str[32];
__no_init char bigicons_str[32];

__arm void MyIDLECSMonCreate(void *data)
{
  static const int smallicons[2]={(int)smallicons_str,0};
  static const int bigicons[2]={(int)bigicons_str,0};
  
#ifdef NEWSGOLD
  static const REGEXPLEXT elf_reg=
  {
    "elf",
    0x55,
    0xFF,
    8, //§¬§Ñ§ä§Ñ§Ý§à§Ô Misc
    MENU_FLAG2,
    smallicons,
    bigicons,
    (int)"Open",    //LGP "§°§ä§Ü§â§í§ä§î"
    (int)"AltOpen", //LGP "§°§á§è§Ú§Ú"
    LGP_DOIT_PIC,
    (void *)elfloader_onload,
    0
  };
#else
  static const REGEXPLEXT elf_reg=
  {
    "elf",
    0x55,
    0xFF,
    7,
    MENU_FLAG2,
    smallicons,
    bigicons,
    (void *)elfloader_onload,
    0
  };
#endif
  CreateHELPER_PROC();
  InitConfig();
  LoadLibrary();
  InitPngBitMap();
  strcpy(smallicons_str+1,":\\ZBin\\img\\elf_small.png");
  strcpy(bigicons_str+1,":\\ZBin\\img\\elf_big.png");
  smallicons_str[0]=bigicons_str[0]=DEFAULT_DISK_N+'0';
  RegExplorerExt(&elf_reg);
//#define SAFE_MODE
#ifdef SAFE_MODE
	if(*RamPressedKey()!='*')
		SUBPROC((void *)LoadDaemons);
#else
  SUBPROC((void *)LoadDaemons);
#endif
  extern BXR1(void *, void (*)(void *));
  BXR1(data,OldOnCreate);
  //  OldOnCreate(data);
  //  asm("NOP\n");
}

/*
unsigned int char8to16(int c)
{
  if (c==0xA8) c=0x401;
  if (c==0xAA) c=0x404;
  if (c==0xAF) c=0x407;
  if (c==0xB8) c=0x451;
  if (c==0xBA) c=0x454;
  if (c==0xBF) c=0x457;
  if (c==0xB2) c=0x406;
  if (c==0xB3) c=0x456;
  if ((c>=0xC0)&&(c<0x100)) c+=0x350;
  return(c);
}

void ascii2ws(char *s, WSHDR *ws)
{
  int c;
  while((c=*s++))
  {
    wsAppendChar(ws,char8to16(c));
  }
}*/

#ifdef NEWSGOLD
__arm void ESI(WSHDR *ws, int dummy, char *s)
#else
__arm void ESI(char *s, WSHDR *ws)
#endif
{
  if (((unsigned int)s>>28)==0xA) //§´§à§Ý§î§Ü§à §ã§ä§â§à§Ü§Ú §Ú§Ù §à§Ò§Ý§Ñ§ã§ä§Ú RAM/FLASH
  {
//#ifndef ZH_CN-UTF8
//#ifdef ANSI_STD
    gb2ws(ws, s, strlen(s));
//#else
//    CutWSTR(ws,0); 
//    ascii2ws(s,ws);
//#endif
//#else
//    utf8_2ws(ws, s, strlen(s));
//#endif
  }
  else
  {
    wsprintf(ws,"|%d|",s);
  }
}

/*int toupper(int c)
{
if ((c>='a')&&(c<='z')) c+='A'-'a';
return(c);
}*/

//static const char extfile[]=DEFAULT_DISK ":\\ZBin\\etc\\extension.cfg";

__arm void DoUnknownFileType(WSHDR *filename)
{
  WSHDR *wsmime=AllocWS(15);
  wsprintf(wsmime,"txt");
  ExecuteFile(filename,wsmime,0);
  FreeWS(wsmime);
}

#ifdef NEWSGOLD 
__no_init int *EXT2_AREA;
#ifdef ELKA
__no_init int EXT2_CNT @ "REGEXPL_CNT";
#endif

#else
__no_init TREGEXPLEXT *EXT2_AREA;
__no_init int EXT2_CNT @ "REGEXPL_CNT";
#endif

#ifdef NEWSGOLD 
#ifdef ELKA
#else
__arm int *GET_EXT2_TABLE(void)
{
  int *p=EXT2_AREA;
  if (p)
  {
    return(p+1);
  }
  p=malloc(4);
  *p=0;
  return ((EXT2_AREA=p)+1);
}
#endif
#endif  

#ifdef NEWSGOLD 
#ifdef ELKA
__arm int *EXT2_REALLOC(void)
{
  int size;
  size=sizeof(REGEXPLEXT);
  int *p;
  int *p2;
  int n;
  LockSched();
  n=EXT2_CNT;
  p=EXT2_AREA;
  p2=malloc((n+1)*size);
  if (p) 
  {    
    memcpy(p2,p,n*size);
    mfree(p);
  }
  EXT2_CNT=n+1;
  EXT2_AREA=p2;
  p2+=(n*(size/sizeof(int)));
  UnlockSched();
  return (p2);
}
#else
__arm int *EXT2_REALLOC(void)
{
  int size;
  size=sizeof(REGEXPLEXT);
  int *p;
  int *p2;
  int n;
  LockSched();
  n=*(p=EXT2_AREA);
  p2=malloc((n+1)*size+4);
  memcpy(p2,p,n*size+4);
  *p2=n+1;
  mfree(p);
  EXT2_AREA=p2;
  p2+=(n*(size/sizeof(int)))+1;
  UnlockSched();
  return (p2);
}
#endif
#else
__arm TREGEXPLEXT *EXT2_REALLOC(void)
{
  TREGEXPLEXT *p,*p2;
  int n;
  LockSched();
  n=EXT2_CNT;
  p=EXT2_AREA;
  p2=malloc((n+1)*sizeof(TREGEXPLEXT));
  zeromem(p2,(n+1)*sizeof(TREGEXPLEXT));
  if (p) 
  {    
    memcpy(p2,p,n*sizeof(TREGEXPLEXT));
    mfree(p);
  }
  EXT2_CNT=n+1;
  EXT2_AREA=p2;
  UnlockSched();
  return (p2+n);
}


#endif



#ifdef NEWSGOLD
__thumb MyShowMSG(int p1, int p2)
{
#ifdef ELKA
  if (p2!=0x1DD1)
#else
    if (p2!=(0x1DCC+5))
#endif    
    {
      OldShowMsg(p1,p2);
      return;
    }
  asm("MOVS R0,R6\n");
  DoUnknownFileType((WSHDR *)p1);
}
#else

__arm void PropertyPatch(WSHDR *unk_foldername, WSHDR *unk_filename)
{
  WSHDR *ws;
  ws=AllocWS(255);
  wstrcpy(ws,unk_foldername);
  wsAppendChar(ws,'\\');
  wstrcat (ws,unk_filename);
  DoUnknownFileType(ws);
  FreeWS(ws);
}

#endif

__arm void FUNC_ABORT(int f)
{
  char s[32];
  extern void StoreErrInfoAndAbort(int code,const char *module_name,int type,int unk3);
  extern void StoreErrString(const char *);
  sprintf(s,"%d(%03X)",f,f);
  StoreErrString(s);
  loopback2();
  StoreErrInfoAndAbort(0xFFFF,"\1\1No function in lib\xA1",2,2);
}

//§±§Ñ§ä§é§Ú
#pragma diag_suppress=Pe177
__root static const int NEW_ONCREATE @ "PATCH_ONCREATE" = (int)MyIDLECSMonCreate;

__root static const int NEW_ONCLOSE @ "PATCH_ONCLOSE" = (int)MyIDLECSMonClose;

#ifdef NEWSGOLD
__root static const int NEW_SHOWMSG @ "PATCH_SHOWMSG_BLF" = (int)MyShowMSG;
#endif

__root static const int SWILIB_FUNC171 @ "SWILIB_FUNC171" = (int)SUBPROC_impl;

__root static const int SWILIB_FUNC172 @ "SWILIB_FUNC172" = (int)REDRAW_impl;

__root static const int SWILIB_FUNC19C @ "SWILIB_FUNC19C" = (int)SEQKILLER_impl;
#pragma diag_default=Pe177
#endif
