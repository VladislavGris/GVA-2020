#pragma once
#include "LT.h"
#include "IT.h"
#include "Log.h"
#include "In.h"
#include "FST.h"
#include <iostream>
#include <cstring>
#define END_OF_INSTRUCTION	'\n'
#define FST_ARRAY_SIZE		22
#define START_OF_LITERAL	'l'
#define START_OF_SUBAREA	'{'
#define END_OF_SUBAREA		'}'
#define START_OF_PARAMETRS	'('
#define END_OF_PARAMETERS	')'
#define COMMENTARY			';'
#define START_OF_INDEX		'['
namespace Lex
{
	struct LEX
	{
		LT::LexTable lextable;
		IT::IdTable idtable;
	};
	bool ParseAChain(In::IN in, LT::LexTable& lextable, IT::IdTable& idtable, Log::LOG log);
	bool IsSeparator(char symbol);		// Символ является разделителем
	bool IsLexSeparator(char symbol);	// Символ является разделителем, который должен быть выведен в табилцу лексем
	bool IsLiteralSeparator(char symbol);
	
}