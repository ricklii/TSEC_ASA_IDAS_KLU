#include "TSECConfig.h"

namespace TSEC
{
	DAEUserData::DAEUserData()
    {
        p = NULL;
        //RelaxTerm = NULL;
        //tmp = NULL;
    }




    Analyzer::Analyzer()
    {
        ida_mem = NULL;
        y       = NULL;
        yp      = NULL;
        //yS      = NULL;
        //ypS     = NULL;
        //ZERO = 0.0;
        //ONE  = 1.0;
        //Geij = NULL;
        //Beij = NULL;
        //pbar = NULL;
        //plist = NULL;
        //IsBusy = false;
        //NumSenEval = 0;
        //IsInitialized = false;
        //IsSparseIDAS = true;
        //Ap0 = NULL;
        //Ai0 = NULL;
        //val0 = NULL;
    }

	bool Analyzer::Init(Diary* myDiary_,PowerInMath* myPowerInMath_,int iSimulator_)
    {
		// Load Other Class Handle
        //myProfile = myProfile_;
        myDiary   = myDiary_;
		myPowerInMath = myPowerInMath_;
        iSimulator = iSimulator_;

		// Load Constant Part in Pass-in UserData
        data.mySimulator = this;
        assert(data.p == NULL);
		data.p = new double[myPowerInMath->np]();//data.p[0]=0.04;data.p[1]=1.0e4;data.p[2]=3.0e7;

		Tf=0.0;
		Tclear = myPowerInMath->Get_t1();
		Tcontrol = myPowerInMath->Get_t2();

		nDAE = myPowerInMath->Get_nDAE();
		nDAEd= myPowerInMath->Get_nDAEd();
		nDAEa= myPowerInMath->Get_nDAEa();
		y = N_VNew_Serial(nDAE);    myPowerInMath->Set_y0(NV_CONTENT_S(y)->data);
		yp = N_VNew_Serial(nDAE);   for(int i=0;i<nDAE;i++) NV_Ith_S(yp,i) = 0.0;//Ith(yp,1)=-0.04;Ith(yp,2)=0.04;Ith(yp,3)=0;

		id = N_VNew_Serial(nDAE);
        for (Index i=0     ; i<nDAEd ; i++)   NV_Ith_S(id,i) = 1.0;
        for (Index i=nDAEd ; i<nDAE  ; i++)   NV_Ith_S(id,i) = 0.0;

		q = N_VNew_Serial(1);       NV_Ith_S(q,0) = 0.0;

		Jacnnz=myPowerInMath->Get_Jacnnz();

		//myProfile->ReadOption("SimRelTol",reltol);
        //myProfile->ReadOption("SimAbsTol",abstol);

        //abstols = N_VNew_Serial(nDAE);
        //for (Index i=0;i<nDAE;i++) NV_Ith_S(abstols,i) = abstol;
		reltol=1e-3;
		abstol=1e-5;

		return true;
	}
    
	bool Analyzer::IDASinit(void)
	{
		myPowerInMath->YmatrixRefresh0();//!!!!!!!!!!!!!!!!!!!!

		// Create IDAS object
        ida_mem = IDACreate();

        // Allocate space for IDAS
        flag = IDAInit(ida_mem, res, Tf, y, yp);//Tf=T0=0.0

        // Specify scalar relative tol. and vector absolute tol.
        flag = IDASStolerances(ida_mem, reltol, abstol);

        // Set ID vector
        flag = IDASetId(ida_mem, id);

        // Attach user data
        flag = IDASetUserData(ida_mem, &data);

		// Attach linear solver and set Jacobian
		flag = IDAKLU(ida_mem, nDAE, Jacnnz);

		std::cout<<"klu set here"<<std::endl;

		flag = IDASlsSetSparseJacFn(ida_mem, JacSparse);

		flag = IDAQuadInit(ida_mem, rhsQ, q);

		flag = IDAQuadSStolerances(ida_mem, reltol, abstol);

		flag = IDASetQuadErrCon(ida_mem, TRUE);

		/* Allocate global memory */
		flag = IDAAdjInit(ida_mem, Steps, IDA_HERMITE);
		/*flag = IDAAdjInit(ida_mem, steps, IDA_POLYNOMIAL);*/

		//flag = IDAAdjSetNoSensi(ida_mem);

		flag = IDACalcIC(ida_mem,IDA_Y_INIT,Tf+0.0001);
		return true;
	}
	bool Analyzer::Sim_TransitionTeriod(void)
	{
		/* Perform forward run */
		printf("Forward integration ... ");

		/* Integrate till TB1 and get the solution (y, y') at that time. */
		flag = IDASolveF(ida_mem, Tclear, &time, y, yp, IDA_NORMAL, &ncheck);
		//if (check_flag(&flag, "IDASolveF", 1)) return(1);


		myPowerInMath->YmatrixRefresh1();//!!!!!!!!!!!!!!!!!!!!
		flag = IDASolveF(ida_mem, 0.8, &time, y, yp, IDA_NORMAL, &ncheck);
		flag = IDAGetNumSteps(ida_mem, &nst);
		//if (check_flag(&flag, "IDAGetNumSteps", 1)) return(1);

		printf("done ( nst = %ld )\n",nst);

		flag = IDAGetQuad(ida_mem, &time, q);
		printf("G:          %12.4e \n",NV_Ith_S(q,0));

		return true;
	}
    

	//user-supplied function wrapper
	int res(realtype t, N_Vector yy, N_Vector yp, 
		N_Vector resval, void *user_data)
	{
		DAEUserData* data;
        data = (DAEUserData*) user_data;

		data->mySimulator->myPowerInMath->res(t,
			NV_CONTENT_S(yy)->data,NV_CONTENT_S(yp)->data,NV_CONTENT_S(resval)->data,
			user_data
			);

		return 0;
	}
	int JacSparse(realtype tt,  realtype cj, 
		N_Vector yy, N_Vector yp, N_Vector resvec,
		SlsMat JacMat, void *user_data,
		N_Vector tempv1, N_Vector tempv2, N_Vector tempv3)
	{
		DAEUserData* data;
        data = (DAEUserData*) user_data;

		data->mySimulator->myPowerInMath->JacSparse(tt,cj,
			NV_CONTENT_S(yy)->data,NV_CONTENT_S(yp)->data,NV_CONTENT_S(resvec)->data,
			JacMat, user_data,
			NV_CONTENT_S(tempv1)->data,NV_CONTENT_S(tempv2)->data,NV_CONTENT_S(tempv3)->data
			);

		return 0;
	}

	int rhsQ(realtype t, N_Vector yy, N_Vector yp, N_Vector qdot, void *user_data)
	{
		DAEUserData* data;
        data = (DAEUserData*) user_data;

		data->mySimulator->myPowerInMath->rhsQ(t,
			NV_CONTENT_S(yy)->data,NV_CONTENT_S(yp)->data,NV_CONTENT_S(qdot)->data,
			user_data
			);

		return 0;
	}
}
