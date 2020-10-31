#include "GVA-2020.h"

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "rus");
	LT::LexTable lextable = LT::Create(2000);
	IT::IdTable idtable = IT::Create(1000);
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);
		Lex::ParseAChain(in, lextable, idtable);
		LT::PrintLexTable(lextable);
		Log::WriteLine(log, "Тест: без ошибок", "");
		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		Log::WriteLine(log, "Тест: с ошибками", "");
		Log::WriteError(log, e);
	}
	system("pause");
	return 0;
}