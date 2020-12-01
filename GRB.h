#pragma once
#include "Error.h"
#include <string.h>
typedef short GRBALPHABET;      // символы алфавита грамматики терминалы > 0, нетерминалы < 0
namespace GRB
{
    struct Rule                 // правило в грамматике Грейбах
    {
        GRBALPHABET nn;             // нетерминал(левый символ правила) < 0
        int iderror;                // идентификатор диагностического сообщения
        short size;                 // количество цепочек - правых частей правила
        struct Chain                // цепочка(правая часть правила)
        {
            short size;                     // длина цепочки
            GRBALPHABET* nt;                // цепочка терминалов(>0) и нетерминалов(<0)
            Chain() {
                size = 0; nt = 0;
            };
            Chain(short psize, GRBALPHABET s, ...); // количество символов в цепочке, символы(терминал и нетерминал)
            char* getCChain(char* b);              // получить правую сторону правила
            static GRBALPHABET T(char t) {
                return GRBALPHABET(t);
            };      // терминал
            static GRBALPHABET N(char n) {
                return -GRBALPHABET(n);
            };     // нетерминал
            static bool isT(GRBALPHABET s) {
                return s > 0;
            };             // терминал?
            static bool isN(GRBALPHABET s) {
                return !isT(s);
            };           // нетерминал?
            static char alphabet_to_char(GRBALPHABET s) {
                return isT(s) ? char(s) : char(-s);
            };  // GRBALPHABET->char
        }*chains;              // массив цепочек - правых частей правила
        Rule() {
            nn = 0x00; size = 0;
        }
        Rule(GRBALPHABET pnn, int iderror, short psize, Chain c, ...);  // нетерминал, идентификатор диагностического сообщения
                                                                        // количество цепочек - правых частей правила, множество цепочек - правых частей правила
        char* getCRule(char* b, short nchain);      // получить правило в виде N->цепочка (для распечатки)
                                                    // буфер, номер цепочки (правой части) в правиле
        short /*Rule::*/getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j);  // получить следующую за j подходящую цепочку, вернуть ее номер или -1
                                                    // первый символ цепочки, возвращаемая цепочка, номер цепочки
    };

    struct Greibach      // Грамматика Грейбах
    {
        short size;     // Количество правил
        GRBALPHABET startN;     // стартовый символ
        GRBALPHABET stbottomT;   // дно стека
        Rule* rules;            // множество правил
        Greibach() {
            short size = 0; startN = 0; stbottomT = 0; rules = 0;
        };
        Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottomT, short psize, Rule r, ...);
        short getRule(GRBALPHABET pnn, Rule& prule);    // Получить правило, возвращается номер парвила или -1
        Rule getRule(short n);  // Получить правило по номеру
    };

    Greibach getGreibach();       // Получить грамматику
}