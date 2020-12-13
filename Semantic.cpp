#include "Semantic.h"
namespace Semantic
{
	void CheckSemantic(Log::LOG log, LT::LexTable& lextable, IT::IdTable& idtable, MFST::Mfst mfst)
	{
		int functionReturnType, parameterCount = 0, funcProtoParameters = 0, errorCount = 0;
		MFST::MfstState state, tempState;
		GRB::Rule rule;
		Error::ERROR e;
		for (int i = 0; i < mfst.storestate.size(); i++)
		{
			state = MFST::Get_Container(mfst.storestate, i);
			rule = mfst.grebach.getRule(state.nrule);
			switch (mfst.deducation.nrules[i])
			{
				//В функции проверяется соответствие указанного возвращаемого типа с типом выражения в return
			case 0:	// S->...
				switch (mfst.deducation.nrulechains[i])
				{
				case 0:	// tfi(F)bNeS
					functionReturnType = idtable.table[lextable.table[state.lenta_position + 2].idxTI].iddatatype;
					break;
				case 1:	// mbNrEe
					functionReturnType = IT::IDDATATYPE::NUM;
					break;
				}
				break;
			case 1:	// N->...
				switch (mfst.deducation.nrulechains[i])
				{
				case 0: case 1:	// ti +
					idtable.table[lextable.table[state.lenta_position + 1].idxTI].declaration = true;
					break;
				case 2: case 3:	// ti[E] +
					if (idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + 1).lenta_position].idxTI].iddatatype != IT::IDDATATYPE::NUM)
					{
						e = ERROR_THROW_IN(404, lextable.table[state.lenta_position].sn, 0);// Размер массива должен быть указан при помощи целочисленного значения
						Log::WriteError(log, e);
						errorCount++;
					}
					idtable.table[lextable.table[state.lenta_position + 1].idxTI].declaration = true;
					break;
				case 4:case 5:	// tisE +
					if (idtable.table[lextable.table[state.lenta_position + 1].idxTI].iddatatype != idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + 1).lenta_position].idxTI].iddatatype)
					{
						e = ERROR_THROW_IN(405, lextable.table[state.lenta_position].sn, 0);// Несоответствие типа переменной и значения, присваиваемого ей
						Log::WriteError(log, e);
						errorCount++;
					}
					//if (idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + 1).lenta_position].idxTI].isArray)
					//{
					//	e = ERROR_THROW_IN(408, lextable.table[state.lenta_position].sn, 0);// Попытка присвоить значение массива переменной, которая не является массивом
					//	Log::WriteError(log, e);
					//	errorCount++;
					//}
					idtable.table[lextable.table[state.lenta_position + 1].idxTI].declaration = true;
					idtable.table[lextable.table[state.lenta_position + 1].idxTI].assignment = true;
					break;
				case 6: case 7:	//ti[E]sE +
					if (idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + 1).lenta_position].idxTI].iddatatype != IT::IDDATATYPE::NUM)
					{
						e = ERROR_THROW_IN(404, lextable.table[state.lenta_position].sn, 0);// Размер массива должен быть указан при помощи целочисленного значения
						Log::WriteError(log, e);
						errorCount++;
					}
					if (idtable.table[lextable.table[state.lenta_position + 1].idxTI].iddatatype != idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + 2).lenta_position].idxTI].iddatatype)
					{
						e = ERROR_THROW_IN(405, lextable.table[state.lenta_position].sn, 0);// Несоответствие типа переменной и значения, присваиваемого ей
						Log::WriteError(log, e);
						errorCount++;
					}
					if (!idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + 2).lenta_position].idxTI].isArray)
					{
						e = ERROR_THROW_IN(409, lextable.table[state.lenta_position].sn, 0);// Попытка присвоить массиву значение, не являющееся массивом
						Log::WriteError(log, e);
						errorCount++;
					}
					idtable.table[lextable.table[state.lenta_position + 1].idxTI].declaration = true;
					idtable.table[lextable.table[state.lenta_position + 1].idxTI].assignment = true;
					break;
				case 8: case 9:	// isE +
					if (!idtable.table[lextable.table[state.lenta_position].idxTI].declaration && !idtable.table[lextable.table[state.lenta_position].idxTI].isArray)
					{
						e = ERROR_THROW_IN(407, lextable.table[state.lenta_position].sn, 0);// Попытка присвоить значение необъявленной переменной
						Log::WriteError(log, e);
						errorCount++;
					}
					if (idtable.table[lextable.table[state.lenta_position].idxTI].iddatatype != idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + 1).lenta_position].idxTI].iddatatype)
					{
						e = ERROR_THROW_IN(405, lextable.table[state.lenta_position].sn, 0);// Несоответствие типа переменной и значения, присваиваемого ей
						Log::WriteError(log, e);
						errorCount++;
					}
					if (idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + 1).lenta_position].idxTI].isArray)
					{
						e = ERROR_THROW_IN(408, lextable.table[state.lenta_position].sn, 0);// Попытка присвоить значение массива переменной, которая не является массивом
						Log::WriteError(log, e);
						errorCount++;
					}
					idtable.table[lextable.table[state.lenta_position].idxTI].assignment = true;
					break;
				case 10: case 11:	// i[E]sE +
					if (!idtable.table[lextable.table[state.lenta_position].idxTI].declaration)
					{
						e = ERROR_THROW_IN(407, lextable.table[state.lenta_position].sn, 0);// Попытка присвоить значение необъявленной переменной
						Log::WriteError(log, e);
						errorCount++;
					}
					if (idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + 1).lenta_position].idxTI].iddatatype != IT::IDDATATYPE::NUM)
					{
						e = ERROR_THROW_IN(410, lextable.table[state.lenta_position].sn, 0);// Индекс массива должен быть задан при поиощи целочисленного значения
						Log::WriteError(log, e);
						errorCount++;
					}
					if (idtable.table[lextable.table[state.lenta_position].idxTI].iddatatype != idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + 2).lenta_position].idxTI].iddatatype)
					{
						e = ERROR_THROW_IN(405, lextable.table[state.lenta_position].sn, 0);// Несоответствие типа переменной и значения, присваиваемого ей
						Log::WriteError(log, e);
						errorCount++;
					}
					idtable.table[lextable.table[state.lenta_position].idxTI].assignment = true;
					break;
				case 14: case 15: case 16:	// a[EoE]h{N}
					if (idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + 1).lenta_position].idxTI].iddatatype != idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + 2).lenta_position].idxTI].iddatatype)
					{
						e = ERROR_THROW_IN(400, lextable.table[state.lenta_position + 2].sn, 0);// Несоответствие типов операндов в выражении условного оператора
						Log::WriteError(log, e);
						errorCount++;
					}
					if (!idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + 1).lenta_position].idxTI].declaration || !idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + 2).lenta_position].idxTI].declaration)
					{
						e = ERROR_THROW_IN(402, lextable.table[state.lenta_position].sn, 0);// Использование необъявленной переменной в условном операторе
						Log::WriteError(log, e);
						errorCount++;
					}
					if (!idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + 1).lenta_position].idxTI].assignment || !idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + 2).lenta_position].idxTI].assignment)
					{
						e = ERROR_THROW_IN(403, lextable.table[state.lenta_position].sn, 0);// Использование в условном операторе переменной, которой не присвоено значение
						Log::WriteError(log, e);
						errorCount++;
					}
					break;
				case 17: case 18:	// rE
					if (idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + 1).lenta_position].idxTI].iddatatype != functionReturnType)
					{
						e = ERROR_THROW_IN(401, lextable.table[state.lenta_position].sn, 0);// Тип возвращаемого значения не соответствует типу возвращаемого значения функиции
						Log::WriteError(log, e);
						errorCount++;
					}
					break;
				}
				break;
			case 2:	// E->...
				switch (mfst.deducation.nrulechains[i])
				{
				case 3:	// i[E]
					if (idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + 1).lenta_position].idxTI].iddatatype != IT::IDDATATYPE::NUM)
					{
						e = ERROR_THROW_IN(410, lextable.table[state.lenta_position].sn, 0);// Индекс массива должен быть задан при поиощи целочисленного значения
						Log::WriteError(log, e);
						errorCount++;
					}
					break;
				}
				break;
			case 3:// F->...
				switch (mfst.deducation.nrulechains[i])
				{
				case 0:case 1:case 2: case 3:
					idtable.table[lextable.table[state.lenta_position + 1].idxTI].assignment = true;
					idtable.table[lextable.table[state.lenta_position + 1].idxTI].declaration = true;
					break;
				}
				break;
			case 4:// W->...
				switch (mfst.deducation.nrulechains[i])
				{
				case 1: case 2:
					IT::IDDATATYPE *param = (IT::IDDATATYPE*)malloc(sizeof(IT::IDDATATYPE));
					bool* isArr = (bool*)malloc(sizeof(IT::IDDATATYPE));
					while (MFST::Get_Container(mfst.storestate, i - parameterCount).nrule == PARAMETERS)	// вычисление количества переданнх в функцию параметров
					{
						parameterCount++;
					}
					if (IT::IsLibFunc(idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i - parameterCount).lenta_position].idxTI].id))
					{
						switch (IT::IsLibFunc(idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i - parameterCount).lenta_position].idxTI].id))
						{
						case 1:				// strlen
							funcProtoParameters = 1;
							param[0] = IT::SYM;
							isArr[0] = true;
							break;
						case 2:				// strlen
							funcProtoParameters = 2;
							param[0] = IT::SYM; param[1] = IT::SYM;
							isArr[0] = true; isArr[1] = true;
							break;
						}
						if (funcProtoParameters != parameterCount)
						{
							e = ERROR_THROW_IN(411, lextable.table[state.lenta_position].sn, 0);
							Log::WriteError(log, e);
							errorCount++;
							continue;
						}
						for (int h = 0; h < funcProtoParameters; h++)
						{
							if (param[h] != idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i - h).lenta_position].idxTI].iddatatype)
							{
								e = ERROR_THROW_IN(412, lextable.table[state.lenta_position].sn, 0);
								Log::WriteError(log, e);
								errorCount++;
							}
							if (isArr[h] && !idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i - h).lenta_position].idxTI].isArray)
							{
								e = ERROR_THROW_IN(414, lextable.table[state.lenta_position].sn, 0);
								Log::WriteError(log, e);
								errorCount++;
							}
							if (!isArr[h] && idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i - h).lenta_position].idxTI].isArray)
							{
								e = ERROR_THROW_IN(413, lextable.table[state.lenta_position].sn, 0);
								Log::WriteError(log, e);
								errorCount++;
							}
						}
					}
					else
					{
						for (int j = 0; j < i - parameterCount; j++)
						{
							if (MFST::Get_Container(mfst.storestate, j).nrule == START_SYMBOL && MFST::Get_Container(mfst.storestate, j).nrulechain == START_SYMBOL)	// Если встречаем правило для стартового символа грамматики
							{
								if (!strcmp(idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, j).lenta_position + 2].idxTI].id, idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i - parameterCount).lenta_position].idxTI].id))
								{
									while (MFST::Get_Container(mfst.storestate, j + 1 + funcProtoParameters).nrule == FUNC_PARAMS)
									{
										funcProtoParameters++;
									}
									if (parameterCount != funcProtoParameters)	// в последствии добавить continue
									{
										e = ERROR_THROW_IN(411, lextable.table[state.lenta_position].sn, 0);
										Log::WriteError(log, e);
										errorCount++;
									}
									for (int h = funcProtoParameters; h > 0; h--)
									{
										if (idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, j + h).lenta_position + 1].idxTI].iddatatype != idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i - parameterCount + h).lenta_position].idxTI].iddatatype)
										{
											e = ERROR_THROW_IN(412, lextable.table[state.lenta_position].sn, 0);
											Log::WriteError(log, e);
											errorCount++;
										}
										if (idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, j + h).lenta_position + 1].idxTI].isArray && !idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i - parameterCount + h).lenta_position].idxTI].isArray)
										{
											e = ERROR_THROW_IN(414, lextable.table[state.lenta_position].sn, 0);
											Log::WriteError(log, e);
											errorCount++;
										}
										if (!idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, j + h).lenta_position + 1].idxTI].isArray && idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i - parameterCount + h).lenta_position].idxTI].isArray)
										{
											e = ERROR_THROW_IN(413, lextable.table[state.lenta_position].sn, 0);
											Log::WriteError(log, e);
											errorCount++;
										}
									}
								}
							}
						}
					}
					parameterCount = 0;
					funcProtoParameters = 0;
					break;
				}
				break;
			//case 5:// V->...
			//	switch (mfst.deducation.nrulechains[i])
			//	{
			//	case 0:
			//		if (idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + 1).lenta_position].idxTI].iddatatype != idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + 2).lenta_position].idxTI].iddatatype)
			//		{
			//			e = ERROR_THROW_IN(400, lextable.table[state.lenta_position].sn, 0);
			//			Log::WriteError(log, e);
			//			errorCount++;
			//		}
			//		if (!idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + 1).lenta_position].idxTI].declaration || !idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + 2).lenta_position].idxTI].declaration)
			//		{
			//			e = ERROR_THROW_IN(402, lextable.table[state.lenta_position].sn, 0);
			//			Log::WriteError(log, e);
			//			errorCount++;
			//		}
			//		if (!idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + 1).lenta_position].idxTI].assignment || !idtable.table[lextable.table[MFST::Get_Container(mfst.storestate, i + 2).lenta_position].idxTI].assignment)
			//		{
			//			e = ERROR_THROW_IN(403, lextable.table[state.lenta_position].sn, 0);
			//			Log::WriteError(log, e);
			//			errorCount++;
			//		}
			//		break;
			//	}
			//	break;
			}
		}
		if (errorCount == 0)
			Log::WriteInfo(log, "Семантический анализ выполнен без ошибок");
		else
		{
			
			Log::WriteInfo(log, "Семантический анализ завершен с ошибками. Количество ошибок: " );
			throw ERROR_THROW(419)
		}
	}
}