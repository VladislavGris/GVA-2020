#pragma once
#define ID_MAXSIZE		6			// максимальное количество символов в иденитфикаторе(размер с учетом \0)
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
#define LIB_FUNC_COUNT		2
#define LIB_FUNC_1			"strle"
#define LIB_FUNC_2			"compa"
#define FUNCTION_AREA		0
#include <iostream>
#include <iomanip>
#include <fstream>
namespace IT
{
	enum IDDATATYPE {
		NUM = 1, SYM = 2
	};
	enum IDTYPE {
		S = 0, V = 1, F = 2, P = 3, L = 4, M = 5
	};
	enum NOTATION {
		D = 10, O = 8, B = 2
	};
	struct Entry
	{
		int idxfirstLE;			// индекс первой строки в таблице лексем
		char id[ID_MAXSIZE];	// идентификатор (автоматически усекаетс€ до ID_MAXSIZE)
		IDDATATYPE iddatatype;	// тип данных
		IDTYPE idtype;			// тип идентификатора
		int areaOfVisibility;	// область видимости
		bool declaration, assignment, isArray;
		union
		{
			struct
			{
				int value;
				NOTATION notation;
			} num;
			struct
			{
				int len;
				char str[TI_STR_MAXSIZE];
			} vstr;
		} value;	// значение идентификатора
	};
	struct IdTable				// экземпл€р таблицы идентификаторов
	{
		int maxsize;			// емкость таблицы идентификаторов < TI_MAXSIZE
		int size;				// текущий размер таблицы идентификаторов < maxsize
		Entry* table;			// массив строк таблицы идентификаторов
	};
	IdTable Create(int size);	// создать таблицу идентификаторов
	Entry FillEntry(int lexTableSize, char* id, IDDATATYPE datatype, IDTYPE type, char* value, int areaofvisibiliti);
	void Add(IdTable& idtable, Entry entry);	// добавить строку в таблицу идентификаторов
	Entry GetEntry(IdTable& idtable, int n);	// получить строку таблицы идентификаторов
	int IsId(IdTable& idtable, char id[ID_MAXSIZE], int areaofvisibility);	// возврат: номер строки (если есть), TI_NULLIDX (если нет)
	void PrintIDTable(IdTable& idtable);
	void Delete(IdTable& idtable);				// удалить таблицу лексем (освободить пам€ть)
	void PrintToFile(IdTable& idtable);
	int IsLibFunc(char* id);
	int BinaryToDecimal(char* num);
	int OctalToDecimal(char* num);
}