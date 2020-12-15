#include "framework.h"
#include <cstring>
#include <stdio.h>
extern "C"
{
	int __stdcall strle(char* str)
	{
		return strlen(str);
	}
	int __stdcall compa(char* str1, char* str2)
	{
		int result = strcmp(str1, str2);
		if (result < 0)					// str1 < str2
			return 2;
		else if (result > 0)			// str1 > str2
			return 1;
		else
			return 0;					// str1 = str2
	}
	int __stdcall cpr(char* str)
	{
		puts(str);
		return 0;
	}
	int __stdcall ipr(int a)
	{
		printf("%d\n", a);
		return 0;
	}
	void hello()
	{
		puts("Hello\n");
	}
}
