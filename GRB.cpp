#include "GRB.h"
#define GRB_ERROR_SERIES 300
namespace GRB
{
#define NS(n) Rule::Chain::N(n)
#define TS(n) Rule::Chain::T(n)
    Greibach greibach(NS('S'), TS('$'),
        6,
        Rule(NS('S'), GRB_ERROR_SERIES + 0,  // Неверная структура программы
            2,
            Rule::Chain(/*12*/10, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('b'), NS('N'), /*TS('r'), NS('E'),*/ TS('e'), NS('S')),
            Rule::Chain(6, TS('m'), TS('b'), NS('N'), TS('r'), NS('E'), TS('e'))
        ),
        Rule(NS('N'), GRB_ERROR_SERIES + 1,   // Ошибочный оператор
            21,
            Rule::Chain(2, TS('t'), TS('i')),           // Объявление переменной, 01
            Rule::Chain(3, TS('t'), TS('i'), NS('N')),
            Rule::Chain(5, TS('t'), TS('i'), TS('['), NS('E'), TS(']')),            // Объявление массива, 23
            Rule::Chain(6, TS('t'), TS('i'), TS('['), NS('E'), TS(']'), NS('N')),
            Rule::Chain(4, TS('t'), TS('i'), TS('s'), NS('E')),         // Инициализация переменной, 45
            Rule::Chain(5, TS('t'), TS('i'), TS('s'), NS('E'), NS('N')),
            Rule::Chain(7, TS('t'), TS('i'), TS('['), NS('E'), TS(']'), TS('s'), NS('E')),          // Инициализация массива, 67
            Rule::Chain(8, TS('t'), TS('i'), TS('['), NS('E'), TS(']'), TS('s'), NS('E'), NS('N')),
            Rule::Chain(3, TS('i'), TS('s'), NS('E')),          // Присвоение значения переменной, 89
            Rule::Chain(4, TS('i'), TS('s'), NS('E'), NS('N')),
            Rule::Chain(6, TS('i'), TS('['), NS('E'), TS(']'), TS('s'), NS('E')),   // Присвоение значения элементу массива, 1011
            Rule::Chain(7, TS('i'), TS('['), NS('E'), TS(']'), TS('s'), NS('E'), NS('N')),
            Rule::Chain(4, TS('p'), TS('('), NS('E'), TS(')')),          // print(...), 1213
            Rule::Chain(5, TS('p'), TS('('), NS('E'), TS(')'), NS('N')),
            Rule::Chain(10, TS('a'), TS('['), NS('E'), TS('o'), NS('E'), TS(']'), TS('h'), TS('{'), NS('N'), TS('}')),         // if[...]then{...}
            Rule::Chain(11, TS('a'), TS('['), NS('E'), TS('o'), NS('E'), TS(']'), TS('h'), TS('{'), NS('N'), TS('}'), NS('N')),
            Rule::Chain(11, TS('a'), TS('['), NS('E'), TS('o'), NS('E'), TS(']'), TS('h'), TS('{'), NS('N'), TS('}'), NS('V')),
            Rule::Chain(2, TS('r'), NS('E')),
            Rule::Chain(3, TS('r'), NS('E'), NS('N')),
            Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
            Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('N'))
        ),
        Rule(NS('E'), GRB_ERROR_SERIES + 2,   // Ошибка в выражении
            4,
            Rule::Chain(1, TS('i')),
            Rule::Chain(1, TS('l')),
            Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
            Rule::Chain(4, TS('i'), TS('['), NS('E'),TS(']'))
        ),
        Rule(NS('F'), GRB_ERROR_SERIES + 3, // Ошибка в параметрах функции
            4,
            Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F')),
            Rule::Chain(2, TS('t'), TS('i')),
            Rule::Chain(4,TS('t'), TS('i'), TS('['), TS(']')),
            Rule::Chain(6, TS('t'), TS('i'), TS('['), TS(']'), TS(','), NS('F'))
        ),
        Rule(NS('W'), GRB_ERROR_SERIES + 4, // Ошибка в параметрах вызываемой функции
            4,
            Rule::Chain(3, TS('l'), TS(','), NS('W')),
            Rule::Chain(1, TS('i')),
            Rule::Chain(1, TS('l')),
            Rule::Chain(3, TS('i'), TS(','), NS('W'))
        ),
        Rule(NS('V'), GRB_ERROR_SERIES + 5, // Ошибка в конструкции условного оператора
            2,
            //Rule::Chain(12, TS('c'), TS('a'), TS('['), NS('E'), TS('o'), NS('E'), TS(']'), TS('h'), TS('{'), NS('N'), TS('}'), NS('V')),  // else if[...]then{...}
            Rule::Chain(4, TS('c'), TS('{'), NS('N'), TS('}')),             //else{...}
            Rule::Chain(5, TS('c'), TS('{'), NS('N'), TS('}'), NS('N'))
        )
    );
    Rule::Chain::Chain(short psize, GRBALPHABET s, ...)
    {
        nt = new GRBALPHABET[size = psize];
        int* p = (int*)&s;
        for (short i = 0; i < psize; ++i)
            nt[i] = (GRBALPHABET)p[i];
    }
    Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...)
    {
        nn = pnn;
        iderror = piderror;
        chains = new Chain[size = psize];
        Chain* p = &c;
        for (int i = 0; i < size; i++)
            chains[i] = p[i];
    }
    Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottom, short psize, Rule r, ...)
    {
        startN = pstartN;
        stbottomT = pstbottom;
        rules = new Rule[size = psize];
        Rule* p = &r;
        for (int i = 0; i < size; i++)
            rules[i] = p[i];
    }

    Greibach getGreibach() {
        return greibach;
    }
    short Greibach::getRule(GRBALPHABET pnn, Rule& prule)
    {
        short rc = -1;
        short k = 0;
        while (k < size && rules[k].nn != pnn) k++;
        if (k < size)
            prule = rules[rc = k];
        return rc;
    }
    Rule Greibach::getRule(short n)
    {
        Rule rc;
        if (n < size) rc = rules[n];
        return rc;
    }
    char* Rule::getCRule(char* b, short nchain)
    {
        char bchain[200];
        b[0] = Chain::alphabet_to_char(nn);
        b[1] = '-';
        b[2] = '>';
        b[3] = 0x00;
        chains[nchain].getCChain(bchain);
        strcat_s(b, sizeof(bchain) + 5, bchain);
        return b;
    }
    short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j)
    {
        short rc = -1;
        while (j < size && chains[j].nt[0] != t) ++j;
        rc = (j < size ? j : -1);
        if (rc >= 0)
            pchain = chains[rc];
        return rc;
    }
    char* Rule::Chain::getCChain(char* b)
    {
        for (int i = 0; i < size; i++)
            b[i] = Chain::alphabet_to_char(nt[i]);
        b[size] = 0x00;
        return b;
    }
}