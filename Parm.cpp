#include "Parm.h"
#include "Error.h"

namespace Parm
{
	PARM getparm(int argc, _TCHAR* argv[])
	{
		PARM PStr;
		if (argv[1])//задан первый параметр. Не известно, какой именно
		{
			if (wcsstr(argv[1], PARM_IN))//первым параметром является параметр in
			{
				if (wcslen(argv[1] + 4) > PARM_MAX_SIZE)
					throw ERROR_THROW(104);
				wcscpy_s(PStr.in, argv[1] + 4);
				if (argv[2])//задан второй параметр. Либо out, либо log
				{
					if (wcslen(argv[2] + 5) > PARM_MAX_SIZE)
						throw ERROR_THROW(104);
					if (wcsstr(argv[2], PARM_OUT))//второй параметр out
					{
						wcscpy_s(PStr.out, argv[2] + 5);
						if (argv[3])//задан третий параметр. Параметр log
						{
							if (wcslen(argv[3] + 5) > PARM_MAX_SIZE)
								throw ERROR_THROW(104);
							wcscpy_s(PStr.log, argv[3] + 5);
						}
						else//параметр log не задан, устанавливаем значение по умолчанию
						{
							wcscpy_s(PStr.log, PStr.in);
							wcscat_s(PStr.log, PARM_LOG_DEFAULT_EXT);
						}
					}
					else//второй параметр log
					{
						wcscpy_s(PStr.log, argv[2] + 5);
						if (argv[3])//задан 3 параметр. Парметр out
						{
							if (wcslen(argv[3] + 5) > PARM_MAX_SIZE)
								throw ERROR_THROW(104);
							wcscpy_s(PStr.out, argv[3] + 5);
						}
						else//параметр Out не задан
						{
							wcscpy_s(PStr.out, PStr.in);
							wcscat_s(PStr.out, PARM_OUT_DEFAULT_EXT);
						}
					}
				}
				else//не задано параметров, кроме параметра in, устанавливаем значения по умолчанию
				{
					wcscpy_s(PStr.out, PStr.in);
					wcscat_s(PStr.out, PARM_OUT_DEFAULT_EXT);
					wcscpy_s(PStr.log, PStr.in);
					wcscat_s(PStr.log, PARM_LOG_DEFAULT_EXT);
				}
			}
			else if (wcsstr(argv[1], PARM_OUT))//первым параметром является параметр out
			{
				if (wcslen(argv[1] + 5) > PARM_MAX_SIZE)
					throw ERROR_THROW(104);
				wcscpy_s(PStr.out, argv[1] + 5);
				if (argv[2])//задан второй параметр. Либо in, либо log
				{
					if (wcsstr(argv[2], PARM_IN))//второй параметр in
					{
						if (wcslen(argv[2] + 4) > PARM_MAX_SIZE)
							throw ERROR_THROW(104);
						wcscpy_s(PStr.in, argv[2] + 4);
						if (argv[3])//третий параметр log
						{
							if (wcslen(argv[3] + 5) > PARM_MAX_SIZE)
								throw ERROR_THROW(104);
							wcscpy_s(PStr.log, argv[3] + 5);
						}
						else//параметр log не задан
						{
							wcscpy_s(PStr.log, PStr.in);
							wcscat_s(PStr.log, PARM_LOG_DEFAULT_EXT);
						}
					}
					else//второй параметр log
					{
						if (wcslen(argv[2] + 5) > PARM_MAX_SIZE)
							throw ERROR_THROW(104);
						wcscpy_s(PStr.log, argv[2] + 5);
						if (argv[3])//третий параметр in
						{
							if (wcslen(argv[3] + 4) > PARM_MAX_SIZE)
								throw ERROR_THROW(104);
							wcscpy_s(PStr.in, argv[3] + 4);
						}
						else//параметр in не задан
						{
							throw ERROR_THROW(100);
						}
					}
				}
				else//второй параметр не задан. Параметр in не задан, генерируем ошибку
				{
					throw ERROR_THROW(100);
				}
			}
			else//первым параметром является параметр log
			{
				if (wcslen(argv[1] + 5) > PARM_MAX_SIZE)
					throw ERROR_THROW(104);
				wcscpy_s(PStr.log, argv[1] + 5);
				if (argv[2])
				{
					if (wcsstr(argv[2], PARM_IN))//второй параметр in
					{
						if (wcslen(argv[2] + 4) > PARM_MAX_SIZE)
							throw ERROR_THROW(104);
						wcscpy_s(PStr.in, argv[2] + 4);
						if (argv[3])//третий параметр out
						{
							if (wcslen(argv[3] + 5) > PARM_MAX_SIZE)
								throw ERROR_THROW(104);
							wcscpy_s(PStr.out, argv[3] + 5);
						}
						else//параметр out по умолчанию
						{
							wcscpy_s(PStr.out, PStr.in);
							wcscat_s(PStr.out, PARM_OUT_DEFAULT_EXT);
						}
					}
					else//второй параметр out
					{
						if (wcslen(argv[2] + 5) > PARM_MAX_SIZE)
							throw ERROR_THROW(104);
						wcscpy_s(PStr.out, argv[2] + 5);
						if (argv[3])//третий параметр in
						{
							if (wcslen(argv[3] + 4) > PARM_MAX_SIZE)
								throw ERROR_THROW(104);
							wcscpy_s(PStr.in, argv[3] + 4);
						}
						else//параметр in не задан
						{
							throw ERROR_THROW(100);
						}
					}
				}
				else//второй параметр не задан. Отсутствует in
				{
					throw ERROR_THROW(100);
				}
			}
		}
		else//параметр не задан, значит ни один параметр не задан
		{
			throw ERROR_THROW(100);
		}
		return PStr;
	}
}