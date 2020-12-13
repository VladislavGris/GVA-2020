#include "Generation.h"
namespace Gen
{
	void Generate(std::ofstream* stream, IT::IdTable idtable, LT::LexTable lextable, MFST::Mfst mfst)
	{
		WriteHeader(stream);
		ConstGeneration(stream, idtable);
		DataGeneration(stream, idtable, mfst);
		CodeGeneration(stream, idtable, lextable, mfst);
	}
	void WriteHeader(std::ofstream* stream)
	{
		(*stream) << ".586" << std::endl;
		(*stream) << ".model flat, stdcall" << std::endl;
		(*stream) << "includelib kernel32.lib" << std::endl;
		(*stream) << "includelib libucrt.lib" << std::endl;
		(*stream) << "includelib Debug/GVALib.lib" << std::endl;
		(*stream) << "ExitProcess proto : dword" << std::endl;
		(*stream) << "strle proto: dword" << std::endl;
		(*stream) << "compa proto: dword,:dword" << std::endl;
		(*stream) << "cpr proto: dword" << std::endl;
		(*stream) << "ipr proto: dword" << std::endl;
		(*stream) << ".stack 4096" << std::endl;
	}
	void WriteProto(std::ofstream* stream, IT::IdTable idtable, LT::LexTable lextable, MFST::Mfst mfst)
	{
		MFST::MfstState state;
		int parmCount = 0;
		for (int i = 0; i < mfst.storestate.size(); i++)	// Проход по дереву разбора
		{
			state = MFST::Get_Container(mfst.storestate, i);
			if (state.nrule == START_SYMBOL_RULE && state.nrulechain == START_SYMBOL_FUNC_RULE)	// Обнаружено правило tfi...
			{
				(*stream) << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i).lenta_position  + 2].idxTI].id << " proto, ";	// Вывод имени функции
				while (MFST::Get_Container(mfst.storestate, i + parmCount + 1).nrule == FUNC_PARAMS_RULE)
				{
					// Вывод параметров функции
					(*stream) << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + parmCount + 1).lenta_position + 1].idxTI].id << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + parmCount + 1).lenta_position + 1].idxTI].areaOfVisibility << ":";
					if (idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + parmCount + 1).lenta_position + 1].idxTI].iddatatype == IT::IDDATATYPE::NUM)
					{
						*(stream) << "dword";
					}
					else
					{
						*(stream) << "byte";
					}
					if (MFST::Get_Container(mfst.storestate, i + parmCount + 1).nrulechain != NOT_RECURS_ID_RULE && MFST::Get_Container(mfst.storestate, i + parmCount + 1).nrulechain != NOT_RECURS_ARR_ID_RULE)	// Нерекурсивные параметры
					{
						*(stream) << ", ";
					}
					parmCount++;
				}
				(*stream) << std::endl;
				parmCount = 0;
			}
		}
	}
	void ConstGeneration(std::ofstream* stream, IT::IdTable idtable)
	{
		(*stream) << ".const" << std::endl;
		for (int i = 0; i < idtable.size; i++)		// Проход по всем полям IT
		{
			if (idtable.table[i].idtype == IT::IDTYPE::L)		// Литералы в .const
			{
				(*stream) << idtable.table[i].id << idtable.table[i].areaOfVisibility << " ";	// Имя константы
				if (idtable.table[i].iddatatype == IT::IDDATATYPE::NUM)
				{
					(*stream) << "dword " << idtable.table[i].value.num.value << std::endl;
				}
				else
				{
					*(stream) << "byte " << "'" << idtable.table[i].value.vstr.str <<"'";
					if (idtable.table[i].isArray)
						(*stream) << ", 0" << std::endl;
					else
						(*stream) << std::endl;
				}
			}
		}
	}
	void DataGeneration(std::ofstream* stream, IT::IdTable idtable, MFST::Mfst mfst)
	{
		(*stream) << ".data" << std::endl;
		for (int i = 0; i < idtable.size; i++)				// Проход по всем строкам IT
		{
			if (idtable.table[i].idtype == IT::IDTYPE::V)	// Выборка переменных
			{
				(*stream) << idtable.table[i].id << idtable.table[i].areaOfVisibility << " ";	// Имя переменной
				if (idtable.table[i].iddatatype == IT::IDDATATYPE::NUM)
					(*stream) << "dword ?" << std::endl;
				else
				{
					(*stream) << "dword ?" << std::endl;
					/*if (idtable.table[i].isArray)
					{
						(*stream) << idtable.table[i + 1].value.num.value << " dup (?)" << std::endl;
					}
					else
						(*stream) << "?" << std::endl;*/
				}
			}
		}
	}
	void CodeGeneration(std::ofstream* stream, IT::IdTable idtable, LT::LexTable lextable, MFST::Mfst mfst)
	{
		char funcName[ID_MAXSIZE];
		int parmCount = 0, instrCount = 0, funcID, callParmCount = 0;
		MFST::MfstState state, tempState;
		memset(funcName, 0, ID_MAXSIZE);
		(*stream) << ".code" << std::endl;
		for (int i = 0; i < mfst.storestate.size(); i++)		// Проход по дереву разбора
		{
			state = MFST::Get_Container(mfst.storestate, i);
			if (state.nrule == START_SYMBOL_RULE)				// Встретили функцию
			{
				if (state.nrulechain == START_SYMBOL_FUNC_RULE)	// Реализация функции
				{
					strcpy_s(funcName, idtable.table[lextable.table[state.lenta_position + 2].idxTI].id);
					(*stream) << funcName << " proc ";
					while (MFST::Get_Container(mfst.storestate, i + parmCount + 1).nrule == FUNC_PARAMS_RULE)	// Перебор параметров
					{
						(*stream) << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + parmCount + 1).lenta_position + 1].idxTI].id << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + parmCount + 1).lenta_position + 1].idxTI].areaOfVisibility;
						if (idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + parmCount + 1).lenta_position + 1].idxTI].iddatatype == IT::IDDATATYPE::NUM)
							(*stream) << ":dword";
						else
							(*stream) << ":byte";
						if (MFST::Get_Container(mfst.storestate, i + parmCount + 1).nrulechain == RECURS_PARM_RULE)
							(*stream) << ", ";
						else
							(*stream) << std::endl;
						parmCount++;
					}
				}
				if (state.nrulechain == START_SYMBOL_MAIN_RULE)	// Реализация main
				{
					strcpy_s(funcName, MAIN_FUNC);
					(*stream) << funcName << " proc" << std::endl;
				}
				while (MFST::Get_Container(mfst.storestate, i + instrCount + 1).nrule != START_SYMBOL_RULE && i + instrCount + 1 != mfst.storestate.size())		// Порходим по всем правилам до встречи правила из S
				{
					tempState = MFST::Get_Container(mfst.storestate, i + instrCount + 1);
					if (tempState.nrule == OPERATOR_RULE)		// Правила, которые порождает нетерминал N
					{
						switch (tempState.nrulechain)			// Определяем конкретное правило
						{
						case 4: case 5:			// tisE | tisEN
							
							switch (MFST::Get_Container(mfst.storestate, i + instrCount + 2).nrulechain)	// Определяем, какое значение присвоили переменной
							{
							case 0: case 1:	// i | l
								if (idtable.table[lextable.table[tempState.lenta_position + 1].idxTI].iddatatype == IT::IDDATATYPE::NUM)
								{
									(*stream) << "lea edx, [" << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 2).lenta_position].idxTI].id << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 2).lenta_position].idxTI].areaOfVisibility << "]" << std::endl;
									(*stream) << "mov eax, [edx]" << std::endl;
									(*stream) << "mov " << idtable.table[lextable.table[tempState.lenta_position + 1].idxTI].id << idtable.table[lextable.table[tempState.lenta_position + 1].idxTI].areaOfVisibility << ", eax" << std::endl;
								}
								else
								{
									(*stream) << "lea edx, [" << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 2).lenta_position].idxTI].id << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 2).lenta_position].idxTI].areaOfVisibility << "]" << std::endl;
									(*stream) << "mov eax, [edx]" << std::endl;
									(*stream) << "mov " << idtable.table[lextable.table[tempState.lenta_position + 1].idxTI].id << idtable.table[lextable.table[tempState.lenta_position + 1].idxTI].areaOfVisibility << ", al" << std::endl;
								}
								//(*stream) << "push " << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 2).lenta_position].idxTI].id << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 2).lenta_position].idxTI].areaOfVisibility << std::endl;
								//(*stream) << "pop " << idtable.table[lextable.table[tempState.lenta_position + 1].idxTI].id << idtable.table[lextable.table[tempState.lenta_position + 1].idxTI].areaOfVisibility << std::endl;
								(*stream) << std::endl;
								break;
							case 2:				// i(W)
								funcID = MFST::Get_Container(mfst.storestate, i + instrCount + 2).lenta_position;
								while (lextable.table[funcID + callParmCount + 1].lexema != PARM_SYMBOL)	// Пока не символ @
									callParmCount++;
								for (int j = 0; j < callParmCount; j++)
								{
									if(idtable.table[lextable.table[funcID + callParmCount - j].idxTI].isArray)
										(*stream) << "push offset " << idtable.table[lextable.table[funcID + callParmCount - j].idxTI].id << idtable.table[lextable.table[funcID + callParmCount - j].idxTI].areaOfVisibility << std::endl;
									else
										(*stream) << "push " << idtable.table[lextable.table[funcID + callParmCount - j].idxTI].id << idtable.table[lextable.table[funcID + callParmCount - j].idxTI].areaOfVisibility << std::endl;
								}
								(*stream) << "call " << idtable.table[lextable.table[funcID].idxTI].id << std::endl;
								(*stream) << "mov " << idtable.table[lextable.table[tempState.lenta_position + 1].idxTI].id << idtable.table[lextable.table[tempState.lenta_position + 1].idxTI].areaOfVisibility << ", eax" << std::endl;
								(*stream) << std::endl;
								break;
							case 3:				// i[E]
								(*stream) << "lea edx, [" << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 2).lenta_position].idxTI].id << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 2).lenta_position].idxTI].areaOfVisibility << "+";
								if (idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 2).lenta_position].idxTI].iddatatype == IT::IDDATATYPE::NUM)
								{
									(*stream) << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 3).lenta_position].idxTI].value.num.value * 4 << "]" << std::endl;
									(*stream) << "mov eax, [edx]" << std::endl;
									(*stream) << "mov " << idtable.table[lextable.table[tempState.lenta_position + 1].idxTI].id << idtable.table[lextable.table[tempState.lenta_position + 1].idxTI].areaOfVisibility << ", eax" << std::endl;
								}
								else
								{
									(*stream) << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 3).lenta_position].idxTI].value.num.value << "]" << std::endl;
									(*stream) << "mov eax, [edx]" << std::endl;
									(*stream) << "mov " << idtable.table[lextable.table[tempState.lenta_position + 1].idxTI].id << idtable.table[lextable.table[tempState.lenta_position + 1].idxTI].areaOfVisibility << ", al" << std::endl;
								}
								(*stream) << std::endl;
								break;
							}
							break;
						case 6: case 7:		// ti[E]sE | ti[E]sEN
							(*stream) << "push offset " << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 3).lenta_position].idxTI].id << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 3).lenta_position].idxTI].areaOfVisibility << std::endl;
							(*stream) << "pop " << idtable.table[lextable.table[tempState.lenta_position + 1].idxTI].id << idtable.table[lextable.table[tempState.lenta_position + 1].idxTI].areaOfVisibility << std::endl;
							(*stream) << std::endl;
							break;
						case 8: case 9:		// isE | isEN
							switch (MFST::Get_Container(mfst.storestate, i + instrCount + 2).nrulechain)	// Определяем, какое значение присвоили переменной
							{
							case 0: case 1:	// i | l
								if (idtable.table[lextable.table[tempState.lenta_position].idxTI].iddatatype == IT::IDDATATYPE::NUM)
								{
									(*stream) << "lea edx, [" << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 2).lenta_position].idxTI].id << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 2).lenta_position].idxTI].areaOfVisibility << "]" << std::endl;
									(*stream) << "mov eax, [edx]" << std::endl;
									(*stream) << "mov " << idtable.table[lextable.table[tempState.lenta_position ].idxTI].id << idtable.table[lextable.table[tempState.lenta_position].idxTI].areaOfVisibility << ", eax" << std::endl;
								}
								else
								{
									(*stream) << "lea edx, [" << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 2).lenta_position].idxTI].id << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 2).lenta_position].idxTI].areaOfVisibility << "]" << std::endl;
									(*stream) << "mov eax, [edx]" << std::endl;
									(*stream) << "mov " << idtable.table[lextable.table[tempState.lenta_position].idxTI].id << idtable.table[lextable.table[tempState.lenta_position].idxTI].areaOfVisibility << ", al" << std::endl;
								}
								//(*stream) << "push " << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 2).lenta_position].idxTI].id << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 2).lenta_position].idxTI].areaOfVisibility << std::endl;
								//(*stream) << "pop " << idtable.table[lextable.table[tempState.lenta_position + 1].idxTI].id << idtable.table[lextable.table[tempState.lenta_position + 1].idxTI].areaOfVisibility << std::endl;
								(*stream) << std::endl;
								break;
							case 2:				// i(W)
								funcID = MFST::Get_Container(mfst.storestate, i + instrCount + 2).lenta_position;
								while (lextable.table[funcID + callParmCount + 1].lexema != PARM_SYMBOL)	// Пока не символ @
									callParmCount++;
								for (int j = 0; j < callParmCount; j++)
								{
									if (idtable.table[lextable.table[funcID + callParmCount - j].idxTI].isArray)
										(*stream) << "push offset " << idtable.table[lextable.table[funcID + callParmCount - j].idxTI].id << idtable.table[lextable.table[funcID + callParmCount - j].idxTI].areaOfVisibility << std::endl;
									else
										(*stream) << "push " << idtable.table[lextable.table[funcID + callParmCount - j].idxTI].id << idtable.table[lextable.table[funcID + callParmCount - j].idxTI].areaOfVisibility << std::endl;
								}
								(*stream) << "call " << idtable.table[lextable.table[funcID].idxTI].id << std::endl;
								(*stream) << "mov " << idtable.table[lextable.table[tempState.lenta_position].idxTI].id << idtable.table[lextable.table[tempState.lenta_position].idxTI].areaOfVisibility << ", eax" << std::endl;
								(*stream) << std::endl;
								break;
							case 3:				// i[E]
								(*stream) << "lea edx, [" << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 2).lenta_position].idxTI].id << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 2).lenta_position].idxTI].areaOfVisibility << "+";
								if (idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 2).lenta_position].idxTI].iddatatype == IT::IDDATATYPE::NUM)
								{
									(*stream) << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 3).lenta_position].idxTI].value.num.value * 4 << "]" << std::endl;
									(*stream) << "mov eax, [edx]" << std::endl;
									(*stream) << "mov " << idtable.table[lextable.table[tempState.lenta_position].idxTI].id << idtable.table[lextable.table[tempState.lenta_position].idxTI].areaOfVisibility << ", eax" << std::endl;
								}
								else
								{
									(*stream) << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 3).lenta_position].idxTI].value.num.value << "]" << std::endl;
									(*stream) << "mov eax, [edx]" << std::endl;
									(*stream) << "mov " << idtable.table[lextable.table[tempState.lenta_position].idxTI].id << idtable.table[lextable.table[tempState.lenta_position].idxTI].areaOfVisibility << ", al" << std::endl;
								}
								(*stream) << std::endl;
								break;
							}
							break;
						case 10: case 11:	// i[E]sE | i[E]sEN
							(*stream) << "push offset " << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 3).lenta_position].idxTI].id << idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 3).lenta_position].idxTI].areaOfVisibility << std::endl;
							(*stream) << "pop " << idtable.table[lextable.table[tempState.lenta_position].idxTI].id << idtable.table[lextable.table[tempState.lenta_position].idxTI].areaOfVisibility << std::endl;
							(*stream) << std::endl;
							break;
						case 12: case 13:	// p(E) | p(E)N
							switch (MFST::Get_Container(mfst.storestate, i + instrCount + 2).nrulechain)
							{
							case 0: case 1:
								(*stream) << "push " << idtable.table[lextable.table[tempState.lenta_position + 1].idxTI].id << idtable.table[lextable.table[tempState.lenta_position + 1].idxTI].areaOfVisibility << std::endl;
								if (idtable.table[lextable.table[tempState.lenta_position + 1].idxTI].iddatatype == IT::IDDATATYPE::NUM)
									(*stream) << "call ipr" << std::endl;
								else
									(*stream) << "call cpr" << std::endl;
								(*stream) << std::endl;
								break;
							case 2:
								//funcID = MFST::Get_Container(mfst.storestate, i + instrCount + 2).lenta_position;
								//while (lextable.table[funcID + callParmCount + 1].lexema != PARM_SYMBOL)	// Пока не символ @
								//	callParmCount++;
								//for (int j = 0; j < callParmCount; j++)
								//{
								//	if (idtable.table[lextable.table[funcID + callParmCount - j].idxTI].isArray)
								//		(*stream) << "push offset " << idtable.table[lextable.table[funcID + callParmCount - j].idxTI].id << idtable.table[lextable.table[funcID + callParmCount - j].idxTI].areaOfVisibility << std::endl;
								//	else
								//		(*stream) << "push " << idtable.table[lextable.table[funcID + callParmCount - j].idxTI].id << idtable.table[lextable.table[funcID + callParmCount - j].idxTI].areaOfVisibility << std::endl;
								//}
								//(*stream) << "call " << idtable.table[lextable.table[funcID].idxTI].id << std::endl;
								//(*stream) << "push eax" << std::endl;
								//if (idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + instrCount + 2).lenta_position].idxTI].iddatatype == IT::IDDATATYPE::NUM)
								//	(*stream) << "call ipr" << std::endl;
								//else
								//	(*stream) << "call cpr" << std::endl;
								//(*stream) << std::endl;
								break;
							}
							break;
						}

					}
					callParmCount = 0;
					instrCount++;
				}

				if (!strcmp(funcName, MAIN_FUNC))
				{
					(*stream) << "push 0" << std::endl;
					(*stream) << "call ExitProcess" << std::endl;
				}
				(*stream) << funcName << " endp" << std::endl;
				instrCount = 0;
				parmCount = 0;
			}

		}
	}
}