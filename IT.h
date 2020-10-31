#pragma once
#define ID_MAXSIZE		5			// максимальное количество символов в иденитфикаторе
#define TI_MAXSIZE		4096		// максимальное количество строк в таблице идентификаторов
#define TI_NUMBER_DEFAULT	0x00000000	// значение по умолчанию дл€ типа integer
#define TI_SYMBOL_DEFAULT	0x00		// занчение по умолчанию дл€ типа string
#define TI_NULLIDX		0xffffffff	// нет элемента таблицы идентификаторов
#define TI_STR_MAXSIZE	255
#define NUM_DATATYPE		1
#define SYMBOL_DATATYPE		2
#define VARIABLE			1
#define FUNCTION			2
#define PARAMETER			3
#define LITERAL				4
#include <iostream>
#include <iomanip>
namespace IT
{
	enum IDDATATYPE {
		INT = 1, STR = 2
	};
	enum IDTYPE {
		V = 1, F = 2, P = 3, L = 4
	};

	struct Entry
	{
		int idxfirstLE;			// индекс первой строки в таблице лексем
		char id[ID_MAXSIZE+1];	// идентификатор (автоматически усекаетс€ до ID_MAXSIZE)
		IDDATATYPE iddatatype;	// тип данных
		IDTYPE idtype;			// тип идентификатора
		int areaOfVisibility;	// область видимости
		union
		{
			int vint;			// значение integer
			struct
			{
				char len;			// количество символов в string
				char str[TI_STR_MAXSIZE - 1];	// символы string
			} vstr[TI_STR_MAXSIZE];				// значение string
		} value;	// значение идентификатора
	};
	struct IdTable				// экземпл€р таблицы идентификаторов
	{
		int maxsize;			// емкость таблицы идентификаторов < TI_MAXSIZE
		int size;				// текущий размер таблицы идентификаторов < maxsize
		Entry* table;			// массив строк таблицы идентификаторов
	};
	IdTable Create(int size);	// создать таблицу идентификаторов
	Entry FillEntry(int lexTableSize, char* id, int datatype, int type, int areaofvisibility);
	void Add(IdTable& idtable, Entry entry);	// добавить строку в таблицу идентификаторов
	Entry GetEntry(IdTable& idtable, int n);	// получить строку таблицы идентификаторов
	int IsId(IdTable& idtable, char id[ID_MAXSIZE], int areaofvisibility);	// возврат: номер строки (если есть), TI_NULLIDX (если нет)
	void PrintIDTable(IdTable& idtable);
	void Delete(IdTable& idtable);				// удалить таблицу лексем (освободить пам€ть)
}