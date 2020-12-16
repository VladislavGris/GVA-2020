#include "GVA-2020.h"
int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "rus");
	int semanticErrorsCount = 0;
	Lex::LEX lex;
	lex.lextable = LT::Create(LT_MAXSIZE);
	lex.idtable = IT::Create(TI_MAXSIZE);
	Log::LOG log = Log::INITLOG;
	std::ofstream* asmStream = new std::ofstream();
	asmStream->open(ASM_FILE_PATH);
	if (!asmStream->is_open())
		throw ERROR_THROW(113);
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);
		Log::WriteInfo(log, "---- Лексический анализ ----\nНачало работы лексического анализатора");
		if (!Lex::ParseAChain(in, lex.lextable, lex.idtable, log))
			Log::WriteInfo(log, "Лексический анализ выполнен успешно");
		else
			throw ERROR_THROW(208);
#ifdef PRINT_TABLES
		LT::PrintLexTable(lex.lextable);
		IT::PrintIDTable(lex.idtable);
#endif
		LT::PrintToFile(lex.lextable);
		IT::PrintToFile(lex.idtable);

#ifdef MFSTT
		MFST_TRACE_START
#endif
		Log::WriteInfo(log, "---- Синтаксический анализ ----\nНачало работы синтаксического анализатора");
		MFST::Mfst mfst(lex, GRB::getGreibach());
		if (mfst.start(log))
			Log::WriteInfo(log, "Синтаксический анализ выполнен успешно");
		else
			throw ERROR_THROW(306);
		mfst.savededucation();
		mfst.printrules();
		Log::WriteInfo(log, "---- Семантический анализ ----\nНачало работы семантического анализатора");
		Semantic::CheckSemantic(log, lex.lextable, lex.idtable, mfst);
		PN::ConvertToPolish(lex.idtable, lex.lextable, mfst);
		LT::PrintToFile(lex.lextable);
		Log::WriteInfo(log, "---- Генерация кода ----\nНачало работы генератора кода");
		Gen::Generate(asmStream, lex.idtable, lex.lextable, mfst);
		Log::WriteInfo(log, "Генерация кода выполнена успешно. Сгенерирован файл GVAAsm.asm");
		Log::WriteInfo(log, "Работа транслятора завершена без ошибок");
		Log::Close(log);
		asmStream->close();
		std::cout << "Выполнено без ошибок" << std::endl;
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
		Log::WriteInfo(log, "Работа транслятора завершена с ошибками");
	}
	system("pause");
	return 0;
}