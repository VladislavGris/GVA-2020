#include "framework.h"
#include <cstring>
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
}
