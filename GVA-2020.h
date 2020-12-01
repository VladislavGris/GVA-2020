#pragma once
#include <iostream>
#include "Error.h"
#include "In.h"
#include "Log.h"
#include "Parm.h"
#include "FST.h"
#include "LT.h"
#include "IT.h"
#include "Lex.h"
#include "MFST.h"
#include "GRB.h"
//#define PRINT_TABLES
#define MFST_TRACE_START	std::cout<<std::setw(4)<<std::left<<"Шаг:"\
								<<std::setw(20)<<std::left<<" Правило"\
								<<std::setw(30)<<std::left<<" Входная лента"\
								<<std::setw(20)<<std::left<<" Стек"\
								<<std::endl;