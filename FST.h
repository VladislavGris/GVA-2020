#pragma once
#include <cstring>
#include <algorithm> 
#include "Error.h"
#include "Log.h"
namespace FST
{
	struct RELATION				// ребро:символ -> вершина графов переходов КА		
	{
		char symbol;			// символ перехода
		short nnode;			// номер смежной вершины
		RELATION(
			char c = 0x00,		// символ перехода
			short ns = 0		// новое состояние
		);
	};
	struct NODE					//вершина графа переходов
	{
		short n_relation;		// количество инцидентных ребер
		RELATION* relations;	// инцидентные ребра
		NODE();
		NODE(
			short n,			// количество инцидентных ребер
			RELATION rel, ...	// список ребер
		);
	};

	struct FST					// недетерминированный конечный автомат
	{
		char* string;			// цепочка (строка, завершается 0x00)
		short position;			// текущая позиция в цепочке
		short nstates;			// количество состояний автомата
		NODE* nodes;			// граф переходов: [0] - начальное состояние, [nstate-1] - конечное
		short* rstates;			// возможные состояния автомата в данной позиции
		FST(
			char* s,			// цепочка (строка, завершается 0x00)
			short ns,			// количество состояний автомата
			NODE n, ...			// список состояний (граф переходов)
		);
	};

	bool execute(				// выполнить распознавание цепочки
		FST& fst				// недетерминированный конечный автомат
	);
}