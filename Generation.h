#pragma once
#include "MFST.h"
#define ASM_FILE_PATH	"GVAAsm.asm"
#define START_SYMBOL_RULE		0
#define START_SYMBOL_FUNC_RULE	0
#define FUNC_PARAMS_RULE		3
#define NOT_RECURS_ID_RULE		1
#define NOT_RECURS_ARR_ID_RULE	2
namespace Gen
{
	void Generate(std::ofstream* stream, IT::IdTable idtable, LT::LexTable lextable, MFST::Mfst mfst);
	void WriteHeader(std::ofstream* stream, IT::IdTable idtable, LT::LexTable lextable, MFST::Mfst mfst);
	void WriteProto(std::ofstream* stream, IT::IdTable idtable, LT::LexTable lextable, MFST::Mfst mfst);
	void ConstGeneration(std::ofstream* stream, IT::IdTable idtable);
	void DataGeneration(std::ofstream* stream, IT::IdTable idtable, MFST::Mfst mfst);
}