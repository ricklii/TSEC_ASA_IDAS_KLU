# ifndef POWERINMATH_H
# define POWERINMATH_H

namespace TSEC
{
    class PowerInMath
    {
    public:
        PowerInMath(Diary* oneDiary);
        ~PowerInMath();

        double Gii,Gij,Gji,Gjj;
		double Bii,Bij,Bji,Bjj;


		//Control Parameter Info
		int np;
		double *up;

		//Generator Information
		int nG;
		int *indexDelta,*indexgentrip;
		double *Tj,*Tj_temp;
		double sumTj_temp;

		//Transient Stability trigger
		double dDeltaBound2;
		bool Flag_TSconstraints_Back;
		int Index_G_out_bound_Back;
		double COI_Back;
		double deltamax_COI_Back;


		int Get_nDAE(void);
		int Get_nDAEd(void);
		int Get_nDAEa(void);
		double Get_t1(void);
		double Get_t2(void);
		int Get_Jacnnz(void);
		int Get_nGenerator(void);
		int Get_nControlPara(void);
		void Get_GeneratorInfo(void);

		void Set_y0(double*);
		void Set_SumTj(DAEUserData*);

		void YmatrixRefresh0(void);
		void YmatrixRefresh1(void);
		void YmatrixRefresh2(void);

		

		//user-supplied functions for idas
		int res(double t, double *yy, double *yp, double *resval, void *user_data);
		void Jac_PointerIndices(SlsMat JacMat);
		int JacSparse(double tt, double alpha,
			double *yy, double *yp, double *resvec,
			SlsMat JacMat, void *user_data,
			double *tempv1, double *tempv2, double *tempv3);
		int rhsQ(double t, double *yy, double *yp, double *qdot, void *user_data);

		int res_Back(double tt,
			double *yy, double *yp,
			double *yyB, double *ypB, double *resB,
			void *user_data);
		void adddgdy(double *yy, double *resB);
		void Jac_PointerIndices_Back(SlsMat JacMat);
		int JacSparse_Back(double tt, double cjB,
			double *yy, double *yp,
			double *yyB, double *ypB, double *resB,
			SlsMat JacMatB, void *user_data,
			double *tmp1B, double *tmp2B, double *tmp3B);
		void PowerInMath::rhsQ_Back(double tt,
			double *yy, double *yp,
			double *yyB, double *ypB,
			double *resQB, void *user_dataB);
		void adddgdp(double *y,double *resQB);


        // Interface
        //Profile* myProfile;
        Diary* myDiary;
		Analyzer* SimulatorPool;
        Optimizer* myOptimizer;

		/*
        // System Parameter
        string CaseFile;
        double baseMVA;

        // Dimension
        Index nC,nB,nDAE,nL,nS,nI,nDAEd,nDAEa;
        Index nGenP,nGenQ;
        Index SlackBus;
        Index Jacnnz;
        Index max_bus_No;
        Index n,m;
        Index m_PF,m_IV,m_MS,m_U2,m_PL,m_PQ,m_RA,m_U2t;
        Index Jac_PF_NNZ,Jac_IV_NNZ,Jac_MS_NNZ,Jac_U2_NNZ,Jac_PL_NNZ,Jac_PQ_NNZ,Jac_RA_NNZ,Jac_U2t_NNZ;
        Index Jac_MS_NNZ_0,Jac_MS_NNZ_t;
        Index NumIter;

        Index nkSims;

        // Data Pool
        vector<bus_record> bus;
        vector<branch_record> branch;
        vector<NTswitch_record> NTswitch;

        // Bus Arrangement
        vector<Index> PermuteTable;
        vector<Index> UnPermuteTable;

        // Y-Matrix
        //sMatrix Gij,Bij;
        vector<double> Gft;
        vector<double> Gtf;
        vector<double> Gff;
        vector<double> Gtt;
        vector<double> Bft;
        vector<double> Btf;
        vector<double> Bff;
        vector<double> Btt;

        // Contingency
        //SparseMatrix G0,G1,G2;
        //SparseMatrix B0,B1,B2;
        Amatrix A0,A1,A2;


        // SCOPF Settings
        double TSOPF_StepSize;
        double TSOPF_Tmax;
        double TSOPF_Freq;
        double TSOPF_AngleMax;

        // Active Parameters
        Index nActiveP;
        vector<Index> IndexActiveP;
        Index nActiveV;
        vector<Index> IndexActiveV;

        // Rotor Angle
        double sM;
        vector<double> M;
        Index nDelta;*/



    };

}

#endif