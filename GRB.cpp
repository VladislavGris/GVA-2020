#include "GRB.h"
#define GRB_ERROR_SERIES 600
namespace GRB
{
#define NS(n) Rule::Chain::N(n)
#define TS(n) Rule::Chain::T(n)
    Greibach greibach(NS('S'), TS('$'),
        7,
        Rule(NS('S'), GRB_ERROR_SERIES + 0,  // Неверная структура программы
            2,
            Rule::Chain(/*12*/10, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('b'), NS('N'), /*TS('r'), NS('E'),*/ TS('e'), NS('S')),
            Rule::Chain(6, TS('m'), TS('b'), NS('N'), TS('r'), NS('E'), TS('e'))
        ),
        Rule(NS('N'), GRB_ERROR_SERIES + 1,   // Ошибочный оператор
            19,
            Rule::Chain(2, TS('t'), TS('i')),
            Rule::Chain(3, TS('t'), TS('i'), NS('N')),
            Rule::Chain(5, TS('t'), TS('i'), TS('['), NS('E'), TS(']')),
            Rule::Chain(6, TS('t'), TS('i'), TS('['), NS('E'), TS(']'), NS('N')),
            Rule::Chain(4, TS('t'), TS('i'), TS('s'), NS('E')),
            Rule::Chain(5, TS('t'), TS('i'), TS('s'), NS('E'), NS('N')),
            Rule::Chain(7, TS('t'), TS('i'), TS('['), NS('E'), TS(']'), TS('s'), NS('E')),
            Rule::Chain(8, TS('t'), TS('i'), TS('['), NS('E'), TS(']'), TS('s'), NS('E'), NS('N')),
            Rule::Chain(3, TS('i'), TS('s'), NS('E')),
            Rule::Chain(4, TS('i'), TS('s'), NS('E'), NS('N')),
            Rule::Chain(6, TS('i'), TS('['), NS('E'), TS(']'), TS('s'), NS('E')),
            Rule::Chain(7, TS('i'), TS('['), NS('E'), TS(']'), TS('s'), NS('E'), NS('N')),
            Rule::Chain(4, TS('p'), TS('('), NS('E'), TS(')')),
            Rule::Chain(5, TS('p'), TS('('), NS('E'), TS(')'), NS('N')),
            Rule::Chain(8, TS('a'), TS('['), NS('C'), TS(']'), TS('h'), TS('{'), NS('N'), TS('}')),
            Rule::Chain(9, TS('a'), TS('['), NS('C'), TS(']'), TS('h'), TS('{'), NS('N'), TS('}'), NS('N')),
            Rule::Chain(9, TS('a'), TS('['), NS('C'), TS(']'), TS('h'), TS('{'), NS('N'), TS('}'), NS('V')),
            Rule::Chain(2, TS('r'), NS('E')),
            Rule::Chain(3, TS('r'), NS('E'), NS('N'))
        ),
        Rule(NS('E'), GRB_ERROR_SERIES + 2,   // Ошибка в выражении
            3,
            Rule::Chain(1, TS('i')),
            Rule::Chain(1, TS('l')),
            Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')'))
        ),
        Rule(NS('F'), GRB_ERROR_SERIES + 3, // Ошибка в параметрах функции
            2,
            Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F')),
            Rule::Chain(2, TS('t'), TS('i'))
        ),
        Rule(NS('W'), GRB_ERROR_SERIES + 4, // Ошибка в параметрах вызываемой функции
            4,
            Rule::Chain(3, TS('l'), TS(','), NS('W')),
            Rule::Chain(1, TS('i')),
            Rule::Chain(1, TS('l')),
            Rule::Chain(3, TS('i'), TS(','), NS('W'))
        ),
        Rule(NS('C'), GRB_ERROR_SERIES + 5, // Ошибка в условии оператора if
            4,
            Rule::Chain(3, TS('i'), TS('o'), TS('i')),
            Rule::Chain(3, TS('i'), TS('o'), TS('l')),
            Rule::Chain(3, TS('l'), TS('o'), TS('i')),
            Rule::Chain(3, TS('l'), TS('o'), TS('l'))
        ),
        Rule(NS('V'), GRB_ERROR_SERIES + 6, // Ошибка в конструкции условного оператора
            3,
            Rule::Chain(10, TS('c'), TS('a'), TS('['), NS('C'), TS(']'), TS('h'), TS('{'), NS('N'), TS('}'), NS('V')),
            Rule::Chain(4, TS('c'), TS('{'), NS('N'), TS('}')),
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