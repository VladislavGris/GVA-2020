#pragma once
#include "IT.h"
#include "LT.h"
#include "MFST.h"
#define PARM_SYMBOL	'@'
#define EMPTY		'$'
namespace PN
{
	void ConvertToPolish(IT::IdTable& idtable, LT::LexTable& lextable, MFST::Mfst mfst);
}