#include "IT.h"
#include "Error.h"
#include <string.h>
namespace IT
{
	IdTable Create(int size)
	{
		IdTable newTable;
		newTable.maxsize = size;
		newTable.size = 0;
		newTable.table = new Entry[newTable.maxsize];
		return newTable;
	}
	void Add(IdTable& idtable, Entry entry)
	{
		idtable.table[idtable.size] = entry;
		idtable.size++;
	}
	Entry FillEntry(int lexTableSize, char* id, IDDATATYPE datatype, IDTYPE type, int areaofvisibiliti)
	{
		Entry entry;
		entry.idxfirstLE = lexTableSize;
		strcpy_s(entry.id, id);
		entry.iddatatype = datatype;
		entry.idtype = type;
		entry.areaOfVisibility = areaofvisibiliti;
		return entry;
	}
	Entry GetEntry(IdTable& idtable, int n)
	{
		return(idtable.table[n]);
	}
	int IsId(IdTable& idtable, char id[ID_MAXSIZE], int areaofvisibility)
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (!strcmp(idtable.table[i].id, id) && idtable.table[i].areaOfVisibility == areaofvisibility)
				return i;
		}
		return TI_NULLIDX;
	}
	void PrintIDTable(IdTable& idtable)
	{
		std::cout << "===========(Таблица идентификаторов)===========" << std::endl;
		std::cout << " №  |  ID  | AREA | DATATYPE |   TYPE   | LTID|" << std::endl;
		
		for (int i = 0; i < idtable.size; i++)
		{
			std::cout << std::setw(5) << i << '|';
			std::cout << std::setw(6) << idtable.table[i].id << '|';
			std::cout << std::setw(6) << idtable.table[i].areaOfVisibility << '|';
			switch (idtable.table[i].iddatatype)
			{
			case NUM:
				std::cout << std::setw(10) << "NUMBER|";
				break;
			case SYM:
				std::cout << std::setw(10) << "SYMBOL|";
			}
			switch (idtable.table[i].idtype)
			{
			case V:
				std::cout << std::setw(10) << "VARIABLE|";
				break;
			case F:
				std::cout << std::setw(10) << "FUNCTION|";
				break;
			case P:
				std::cout << std::setw(10) << "PARAMETER|";
				break;
			case L:
				std::cout << std::setw(10) << "LITERAL|";
				break;
			}
			std::cout << std::setw(5) << idtable.table[i].idxfirstLE << std::endl;
		}
	}
	void Delete(IdTable& idtable)
	{
		delete& idtable;
	}
}