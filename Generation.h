#pragma once
#include "MFST.h"
#define ASM_FILE_PATH	"GVAAsm.asm"
#define MAIN_FUNC		"main"
#define PARM_SYMBOL		'@'
#define RIGHT_BRACE		'}'
#define EQUAL			"="
#define NOT_EQUAL		"#"
#define LESSER			"<"
#define GREATER			">"
#define GE				"GE"
#define LE				"LE"
#define ELSE_RULE				5
#define START_SYMBOL_RULE		0
#define START_SYMBOL_FUNC_RULE	0
#define START_SYMBOL_MAIN_RULE	1
#define FUNC_PARAMS_RULE		3
#define RECURS_PARM_RULE		0
#define OPERATOR_RULE			1
#define EXP_ARR_RULE			3
#define NOT_RECURS_ID_RULE		1
#define NOT_RECURS_ARR_ID_RULE	2
namespace Gen
{
	void Generate(std::ofstream* stream, IT::IdTable idtable, LT::LexTable lextable, MFST::Mfst mfst);
	void WriteHeader(std::ofstream* stream);
	void WriteProto(std::ofstream* stream, IT::IdTable idtable, LT::LexTable lextable, MFST::Mfst mfst);
	void ConstGeneration(std::ofstream* stream, IT::IdTable idtable);
	void DataGeneration(std::ofstream* stream, IT::IdTable idtable, MFST::Mfst mfst);
	void CodeGeneration(std::ofstream* stream, IT::IdTable idtable, LT::LexTable lextable, MFST::Mfst mfst);
}