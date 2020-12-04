#include "Semantic.h"
namespace Semantic
{
	void CheckSemantic(Log::LOG log, LT::LexTable& lextable, IT::IdTable& idtable, MFST::Mfst mfst)
	{
		bool isMain;
		int functionReturnType;
		MFST::MfstState state;
		GRB::Rule rule;
		for (int i = 0; i < mfst.storestate.size(); i++)
		{
			state = MFST::Get_Container(mfst.storestate, i);
			rule = mfst.grebach.getRule(state.nrule);
			switch (mfst.deducation.nrules[i])
			{
				//¬ функции провер€етс€ соответствие указанного возвращаемого типа с типом выражени€ в return
			case 0:	// S->...
				switch (mfst.deducation.nrulechains[i])
				{
				case 0:	// tfi(F)bNeS
					functionReturnType = idtable.table[lextable.table[state.lenta_position].idxTI].iddatatype;
					break;
				case 1:	// mbNrEe
					isMain = true;
					functionReturnType = IT::IDDATATYPE::NUM;
					break;
				}
				break;
			case 1:	// N->...
				switch (mfst.deducation.nrulechains[i])
				{
				case 14:	// a[EoE]h{N}V
					if (idtable.table[lextable.table[state.lenta_position + 2].idxTI].iddatatype != idtable.table[lextable.table[state.lenta_position + 4].idxTI].iddatatype)
						throw ERROR_THROW_IN(400, lextable.table[state.lenta_position + 2].sn, 0);	// Ќесоответствие типов операндов в выражении условного оператора
					break;
				case 15:	// rE
					if (idtable.table[lextable.table[state.lenta_position + 1].idxTI].iddatatype != functionReturnType)
						throw ERROR_THROW_IN(401, lextable.table[state.lenta_position].sn, 0);
					break;
				}
				break;
			case 2:	// E->...
				break;
			case 3:// F->...
				break;
			case 4:// W->...
				break;
			case 5:// V->...
				break;
			}
		}
	}
}