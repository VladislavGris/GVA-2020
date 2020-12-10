#include "PolishNotation.h"
namespace PN
{
	void ConvertToPolish(IT::IdTable& idtable, LT::LexTable& lextable, MFST::Mfst mfst)
	{
		MFST::MfstState state, tempState;
		
		int pos = 0, str = 0, count = 0, parmCount = 0;
		char buf[3];
		bool parm = false;
		 //преобразовать if и функции
		for (int i = 0; i < mfst.storestate.size(); i++)
		{
			memset(buf, '\0', 3);
			state = MFST::Get_Container(mfst.storestate, i);
			// Получил позиции функций в таблице лексем
			if ((mfst.deducation.nrules[i] == 1 && (mfst.deducation.nrulechains[i] == 20 || mfst.deducation.nrulechains[i] == 19 || mfst.deducation.nrulechains[i] == 13 || mfst.deducation.nrulechains[i] == 12)) ||
				(mfst.deducation.nrules[i] == 2 && mfst.deducation.nrulechains[i] == 2))
			{
				LT::LexTable tempTable = LT::Create(12);
				pos = state.lenta_position;
				str = lextable.table[pos].sn;
				while (lextable.table[pos + count].sn == str)	// Цикл до конца строки
					count++;
				for (int i = 0; i < count; i++)
				{
					if (i != 0)
						parm = true;
					switch (lextable.table[pos + i].lexema)
					{
					case LEX_ID: case LEX_LITERAL: case LEX_PRINT:
						LT::Add(tempTable, lextable.table[pos + i]);
						if (parm)
							parmCount++;
						break;
					/*case LEX_COMMA:
						if (parmCount == 0)
							parmCount += 2;
						else
							parmCount++;
						break;*/
					case LEX_LEFTHESIS:
						break;
					case LEX_RIGHTHESIS:
						LT::Add(tempTable, LT::FillEntry(PARM_SYMBOL, lextable.table[pos + i].sn, LT_TI_NULLIDX, lextable.table[pos + i].operptorSymbol));
						sprintf_s(buf, "%d", parmCount);
						LT::Add(tempTable, LT::FillEntry(buf[0], lextable.table[pos + i].sn, LT_TI_NULLIDX, lextable.table[pos + i].operptorSymbol));
						break;
					}
				}
				for (int i = tempTable.size; i < count; i++)
					LT::Add(tempTable, LT::FillEntry(EMPTY, lextable.table[pos].sn, LT_TI_NULLIDX, lextable.table[pos].operptorSymbol));
				for (int i = 0; i < tempTable.size; i++)
					lextable.table[pos + i] = tempTable.table[i];
			}
			parm = false;
			count = 0;
			parmCount = 0;
		}
	}
}