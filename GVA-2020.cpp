#include "GVA-2020.h"

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "rus");
	Lex::LEX lex;
	lex.lextable = LT::Create(LT_MAXSIZE);
	lex.idtable = IT::Create(TI_MAXSIZE);
	Log::LOG log = Log::INITLOG;
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
		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
		if(e.id >= 200 && e.id < 300)
			Log::WriteInfo(log, "Работа лексического анализатора прервана");
	}
	system("pause");
	return 0;
}