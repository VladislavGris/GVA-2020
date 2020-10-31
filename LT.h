#pragma once
#include "Lexemes.h"
#include "Error.h"
#include <iostream>
#include <iomanip>
#include <ctype.h>

namespace LT
{
	struct Entry
	{
		char lexema[LEXEMA_FIXSIZE];	// лексема
		int sn;							// номер строки
		int idxTI;						// индекс в таблице идентификаторов
		char operptorSymbol[OPERATOR_FIXSIZE];			// символ оператора, или NOT_AN_OPERATOR
	};

	struct LexTable
	{
		int maxsize;
		int size;
		Entry* table;
	};
	LexTable Create(int size);
	Entry FillEntry(char* lexema, int strNum, int id, const char* operatorSymbol = "-1");
	void Add(LexTable& lextable, Entry entry);
	Entry GetEntry(LexTable& lextable, int n);
	void PrintLexTable(LexTable& lextable);
	void RemoveEntry(LexTable& lextable, int position);
	void Delete(LexTable& lextable);
}