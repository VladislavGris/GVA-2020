#pragma once
#include "Log.h"
#include "IT.h"
#include "LT.h"
#include "MFST.h"
#define PARAMETERS		4
#define START_SYMBOL	0
#define FUNC_PARAMS		3
namespace Semantic
{
	void CheckSemantic(Log::LOG log, LT::LexTable& lextable, IT::IdTable& idtable, MFST::Mfst mfst);
}