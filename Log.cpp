#include "Log.h"
namespace Log
{
	LOG getlog(wchar_t logfile[])
	{
		LOG log;
		log.stream = new std::ofstream;
		log.stream->open(logfile);
		if (!log.stream->is_open())
		{
			throw ERROR_THROW(112);
		}
		wcscpy_s(log.logfile, logfile);
		return log;
	}
	void WriteInfo(LOG log, char* c)
	{
		*(log.stream) << c << '\n';
		log.stream->flush();
	}
	void WriteInfo(LOG log, const char* c)
	{
		*(log.stream) << c << '\n';
		log.stream->flush();
	}
	void WriteInfo(LOG log, const char* c, int a)
	{
		*(log.stream) << c << a<< '\n';
		log.stream->flush();
	}
	void WriteLine(LOG log, const char* c, ...)
	{
		va_list args;
		va_start(args, c);
		const char* buf = c;
		*(log.stream) << buf;
		while ((buf = va_arg(args, char*)) != "")
		{
			*(log.stream) << buf;
		}
		va_end(args);
		*(log.stream) <<'\n';
		log.stream->flush();
	}
	void WriteLine(LOG log, const wchar_t* c, ...)
	{
		const wchar_t** ptr = &c;
		char buf[100];
		while (*ptr != L"")
		{
			wcstombs(buf, *ptr++, sizeof(buf));
			*(log.stream) << buf;
			++ptr;
		}
		log.stream->flush();
	}
	void WriteLog(LOG log)
	{
		*(log.stream) << "---- Протокол ----\nДата: ";
		time_t now = time(0);
		tm date;
		localtime_s(&date, &now);
		char buf[100];
		strftime(buf, sizeof(buf), "%c", &date);
		*(log.stream) << buf << std::endl;
		log.stream->flush();
	}
	void WriteParm(LOG log, Parm::PARM parm)
	{
		*(log.stream) << "---- Параметры ----" << std::endl;
		char buf[100];
		wcstombs(buf, parm.log, sizeof(parm.log));
		*(log.stream) << "-log: " << buf << std::endl;
		wcstombs(buf, parm.out, sizeof(parm.out));
		*(log.stream) << "-out: " << buf << std::endl;
		wcstombs(buf, parm.in, sizeof(parm.in));
		*(log.stream) << "-in: " << buf << std::endl;
	}
	void WriteIn(LOG log, In::IN in)
	{
		*(log.stream) << "---- Исходные данные ----" << std::endl;
		*(log.stream) <<"Количество символов: " <<in.size << std::endl;
		*(log.stream) <<"Проигнорировано    : " <<in.ignor << std::endl;
		*(log.stream) <<"Количество строк   : " <<in.lines << std::endl;
	}
	void WriteError(LOG log, Error::ERROR error)
	{
		if (error.inext.line < 0)
		{
			*(log.stream) << "Ошибка " << error.id << " : " << error.message << std::endl;
			std::cout << "Ошибка " << error.id << " : " << error.message << std::endl;
		}
		else
		{
			*(log.stream) << "Ошибка " << error.id << " : " << error.message << ", строка " << error.inext.line << ", позиция " << error.inext.col << std::endl;
			std::cout << "Ошибка " << error.id << " : " << error.message << ", строка " << error.inext.line << ", позиция " << error.inext.col << std::endl;
		}
	}
	void Close(LOG log)
	{
		log.stream->close();
	}
}