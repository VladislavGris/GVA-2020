#pragma once
#define IN_MAX_LEN_TEXT 1024*1024
#define IN_CODE_ENDL '\n'

/*     0     1     2     3     4     5     6     7     8     9     A     B     C     D      E     F*/
#define IN_CODE_TABLE {\
/*0*/IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::T,IN::T,IN::F,IN::F,IN::F,IN::F,IN::F,\
/*1*/IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,\
/*2*/IN::T,IN::T,IN::T,IN::T,IN::F,IN::F,IN::F,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,\
/*3*/IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,\
/*4*/IN::F,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,\
/*5*/IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::F,IN::F,\
/*6*/IN::F,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,\
/*7*/IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::F,IN::F,\
																								\
/*8*/IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,\
/*9*/IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,\
/*A*/IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::T,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,\
/*B*/IN::F,IN::F,IN::F,IN::T,IN::F,IN::F,IN::F,IN::F,IN::T,IN::T,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,\
/*C*/IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,\
/*D*/IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,\
/*E*/IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,\
/*F*/IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,\
}

namespace In
{
	struct IN			
	{
		enum { T = 1024, F = 2048, I = 4096 };	
		int size;								
		int lines;								
		int ignor;								
		unsigned char* text;					
		int code[256];							
	};
	IN getin(wchar_t infile[]);					
}