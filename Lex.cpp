#include "Lex.h"
namespace Lex
{
	void ParseAChain(In::IN in, LT::LexTable& lextable, IT::IdTable& idtable)
	{
		int lexemeSize = 0, strCount = 1, idxTI = LT_TI_NULLIDX, areaOfVisibility = 0, baseArea=0, literalCount = 1;
		char* lexeme = new char[BUF_SIZE], symbol, operation[OPERATOR_FIXSIZE], empty[2] = "", id[ID_MAXSIZE], lexNumBuf[ID_MAXSIZE - 1];
		char token, lastToken = '0';
		const char lexArray[FST_ARRAY_SIZE] = {LEX_NUMBER, LEX_FUNCTION, LEX_SYMBOL, LEX_BEGIN, LEX_IF, LEX_THEN, LEX_RETURN, 
												LEX_ELSE, LEX_END, LEX_MAIN, LEX_PRINT, LEX_ASIGNMENT, LEX_GE,
												LEX_GREATER, LEX_EQUAL, LEX_NOT_EQUAL, LEX_ID, LEX_LITERAL, LEX_LITERAL };
		bool wasSeparator = false, isLiteral = false, wasChanged = false, areParametrs = false;
		IT::IDDATATYPE datatype;
		IT::IDTYPE type;
		LT::Entry tempEntry;
		IT::Entry ITTempEntry;
		memset(lexeme, 0, BUF_SIZE);
		for (int i = 0; i <= in.size; i++)
		{
			symbol = in.text[i];
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
					// 11 < , <-
					{
						lexeme,
						3,
						FST::NODE(2, FST::RELATION('<', 2), FST::RELATION('<', 1)),
						FST::NODE(1, FST::RELATION('-', 2)),
						FST::NODE()
					},
					// 12 GE , LE
					{
						lexeme,
						3,
						FST::NODE(2, FST::RELATION('G', 1), FST::RELATION('L', 1)),
						FST::NODE(1, FST::RELATION('E', 2)),
						FST::NODE()
					},
					// 13 >
					{
						lexeme,
						2,
						FST::NODE(1, FST::RELATION('>',1)),
						FST::NODE()
					},
					// 14 =
					{
						lexeme,
						2,
						FST::NODE(1, FST::RELATION('=',1)),
						FST::NODE()
					},
					// 15 #
					{
						lexeme,
						2,
						FST::NODE(1, FST::RELATION('#',1)),
						FST::NODE()
					},
					// 16 identifier
					{
						lexeme,
						2,
						FST::NODE(104 ,FST::RELATION('a',0), FST::RELATION('b',0), FST::RELATION('c',0), FST::RELATION('d',0),
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
									FST::RELATION('y',1),FST::RELATION('z',1),
									FST::RELATION('A',0), FST::RELATION('B',0), FST::RELATION('C',0), FST::RELATION('D',0),
									FST::RELATION('E',0), FST::RELATION('F',0), FST::RELATION('G',0), FST::RELATION('H',0),
									FST::RELATION('I',0), FST::RELATION('J',0), FST::RELATION('K',0) ,FST::RELATION('L',0),
									FST::RELATION('N',0), FST::RELATION('M',0) ,FST::RELATION('O',0), FST::RELATION('P',0),
									FST::RELATION('Q',0), FST::RELATION('R',0), FST::RELATION('S',0), FST::RELATION('T',0),
									FST::RELATION('U',0), FST::RELATION('V',0), FST::RELATION('W',0), FST::RELATION('X',0),
									FST::RELATION('Y',0),FST::RELATION('Z',0),
									FST::RELATION('A',1), FST::RELATION('B',1), FST::RELATION('C',1), FST::RELATION('D',1),
									FST::RELATION('E',1), FST::RELATION('F',1), FST::RELATION('G',1), FST::RELATION('H',1),
									FST::RELATION('I',1), FST::RELATION('J',1), FST::RELATION('K',1) ,FST::RELATION('L',1),
									FST::RELATION('N',1), FST::RELATION('M',1) ,FST::RELATION('O',1), FST::RELATION('P',1),
									FST::RELATION('Q',1), FST::RELATION('R',1), FST::RELATION('S',1), FST::RELATION('T',1),
									FST::RELATION('U',1), FST::RELATION('V',1), FST::RELATION('W',1), FST::RELATION('X',1),
									FST::RELATION('Y',1),FST::RELATION('Z',1)),
						FST::NODE()
					},
					// 17 10x(1|2|3|4|5|6|7|8|9|0)*
					{
						lexeme,
						5,
						FST::NODE(1, FST::RELATION('1',1)),
						FST::NODE(1, FST::RELATION('0',2)),
						FST::NODE(1, FST::RELATION('x',3)),
						FST::NODE(20, FST::RELATION('1',4), FST::RELATION('2',4), FST::RELATION('3',4), FST::RELATION('4',4),
									FST::RELATION('5',4), FST::RELATION('6',4), FST::RELATION('7',4), FST::RELATION('8',4),
									FST::RELATION('9',4),FST::RELATION('0',4),
									FST::RELATION('1',3), FST::RELATION('2',3), FST::RELATION('3',3), FST::RELATION('4',3),
									FST::RELATION('5',3), FST::RELATION('6',3), FST::RELATION('7',3), FST::RELATION('8',3),
									FST::RELATION('9',3),FST::RELATION('0',3)),
						FST::NODE()
					},
					// 18 8x(1|2|3|4|5|6|7|8|9|0)* | 2x(1|2|3|4|5|6|7|8|9|0)*
					{
						lexeme,
						4,
						FST::NODE(2, FST::RELATION('8',1), FST::RELATION('2', 1)),
						FST::NODE(1, FST::RELATION('x',2)),
						FST::NODE(20, FST::RELATION('1',3), FST::RELATION('2',3), FST::RELATION('3',3), FST::RELATION('3',3),
									FST::RELATION('5',3), FST::RELATION('6',3), FST::RELATION('7',3), FST::RELATION('8',3),
									FST::RELATION('9',3),FST::RELATION('0',3),
									FST::RELATION('1',2), FST::RELATION('2',2), FST::RELATION('2',2), FST::RELATION('4',2),
									FST::RELATION('5',2), FST::RELATION('6',2), FST::RELATION('7',2), FST::RELATION('8',2),
									FST::RELATION('9',2),FST::RELATION('0',2)),
						FST::NODE()
					}
				};
				// wasChanged может быть установлен в true, если были считаны символ или символьная строка
				if (!wasChanged)
				{
					if (lastToken == LEX_FUNCTION && symbol == START_OF_PARAMETRS)
						areParametrs = true;
					if (areParametrs && symbol == END_OF_PARAMETERS)
						areParametrs = false;
					if (symbol == START_OF_PARAMETRS)
						type = IT::F;
					for (int i = 0; i < FST_ARRAY_SIZE; i++)
						if (FST::execute(fstArray[i]))
						{
							switch (i) 
							{
							case 0:						// number
								datatype = IT::NUM;
								if (areParametrs)
									type = IT::P;
								else
									type = IT::V;
								break;
							case 1:						// function
								type = IT::F;
								break;
							case 2:						// symbol
								datatype = IT::SYM;
								if (areParametrs)
									type = IT::P;
								else
									type = IT::V;
								break;
							case 17: case 18:			// 10x... || 8x... || 2x...
								type = IT::L;
								datatype = IT::NUM;
								break;
							}
							token = lexArray[i];
							wasChanged = true;
							break;
						}
					
				}
				// Если wasChanged так и остался в false, то лексема не определена
				// СГЕНЕРИРОВАТЬ ОШИБКУ
				if (!wasChanged)
					token = LEX_UNDEF;
				lastToken = token;
				// Не выводим лексему, если предыдущий символ был сепаратором(два последовательно идущих сепаратора)
				if (!wasSeparator)
				{
					if (token == LEX_EQUAL)		// Заполнение поля operptorSymbol если токен распознан как операция
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
						// СГЕНЕРИРОВАТЬ ИСКЛЮЧЕНИЕ ЕСЛИ ФУНКЦИИ НЕ ОБЪЯВЛЕНО В ОБЛАСТИ
						if (type == IT::F && idxTI == TI_NULLIDX)
							idxTI = IT::IsId(idtable, id, FUNCTION_AREA);
						if (idxTI == TI_NULLIDX)
						{
							ITTempEntry = IT::FillEntry(lextable.size, id, datatype, type, areaOfVisibility);
							idxTI = idtable.size;
							IT::Add(idtable, ITTempEntry);
						}
						tempEntry = LT::FillEntry(token, strCount, idxTI, operation);
					}
					else
						tempEntry = LT::FillEntry(token, strCount, LT_TI_NULLIDX, operation);
					LT::Add(lextable, tempEntry);
				}
				// Входим в область видимости по символу ( и по main
				if ((symbol == START_OF_PARAMETRS && areaOfVisibility == 0) || token == LEX_MAIN)
				{
					areaOfVisibility = ++baseArea;
				}
				// Выходим из области видимости по end
				if (token == LEX_END)
				{
					areaOfVisibility = 0;
				}
				// Определение сепараторов, которые должны выводиться в таблицу лексем
				if (IsLexSeparator(symbol))
				{
					strcpy_s(operation, empty);
					tempEntry = LT::FillEntry(symbol, strCount, TI_NULLIDX, operation);
					LT::Add(lextable, tempEntry);
				}
				// Определение начала символа или символьной строки
				if (IsLiteralSeparator(symbol))
					isLiteral = true;
				// Подсчет строк
				if (symbol == END_OF_INSTRUCTION)
					strCount++;
				memset(lexeme, 0, BUF_SIZE);
				lexemeSize = 0;
				wasChanged = false;
				wasSeparator = true;
				continue;
			}
			wasSeparator = false;
			// встреча символов ' и ", обозначающих конец символа или символьной строки
			if (IsLiteralSeparator(symbol))
			{
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
	}

	bool IsSeparator(char symbol)
	{
		if (symbol == ' ' || symbol == '\n' || symbol == '\'' || symbol == ',' || symbol == '[' || symbol == ']' || symbol == '(' || symbol == ')' || symbol == '"' || symbol == '{' || symbol == '}')
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