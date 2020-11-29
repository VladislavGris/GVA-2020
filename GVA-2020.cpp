#include "GVA-2020.h"

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "rus");
	LT::LexTable lextable = LT::Create(LT_MAXSIZE);
	IT::IdTable idtable = IT::Create(TI_MAXSIZE);
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);
		Log::WriteInfo(log, "----Лексический анализ----");
		if (!Lex::ParseAChain(in, lextable, idtable, log))
			Log::WriteInfo(log, "Лексический анализ выполнен успешно");
#ifdef PRINT_TABLES
		LT::PrintLexTable(lextable);
		IT::PrintIDTable(idtable);
#endif
		//Log::WriteInfo(log, "Тест: без ошибок");
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