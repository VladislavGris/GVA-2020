#include "framework.h"
#include <cstring>
#include <iostream>
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
	void __stdcall cpr(char* str)
	{
		std::cout << str << std::endl;
		
	}
	void __stdcall ipr(int a)
	{
		std::cout << a << std::endl;
		
	}
}
