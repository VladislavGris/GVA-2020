#pragma once
#include <stack>
#include <iostream>
#include <iomanip>
#include "GRB.h"
#include "Lex.h"
#define MFSTT
#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3
typedef std::stack<short>   MFSTSTACK;

namespace MFST
{
    struct MfstState
    {
        short lenta_position;
        short nrule;
        short nrulechain;
        MFSTSTACK st;
        MfstState();
        MfstState(
            short pposition,
            MFSTSTACK pst,
            short pnrulechain
        );
        MfstState(
            short pposition,
            MFSTSTACK pst,
            short pnrule,
            short pnrulechain
        );
    };
    struct Mfst
    {
        enum RC_STEP {
            NS_OK,
            NS_NORULE,
            NS_NORULECHIN,
            NS_ERROR,
            TS_OK,
            TS_NOK,
            LENTA_END,
            SURPRISE
        };
        struct MfstDiagnosis
        {
            short lenta_position;
            RC_STEP rc_step;
            short nrule;
            short nrule_chain;
            MfstDiagnosis();
            MfstDiagnosis(
                short plenta_position,
                RC_STEP prc_step,
                short pnrule,
                short pnrule_chin
            );
        } diagnosis[MFST_DIAGN_NUMBER];

        GRBALPHABET* lenta;
        short lenta_position;
        short nrule;
        short nrulechain;
        short lenta_size;
        GRB::Greibach grebach;
        Lex::LEX lex;
        MFSTSTACK st;
        std::stack<MfstState> storestate;
        Mfst();
        Mfst(
            Lex::LEX plex,
            GRB::Greibach pgrebach
        );
        char* getCst(char* buf);
        char* getCLenta(char* buf, short pos, short n = 25);
        char* getDiagnosis(short n, char* buf);
        bool savestate();
        bool reststate();
        bool push_chain(GRB::Rule::Chain chain);
        RC_STEP step();
        bool start();
        bool savediagnosis(RC_STEP pprc_step);
        void printrules();

        struct Deducation
        {
            short size;
            short* nrules;
            short* nrulechains;
            Deducation() {
                size = 0; nrules = 0; nrulechains = 0;
            };
        } deducation;
        bool savededucation();
    };
    MfstState Get_Container(std::stack<MfstState> st, unsigned short pos);
    short Get_Container(MFSTSTACK st, int pos);
}