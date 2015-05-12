#include "TSECConfig.h"

namespace TSEC
{
	PowerInMath::PowerInMath(Diary* oneDiary)
	{
		//myProfile=oneProfile;
		myDiary=oneDiary;
		SimulatorPool = NULL;

		myDiary->HotLine(Diary::MileStone,"PowerInMath starts to initialize");
		myDiary->HotLine(Diary::CheckPoint,"Initialization");


		nG=Get_nGenerator();
		Tj=new double[nG]();
		Tj_temp=new double[nG]();
		np=Get_nControlPara();
		//up=new [np]();

		indexgentrip=new int[nG]();
		indexDelta=new int[nG]();

		dDeltaBound2=120/180*3.1415926;
	}
	PowerInMath::~PowerInMath()
	{
		if (SimulatorPool != NULL)
		{
			delete[] SimulatorPool;
		}
		myDiary->HotLine(Diary::MileStone,"PowerInMath finalize successfully");
	}

	void PowerInMath::Set_SumTj(DAEUserData *userdata)
	{
		up=userdata->p;

		sumTj_temp=0;
		for(int i=0;i<nG;i++){
			if(indexgentrip[i]>=0){
				Tj_temp[i]=(1-up[indexgentrip[i]])*Tj[i];
			}
			else
				Tj_temp[i]=Tj[i];
			sumTj_temp+=Tj_temp[i];
		}
	}

	int PowerInMath::rhsQ(double t, double *y, double *yp, double *qdot, void *user_data)
	{
		//realtype *y;
		//y=N_VGetArrayPointer(yy);

		bool Flag_TSconstraints=false;
		int Index_G_out_bound=0;
		double COI=0;
		for(int i=0;i<nG;i++){
			COI+=Tj_temp[i]*y[indexDelta[i]];
		}
		COI/=sumTj_temp;
		double maxdDelta2=(y[indexDelta[0]]-COI)*(y[indexDelta[0]]-COI);
		for(int i=1;i<nG;i++){
			double dDelta2=(y[indexDelta[i]]-COI)*(y[indexDelta[i]]-COI);
			if(dDelta2>maxdDelta2){
				Index_G_out_bound=i;
				maxdDelta2=dDelta2;
			}
		}
		if(maxdDelta2>dDeltaBound2){
			Flag_TSconstraints=true;
			qdot[0]=maxdDelta2-dDeltaBound2;
			//deltamax_COI=sqrt(maxdDelta2);
		}
		else{
			qdot[0]=0;
		}

		return 0;
	}

	void PowerInMath::adddgdy(double *y, double *resB)
	{
		//realtype *y;
		//y=N_VGetArrayPointer(yy);

		Flag_TSconstraints_Back=false;
		Index_G_out_bound_Back=0;
		COI_Back=0;
		for(int i=0;i<nG;i++){
			COI_Back+=Tj_temp[i]*y[indexDelta[i]];
		}
		COI_Back/=sumTj_temp;
		double maxdDelta2=(y[indexDelta[0]]-COI_Back)*(y[indexDelta[0]]-COI_Back);
		for(int i=1;i<nG;i++){
			double dDelta2=(y[indexDelta[i]]-COI_Back)*(y[indexDelta[i]]-COI_Back);
			if(dDelta2>maxdDelta2){
				Index_G_out_bound_Back=i;
				maxdDelta2=dDelta2;
			}
		}
		if(maxdDelta2>dDeltaBound2){
			Flag_TSconstraints_Back=true;
			//qdot[0]=maxdDelta2-dDeltaBound2;
			deltamax_COI_Back=sqrt(maxdDelta2);
		}

		if(Flag_TSconstraints_Back==false)
			return;
		else
		{
			for(int i=0;i<nG;i++){
				//NV_Ith_S(resB,indexDelta[i]) = NV_Ith_S(resB,indexDelta[i]) - 2.0*Tj_temp[i]*deltamax_COI_Back/sumTj_temp;
				resB[indexDelta[i]] += - 2.0*Tj_temp[i]*deltamax_COI_Back/sumTj_temp;
			}

			//NV_Ith_S(resB,indexDelta[Index_G_out_bound_Back]) = NV_Ith_S(resB,indexDelta[Index_G_out_bound_Back]) + 2.0*deltamax_COI_Back;
			resB[indexDelta[Index_G_out_bound_Back]] +=  + 2.0*deltamax_COI_Back;
		}
	}


	void PowerInMath::adddgdp(double *y,double *resQB)
	{
		//realtype *y;
		//y=N_VGetArrayPointer(yy);

		if(Flag_TSconstraints_Back==false)
			return;
		else
		{
			for(int i=0;i<nG;i++){
				if(indexgentrip[i]>=0){
					//NV_Ith_S(resQB,indexgentrip[i]) = NV_Ith_S(resQB,indexgentrip[i]) + 2.0*deltamax_COI_Back*Tj[i]/sumTj_temp*(y[indexDelta[i]]-COI_Back);
					resQB[indexgentrip[i]] += + 2.0*deltamax_COI_Back*Tj[i]/sumTj_temp*(y[indexDelta[i]]-COI_Back);
				}
			}
		}
	}
}