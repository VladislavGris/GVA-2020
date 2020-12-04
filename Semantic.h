#pragma once
#include "Log.h"
#include "IT.h"
#include "LT.h"
#include "MFST.h"

namespace Semantic
{
	void CheckSemantic(Log::LOG log, LT::LexTable& lextable, IT::IdTable& idtable, MFST::Mfst mfst);
}