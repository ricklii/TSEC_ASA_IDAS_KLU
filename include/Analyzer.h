#ifndef ANALYZER_H
#define ANALYZER_H

//#include "TSECConfig.h"
namespace TSEC
{
#define Steps 10
	class DAEUserData
    {
    public:
        Analyzer* mySimulator;
        Number* p;           /* problem parameters */
        Number T0,T1;
        //bool IsCalcRelaxTerm;
        //Number* RelaxTerm;
        //Number* tmp;
        //Number beta;

        DAEUserData();
    }; 

	class Analyzer
    {
    public:
        void *ida_mem;
        DAEUserData data;
        int flag;
        double reltol,abstol;
        N_Vector y, yp, abstols, id, q;
		double time;
		int ncheck;
		long int nst,nstB;
        //N_Vector *yS, *ypS;
        //Index ZERO,ONE;
        //Index nDAE,nP,nB,nS,nDAEd,nDAEa,nC,nI,nAP,nAV;
        //bool IsBusy;
        //bool IsInitialized;
        //Index NumSenEval;
		int Jacnnz;

        Analyzer();
		bool Init(Diary* myDiary_,PowerInMath* myPowerInMath_,int iSimulator_);
		bool IDASinit(void);
		bool Sim_TransitionTeriod(void);
        //bool Init(Profile* myProfile_,Diary* myDiary_,PowerWorld* myPowerWorld_,Optimizer* myOptimizer_,Index iSimulator_);
        //bool Run(bool IsSens,Number* x,Number* out,bool IsTimeStep,vector<Number>* tDAE,vector< vector<Number> >* xDAE,vector< vector<Number> >* sDAE);
        //bool Finalize();
        int check_flag(void *flagvalue, char *funcname, int opt);
        //Profile* myProfile;
        Diary* myDiary;
		PowerInMath* myPowerInMath;
        //PowerWorld* myPowerWorld;
        //Optimizer* myOptimizer;
        int iSimulator;
		int nDAE,nDAEd,nDAEa;
		double Tf,Tclear,Tcontrol;
        //template<class TI,class TP,class TO> bool DAE_Core(Number t, TI* yy,Number* yp,TO* resval, TP* para,DAEUserData* data);
        //bool DAE_Jac_Core(Number t, Number* yy,Number* yp,Number cj, DlsMat Jac, DAEUserData* data);
        //bool DAE_Jac_Core_Sparse(Number t, Number* yy,Number* yp,Number cj, Index** Ap, Index** Ai, Number** val, DAEUserData* data);
        //bool DAE_Sen_Core(Number t, Number* yy,Number* yp,
            //N_Vector *yyS, N_Vector *ypS, N_Vector *resvalS,DAEUserData* data);
        //bool DAE_Sen_Core_Sparse(Number t, Number* yy,Number* yp,
            //N_Vector *yyS, N_Vector *ypS, N_Vector *resvalS,DAEUserData* data);
        //SparseMatrix *Geij, *Beij;
        //Amatrix *Aeij;
        //Number T1,T0;
        //Number* pbar;
        //Index* plist;

        //bool IsFirstRun;
        //bool IsFirstRunSen;
        //bool IsFault;
        //bool IsClear;

        //bool IsSparseIDAS;
        //bool IsIDASStat;
        //bool IsFullAD;
        //Index* Ap0;
        //Index* Ai0;
        //Number* val0;


        //Index EvalSenMultMethod;

    };
	int res(realtype t, N_Vector yy, N_Vector yp, 
		N_Vector resval, void *user_data);
	int JacSparse(realtype tt,  realtype cj, 
		N_Vector yy, N_Vector yp, N_Vector resvec,
		SlsMat JacMat, void *user_data,
		N_Vector tempv1, N_Vector tempv2, N_Vector tempv3);
	int rhsQ(realtype t, N_Vector yy, N_Vector yp, N_Vector qdot, void *user_data);


	/*
    int res(realtype t, N_Vector yy, N_Vector yp, N_Vector resval, void *user_data);
    int resJs(long int Neq, realtype tt, realtype cj,
        N_Vector yy, N_Vector yp, N_Vector rr,
        Index** Ap, Index** Ai, Number** val, void *user_data,
        N_Vector tmp1, N_Vector tmp2, N_Vector tmp3);
    int resJ(long int Neq, realtype tt, realtype cj,
        N_Vector yy, N_Vector yp, N_Vector rr,
        DlsMat Jac, void *user_data,
        N_Vector tmp1, N_Vector tmp2, N_Vector tmp3);
    int resSs(int Ns, realtype t, 
        N_Vector yy, N_Vector yp, N_Vector resval,
        N_Vector *yyS, N_Vector *ypS, N_Vector *resvalS,
        void *user_data, 
        N_Vector tmp1, N_Vector tmp2, N_Vector tmp3);
    int resS(int Ns, realtype t, 
        N_Vector yy, N_Vector yp, N_Vector resval,
        N_Vector *yyS, N_Vector *ypS, N_Vector *resvalS,
        void *user_data, 
        N_Vector tmp1, N_Vector tmp2, N_Vector tmp3);
		*/
}


#endif