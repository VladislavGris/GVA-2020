#include "Generation.h"
namespace Gen
{
	void Generate(std::ofstream* stream, IT::IdTable idtable, LT::LexTable lextable, MFST::Mfst mfst)
	{
		WriteHeader(stream, idtable, lextable, mfst);
		ConstGeneration(stream, idtable);
		DataGeneration(stream, idtable, mfst);
	}
	void WriteHeader(std::ofstream* stream, IT::IdTable idtable, LT::LexTable lextable, MFST::Mfst mfst)
	{
		(*stream) << ".586" << std::endl;
		(*stream) << ".model flat, stdcall" << std::endl;
		(*stream) << "includelib kernel32.lib" << std::endl;
		(*stream) << "includelib libucrt.lib" << std::endl;
		(*stream) << "includelib Debug/GVALib.lib" << std::endl;
		(*stream) << "ExitProcess proto : dword" << std::endl;
		(*stream) << "strle proto: byte" << std::endl;
		(*stream) << "compa proto: byte,:byte" << std::endl;
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
					(*stream) << "byte ";
					if (idtable.table[i].isArray)
					{
						/*MFST::MfstState state;
						for (int i = 0; i < mfst.storestate.size(); i++)
						{
							state = MFST::Get_Container(mfst.storestate, i);
							if (state.lenta_position == idtable.table[i].idxfirstLE - 1)
							{
								(*stream)<<idtable.table
							}
						}*/
						(*stream) << idtable.table[i + 1].value.num.value << " dup (?)" << std::endl;
					}
					else
						(*stream) << "?" << std::endl;
				}
			}
		}
	}
}