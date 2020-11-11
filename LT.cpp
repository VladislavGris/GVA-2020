#include "LT.h"
namespace LT
{
	LexTable Create(int size)
	{
		LexTable newTable;
		newTable.maxsize = size;
		newTable.size = 0;
		newTable.table = new Entry[newTable.maxsize];
		return newTable;
	}
	Entry FillEntry(char* lexema, int strNum, int id, char* operatorSymbol)
	{
		Entry entry;
		entry.idxTI = id;
		memset(entry.lexema, 0, LEXEMA_FIXSIZE);
		strcpy_s(entry.lexema, lexema);
		entry.sn = strNum;
		strcpy_s(entry.operptorSymbol,operatorSymbol);
		return entry;
	}
	void Add(LexTable& lextable, Entry entry)
	{
		lextable.table[lextable.size] = entry;
		lextable.size++;
	}
	Entry GetEntry(LexTable& lextable, int n)
	{
		return(lextable.table[n-1]);
	}
	void RemoveEntry(LexTable& lextable, int position)
	{
		for (int i = position + 1; i < lextable.size; i++)
		{
			lextable.table[i - 1] = lextable.table[i];
		}
		lextable.size--;
	}
	void Delete(LexTable& lextable)
	{
		delete &lextable;
	}
	void PrintLexTable(LexTable& lextable)
	{
		std::cout << "--- Таблица лексем ---" << std::endl;
		std::cout << std::setw(3) << '№'<<std::setw(3)<< '|';
		std::cout << std::setw(7) << "strNum|";
		std::cout << std::setw(4) << "lex|";
		std::cout << std::setw(6) << "idxTI|";
		std::cout << std::setw(3) << "op|" << std::endl;
		for (int i = 0; i < lextable.size; i++)
		{
			std::cout << std::setw(5) << i << '|';
			std::cout << std::setw(6) << lextable.table[i].sn << '|';
			std::cout << std::setw(3) << lextable.table[i].lexema << '|';
			if(lextable.table[i].idxTI == LT_TI_NULLIDX)
				std::cout << std::setw(6) << '|';
			else
				std::cout << std::setw(5) << lextable.table[i].idxTI << '|';
			std::cout << std::setw(3) << lextable.table[i].operptorSymbol << '|' << std::endl;
		}
	}
}