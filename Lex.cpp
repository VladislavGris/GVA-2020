#include "Lex.h"
namespace Lex
{
	bool ParseAChain(In::IN in, LT::LexTable& lextable, IT::IdTable& idtable, Log::LOG log)
	{
		int lexemeSize = 0, strCount = 1, position = 0, idxTI = LT_TI_NULLIDX, areaOfVisibility = 0, baseArea = 0, literalCount = 1;
		char* lexeme = new char[TI_STR_MAXSIZE], symbol, operation[OPERATOR_FIXSIZE], empty[2] = "", id[ID_MAXSIZE], lexNumBuf[ID_MAXSIZE - 1];
		char token, lastToken = '0';
		const char lexArray[FST_ARRAY_SIZE] = { LEX_NUMBER, LEX_FUNCTION, LEX_SYMBOL, LEX_BEGIN, LEX_IF, LEX_THEN, LEX_RETURN,
												LEX_ELSE, LEX_END, LEX_MAIN, LEX_PRINT,LEX_LESSER, LEX_ASIGNMENT, LEX_GE,
												LEX_GREATER, LEX_EQUAL, LEX_NOT_EQUAL, LEX_ID, LEX_LITERAL,LEX_LITERAL, LEX_LITERAL, LEX_LITERAL/*, LEX_LITERAL*/};
		bool wasSeparator = false, isLiteral = false, wasChanged = false, areParametrs = false, wasError = false, isCommentary = false, arrayLiteral = false, hasMain = false, wasFuncRet = true,
			inIf = false, inElse = false, ifRet = false, elseRet = false, wasIf = false, wasElse = false;
		IT::IDDATATYPE datatype = IT::IDDATATYPE::NUM;
		IT::IDTYPE type = IT::IDTYPE::V;
		LT::Entry tempEntry;
		IT::Entry ITTempEntry;
		Error::ERROR e;
		memset(lexeme, 0, TI_STR_MAXSIZE);
		for (int i = 0; i <= in.size; i++)
		{
			symbol = in.text[i];
			// Работа с комментариями
			if (isCommentary)
			{
				if (symbol == END_OF_INSTRUCTION)
				{
					strCount++;
					position = 0;
					isCommentary = false;
				}
				continue;
			}
			if (symbol == COMMENTARY)
			{
				isCommentary = true;
				continue;
			}
			position++;
			if ((IsSeparator(symbol) && !isLiteral) || i == in.size)
			{
				FST::FST fstArray[FST_ARRAY_SIZE] =
				{
					// 0 number
					{
						lexeme,
						7,
						FST::NODE(1, FST::RELATION('n',1)),
						FST::NODE(1, FST::RELATION('u',2)),
						FST::NODE(1, FST::RELATION('m',3)),
						FST::NODE(1, FST::RELATION('b',4)),
						FST::NODE(1, FST::RELATION('e',5)),
						FST::NODE(1, FST::RELATION('r',6)),
						FST::NODE()
					},
					// 1 function
					{
						lexeme,
						9,
						FST::NODE(1, FST::RELATION('f',1)),
						FST::NODE(1, FST::RELATION('u',2)),
						FST::NODE(1, FST::RELATION('n',3)),
						FST::NODE(1, FST::RELATION('c',4)),
						FST::NODE(1, FST::RELATION('t',5)),
						FST::NODE(1, FST::RELATION('i',6)),
						FST::NODE(1, FST::RELATION('o',7)),
						FST::NODE(1, FST::RELATION('n',8)),
						FST::NODE()
					},
					// 2 symbol
					{
						lexeme,
						7,
						FST::NODE(1, FST::RELATION('s',1)),
						FST::NODE(1, FST::RELATION('y',2)),
						FST::NODE(1, FST::RELATION('m',3)),
						FST::NODE(1, FST::RELATION('b',4)),
						FST::NODE(1, FST::RELATION('o',5)),
						FST::NODE(1, FST::RELATION('l',6)),
						FST::NODE()
					},
					// 3 begin
					{
						lexeme,
						6,
						FST::NODE(1, FST::RELATION('b',1)),
						FST::NODE(1, FST::RELATION('e',2)),
						FST::NODE(1, FST::RELATION('g',3)),
						FST::NODE(1, FST::RELATION('i',4)),
						FST::NODE(1, FST::RELATION('n',5)),
						FST::NODE()
					},
					// 4 if
					{
						lexeme,
						3,
						FST::NODE(1, FST::RELATION('i',1)),
						FST::NODE(1, FST::RELATION('f',2)),
						FST::NODE()
					},
					// 5 then
					{
						lexeme,
						5,
						FST::NODE(1, FST::RELATION('t',1)),
						FST::NODE(1, FST::RELATION('h',2)),
						FST::NODE(1, FST::RELATION('e',3)),
						FST::NODE(1, FST::RELATION('n',4)),
						FST::NODE()
					},
					// 6 return
					{
						lexeme,
						7,
						FST::NODE(1, FST::RELATION('r',1)),
						FST::NODE(1, FST::RELATION('e',2)),
						FST::NODE(1, FST::RELATION('t',3)),
						FST::NODE(1, FST::RELATION('u',4)),
						FST::NODE(1, FST::RELATION('r',5)),
						FST::NODE(1, FST::RELATION('n',6)),
						FST::NODE()
					},
					// 7 else
					{
						lexeme,
						5,
						FST::NODE(1, FST::RELATION('e',1)),
						FST::NODE(1, FST::RELATION('l',2)),
						FST::NODE(1, FST::RELATION('s',3)),
						FST::NODE(1, FST::RELATION('e',4)),
						FST::NODE()
					},
					// 8 end
					{
						lexeme,
						4,
						FST::NODE(1, FST::RELATION('e',1)),
						FST::NODE(1, FST::RELATION('n',2)),
						FST::NODE(1, FST::RELATION('d',3)),
						FST::NODE()
					},
					// 9 main
					{
						lexeme,
						5,
						FST::NODE(1, FST::RELATION('m',1)),
						FST::NODE(1, FST::RELATION('a',2)),
						FST::NODE(1, FST::RELATION('i',3)),
						FST::NODE(1, FST::RELATION('n',4)),
						FST::NODE()
					},
					// 10 print
					{
						lexeme,
						6,
						FST::NODE(1, FST::RELATION('p',1)),
						FST::NODE(1, FST::RELATION('r',2)),
						FST::NODE(1, FST::RELATION('i',3)),
						FST::NODE(1, FST::RELATION('n',4)),
						FST::NODE(1, FST::RELATION('t',5)),
						FST::NODE()
					},
					// 11 <
					{
						lexeme,
						2,
						FST::NODE(1, FST::RELATION('<', 1)),
						FST::NODE()
					},
					// 12 <-
					{
						lexeme,
						3,
						FST::NODE(1, FST::RELATION('<', 1)),
						FST::NODE(1, FST::RELATION('-', 2)),
						FST::NODE()
					},
					// 13 GE , LE
					{
						lexeme,
						3,
						FST::NODE(2, FST::RELATION('G', 1), FST::RELATION('L', 1)),
						FST::NODE(1, FST::RELATION('E', 2)),
						FST::NODE()
					},
					// 14 >
					{
						lexeme,
						2,
						FST::NODE(1, FST::RELATION('>',1)),
						FST::NODE()
					},
					// 15 =
					{
						lexeme,
						2,
						FST::NODE(1, FST::RELATION('=',1)),
						FST::NODE()
					},
					// 16 #
					{
						lexeme,
						2,
						FST::NODE(1, FST::RELATION('#',1)),
						FST::NODE()
					},
					// 17 identifier
					{
						lexeme,
						2,
						FST::NODE(52 ,FST::RELATION('a',0), FST::RELATION('b',0), FST::RELATION('c',0), FST::RELATION('d',0),
									FST::RELATION('e',0), FST::RELATION('f',0), FST::RELATION('g',0), FST::RELATION('h',0),
									FST::RELATION('i',0), FST::RELATION('j',0), FST::RELATION('k',0) ,FST::RELATION('l',0),
									FST::RELATION('n',0), FST::RELATION('m',0) ,FST::RELATION('o',0), FST::RELATION('p',0),
									FST::RELATION('q',0), FST::RELATION('r',0), FST::RELATION('s',0), FST::RELATION('t',0),
									FST::RELATION('u',0), FST::RELATION('v',0), FST::RELATION('w',0), FST::RELATION('x',0),
									FST::RELATION('y',0),FST::RELATION('z',0),
									FST::RELATION('a',1), FST::RELATION('b',1), FST::RELATION('c',1), FST::RELATION('d',1),
									FST::RELATION('e',1), FST::RELATION('f',1), FST::RELATION('g',1), FST::RELATION('h',1),
									FST::RELATION('i',1), FST::RELATION('j',1), FST::RELATION('k',1) ,FST::RELATION('l',1),
									FST::RELATION('n',1), FST::RELATION('m',1) ,FST::RELATION('o',1), FST::RELATION('p',1),
									FST::RELATION('q',1), FST::RELATION('r',1), FST::RELATION('s',1), FST::RELATION('t',1),
									FST::RELATION('u',1), FST::RELATION('v',1), FST::RELATION('w',1), FST::RELATION('x',1),
									FST::RELATION('y',1),FST::RELATION('z',1)),
						FST::NODE()
					},
					// 18 (1|2|3|4|5|6|7|8|9|0)*
					{
						lexeme,
						2,
						FST::NODE(20, FST::RELATION('1',0), FST::RELATION('2',0), FST::RELATION('3',0), FST::RELATION('4',0),
									FST::RELATION('5',0), FST::RELATION('6',0), FST::RELATION('7',0), FST::RELATION('8',0),
									FST::RELATION('9',0),FST::RELATION('0',0),
									FST::RELATION('1',1), FST::RELATION('2',1), FST::RELATION('3',1), FST::RELATION('4',1),
									FST::RELATION('5',1), FST::RELATION('6',1), FST::RELATION('7',1), FST::RELATION('8',1),
									FST::RELATION('9',1),FST::RELATION('0',1)),
						FST::NODE()
					},
					// 19
					{
						lexeme,
						3,
						FST::NODE(1, FST::RELATION('-', 1)),
						FST::NODE(20, FST::RELATION('1',1), FST::RELATION('2',1), FST::RELATION('3',1), FST::RELATION('4',1),
									FST::RELATION('5',1), FST::RELATION('6',1), FST::RELATION('7',1), FST::RELATION('8',1),
									FST::RELATION('9',1),FST::RELATION('0',1),
									FST::RELATION('1',2), FST::RELATION('2',2), FST::RELATION('3',2), FST::RELATION('4',2),
									FST::RELATION('5',2), FST::RELATION('6',2), FST::RELATION('7',2), FST::RELATION('8',2),
									FST::RELATION('9',2),FST::RELATION('0',2)),
						FST::NODE()
					},
					// 20 8x(1|2|3|4|5|6|7|8|9|0)* | 2x(1|2|3|4|5|6|7|8|9|0)*
					{
						lexeme,
						3,
						FST::NODE(20, FST::RELATION('1',0), FST::RELATION('2',0), FST::RELATION('3',0), FST::RELATION('3',0),
									FST::RELATION('5',0), FST::RELATION('6',0), FST::RELATION('7',0), FST::RELATION('8',0),
									FST::RELATION('9',0),FST::RELATION('0',0),
									FST::RELATION('1',1), FST::RELATION('2',1), FST::RELATION('2',1), FST::RELATION('4',1),
									FST::RELATION('5',1), FST::RELATION('6',1), FST::RELATION('7',1), FST::RELATION('8',1),
									FST::RELATION('9',1),FST::RELATION('0',1)),
						FST::NODE(2, FST::RELATION('b', 2), FST::RELATION('o', 2)),
						FST::NODE()
					},
					// 21
					{
						lexeme,
						4,
						FST::NODE(1, FST::RELATION('-', 1)),
						FST::NODE(20, FST::RELATION('1',1), FST::RELATION('2',1), FST::RELATION('3',1), FST::RELATION('4',1),
									FST::RELATION('5',1), FST::RELATION('6',1), FST::RELATION('7',1), FST::RELATION('8',1),
									FST::RELATION('9',1),FST::RELATION('0',1),
									FST::RELATION('1',2), FST::RELATION('2',2), FST::RELATION('3',2), FST::RELATION('4',2),
									FST::RELATION('5',2), FST::RELATION('6',2), FST::RELATION('7',2), FST::RELATION('8',2),
									FST::RELATION('9',2),FST::RELATION('0',2)),
						FST::NODE(2, FST::RELATION('b', 3), FST::RELATION('o', 3)),
						FST::NODE()
					}
				};
				// wasChanged может быть установлен в true, если были считаны символ или символьная строка
				if (!wasChanged)
				{
					if (lastToken == LEX_FUNCTION && symbol == START_OF_PARAMETRS)
						areParametrs = true;
					if (symbol == START_OF_PARAMETRS)
						type = IT::F;
					else if (areParametrs)
						type = IT::P;
					else
						type = IT::V;
					for (int i = 0; i < FST_ARRAY_SIZE; i++)
						if (FST::execute(fstArray[i]))
						{
							switch (i)
							{
							case 0:						// number
								datatype = IT::NUM;
								break;
							case 1:						// function
								type = IT::F;
								break;
							case 2:						// symbol
								datatype = IT::SYM;
								break;
							case 18: case 19: case 20: case 21:			// 10x... || 8x... || 2x... || ...
								type = IT::L;
								datatype = IT::NUM;
								break;
							}
							token = lexArray[i];
							wasChanged = true;
							break;
						}
					if (areParametrs && symbol == END_OF_PARAMETERS)
						areParametrs = false;
					if (token == LEX_MAIN)
					{
						if (hasMain)
							throw ERROR_THROW_IN(205, strCount, position);
						hasMain = true;
					}
					if (token == LEX_RETURN)
					{
						if (inIf)
							ifRet = true;
						else if (inElse)
							elseRet = true;
						else
							wasFuncRet = true;
					}
					if (token == LEX_FUNCTION || token == LEX_MAIN)
					{
						//if((wasElse && wasIf && ifRet && elseRet))
						if (wasElse && wasIf)
						{
							if (!ifRet || !elseRet)
							{
								e = ERROR_THROW_IN(207, strCount - 1, 0);
								Log::WriteError(log, e);
								wasError = true;
							}
						}
						else if (!wasFuncRet)
						{
							e = ERROR_THROW_IN(207, strCount - 1, 0);
							Log::WriteError(log, e);
							wasError = true;
						}
						wasElse = false;
						wasIf = false;
						ifRet = false;
						elseRet = false;
						wasFuncRet = false;
						/*if (wasFuncRet)
							wasFuncRet = false;
						else
						{
							e = ERROR_THROW(207, strCount - 1, 0);
							Log::WriteError(log, e);
							wasError = true;
						}*/
					}
					if (token == LEX_IF)
					{
						inIf = true;
						wasElse = false;
						ifRet = false;
						elseRet = false;
						wasIf = true;
						wasElse = false;
					}
					if (token == LEX_ELSE)
					{
						inElse = true;
						wasElse = true;
					}
				}
				// Не выводим лексему, если предыдущий символ был сепаратором(два последовательно идущих сепаратора)
				if (!wasSeparator)
				{
					// Если wasChanged так и остался в false, то лексема не определена
					if (!wasChanged)
					{
						token = LEX_UNDEF;
						e = ERROR_THROW_IN(202, strCount, position);
						Log::WriteError(log, e);
						wasError = true;
					}
					if (token == LEX_EQUAL || token == LEX_ASIGNMENT)		// Заполнение поля operptorSymbol если токен распознан как операция
						strcpy_s(operation, lexeme);
					else
						strcpy_s(operation, empty);
					if (token == LEX_ID || token == LEX_LITERAL)
					{
						memset(id, 0, ID_MAXSIZE);
						if (token == LEX_ID)
						{
							for (int i = 0; i < (ID_MAXSIZE - 1); i++)
								id[i] = lexeme[i];
							id[ID_MAXSIZE - 1] = '\0';
						}
						else
						{
							sprintf_s(lexNumBuf, "%d", literalCount++);
							id[0] = START_OF_LITERAL;
							for (int i = 0; i < ID_MAXSIZE; i++)
								id[i + 1] = lexNumBuf[i];
						}
						idxTI = IT::IsId(idtable, id, areaOfVisibility);
						if (lastToken == LEX_SYMBOL && idxTI != TI_NULLIDX)
							throw ERROR_THROW_IN(204, strCount, position);
						if (type == IT::F && idxTI == TI_NULLIDX)
						{
							idxTI = IT::IsId(idtable, id, FUNCTION_AREA);
							if (areaOfVisibility != FUNCTION_AREA && idxTI == TI_NULLIDX && !IT::IsLibFunc(id))
								throw ERROR_THROW_IN(203, strCount, position);	// Функция не объявлена
						}
						if (idxTI == TI_NULLIDX)
						{
							ITTempEntry = IT::FillEntry(lextable.size, id, datatype, type, lexeme, areaOfVisibility);
							idxTI = idtable.size;
							if (symbol == START_OF_INDEX || arrayLiteral)
							{
								ITTempEntry.isArray = true;
								arrayLiteral = false;
							}
							IT::Add(idtable, ITTempEntry);
						}
						tempEntry = LT::FillEntry(token, strCount, idxTI, operation);
					}
					else
						tempEntry = LT::FillEntry(token, strCount, LT_TI_NULLIDX, operation);
					if (token != LEX_UNDEF)
						LT::Add(lextable, tempEntry);
					lastToken = token;
				}
				// Входим в область видимости по символу ( и по main
				if ((symbol == START_OF_PARAMETRS && areaOfVisibility == 0) || token == LEX_MAIN)
				{
					areaOfVisibility = ++baseArea;
				}
				// Выходим из области видимости по end
				if (token == LEX_END)
				{
					areaOfVisibility = FUNCTION_AREA;
				}
				// Определение сепараторов, которые должны выводиться в таблицу лексем
				if (IsLexSeparator(symbol))
				{
					if (symbol == END_OF_SUBAREA)
					{
						if (inIf)
							inIf = false;
						if (inElse)
							inElse = false;
					}
					strcpy_s(operation, empty);
					tempEntry = LT::FillEntry(symbol, strCount, TI_NULLIDX, operation);
					LT::Add(lextable, tempEntry);
				}
				// Определение начала символа или символьной строки
				if (IsLiteralSeparator(symbol))
					isLiteral = true;
				// Подсчет строк
				if (symbol == END_OF_INSTRUCTION)
				{
					strCount++;
					position = 0;
				}
				memset(lexeme, 0, TI_STR_MAXSIZE);
				lexemeSize = 0;
				wasChanged = false;
				wasSeparator = true;
				continue;
			}
			wasSeparator = false;
			// встреча символов ' и ", обозначающих конец символа или символьной строки
			if (IsLiteralSeparator(symbol))
			{
				if (symbol == '"')
					arrayLiteral = true;
				isLiteral = false;
				token = LEX_LITERAL;
				wasChanged = true;
				type = IT::L;
				datatype = IT::SYM;
				continue;
			}
			lexeme[lexemeSize] = symbol;
			lexemeSize++;
		}
		if (!hasMain)
			throw ERROR_THROW(206);
		return wasError;
	}

	bool IsSeparator(char symbol)
	{
		if (symbol == ' ' || symbol == '\n' || symbol == '\'' || symbol == ',' || symbol == '[' || symbol == ']' || symbol == '(' || symbol == ')' || symbol == '"' || symbol == '{' || symbol == '}' || symbol == '\t')
			return true;
		return false;
	}
	bool IsLexSeparator(char symbol)
	{
		if (symbol == ',' || symbol == '[' || symbol == ']' || symbol == '(' || symbol == ')' || symbol == '{' || symbol == '}')
			return true;
		return false;
	}
	bool IsLiteralSeparator(char symbol)
	{
		if (symbol == '\'' || symbol == '"')
			return true;
		return false;
	}
	
}