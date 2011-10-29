#include <stdio.h>
#include <windows.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#define PATHSLASH   '\\'
#define make_dir(A) mkdir(A);

#define __int8 char
typedef unsigned char _BYTE;
typedef unsigned short _WORD;
typedef unsigned int _DWORD;

char *Seed="\x20\0\0\0WgQgJ3vyYvAAkHHhFdueKh2ssZli8Ko4";       // beta
char *SeedPtr=0;

static int Keys[3];
static int Keys1[3];

int FileSize=0;
void* Base=0;

void *ReadPtr=0;

int NumFiles=0;
int IndexSize=0;
int IndexOffs=0;

static const unsigned int   dword_1AFDA80[256] = {
    0x00000000, 0x77073096, 0xee0e612c, 0x990951ba,
    0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
    0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
    0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
    0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de,
    0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
    0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,
    0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
    0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
    0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
    0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940,
    0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
    0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116,
    0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
    0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
    0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
    0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a,
    0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
    0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818,
    0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
    0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
    0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
    0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c,
    0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
    0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2,
    0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
    0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
    0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
    0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086,
    0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
    0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4,
    0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,
    0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
    0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
    0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8,
    0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
    0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe,
    0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
    0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
    0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
    0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252,
    0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
    0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60,
    0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
    0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
    0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
    0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04,
    0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
    0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a,
    0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
    0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
    0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
    0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e,
    0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
    0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c,
    0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
    0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
    0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
    0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0,
    0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
    0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6,
    0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
    0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
    0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

int CryptCRC_(int *Keys, char param3)
{
  int result; // eax@1
  int *v4; // ST00_4@1

  v4 = Keys;
  *Keys = dword_1AFDA80[(unsigned __int8)(*Keys ^ param3)] ^ ((unsigned int)*Keys >> 8);
  v4[1] += *v4 & 0xFF;
  v4[1] = 290333451 * v4[1] + 1;
  result = (int)Keys;
  Keys[2] = dword_1AFDA80[(unsigned __int8)(Keys[2] ^ ((unsigned int)Keys[1] >> 24))] ^ ((unsigned int)Keys[2] >> 8);
  return result;
}

int InitCrypt(int *Keys, int **Par2, int FileSize)
{
  int result; // eax@5
  int j; // [sp+8h] [bp-38h]@11
  int *v5; // [sp+Ch] [bp-34h]@11
  int v6; // [sp+10h] [bp-30h]@11
  int i; // [sp+1Ch] [bp-24h]@7
  int *v8; // [sp+20h] [bp-20h]@7
  int v9; // [sp+24h] [bp-1Ch]@7
  int k; // [sp+30h] [bp-10h]@2
  int *v11; // [sp+34h] [bp-Ch]@2
  int v12; // [sp+38h] [bp-8h]@2

  if ( FileSize % 3u )
  {
    if ( FileSize % 3u == 1 )
    {
      v9 = *(*Par2 - 1);
      v8 = *Par2;
      *Keys = 305419896;
      Keys[1] = FileSize;
      Keys[2] = 878082192;
      for ( i = 0; i < v9; ++i )
        CryptCRC_(Keys, *((_BYTE *)v8 + i));
      result = (int)Keys;
    }
    else
    {
      v6 = *(*Par2 - 1);
      v5 = *Par2;
      *Keys = 305419896;
      Keys[1] = 591751049;
      Keys[2] = FileSize;
      for ( j = 0; j < v6; ++j )
        CryptCRC_(Keys, *((_BYTE *)v5 + j));
      result = (int)Keys;
    }
  }
  else
  {
    v12 = *(*Par2 - 1);
    v11 = *Par2;
    *Keys = FileSize;
    Keys[1] = 591751049;
    Keys[2] = 878082192;
    for ( k = 0; k < v12; ++k )
      CryptCRC_(Keys, *((_BYTE *)v11 + k));
    result = (int)Keys;
  }
  return result;
}

int DeCrypt(int *Keys, char *pBuffer, int Count)
{
  int result; // eax@3
  int v4; // edx@3
  char v5; // ST17_1@3
  int *v6; // [sp+0h] [bp-18h]@1
  int v7; // [sp+14h] [bp-4h]@1

  v6 = Keys;
  v7 = 0;
  while ( v7 < Count )
  {
    v4 = (unsigned __int8)((unsigned __int16)((*((_WORD *)v6 + 4) | 2) * ((*((_WORD *)v6 + 4) | 2) ^ 1)) >> 8);
    v5 = v4 ^ *(_BYTE *)pBuffer;
    CryptCRC_(v6, *(_BYTE *)pBuffer);
    *(_BYTE *)pBuffer = v5;
    result = v7++ + 1;
    pBuffer = (char *)((char *)pBuffer + 1);
  }
  return result;
}

int CalcNameHash(char *Name)
{
  char v2; // [sp+3h] [bp-15h]@7
  char v3; // [sp+4h] [bp-14h]@4
  char v4; // [sp+5h] [bp-13h]@5
  int i; // [sp+10h] [bp-8h]@1
  int v6; // [sp+14h] [bp-4h]@1

  v6 = 0;
  for ( i = 0; i < *((_DWORD *)Name + 1); ++i )
  {
    if ( *(_BYTE *)(*(_DWORD *)Name + i) == 92 )
    {
      v3 = 47;
    }
    else
    {
      v4 = *(_BYTE *)(*(_DWORD *)Name + i);
      if ( v4 < 'A' || v4 > 'Z' )
        v2 = *(_BYTE *)(*(_DWORD *)Name + i);
      else
        v2 = v4 + ' ';
      v3 = v2;
    }
    v6 = v3 + 5 * v6;
  }
  return v6;
}


void DecryptBytes(int Len, void*Ptr)
{
	if(Len==0)
		return;
    memcpy(Ptr,ReadPtr,Len);
    DeCrypt(Keys,(char*)ReadPtr,Len);
    ReadPtr=Len+(char*)ReadPtr;
}

int DecryptDword()
{
    int Tmp=0;
    DecryptBytes(4,&Tmp);
    return Tmp;
}

int DecryptWord()
{
    int Tmp=0;
    DecryptBytes(2,&Tmp);
    return Tmp&65535;
}

char *create_dir(char *name) {
    char      *p,
            *l;

    for(p = name; (*p == '\\') || (*p == '/') || (*p == '.'); p++);
    name = p;

    for(;;) {
        if((p[0] && (p[1] == ':')) || ((p[0] == '.') && (p[1] == '.'))) p[0] = '_';

        l = strchr(p, '\\');
        if(!l) {
            l = strchr(p, '/');
            if(!l) break;
        }
        *l = 0;
        p = l + 1;
        make_dir(name);
        *l = PATHSLASH;
    }
    return(name);
}

int main(int argc, char*argv[])
{
    int Tmp,i, FNLen,FileSize,FileExpSize,FileOffs,Bad,CompressMethod,Extra,Comment;
    char Buff[4097];
    char *zfile,*file;
    void *OldReadPtr;
    HANDLE HF,HM;
    FILE *nul=fopen("nul","w");

    strcpy(Buff,argv[1]);
    strcat(Buff,".orc");
    printf("Copying '%s' to '%s'\n",argv[1],Buff);
    CopyFile(argv[1],Buff,FALSE);

    HF=CreateFile(Buff,GENERIC_READ|GENERIC_WRITE,
        FILE_SHARE_WRITE|FILE_SHARE_READ,0,OPEN_EXISTING,0,0);

    HM=CreateFileMapping(HF,0,PAGE_READWRITE,0,0,0);

    Base=MapViewOfFile(HM,FILE_MAP_WRITE,0,0,0);

    SeedPtr=Seed+4;

    if(!HF || !HM || !Base)
    {
        fprintf(nul,"Error\n");
        return;
    }

    FileSize=GetFileSize(HF,0);

    ReadPtr=((char*)Base)+FileSize-0x16;
    
    InitCrypt(Keys,(int**)&SeedPtr,FileSize-0x16);
    fprintf(nul,"Keys: %08x %08X %08X\n",Keys[0],Keys[1],Keys[2]);	// 05f0638b 92BB87AF BFE44C9E

    Tmp=DecryptDword();
    fprintf(nul,"Signature: %08X\n",Tmp);
    if(Tmp!=0x6054B50)
    {
	puts("Incorrect signature");
	return;
    }
    fprintf(nul,"%04X\n",DecryptWord());  	// always 0
    fprintf(nul,"%04X\n",DecryptWord());     // always 0
    NumFiles=DecryptWord();
    fprintf(nul,"Number of files: %04X\n",NumFiles); 	// number of files?
    fprintf(nul,"%04X\n",DecryptWord());                     // ==

    IndexSize=DecryptDword();
    fprintf(nul,"Index Size  	: %08X\n",IndexSize);
    IndexOffs=DecryptDword();
    fprintf(nul,"Index Offset: %08X\n",IndexOffs);

    fprintf(nul,"%04X\n",DecryptWord());     // always 0

    if(IndexSize+IndexOffs+0x16!=FileSize)
    {
    	puts("Error!");
	return;
    }

    ReadPtr=((char*)Base)+IndexOffs;
    InitCrypt(Keys,(int**)&SeedPtr,IndexOffs);

Loop:
	printf("\r%d  ",NumFiles);
    Tmp=DecryptDword();

    fprintf(nul,"Idx signature: %08X\n",Tmp);
    if(Tmp!=0x2014B50)
    {
		puts("Incorrect signature");
		return;
    }

    fprintf(nul,"%04X\n",DecryptWord());  
    fprintf(nul,"%04X\n",DecryptWord());   // <= 0x14
    fprintf(nul,"%04X\n",DecryptWord());   // AND 0x2061 == 0
    CompressMethod=DecryptWord();
    fprintf(nul,"%04X\n",CompressMethod);   // == 0 or == 8

    fprintf(nul,"%08X\n",DecryptDword());  // filedatetime
    fprintf(nul,"%08X\n",DecryptDword());  // crc
    FileSize=DecryptDword();
    fprintf(nul,"File size: %08X\n",FileSize);  
    FileExpSize=DecryptDword();
    fprintf(nul,"Exp size: %08X\n",FileExpSize);  

    FNLen=DecryptWord();
    fprintf(nul,"Filename Len: %04X\n",FNLen);   // ?
    Extra=DecryptWord();
    fprintf(nul,"%04X\n",Extra);  
    Comment=DecryptWord();
    fprintf(nul,"%04X\n",Comment);  
    fprintf(nul,"%04X\n",DecryptWord());  
    fprintf(nul,"%04X\n",DecryptWord());  

    fprintf(nul,"%08X\n",DecryptDword());  
    FileOffs=DecryptDword();
    fprintf(nul,"File Offset: %08X\n",FileOffs);  

    DecryptBytes(FNLen,Buff);
    Buff[FNLen]=0;
    fprintf(nul,"Filename: '%s'\n",Buff);

    DecryptBytes(Extra,Buff); 	
    DecryptBytes(Comment,Buff); 	
//    for(i=0; i<SkipLen+1 ; i++)		// в публике == 9!
//        fprintf(nul,"%08X\n",DecryptDword());  

do_dump:
	OldReadPtr=ReadPtr;
	memcpy(Keys1,Keys,3*4);

    ReadPtr=((char*)Base)+FileOffs;
    InitCrypt(Keys,(int**)&SeedPtr,FileOffs);

    Tmp=DecryptDword();
    fprintf(nul,"File signature: %08X\n",Tmp);
    if(Tmp!=0x4034B50)
    {
		puts("Incorrect signature");
		return;
    }

    fprintf(nul,"%04X\n",DecryptWord());   // <0x14
    fprintf(nul,"%04X\n",DecryptWord());   // AND 0x2061 == 0
    fprintf(nul,"%04X\n",DecryptWord());

    fprintf(nul,"%08X\n",DecryptDword());  
    fprintf(nul,"%08X\n",DecryptDword());  
    FileSize=DecryptDword();
    fprintf(nul,"File Compressed Size: %08X\n",FileSize);  
    FileExpSize=DecryptDword();
    fprintf(nul,"File Expanded Size: %08X\n",FileExpSize);  

    FNLen=DecryptWord();
    fprintf(nul,"%04X\n",FNLen);
    Extra=DecryptWord();
    fprintf(nul,"%04X\n",Extra);

    DecryptBytes(FNLen,Buff);	// Second copy of file name
    DecryptBytes(Extra,Buff);	// Second copy of file name

	ReadPtr=OldReadPtr;
	memcpy(Keys,Keys1,3*4);
	if(--NumFiles)
		goto Loop;
Exit:
	puts("\nDone!");
}

