#include "TSECConfig.h"

namespace TSEC
{
	Optimizer::Optimizer(Diary* myDiary_,PowerInMath* myPowerInMath_)
	{
		// Load Other Class Handle
		//myProfile = myProfile_;
		myDiary   = myDiary_;
		myPowerInMath = myPowerInMath_;
		myPowerInMath->myOptimizer = this;
		myAnalyzer=new Analyzer[1];

		NLPSolver = 1;
		AppSelect = 4;
		//myProfile->ReadOption("NLPSolver",NLPSolver);
		switch (NLPSolver)
		{
		case 1: myDiary->HotLine(Diary::Log,"Using Ipopt as NLP Solver"); break;
		case 2: myDiary->HotLine(Diary::Log,"Using KNITRO as NLP Solver"); break;
		default: myDiary->HotLine(Diary::Error,"Unknown NLP Solver Code"); break;
		}
		//myProfile->ReadOption("AppSelect",AppSelect);
		switch (AppSelect)
		{
		case 1: myDiary->HotLine(Diary::Error,"OPF Application"); break;
		case 2: myDiary->HotLine(Diary::Log,"TSCOPF Application"); break;
		case 3: myDiary->HotLine(Diary::Log,"Trajectory Sensitivity Analysis"); break;

		case 4: myDiary->HotLine(Diary::Log,"Adjoint Sensitivity Analysis");break;
		default: assert(false);
		}
#ifdef ENABLE_IPOPT
		mynlp = NULL;
#endif
#ifdef ENABLE_KNITRO
		KnitroDriver = NULL;
#endif
	}



	bool Optimizer::Init(void)
	{
		myAnalyzer->Init(myDiary,myPowerInMath,0);
		myDiary->HotLine(Diary::Log,"Analyzer has initialized with ID 0");
		myAnalyzer->IDASinit();
		myDiary->HotLine(Diary::Log,"Analyzer has initialized for forward integration");

		myDiary->HotLine(Diary::Log,"Optimizer has finished initialization");
		return true;
	}
	bool Optimizer::Run(void)
	{

		return true;
	}
	bool Optimizer::Finalize(void)
	{

		return true;
	}

}