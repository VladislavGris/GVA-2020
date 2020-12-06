//#include "stdafx.h"
#include "Error.h"
#include <cstring>
namespace Error
{
	// серии ошибок: 0 - 99 - системные ошибки
	//				100 - 109 - ошибки параметров
	//				110 - 119 - ошибки открытия и чтения файлов
	ERROR errors[ERROR_MAX_ENTRY] = // таблица ошибок
	{
		ERROR_ENTRY(0, "Недопустимый код ошибки"),	//код ошибки вне диапазона 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1, "Системный сбой"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),ERROR_ENTRY_NODEF(6),ERROR_ENTRY_NODEF(7),ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10),ERROR_ENTRY_NODEF10(20),ERROR_ENTRY_NODEF10(30),ERROR_ENTRY_NODEF10(40),ERROR_ENTRY_NODEF10(50),ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101),ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111, "Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY_NODEF(113),ERROR_ENTRY_NODEF(114),ERROR_ENTRY_NODEF(115),ERROR_ENTRY_NODEF(116),ERROR_ENTRY_NODEF(117),ERROR_ENTRY_NODEF(118),ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF10(120),ERROR_ENTRY_NODEF10(130),ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150),ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY(200, "Переполнение таблицы лексем"),ERROR_ENTRY(201, "Переполнение таблицы идентификаторов"), ERROR_ENTRY(202, "Неопределенная лексема"),ERROR_ENTRY(203, "Отсутствует объявление функции"),
		ERROR_ENTRY(204, "Переменная с таким именем уже задана в текущей области видимости"),ERROR_ENTRY_NODEF(205),ERROR_ENTRY_NODEF(206),ERROR_ENTRY_NODEF(207),ERROR_ENTRY_NODEF(208),ERROR_ENTRY_NODEF(209),
		ERROR_ENTRY_NODEF10(210),ERROR_ENTRY_NODEF10(220),ERROR_ENTRY_NODEF10(230),ERROR_ENTRY_NODEF10(240),ERROR_ENTRY_NODEF10(250),ERROR_ENTRY_NODEF10(260),ERROR_ENTRY_NODEF10(270),ERROR_ENTRY_NODEF10(280),ERROR_ENTRY_NODEF10(290),
		ERROR_ENTRY(300, "Неверная структура программы"),ERROR_ENTRY(301, "Ошибочный оператор"),ERROR_ENTRY(302, "Ошибка в выражении"),ERROR_ENTRY(303, "Ошибка в параметрах функции"),
		ERROR_ENTRY(304, "Ошибка в параметрах вызываемой функции"),ERROR_ENTRY(305, "Ошибка в конструкции условного оператора"),ERROR_ENTRY(306, "Работа синтаксического анализатора завершена с ошибками"),
		ERROR_ENTRY_NODEF(307),ERROR_ENTRY_NODEF(308),ERROR_ENTRY_NODEF(309),ERROR_ENTRY_NODEF10(310), ERROR_ENTRY_NODEF10(320),ERROR_ENTRY_NODEF10(330),ERROR_ENTRY_NODEF10(340),
		ERROR_ENTRY_NODEF10(350), ERROR_ENTRY_NODEF10(360),ERROR_ENTRY_NODEF10(370),ERROR_ENTRY_NODEF10(380),ERROR_ENTRY_NODEF10(390),
		ERROR_ENTRY(400, "Несоответствие типов операндов в выражении условного оператора"),ERROR_ENTRY(401, "Тип возвращаемого значения не соответствует типу возвращаемого значения функиции"),ERROR_ENTRY(402, "Использование необъявленной переменной в условном операторе"),ERROR_ENTRY(403, "Использование в условном операторе переменной, которой не присвоено значение"),ERROR_ENTRY(404, "Размер массива должен быть указан при помощи целочисленного значения"),ERROR_ENTRY(405, "Несоответствие типа переменной и значения, присваиваемого ей"),ERROR_ENTRY(406, "Индекс элемента массива должен быть указан при помощи целочисленного значения"),ERROR_ENTRY(407, "Попытка присвоить значение необъявленной переменной"),
		ERROR_ENTRY(408, "Попытка присвоить значение массива переменной, которая не является массивом"),ERROR_ENTRY(409, "Попытка присвоить массиву значение, не являющееся массивом"),ERROR_ENTRY(410, "Индекс массива должен быть задан при поиощи целочисленного значения"),
		ERROR_ENTRY(411, "Количество формальных и фактических параметров функции не совпадает"),ERROR_ENTRY(412, "Несоответствие типов формального и фактического параметров"),ERROR_ENTRY(413, "Попытка передачи массива в качестве фактического параметра, когда формальный параметр массивом не является"),ERROR_ENTRY(414, "Попытка передачи переменной, которая не является массивом, в качестве фактического параметра, когда формальный параметр является массивом"),
		ERROR_ENTRY_NODEF(415),ERROR_ENTRY_NODEF(416),ERROR_ENTRY_NODEF(417),ERROR_ENTRY_NODEF(418),ERROR_ENTRY_NODEF(419), ERROR_ENTRY_NODEF10(420),ERROR_ENTRY_NODEF10(430),ERROR_ENTRY_NODEF10(440),ERROR_ENTRY_NODEF10(450),ERROR_ENTRY_NODEF10(460),ERROR_ENTRY_NODEF10(470),
		ERROR_ENTRY_NODEF10(480),ERROR_ENTRY_NODEF10(490),ERROR_ENTRY_NODEF100(500),ERROR_ENTRY_NODEF100(600),ERROR_ENTRY_NODEF100(700),ERROR_ENTRY_NODEF100(800),ERROR_ENTRY_NODEF100(900)
	};
	ERROR geterror(int id)
	{
		ERROR e;
		if (0 < id < ERROR_MAX_ENTRY)
		{
			e.id = errors[id].id;
			strcpy_s(e.message, errors[id].message);
		}
		else
		{
			e.id = errors[0].id;
			strcpy_s(e.message, errors[0].message);
		}
		return e;
	}
	ERROR geterrorin(int id, int line = -1, int col = -1)
	{
		ERROR e;
		if (0 < id < ERROR_MAX_ENTRY)
		{
			e.id = errors[id].id;
			strcpy_s(e.message, errors[id].message);
			e.inext.line = line;
			e.inext.col = col;
		}
		else
		{
			e.id = errors[0].id;
			strcpy_s(e.message, errors[0].message);
			e.inext.line = line;
			e.inext.col = col;
		}
		return e;
	}
}