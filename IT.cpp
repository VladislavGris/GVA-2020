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
	Entry FillEntry(int lexTableSize, char* id, int datatype, int type, int areaofvisibiliti)
	{
		Entry entry;
		entry.idxfirstLE = lexTableSize;
		for (int i = 0; i < ID_MAXSIZE; i++)
		{
			entry.id[i] = id[i];
		}
		entry.id[ID_MAXSIZE] = '\0';
		entry.areaOfVisibility = areaofvisibiliti;
		if (datatype == NUM_DATATYPE)
		{
			entry.iddatatype = INT;
		}
		else
		{
			entry.iddatatype = STR;
		}
		if (type == VARIABLE)
		{
			entry.idtype = V;
			if (entry.idtype == INT)
			{
				entry.value.vint = 0;
			}
			else
			{
				entry.value.vstr->len = 0;
			}
		}
		else if (type == FUNCTION)
		{
			entry.idtype = F;
		}
		else if (type == PARAMETER)
		{
			entry.idtype = P;
		}
		else
		{
			entry.idtype = L;
		}
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
			if (!strcmp(idtable.table[i].id, id) && idtable.table[i].idtype == F)
				return (i+1);
			if (!strcmp(idtable.table[i].id, id) && idtable.table[i].areaOfVisibility == areaofvisibility)
				return (i+1);
		}
		return TI_NULLIDX;
	}
	void PrintIDTable(IdTable& idtable)
	{
		std::cout << "===========(Таблица идентификаторов)===========" << std::endl;
		std::cout << " № |  ID  | AREA | DATATYPE |   TYPE   | LTID|" << std::endl;
		
		for (int i = 0; i < idtable.size; i++)
		{
			std::cout <<std::setw(3)<< i+1 << "|"<< std::setw(6) << idtable.table[i].id<<"|"<< std::setw(6) <<idtable.table[i].areaOfVisibility<<"|";
			if (idtable.table[i].iddatatype == NUM_DATATYPE)
			{
				std::cout << std::setw(10) << "INT" << "|";
			}
			else
			{
				std::cout << std::setw(10) << "STR" << "|";
			}
			if (idtable.table[i].idtype == VARIABLE)
			{
				std::cout << std::setw(10) << "VARIABLE"<<"|";
			}
			else if (idtable.table[i].idtype == FUNCTION)
			{
				std::cout << std::setw(10) << "FUNCTION"<<"|";
			}
			else if (idtable.table[i].idtype == PARAMETER)
			{
				std::cout << std::setw(10) << "PARAMETER"<<"|";
			}
			else
			{
				std::cout << std::setw(10) << "LITERAL "<<"|";
			}
			std::cout << std::setw(5) <<idtable.table[i].idxfirstLE <<"|"<<  std::endl;
		}
	}
	void Delete(IdTable& idtable)
	{
		delete& idtable;
	}
}