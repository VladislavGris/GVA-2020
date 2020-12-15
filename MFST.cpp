#include "MFST.h"
#define MFST_TRACE_START	std::cout<<std::setw(4)<<std::left<<"Шаг:"\
								<<std::setw(20)<<std::left<<" Правило"\
								<<std::setw(30)<<std::left<<" Входная лента"\
								<<std::setw(20)<<std::left<<" Стек"\
								<<std::endl;
int FST_TRACE_n = -1;
char rbuf[205], sbuf[205], lbuf[1024];
#define NS(n)	GRB::Rule::Chain::N(n)
#define TS(n)	GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)
#define MFST_TRACE1		std::cout<<std::setw(4)<<std::left<<++FST_TRACE_n<<": " \
								 <<std::setw(20)<<std::left<<rule.getCRule(rbuf, nrulechain) \
								 <<std::setw(30)<<std::left<<getCLenta(lbuf, lenta_position) \
								 <<std::setw(20)<<std::left<<getCst(sbuf) \
								 <<std::endl;
#define MFST_TRACE2		std::cout<<std::setw(4)<<std::left<<FST_TRACE_n<<": " \
								 <<std::setw(20)<<std::left<<" " \
								 <<std::setw(30)<<std::left<<getCLenta(lbuf, lenta_position) \
								 <<std::setw(20)<<std::left<<getCst(sbuf) \
								 <<std::endl;
#define MFST_TRACE3		std::cout<<std::setw(4)<<std::left<<++FST_TRACE_n<<": " \
								 <<std::setw(20)<<std::left<<" " \
								 <<std::setw(30)<<std::left<<getCLenta(lbuf, lenta_position) \
								 <<std::setw(20)<<std::left<<getCst(sbuf) \
								 <<std::endl;
#define MFST_TRACE4(c)		std::cout<<std::setw(4)<<std::left<<++FST_TRACE_n<<": "<<std::setw(20)<<std::left<<c<<std::endl;
#define MFST_TRACE5(c)		std::cout<<std::setw(4)<<std::left<<FST_TRACE_n<<": "<<std::setw(20)<<std::left<<c<<std::endl;
#define MFST_TRACE6(c,k)	std::cout<<std::setw(4)<<std::left<<FST_TRACE_n<<": "<<std::setw(20)<<std::left<<c<<k<<std::endl;
#define MFST_TRACE7			fout<<std::setw(4)<<std::left<<state.lenta_position<< " " << state.nrule <<" "<<  state.nrulechain <<": " \
									 <<std::setw(20)<<std::left<<rule.getCRule(rbuf, state.nrulechain) \
									 <<std::endl;

namespace MFST
{
	MfstState::MfstState()
	{
		lenta_position = 0;
		nrule = -1;
		nrulechain = -1;
	};
	MfstState::MfstState(short pposition, MFSTSTACK pst, short pnrulechain)
	{
		lenta_position = pposition;
		st = pst;
		nrulechain = pnrulechain;
	};
	MfstState::MfstState(short pposition, MFSTSTACK pst, short pnrule, short pnrulechain)
	{
		lenta_position = pposition;
		st = pst;
		nrule = pnrule;
		nrulechain = pnrulechain;
	}
	Mfst::MfstDiagnosis::MfstDiagnosis()
	{
		lenta_position = -1;
		rc_step = SURPRISE;
		nrule = -1;
		nrule_chain = -1;
	};
	Mfst::MfstDiagnosis::MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain)
	{
		lenta_position = plenta_position;
		rc_step = prc_step;
		nrule = pnrule;
		nrule_chain = pnrule_chain;
	}
	Mfst::Mfst() {
		lenta = 0; lenta_size = lenta_position = 0;
	}
	Mfst::Mfst(Lex::LEX plex, GRB::Greibach pgrebach)
	{
		grebach = pgrebach;
		lex = plex;
		lenta = new short[lenta_size = lex.lextable.size];
		for (int k = 0; k < lenta_size; k++) lenta[k] = TS(lex.lextable.table[k].lexema);
		lenta_position = 0;
		st.push(grebach.stbottomT);
		st.push(grebach.startN);
		nrulechain = -1;
	}

	Mfst::RC_STEP Mfst::step()
	{
		RC_STEP rc = SURPRISE;
		if (lenta_position < lenta_size)
		{
			if (ISNS(st.top()))
			{
				GRB::Rule rule;
				if ((nrule = grebach.getRule(st.top(), rule)) >= 0)
				{
					GRB::Rule::Chain chain;
					if ((nrulechain = rule.getNextChain(lenta[lenta_position], chain, nrulechain + 1)) >= 0)
					{
#ifdef MFSTT
						MFST_TRACE1
#endif
							savestate();
						st.pop();
						push_chain(chain);
						rc = NS_OK;
#ifdef MFSTT
						MFST_TRACE2
#endif
					}
					else
					{
#ifdef MFSTT
						MFST_TRACE4("TNS_NORULECHAIN/NS_NORULE")
#endif
							savediagnosis(NS_NORULECHIN); rc = reststate() ? NS_NORULECHIN : NS_NORULE;
					};
				}
				else rc = NS_ERROR;
			}
			else if ((st.top() == lenta[lenta_position]))
			{
				lenta_position++; st.pop(); nrulechain = -1; rc = TS_OK;
#ifdef MFSTT
				MFST_TRACE3
#endif
			}
			else
			{
#ifdef MFSTT
				MFST_TRACE4("TS_NOK/NS_NORULECHAIN")
#endif
					rc = reststate() ? TS_NOK : NS_NORULECHIN;
			};
		}
		else
		{
			rc = LENTA_END;
#ifdef MFSTT
			MFST_TRACE4("LENTA_END")
#endif
		};
		return rc;
	}
	bool Mfst::push_chain(GRB::Rule::Chain chain)
	{
		for (int k = chain.size - 1; k >= 0; k--) st.push(chain.nt[k]);
		return true;
	};
	bool Mfst::savestate()
	{
		storestate.push(MfstState(lenta_position, st, nrule, nrulechain));
#ifdef MFSTT
		MFST_TRACE6("SAVESTATE:", storestate.size());
#endif
		return true;
	};
	bool Mfst::reststate()
	{
		bool rc = false;
		MfstState state;
		if (rc = (storestate.size() > 0))
		{
			state = storestate.top();
			lenta_position = state.lenta_position;
			st = state.st;
			nrule = state.nrule;
			nrulechain = state.nrulechain;
			storestate.pop();
#ifdef MFSTT
			MFST_TRACE5("RESSTATE")
				MFST_TRACE2
#endif
		};
		return rc;
	};
	bool Mfst::savediagnosis(RC_STEP prc_step)
	{
		bool rc = false;
		short k = 0;
		while (k < MFST_DIAGN_NUMBER && lenta_position <= diagnosis[k].lenta_position) k++;
		if (rc = (k < MFST_DIAGN_NUMBER))
		{
			diagnosis[k] = MfstDiagnosis(lenta_position, prc_step, nrule, nrulechain);
			for (short j = k + 1; j < MFST_DIAGN_NUMBER; j++) diagnosis[j].lenta_position = -1;
		};
		return rc;
	};
	bool Mfst::start(Log::LOG log)
	{
		bool rc = false;
		RC_STEP rc_step = SURPRISE;
		char buf[MFST_DIAGN_MAXSIZE];
		rc_step = step();
		while (rc_step == NS_OK || rc_step == NS_NORULECHIN || rc_step == TS_OK || rc_step == TS_NOK) rc_step = step();
		switch (rc_step)
		{
		case LENTA_END:
			sprintf_s(buf, MFST_DIAGN_MAXSIZE, "%d: всего строк %d, синтаксический анализ выполнен без ошибок", 0, lenta_size);
#ifdef MFSTT
			MFST_TRACE4("------>LENTA_END")
			std::cout << "-------------------------------------------------------------------------- ----" << std::endl;
			std::cout << std::setw(4) << std::left << 0 << ": всего строк " << lenta_size << " , синтаксический анализ выполнен без ошибок" << std::endl;
#endif
			Log::WriteInfo(log, buf);
			rc = true;
			break;
		case NS_NORULE:		
#ifdef MFSTT
			MFST_TRACE4("------>NS_NORULE")
			std::cout << "-------------------------------------------------------------------------- ----" << std::endl;
			std::cout << getDiagnosis(0, buf) << std::endl;
			std::cout << getDiagnosis(1, buf) << std::endl;
			std::cout << getDiagnosis(2, buf) << std::endl;
#endif
			for (int i = 0; i < MFST_DIAGN_NUMBER; i++)
				Log::WriteInfo(log, getDiagnosis(i, buf));
			break;
		case NS_NORULECHIN:
#ifdef MFSTT
			MFST_TRACE4("------>NS_NORULECHAIN") 
#endif
				break;
		case NS_ERROR:
#ifdef MFSTT
			MFST_TRACE4("------>NS_ERROR")
#endif
				break;
		case SURPRISE:		
#ifdef MFSTT
			MFST_TRACE4("------>SURPRISE") 
#endif
				break;
		};
		return rc;
	}
	char* Mfst::getCst(char* buf)
	{
		for (int k = (signed)st.size() - 1; k >= 0; --k)
		{
			short p = Get_Container(st, k);
			buf[st.size() - 1 - k] = GRB::Rule::Chain::alphabet_to_char(p);
		};
		buf[st.size()] = 0x00;
		return buf;
	};
	char* Mfst::getCLenta(char* buf, short pos, short n)
	{
		short i, k = (pos + n < lenta_size) ? pos + n : lenta_size;
		for (i = pos; i < k; i++)
			buf[i - pos] = GRB::Rule::Chain::alphabet_to_char(lenta[i]);
		buf[i - pos] = 0x00;
		return buf;
	}
	char* Mfst::getDiagnosis(short n, char* buf)
	{
		char* rc = (char*)"";
		int errid = 0;
		int lpos = -1;
		if (n < MFST_DIAGN_NUMBER && (lpos = diagnosis[n].lenta_position) >= 0)
		{
			errid = grebach.getRule(diagnosis[n].nrule).iderror;
			Error::ERROR err = Error::geterror(errid);
			sprintf_s(buf, MFST_DIAGN_MAXSIZE, "%d: строка %d, %s", err.id, lex.lextable.table[lpos].sn, err.message);
			rc = buf;
		};
		return rc;
	};
	void Mfst::printrules()
	{
		MfstState state;
		GRB::Rule rule;
		std::ofstream fout;
		fout.open(MFST_FILE_PATH);
		for (unsigned short k = 0; k < storestate.size(); k++)
		{
			fout << k << " ";
			state = Get_Container(storestate, k);
			rule = grebach.getRule(state.nrule);
			MFST_TRACE7
		};
	};
	bool Mfst::savededucation()
	{
		MfstState state;
		GRB::Rule rule;
		deducation.nrules = new short[deducation.size = storestate.size()];
		deducation.nrulechains = new short[deducation.size];
		for (unsigned short k = 0; k < storestate.size(); k++)
		{
			state = Get_Container(storestate, k);
			deducation.nrules[k] = state.nrule;
			//std::cout << deducation.nrules[k] << " ";
			deducation.nrulechains[k] = state.nrulechain;
			//std::cout << deducation.nrulechains[k] << std::endl;
		};
		return true;
	};
	MfstState Get_Container(std::stack<MfstState> st, unsigned short pos)
	{
		int popCount = (st.size() - (pos + 1));
		for (int i = 0; i < popCount; i++)
			st.pop();
		return st.top();
	}
	short Get_Container(MFSTSTACK st, int pos)
	{
		int popCount = (st.size() - (pos + 1));
		for (int i = 0; i < popCount; i++)
			st.pop();
		return st.top();
	}
}
