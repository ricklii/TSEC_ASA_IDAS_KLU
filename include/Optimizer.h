#ifndef H_OPTIMIZER
#define H_OPTIMIZER

namespace TSEC
{
    class Optimizer
    {
    public:
        Optimizer(Diary* myDiary_,PowerInMath* myPowerInMath_);
		bool Init(void);
        bool Run(void);
        bool Finalize(void);

        int NLPSolver,AppSelect;
        
#ifdef ENABLE_IPOPT
        // Ipopt
        Ipopt::SmartPtr<TNLP> mynlp;
        Ipopt::SmartPtr<IpoptApplication> app;
        Ipopt::ApplicationReturnStatus status;
#endif

#ifdef ENABLE_KNITRO
        // KNITRO
        KnitroWrapper* KnitroDriver;
        KTR_context_ptr kc;
#endif

        //Profile* myProfile;
        Diary* myDiary;
		PowerInMath* myPowerInMath;
		Analyzer* myAnalyzer;
        Index nS;
        //dVector g_l,g_u;
    };
}

#endif