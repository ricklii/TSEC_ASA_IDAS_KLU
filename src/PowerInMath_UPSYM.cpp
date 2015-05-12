//This C++ file is generated from SymAdjointSA.
//for Adjoint Sensitivity Analysis by IDAS in Sundials
#include "TSECConfig.h"

namespace TSEC
{
	int PowerInMath::Get_nDAE(void) { return 24; }
	//int PowerInMath::Get_nDAE(void) { return 3; }

	int PowerInMath::Get_nDAEd(void) { return 6; }

	int PowerInMath::Get_nDAEa(void) { return 18; }

	double PowerInMath::Get_t1(void) { return 0.200000; }

	double PowerInMath::Get_t2(void) { return 0.400000; }

	int PowerInMath::Get_Jacnnz(void) {return 90; }
	//int PowerInMath::Get_Jacnnz(void) {return 9; }

	int PowerInMath::Get_nGenerator(void) {return 3;}

	int PowerInMath::Get_nControlPara(void) {return 5;}//number of generator-tripping and load-shedding nodes
	//int PowerInMath::Get_nControlPara(void) {return 3;}


	void PowerInMath::Set_y0(double* y0) {
		y0[0] = 0.065010;
		y0[1] = 1.000000;
		y0[2] = 0.407630;
		y0[3] = 1.000000;
		y0[4] = 0.325601;
		y0[5] = 1.000000;
		y0[6] = 1.062742;
		y0[7] = 1.036353;
		y0[8] = 1.048839;
		y0[9] = 0.993471;
		y0[10] = 0.973305;
		y0[11] = 1.019841;
		y0[12] = 0.997553;
		y0[13] = 0.999665;
		y0[14] = 0.909881;
		y0[15] = 0.000000;
		y0[16] = 0.179815;
		y0[17] = 0.144178;
		y0[18] = -0.069840;
		y0[19] = -0.080878;
		y0[20] = 0.066423;
		y0[21] = 0.020014;
		y0[22] = 0.059402;
		y0[23] = -0.162703;
	}
	/*void PowerInMath::Set_y0(double* y0) {
		y0[0] = 1;
		y0[1] = 0;
		y0[2] = 0;
	}*/

	//DAE key coefficient change(related to line-fault)
	void PowerInMath::YmatrixRefresh0(void) {
		Gii = 0.0;
		Bii = -23.8095238095;
		Gij = 0.0;
		Bij = 13.8888888889;
		Gji = 0.0;
		Bji = 13.8888888889;
		Gjj = 0.0;
		Bjj = -36.1000690131;
	}

	void PowerInMath::YmatrixRefresh1(void) {
		Gii = 50000000.0;
		Bii = -50000009.9206;
		Gij = -5e-11;
		Bij = 5e-11;
		Gji = -5e-11;
		Bji = 5e-11;
		Gjj = 5e-11;
		Bjj = -22.2111801243;
	}

	void PowerInMath::YmatrixRefresh2(void) {
		Gii = 5e-11;
		Bii = -9.92063492068;
		Gij = -5e-11;
		Bij = 5e-11;
		Gji = -5e-11;
		Bji = 5e-11;
		Gjj = 5e-11;
		Bjj = -22.2111801243;
	}


	/*
	int PowerInMath::res(double t, double *y, double *d, double *rval, void *user_data)
	{
		double y1,y2,y3,yp1,yp2,yp3;
		double p1,p2,p3;
		y1  = y[0]; y2  = y[1]; y3  = y[2]; 
		yp1  = d[0]; yp2  = d[1]; yp3  = d[2]; 
		//rval = NV_DATA_S(resval);
		DAEUserData* data;
		double *u;
		data = (DAEUserData*) user_data;
		//data = (UserData) user_data;
		p1 = data->p[0]; p2 = data->p[1]; p3 = data->p[2];

		rval[0] = p1*y1-p2*y2*y3;
		rval[1] = -rval[0] + p3*y2*y2 + yp2;
		rval[0]+= yp1;
		rval[2] = y1+y2+y3-1;

		return 0;
	}
	int PowerInMath::JacSparse(double tt, double cj,
			double *y, double *d, double *resvec,
			SlsMat JacMat, void *user_data,
			double *tempv1, double *tempv2, double *tempv3)
	{
		double y1,y2,y3,yp1,yp2,yp3;
		double p1,p2,p3;
		y1  = y[0]; y2  = y[1]; y3  = y[2]; 
		yp1  = d[0]; yp2  = d[1]; yp3  = d[2]; 
		//rval = NV_DATA_S(resval);
		DAEUserData* data;
		double *u;
		data = (DAEUserData*) user_data;
		//data = (UserData) user_data;
		p1 = data->p[0]; p2 = data->p[1]; p3 = data->p[2];

		JacMat->colptrs[0] = 0;
		JacMat->colptrs[1] = 3;
		JacMat->colptrs[2] = 6;
		JacMat->colptrs[3] = 9;

		JacMat->data[0] = p1+cj;
		JacMat->rowvals[0] = 0;
		JacMat->data[1] = -p1;
		JacMat->rowvals[1] = 1;
		JacMat->data[2] = 1.0;
		JacMat->rowvals[2] = 2;

		JacMat->data[3] = -p2*y3;
		JacMat->rowvals[3] = 0;
		JacMat->data[4] = p2*y3+2*p3*y2+cj;
		JacMat->rowvals[4] = 1;
		JacMat->data[5] = 1.0;
		JacMat->rowvals[5] = 2;

		JacMat->data[6] = -p2*y2;
		JacMat->rowvals[6] = 0;
		JacMat->data[7] = p2*y2;
		JacMat->rowvals[7] = 1;
		JacMat->data[8] = 1.0;
		JacMat->rowvals[8] = 2;

		return 0;
	}*/
	int PowerInMath::res(double t, double *y, double *d, double *out_2308655140238706424, void *user_data)
	{
		//realtype *out_2308655140238706424,*y,*d;
		DAEUserData* data;
		double *u;
		//out_2308655140238706424=N_VGetArrayPointer(resval);
		//y=N_VGetArrayPointer(yy);
		//d=N_VGetArrayPointer(yp);
		
		data = (DAEUserData*) user_data;
		u=data->p;


		out_2308655140238706424[0] = d[0] - 376.991118430775*y[1] + 376.991118430775;
		out_2308655140238706424[1] = d[1] - 0.394755732099167*y[15]*cos(y[0]) + 0.394755732099167*y[6]*sin(y[0]) - 0.0272539654028846;
		out_2308655140238706424[2] = d[2] - 376.991118430775*y[3] + 376.991118430775;
		out_2308655140238706424[3] = d[3] - 0.601148164672177*y[16]*cos(y[2]) + 0.601148164672177*y[7]*sin(y[2]) - 0.147741125349634;
		out_2308655140238706424[4] = d[4] - 376.991118430775*y[5] + 376.991118430775;
		out_2308655140238706424[5] = d[5] - 1.10271188187982*y[17]*cos(y[4]) + 1.10271188187982*y[8]*sin(y[4]) - 0.219326596557525;
		out_2308655140238706424[6] = 17.3611111111111*y[15] - 17.3611111111111*y[18] - (-u[0] + 1.0)*(-16.3934426229508*y[15] + 18.6640510136486*sin(y[0]));
		out_2308655140238706424[7] = 22.25*y[16] - 16.0*y[22] - 7.69469650780387*sin(y[2]);
		out_2308655140238706424[8] = 17.0648464163823*y[17] - 17.0648464163823*y[20] - (-u[1] + 1.0)*(-5.52486187845304*y[17] + 6.63832552891652*sin(y[4]));
		out_2308655140238706424[9] = -17.3611111111111*y[15] + 39.9953822108554*y[18] - 10.8695652173913*y[19] - 11.7647058823529*y[23];
		out_2308655140238706424[10] = -10.8695652173913*y[18] + 16.7519181585678*y[19] - 5.88235294117647*y[20] - (-u[2] + 1.0)*(-1.0*y[10] - 0.4*y[19])/(pow(y[10], 2) + pow(y[19], 2));
		out_2308655140238706424[11] = -17.0648464163823*y[17] - 5.88235294117647*y[19] + 32.8678342781936*y[20] - 9.92063492063492*y[21];
		out_2308655140238706424[12] = -Bii*y[21] - Bij*y[22] + Gii*y[12] + Gij*y[13] - 9.92063492063492*y[20] - (-u[3] + 1.0)*(-1.0*y[12] - 0.27*y[21])/(pow(y[12], 2) + pow(y[21], 2));
		out_2308655140238706424[13] = -Bji*y[21] - Bjj*y[22] + Gji*y[12] + Gjj*y[13] - 16.0*y[16] - 6.2111801242236*y[23];
		out_2308655140238706424[14] = -11.7647058823529*y[18] - 6.2111801242236*y[22] + 17.9758860065765*y[23] - (-u[4] + 1.0)*(-2.5*y[14] - 1.0*y[23])/(pow(y[14], 2) + pow(y[23], 2));
		out_2308655140238706424[15] = -17.3611111111111*y[6] + 17.3611111111111*y[9] - (-u[0] + 1.0)*(16.3934426229508*y[6] - 18.6640510136486*cos(y[0]));
		out_2308655140238706424[16] = 16.0*y[13] - 22.25*y[7] + 7.69469650780387*cos(y[2]);
		out_2308655140238706424[17] = 17.0648464163823*y[11] - 17.0648464163823*y[8] - (-u[1] + 1.0)*(5.52486187845304*y[8] - 6.63832552891652*cos(y[4]));
		out_2308655140238706424[18] = 10.8695652173913*y[10] + 11.7647058823529*y[14] + 17.3611111111111*y[6] - 39.9953822108554*y[9];
		out_2308655140238706424[19] = -16.7519181585678*y[10] + 5.88235294117647*y[11] + 10.8695652173913*y[9] - (-u[2] + 1.0)*(0.4*y[10] - 1.0*y[19])/(pow(y[10], 2) + pow(y[19], 2));
		out_2308655140238706424[20] = 5.88235294117647*y[10] - 32.8678342781936*y[11] + 9.92063492063492*y[12] + 17.0648464163823*y[8];
		out_2308655140238706424[21] = Bii*y[12] + Bij*y[13] + Gii*y[21] + Gij*y[22] + 9.92063492063492*y[11] - (-u[3] + 1.0)*(0.27*y[12] - 1.0*y[21])/(pow(y[12], 2) + pow(y[21], 2));
		out_2308655140238706424[22] = Bji*y[12] + Bjj*y[13] + Gji*y[21] + Gjj*y[22] + 6.2111801242236*y[14] + 16.0*y[7];
		out_2308655140238706424[23] = 6.2111801242236*y[13] - 17.9758860065765*y[14] + 11.7647058823529*y[9] - (-u[4] + 1.0)*(1.0*y[14] - 2.5*y[23])/(pow(y[14], 2) + pow(y[23], 2));
		
		/*
		std::cout<<"t:  "<<t<<std::endl;
		double maxxx=0;
		for(int i=0;i<24;i++)
		{
			if(abs(out_2308655140238706424[i])>maxxx)
				maxxx=abs(out_2308655140238706424[i]);
			//std::cout<<out_2308655140238706424[i]<<std::endl;
		}
		std::cout<<maxxx<<std::endl;
		std::cout<<std::endl;*/

		return 0;
	}

	void PowerInMath::Jac_PointerIndices(SlsMat JacMat)
	{
		JacMat->colptrs[0] = 0;
		JacMat->colptrs[1] = 4;
		JacMat->colptrs[2] = 6;
		JacMat->colptrs[3] = 10;
		JacMat->colptrs[4] = 12;
		JacMat->colptrs[5] = 16;
		JacMat->colptrs[6] = 18;
		JacMat->colptrs[7] = 21;
		JacMat->colptrs[8] = 24;
		JacMat->colptrs[9] = 27;
		JacMat->colptrs[10] = 31;
		JacMat->colptrs[11] = 35;
		JacMat->colptrs[12] = 39;
		JacMat->colptrs[13] = 44;
		JacMat->colptrs[14] = 50;
		JacMat->colptrs[15] = 54;
		JacMat->colptrs[16] = 57;
		JacMat->colptrs[17] = 60;
		JacMat->colptrs[18] = 63;
		JacMat->colptrs[19] = 67;
		JacMat->colptrs[20] = 71;
		JacMat->colptrs[21] = 75;
		JacMat->colptrs[22] = 80;
		JacMat->colptrs[23] = 86;
		JacMat->colptrs[24] = 90;
		JacMat->rowvals[0] = 0;
		JacMat->rowvals[1] = 1;
		JacMat->rowvals[2] = 6;
		JacMat->rowvals[3] = 15;
		JacMat->rowvals[4] = 0;
		JacMat->rowvals[5] = 1;
		JacMat->rowvals[6] = 2;
		JacMat->rowvals[7] = 3;
		JacMat->rowvals[8] = 7;
		JacMat->rowvals[9] = 16;
		JacMat->rowvals[10] = 2;
		JacMat->rowvals[11] = 3;
		JacMat->rowvals[12] = 4;
		JacMat->rowvals[13] = 5;
		JacMat->rowvals[14] = 8;
		JacMat->rowvals[15] = 17;
		JacMat->rowvals[16] = 4;
		JacMat->rowvals[17] = 5;
		JacMat->rowvals[18] = 1;
		JacMat->rowvals[19] = 15;
		JacMat->rowvals[20] = 18;
		JacMat->rowvals[21] = 3;
		JacMat->rowvals[22] = 16;
		JacMat->rowvals[23] = 22;
		JacMat->rowvals[24] = 5;
		JacMat->rowvals[25] = 17;
		JacMat->rowvals[26] = 20;
		JacMat->rowvals[27] = 15;
		JacMat->rowvals[28] = 18;
		JacMat->rowvals[29] = 19;
		JacMat->rowvals[30] = 23;
		JacMat->rowvals[31] = 10;
		JacMat->rowvals[32] = 18;
		JacMat->rowvals[33] = 19;
		JacMat->rowvals[34] = 20;
		JacMat->rowvals[35] = 17;
		JacMat->rowvals[36] = 19;
		JacMat->rowvals[37] = 20;
		JacMat->rowvals[38] = 21;
		JacMat->rowvals[39] = 12;
		JacMat->rowvals[40] = 13;
		JacMat->rowvals[41] = 20;
		JacMat->rowvals[42] = 21;
		JacMat->rowvals[43] = 22;
		JacMat->rowvals[44] = 12;
		JacMat->rowvals[45] = 13;
		JacMat->rowvals[46] = 16;
		JacMat->rowvals[47] = 21;
		JacMat->rowvals[48] = 22;
		JacMat->rowvals[49] = 23;
		JacMat->rowvals[50] = 14;
		JacMat->rowvals[51] = 18;
		JacMat->rowvals[52] = 22;
		JacMat->rowvals[53] = 23;
		JacMat->rowvals[54] = 1;
		JacMat->rowvals[55] = 6;
		JacMat->rowvals[56] = 9;
		JacMat->rowvals[57] = 3;
		JacMat->rowvals[58] = 7;
		JacMat->rowvals[59] = 13;
		JacMat->rowvals[60] = 5;
		JacMat->rowvals[61] = 8;
		JacMat->rowvals[62] = 11;
		JacMat->rowvals[63] = 6;
		JacMat->rowvals[64] = 9;
		JacMat->rowvals[65] = 10;
		JacMat->rowvals[66] = 14;
		JacMat->rowvals[67] = 9;
		JacMat->rowvals[68] = 10;
		JacMat->rowvals[69] = 11;
		JacMat->rowvals[70] = 19;
		JacMat->rowvals[71] = 8;
		JacMat->rowvals[72] = 10;
		JacMat->rowvals[73] = 11;
		JacMat->rowvals[74] = 12;
		JacMat->rowvals[75] = 11;
		JacMat->rowvals[76] = 12;
		JacMat->rowvals[77] = 13;
		JacMat->rowvals[78] = 21;
		JacMat->rowvals[79] = 22;
		JacMat->rowvals[80] = 7;
		JacMat->rowvals[81] = 12;
		JacMat->rowvals[82] = 13;
		JacMat->rowvals[83] = 14;
		JacMat->rowvals[84] = 21;
		JacMat->rowvals[85] = 22;
		JacMat->rowvals[86] = 9;
		JacMat->rowvals[87] = 13;
		JacMat->rowvals[88] = 14;
		JacMat->rowvals[89] = 23;
	}
	
	int PowerInMath::JacSparse(double tt, double alpha,
			double *y, double *d, double *resvec,
			SlsMat JacMat, void *user_data,
			double *tempv1, double *tempv2, double *tempv3)
	{
		double *out_6745007630235635912;
		out_6745007630235635912=JacMat->data;

		Jac_PointerIndices(JacMat);

		//y=N_VGetArrayPointer(yy);
		//d=N_VGetArrayPointer(yp);
		//u=(double*)user_data;

		DAEUserData* data;
		double *u;
		data = (DAEUserData*) user_data;
		u=data->p;

		out_6745007630235635912[0] = alpha;
		out_6745007630235635912[1] = 0.394755732099167*y[15]*sin(y[0]) + 0.394755732099167*y[6]*cos(y[0]);
		out_6745007630235635912[2] = -18.6640510136486*(-u[0] + 1.0)*cos(y[0]);
		out_6745007630235635912[3] = -18.6640510136486*(-u[0] + 1.0)*sin(y[0]);
		out_6745007630235635912[4] = -376.991118430775;
		out_6745007630235635912[5] = alpha;
		out_6745007630235635912[6] = alpha;
		out_6745007630235635912[7] = 0.601148164672177*y[16]*sin(y[2]) + 0.601148164672177*y[7]*cos(y[2]);
		out_6745007630235635912[8] = -7.69469650780387*cos(y[2]);
		out_6745007630235635912[9] = -7.69469650780387*sin(y[2]);
		out_6745007630235635912[10] = -376.991118430775;
		out_6745007630235635912[11] = alpha;
		out_6745007630235635912[12] = alpha;
		out_6745007630235635912[13] = 1.10271188187982*y[17]*sin(y[4]) + 1.10271188187982*y[8]*cos(y[4]);
		out_6745007630235635912[14] = -6.63832552891652*(-u[1] + 1.0)*cos(y[4]);
		out_6745007630235635912[15] = -6.63832552891652*(-u[1] + 1.0)*sin(y[4]);
		out_6745007630235635912[16] = -376.991118430775;
		out_6745007630235635912[17] = alpha;
		out_6745007630235635912[18] = 0.394755732099167*sin(y[0]);
		out_6745007630235635912[19] = 16.3934426229508*u[0] - 33.7545537340619;
		out_6745007630235635912[20] = 17.3611111111111;
		out_6745007630235635912[21] = 0.601148164672177*sin(y[2]);
		out_6745007630235635912[22] = -22.25;
		out_6745007630235635912[23] = 16.0;
		out_6745007630235635912[24] = 1.10271188187982*sin(y[4]);
		out_6745007630235635912[25] = 5.52486187845304*u[1] - 22.5897082948353;
		out_6745007630235635912[26] = 17.0648464163823;
		out_6745007630235635912[27] = 17.3611111111111;
		out_6745007630235635912[28] = -39.9953822108554;
		out_6745007630235635912[29] = 10.8695652173913;
		out_6745007630235635912[30] = 11.7647058823529;
		out_6745007630235635912[31] = 2*y[10]*(-u[2] + 1.0)*(-1.0*y[10] - 0.4*y[19])/pow(pow(y[10], 2) + pow(y[19], 2), 2) + 1.0*(-u[2] + 1.0)/(pow(y[10], 2) + pow(y[19], 2));
		out_6745007630235635912[32] = 10.8695652173913;
		out_6745007630235635912[33] = 2*y[10]*(-u[2] + 1.0)*(0.4*y[10] - 1.0*y[19])/pow(pow(y[10], 2) + pow(y[19], 2), 2) - 0.4*(-u[2] + 1.0)/(pow(y[10], 2) + pow(y[19], 2)) - 16.7519181585678;
		out_6745007630235635912[34] = 5.88235294117647;
		out_6745007630235635912[35] = 17.0648464163823;
		out_6745007630235635912[36] = 5.88235294117647;
		out_6745007630235635912[37] = -32.8678342781936;
		out_6745007630235635912[38] = 9.92063492063492;
		out_6745007630235635912[39] = Gii + 2*y[12]*(-u[3] + 1.0)*(-1.0*y[12] - 0.27*y[21])/pow(pow(y[12], 2) + pow(y[21], 2), 2) + 1.0*(-u[3] + 1.0)/(pow(y[12], 2) + pow(y[21], 2));
		out_6745007630235635912[40] = Gji;
		out_6745007630235635912[41] = 9.92063492063492;
		out_6745007630235635912[42] = Bii + 2*y[12]*(-u[3] + 1.0)*(0.27*y[12] - 1.0*y[21])/pow(pow(y[12], 2) + pow(y[21], 2), 2) - 0.27*(-u[3] + 1.0)/(pow(y[12], 2) + pow(y[21], 2));
		out_6745007630235635912[43] = Bji;
		out_6745007630235635912[44] = Gij;
		out_6745007630235635912[45] = Gjj;
		out_6745007630235635912[46] = 16.0;
		out_6745007630235635912[47] = Bij;
		out_6745007630235635912[48] = Bjj;
		out_6745007630235635912[49] = 6.2111801242236;
		out_6745007630235635912[50] = 2*y[14]*(-u[4] + 1.0)*(-2.5*y[14] - 1.0*y[23])/pow(pow(y[14], 2) + pow(y[23], 2), 2) + 2.5*(-u[4] + 1.0)/(pow(y[14], 2) + pow(y[23], 2));
		out_6745007630235635912[51] = 11.7647058823529;
		out_6745007630235635912[52] = 6.2111801242236;
		out_6745007630235635912[53] = 2*y[14]*(-u[4] + 1.0)*(1.0*y[14] - 2.5*y[23])/pow(pow(y[14], 2) + pow(y[23], 2), 2) - 1.0*(-u[4] + 1.0)/(pow(y[14], 2) + pow(y[23], 2)) - 17.9758860065765;
		out_6745007630235635912[54] = -0.394755732099167*cos(y[0]);
		out_6745007630235635912[55] = -16.3934426229508*u[0] + 33.7545537340619;
		out_6745007630235635912[56] = -17.3611111111111;
		out_6745007630235635912[57] = -0.601148164672177*cos(y[2]);
		out_6745007630235635912[58] = 22.25;
		out_6745007630235635912[59] = -16.0;
		out_6745007630235635912[60] = -1.10271188187982*cos(y[4]);
		out_6745007630235635912[61] = -5.52486187845304*u[1] + 22.5897082948353;
		out_6745007630235635912[62] = -17.0648464163823;
		out_6745007630235635912[63] = -17.3611111111111;
		out_6745007630235635912[64] = 39.9953822108554;
		out_6745007630235635912[65] = -10.8695652173913;
		out_6745007630235635912[66] = -11.7647058823529;
		out_6745007630235635912[67] = -10.8695652173913;
		out_6745007630235635912[68] = 2*y[19]*(-u[2] + 1.0)*(-1.0*y[10] - 0.4*y[19])/pow(pow(y[10], 2) + pow(y[19], 2), 2) + 0.4*(-u[2] + 1.0)/(pow(y[10], 2) + pow(y[19], 2)) + 16.7519181585678;
		out_6745007630235635912[69] = -5.88235294117647;
		out_6745007630235635912[70] = 2*y[19]*(-u[2] + 1.0)*(0.4*y[10] - 1.0*y[19])/pow(pow(y[10], 2) + pow(y[19], 2), 2) + 1.0*(-u[2] + 1.0)/(pow(y[10], 2) + pow(y[19], 2));
		out_6745007630235635912[71] = -17.0648464163823;
		out_6745007630235635912[72] = -5.88235294117647;
		out_6745007630235635912[73] = 32.8678342781936;
		out_6745007630235635912[74] = -9.92063492063492;
		out_6745007630235635912[75] = -9.92063492063492;
		out_6745007630235635912[76] = -Bii + 2*y[21]*(-u[3] + 1.0)*(-1.0*y[12] - 0.27*y[21])/pow(pow(y[12], 2) + pow(y[21], 2), 2) + 0.27*(-u[3] + 1.0)/(pow(y[12], 2) + pow(y[21], 2));
		out_6745007630235635912[77] = -Bji;
		out_6745007630235635912[78] = Gii + 2*y[21]*(-u[3] + 1.0)*(0.27*y[12] - 1.0*y[21])/pow(pow(y[12], 2) + pow(y[21], 2), 2) + 1.0*(-u[3] + 1.0)/(pow(y[12], 2) + pow(y[21], 2));
		out_6745007630235635912[79] = Gji;
		out_6745007630235635912[80] = -16.0;
		out_6745007630235635912[81] = -Bij;
		out_6745007630235635912[82] = -Bjj;
		out_6745007630235635912[83] = -6.2111801242236;
		out_6745007630235635912[84] = Gij;
		out_6745007630235635912[85] = Gjj;
		out_6745007630235635912[86] = -11.7647058823529;
		out_6745007630235635912[87] = -6.2111801242236;
		out_6745007630235635912[88] = 2*y[23]*(-u[4] + 1.0)*(-2.5*y[14] - 1.0*y[23])/pow(pow(y[14], 2) + pow(y[23], 2), 2) + 1.0*(-u[4] + 1.0)/(pow(y[14], 2) + pow(y[23], 2)) + 17.9758860065765;
		out_6745007630235635912[89] = 2*y[23]*(-u[4] + 1.0)*(1.0*y[14] - 2.5*y[23])/pow(pow(y[14], 2) + pow(y[23], 2), 2) + 2.5*(-u[4] + 1.0)/(pow(y[14], 2) + pow(y[23], 2));

		return 0;
	}
	void PowerInMath::Get_GeneratorInfo(void)
	{
		indexDelta[0] = 0;
		Tj[0] = 47;
		indexgentrip[0]=0;

		indexDelta[1] = 2;
		Tj[1] = 12;
		indexgentrip[1]=-1;

		indexDelta[2] = 4;
		Tj[2] = 6;
		indexgentrip[2]=1;

	}
	/*Jacobian for backward problem. */
	int PowerInMath::res_Back(double tt,
			double *y, double *yp,
			double *lamda, double *lamdap, double *out_59027570521894825,
			void *user_data)
	{
		//realtype *out_59027570521894825,*y,*lamda,*lamdap;
		//double *u;

		//out_59027570521894825=N_VGetArrayPointer(resB);

		//y=N_VGetArrayPointer(yy);
		//lamda=N_VGetArrayPointer(yyB);
		//lamdap=N_VGetArrayPointer(ypB);
		DAEUserData* data;
		double *u;
		data = (DAEUserData*) user_data;
		u=data->p;
		double alpha=0.0;//Because alpha is passed from JacMatrix(dF/dy+alpha*dF/dyp), and is redundant here

		out_59027570521894825[0] = -alpha*lamda[0] + 18.6640510136486*lamda[15]*(-u[0] + 1.0)*sin(y[0]) - lamda[1]*(0.394755732099167*y[15]*sin(y[0]) + 0.394755732099167*y[6]*cos(y[0])) + 18.6640510136486*lamda[6]*(-u[0] + 1.0)*cos(y[0]) + lamdap[0];
		out_59027570521894825[1] = -alpha*lamda[1] + 376.991118430775*lamda[0] + lamdap[1];
		out_59027570521894825[2] = -alpha*lamda[2] + 7.69469650780387*lamda[16]*sin(y[2]) - lamda[3]*(0.601148164672177*y[16]*sin(y[2]) + 0.601148164672177*y[7]*cos(y[2])) + 7.69469650780387*lamda[7]*cos(y[2]) + lamdap[2];
		out_59027570521894825[3] = -alpha*lamda[3] + 376.991118430775*lamda[2] + lamdap[3];
		out_59027570521894825[4] = -alpha*lamda[4] + 6.63832552891652*lamda[17]*(-u[1] + 1.0)*sin(y[4]) - lamda[5]*(1.10271188187982*y[17]*sin(y[4]) + 1.10271188187982*y[8]*cos(y[4])) + 6.63832552891652*lamda[8]*(-u[1] + 1.0)*cos(y[4]) + lamdap[4];
		out_59027570521894825[5] = -alpha*lamda[5] + 376.991118430775*lamda[4] + lamdap[5];
		out_59027570521894825[6] = -lamda[15]*(16.3934426229508*u[0] - 33.7545537340619) - 17.3611111111111*lamda[18] - 0.394755732099167*lamda[1]*sin(y[0]);
		out_59027570521894825[7] = 22.25*lamda[16] - 16.0*lamda[22] - 0.601148164672177*lamda[3]*sin(y[2]);
		out_59027570521894825[8] = -lamda[17]*(5.52486187845304*u[1] - 22.5897082948353) - 17.0648464163823*lamda[20] - 1.10271188187982*lamda[5]*sin(y[4]);
		out_59027570521894825[9] = -17.3611111111111*lamda[15] + 39.9953822108554*lamda[18] - 10.8695652173913*lamda[19] - 11.7647058823529*lamda[23];
		out_59027570521894825[10] = -lamda[10]*(2*y[10]*(-u[2] + 1.0)*(-1.0*y[10] - 0.4*y[19])/pow(pow(y[10], 2) + pow(y[19], 2), 2) + 1.0*(-u[2] + 1.0)/(pow(y[10], 2) + pow(y[19], 2))) - 10.8695652173913*lamda[18] - lamda[19]*(2*y[10]*(-u[2] + 1.0)*(0.4*y[10] - 1.0*y[19])/pow(pow(y[10], 2) + pow(y[19], 2), 2) - 0.4*(-u[2] + 1.0)/(pow(y[10], 2) + pow(y[19], 2)) - 16.7519181585678) - 5.88235294117647*lamda[20];
		out_59027570521894825[11] = -17.0648464163823*lamda[17] - 5.88235294117647*lamda[19] + 32.8678342781936*lamda[20] - 9.92063492063492*lamda[21];
		out_59027570521894825[12] = -Bji*lamda[22] - Gji*lamda[13] - lamda[12]*(Gii + 2*y[12]*(-u[3] + 1.0)*(-1.0*y[12] - 0.27*y[21])/pow(pow(y[12], 2) + pow(y[21], 2), 2) + 1.0*(-u[3] + 1.0)/(pow(y[12], 2) + pow(y[21], 2))) - 9.92063492063492*lamda[20] - lamda[21]*(Bii + 2*y[12]*(-u[3] + 1.0)*(0.27*y[12] - 1.0*y[21])/pow(pow(y[12], 2) + pow(y[21], 2), 2) - 0.27*(-u[3] + 1.0)/(pow(y[12], 2) + pow(y[21], 2)));
		out_59027570521894825[13] = -Bij*lamda[21] - Bjj*lamda[22] - Gij*lamda[12] - Gjj*lamda[13] - 16.0*lamda[16] - 6.2111801242236*lamda[23];
		out_59027570521894825[14] = -lamda[14]*(2*y[14]*(-u[4] + 1.0)*(-2.5*y[14] - 1.0*y[23])/pow(pow(y[14], 2) + pow(y[23], 2), 2) + 2.5*(-u[4] + 1.0)/(pow(y[14], 2) + pow(y[23], 2))) - 11.7647058823529*lamda[18] - 6.2111801242236*lamda[22] - lamda[23]*(2*y[14]*(-u[4] + 1.0)*(1.0*y[14] - 2.5*y[23])/pow(pow(y[14], 2) + pow(y[23], 2), 2) - 1.0*(-u[4] + 1.0)/(pow(y[14], 2) + pow(y[23], 2)) - 17.9758860065765);
		out_59027570521894825[15] = 0.394755732099167*lamda[1]*cos(y[0]) - lamda[6]*(-16.3934426229508*u[0] + 33.7545537340619) + 17.3611111111111*lamda[9];
		out_59027570521894825[16] = 16.0*lamda[13] + 0.601148164672177*lamda[3]*cos(y[2]) - 22.25*lamda[7];
		out_59027570521894825[17] = 17.0648464163823*lamda[11] + 1.10271188187982*lamda[5]*cos(y[4]) - lamda[8]*(-5.52486187845304*u[1] + 22.5897082948353);
		out_59027570521894825[18] = 10.8695652173913*lamda[10] + 11.7647058823529*lamda[14] + 17.3611111111111*lamda[6] - 39.9953822108554*lamda[9];
		out_59027570521894825[19] = -lamda[10]*(2*y[19]*(-u[2] + 1.0)*(-1.0*y[10] - 0.4*y[19])/pow(pow(y[10], 2) + pow(y[19], 2), 2) + 0.4*(-u[2] + 1.0)/(pow(y[10], 2) + pow(y[19], 2)) + 16.7519181585678) + 5.88235294117647*lamda[11] - lamda[19]*(2*y[19]*(-u[2] + 1.0)*(0.4*y[10] - 1.0*y[19])/pow(pow(y[10], 2) + pow(y[19], 2), 2) + 1.0*(-u[2] + 1.0)/(pow(y[10], 2) + pow(y[19], 2))) + 10.8695652173913*lamda[9];
		out_59027570521894825[20] = 5.88235294117647*lamda[10] - 32.8678342781936*lamda[11] + 9.92063492063492*lamda[12] + 17.0648464163823*lamda[8];
		out_59027570521894825[21] = Bji*lamda[13] - Gji*lamda[22] + 9.92063492063492*lamda[11] - lamda[12]*(-Bii + 2*y[21]*(-u[3] + 1.0)*(-1.0*y[12] - 0.27*y[21])/pow(pow(y[12], 2) + pow(y[21], 2), 2) + 0.27*(-u[3] + 1.0)/(pow(y[12], 2) + pow(y[21], 2))) - lamda[21]*(Gii + 2*y[21]*(-u[3] + 1.0)*(0.27*y[12] - 1.0*y[21])/pow(pow(y[12], 2) + pow(y[21], 2), 2) + 1.0*(-u[3] + 1.0)/(pow(y[12], 2) + pow(y[21], 2)));
		out_59027570521894825[22] = Bij*lamda[12] + Bjj*lamda[13] - Gij*lamda[21] - Gjj*lamda[22] + 6.2111801242236*lamda[14] + 16.0*lamda[7];
		out_59027570521894825[23] = 6.2111801242236*lamda[13] - lamda[14]*(2*y[23]*(-u[4] + 1.0)*(-2.5*y[14] - 1.0*y[23])/pow(pow(y[14], 2) + pow(y[23], 2), 2) + 1.0*(-u[4] + 1.0)/(pow(y[14], 2) + pow(y[23], 2)) + 17.9758860065765) - lamda[23]*(2*y[23]*(-u[4] + 1.0)*(1.0*y[14] - 2.5*y[23])/pow(pow(y[14], 2) + pow(y[23], 2), 2) + 2.5*(-u[4] + 1.0)/(pow(y[14], 2) + pow(y[23], 2))) + 11.7647058823529*lamda[9];

		adddgdy(y, out_59027570521894825);//see attachfunc.cpp
		return 0;
	}

	void PowerInMath::Jac_PointerIndices_Back(SlsMat JacMat)
	{
		JacMat->colptrs[0] = 0;
		JacMat->colptrs[1] = 2;
		JacMat->colptrs[2] = 6;
		JacMat->colptrs[3] = 8;
		JacMat->colptrs[4] = 12;
		JacMat->colptrs[5] = 14;
		JacMat->colptrs[6] = 18;
		JacMat->colptrs[7] = 21;
		JacMat->colptrs[8] = 24;
		JacMat->colptrs[9] = 27;
		JacMat->colptrs[10] = 31;
		JacMat->colptrs[11] = 35;
		JacMat->colptrs[12] = 39;
		JacMat->colptrs[13] = 44;
		JacMat->colptrs[14] = 50;
		JacMat->colptrs[15] = 54;
		JacMat->colptrs[16] = 57;
		JacMat->colptrs[17] = 60;
		JacMat->colptrs[18] = 63;
		JacMat->colptrs[19] = 67;
		JacMat->colptrs[20] = 71;
		JacMat->colptrs[21] = 75;
		JacMat->colptrs[22] = 80;
		JacMat->colptrs[23] = 86;
		JacMat->colptrs[24] = 90;
		JacMat->rowvals[0] = 0;
		JacMat->rowvals[1] = 1;
		JacMat->rowvals[2] = 0;
		JacMat->rowvals[3] = 1;
		JacMat->rowvals[4] = 6;
		JacMat->rowvals[5] = 15;
		JacMat->rowvals[6] = 2;
		JacMat->rowvals[7] = 3;
		JacMat->rowvals[8] = 2;
		JacMat->rowvals[9] = 3;
		JacMat->rowvals[10] = 7;
		JacMat->rowvals[11] = 16;
		JacMat->rowvals[12] = 4;
		JacMat->rowvals[13] = 5;
		JacMat->rowvals[14] = 4;
		JacMat->rowvals[15] = 5;
		JacMat->rowvals[16] = 8;
		JacMat->rowvals[17] = 17;
		JacMat->rowvals[18] = 0;
		JacMat->rowvals[19] = 15;
		JacMat->rowvals[20] = 18;
		JacMat->rowvals[21] = 2;
		JacMat->rowvals[22] = 16;
		JacMat->rowvals[23] = 22;
		JacMat->rowvals[24] = 4;
		JacMat->rowvals[25] = 17;
		JacMat->rowvals[26] = 20;
		JacMat->rowvals[27] = 15;
		JacMat->rowvals[28] = 18;
		JacMat->rowvals[29] = 19;
		JacMat->rowvals[30] = 23;
		JacMat->rowvals[31] = 10;
		JacMat->rowvals[32] = 18;
		JacMat->rowvals[33] = 19;
		JacMat->rowvals[34] = 20;
		JacMat->rowvals[35] = 17;
		JacMat->rowvals[36] = 19;
		JacMat->rowvals[37] = 20;
		JacMat->rowvals[38] = 21;
		JacMat->rowvals[39] = 12;
		JacMat->rowvals[40] = 13;
		JacMat->rowvals[41] = 20;
		JacMat->rowvals[42] = 21;
		JacMat->rowvals[43] = 22;
		JacMat->rowvals[44] = 12;
		JacMat->rowvals[45] = 13;
		JacMat->rowvals[46] = 16;
		JacMat->rowvals[47] = 21;
		JacMat->rowvals[48] = 22;
		JacMat->rowvals[49] = 23;
		JacMat->rowvals[50] = 14;
		JacMat->rowvals[51] = 18;
		JacMat->rowvals[52] = 22;
		JacMat->rowvals[53] = 23;
		JacMat->rowvals[54] = 0;
		JacMat->rowvals[55] = 6;
		JacMat->rowvals[56] = 9;
		JacMat->rowvals[57] = 2;
		JacMat->rowvals[58] = 7;
		JacMat->rowvals[59] = 13;
		JacMat->rowvals[60] = 4;
		JacMat->rowvals[61] = 8;
		JacMat->rowvals[62] = 11;
		JacMat->rowvals[63] = 6;
		JacMat->rowvals[64] = 9;
		JacMat->rowvals[65] = 10;
		JacMat->rowvals[66] = 14;
		JacMat->rowvals[67] = 9;
		JacMat->rowvals[68] = 10;
		JacMat->rowvals[69] = 11;
		JacMat->rowvals[70] = 19;
		JacMat->rowvals[71] = 8;
		JacMat->rowvals[72] = 10;
		JacMat->rowvals[73] = 11;
		JacMat->rowvals[74] = 12;
		JacMat->rowvals[75] = 11;
		JacMat->rowvals[76] = 12;
		JacMat->rowvals[77] = 13;
		JacMat->rowvals[78] = 21;
		JacMat->rowvals[79] = 22;
		JacMat->rowvals[80] = 7;
		JacMat->rowvals[81] = 12;
		JacMat->rowvals[82] = 13;
		JacMat->rowvals[83] = 14;
		JacMat->rowvals[84] = 21;
		JacMat->rowvals[85] = 22;
		JacMat->rowvals[86] = 9;
		JacMat->rowvals[87] = 13;
		JacMat->rowvals[88] = 14;
		JacMat->rowvals[89] = 23;
	}
	int PowerInMath::JacSparse_Back(double tt, double cjB,
		double *y, double *yp,
		double *lamda, double *lamdap, double *out_8226810114989392549,
		SlsMat JacMatB, void *user_data,
		double *tmp1B, double *tmp2B, double *tmp3B)
	{
		//realtype *out_8226810114989392549,*y,*lamda,*lamdap;
		//double *u;
		out_8226810114989392549=JacMatB->data;
		Jac_PointerIndices_Back(JacMatB);

		//y=N_VGetArrayPointer(yy);
		//lamda=N_VGetArrayPointer(yyB);
		//lamdap=N_VGetArrayPointer(ypB);
		DAEUserData* data;
		double *u;
		data = (DAEUserData*) user_data;
		u=data->p;
		double alpha= - cjB;


		out_8226810114989392549[0] = -alpha;
		out_8226810114989392549[1] = 376.991118430775;
		out_8226810114989392549[2] = -0.394755732099167*y[15]*sin(y[0]) - 0.394755732099167*y[6]*cos(y[0]);
		out_8226810114989392549[3] = -alpha;
		out_8226810114989392549[4] = -0.394755732099167*sin(y[0]);
		out_8226810114989392549[5] = 0.394755732099167*cos(y[0]);
		out_8226810114989392549[6] = -alpha;
		out_8226810114989392549[7] = 376.991118430775;
		out_8226810114989392549[8] = -0.601148164672177*y[16]*sin(y[2]) - 0.601148164672177*y[7]*cos(y[2]);
		out_8226810114989392549[9] = -alpha;
		out_8226810114989392549[10] = -0.601148164672177*sin(y[2]);
		out_8226810114989392549[11] = 0.601148164672177*cos(y[2]);
		out_8226810114989392549[12] = -alpha;
		out_8226810114989392549[13] = 376.991118430775;
		out_8226810114989392549[14] = -1.10271188187982*y[17]*sin(y[4]) - 1.10271188187982*y[8]*cos(y[4]);
		out_8226810114989392549[15] = -alpha;
		out_8226810114989392549[16] = -1.10271188187982*sin(y[4]);
		out_8226810114989392549[17] = 1.10271188187982*cos(y[4]);
		out_8226810114989392549[18] = 18.6640510136486*(-u[0] + 1.0)*cos(y[0]);
		out_8226810114989392549[19] = 16.3934426229508*u[0] - 33.7545537340619;
		out_8226810114989392549[20] = 17.3611111111111;
		out_8226810114989392549[21] = 7.69469650780387*cos(y[2]);
		out_8226810114989392549[22] = -22.25;
		out_8226810114989392549[23] = 16.0;
		out_8226810114989392549[24] = 6.63832552891652*(-u[1] + 1.0)*cos(y[4]);
		out_8226810114989392549[25] = 5.52486187845304*u[1] - 22.5897082948353;
		out_8226810114989392549[26] = 17.0648464163823;
		out_8226810114989392549[27] = 17.3611111111111;
		out_8226810114989392549[28] = -39.9953822108554;
		out_8226810114989392549[29] = 10.8695652173913;
		out_8226810114989392549[30] = 11.7647058823529;
		out_8226810114989392549[31] = -2*y[10]*(-u[2] + 1.0)*(-1.0*y[10] - 0.4*y[19])/pow(pow(y[10], 2) + pow(y[19], 2), 2) - 1.0*(-u[2] + 1.0)/(pow(y[10], 2) + pow(y[19], 2));
		out_8226810114989392549[32] = 10.8695652173913;
		out_8226810114989392549[33] = -2*y[19]*(-u[2] + 1.0)*(-1.0*y[10] - 0.4*y[19])/pow(pow(y[10], 2) + pow(y[19], 2), 2) - 0.4*(-u[2] + 1.0)/(pow(y[10], 2) + pow(y[19], 2)) - 16.7519181585678;
		out_8226810114989392549[34] = 5.88235294117647;
		out_8226810114989392549[35] = 17.0648464163823;
		out_8226810114989392549[36] = 5.88235294117647;
		out_8226810114989392549[37] = -32.8678342781936;
		out_8226810114989392549[38] = 9.92063492063492;
		out_8226810114989392549[39] = -Gii - 2*y[12]*(-u[3] + 1.0)*(-1.0*y[12] - 0.27*y[21])/pow(pow(y[12], 2) + pow(y[21], 2), 2) - 1.0*(-u[3] + 1.0)/(pow(y[12], 2) + pow(y[21], 2));
		out_8226810114989392549[40] = -Gij;
		out_8226810114989392549[41] = 9.92063492063492;
		out_8226810114989392549[42] = Bii - 2*y[21]*(-u[3] + 1.0)*(-1.0*y[12] - 0.27*y[21])/pow(pow(y[12], 2) + pow(y[21], 2), 2) - 0.27*(-u[3] + 1.0)/(pow(y[12], 2) + pow(y[21], 2));
		out_8226810114989392549[43] = Bij;
		out_8226810114989392549[44] = -Gji;
		out_8226810114989392549[45] = -Gjj;
		out_8226810114989392549[46] = 16.0;
		out_8226810114989392549[47] = Bji;
		out_8226810114989392549[48] = Bjj;
		out_8226810114989392549[49] = 6.2111801242236;
		out_8226810114989392549[50] = -2*y[14]*(-u[4] + 1.0)*(-2.5*y[14] - 1.0*y[23])/pow(pow(y[14], 2) + pow(y[23], 2), 2) - 2.5*(-u[4] + 1.0)/(pow(y[14], 2) + pow(y[23], 2));
		out_8226810114989392549[51] = 11.7647058823529;
		out_8226810114989392549[52] = 6.2111801242236;
		out_8226810114989392549[53] = -2*y[23]*(-u[4] + 1.0)*(-2.5*y[14] - 1.0*y[23])/pow(pow(y[14], 2) + pow(y[23], 2), 2) - 1.0*(-u[4] + 1.0)/(pow(y[14], 2) + pow(y[23], 2)) - 17.9758860065765;
		out_8226810114989392549[54] = 18.6640510136486*(-u[0] + 1.0)*sin(y[0]);
		out_8226810114989392549[55] = -16.3934426229508*u[0] + 33.7545537340619;
		out_8226810114989392549[56] = -17.3611111111111;
		out_8226810114989392549[57] = 7.69469650780387*sin(y[2]);
		out_8226810114989392549[58] = 22.25;
		out_8226810114989392549[59] = -16.0;
		out_8226810114989392549[60] = 6.63832552891652*(-u[1] + 1.0)*sin(y[4]);
		out_8226810114989392549[61] = -5.52486187845304*u[1] + 22.5897082948353;
		out_8226810114989392549[62] = -17.0648464163823;
		out_8226810114989392549[63] = -17.3611111111111;
		out_8226810114989392549[64] = 39.9953822108554;
		out_8226810114989392549[65] = -10.8695652173913;
		out_8226810114989392549[66] = -11.7647058823529;
		out_8226810114989392549[67] = -10.8695652173913;
		out_8226810114989392549[68] = -2*y[10]*(-u[2] + 1.0)*(0.4*y[10] - 1.0*y[19])/pow(pow(y[10], 2) + pow(y[19], 2), 2) + 0.4*(-u[2] + 1.0)/(pow(y[10], 2) + pow(y[19], 2)) + 16.7519181585678;
		out_8226810114989392549[69] = -5.88235294117647;
		out_8226810114989392549[70] = -2*y[19]*(-u[2] + 1.0)*(0.4*y[10] - 1.0*y[19])/pow(pow(y[10], 2) + pow(y[19], 2), 2) - 1.0*(-u[2] + 1.0)/(pow(y[10], 2) + pow(y[19], 2));
		out_8226810114989392549[71] = -17.0648464163823;
		out_8226810114989392549[72] = -5.88235294117647;
		out_8226810114989392549[73] = 32.8678342781936;
		out_8226810114989392549[74] = -9.92063492063492;
		out_8226810114989392549[75] = -9.92063492063492;
		out_8226810114989392549[76] = -Bii - 2*y[12]*(-u[3] + 1.0)*(0.27*y[12] - 1.0*y[21])/pow(pow(y[12], 2) + pow(y[21], 2), 2) + 0.27*(-u[3] + 1.0)/(pow(y[12], 2) + pow(y[21], 2));
		out_8226810114989392549[77] = -Bij;
		out_8226810114989392549[78] = -Gii - 2*y[21]*(-u[3] + 1.0)*(0.27*y[12] - 1.0*y[21])/pow(pow(y[12], 2) + pow(y[21], 2), 2) - 1.0*(-u[3] + 1.0)/(pow(y[12], 2) + pow(y[21], 2));
		out_8226810114989392549[79] = -Gij;
		out_8226810114989392549[80] = -16.0;
		out_8226810114989392549[81] = -Bji;
		out_8226810114989392549[82] = -Bjj;
		out_8226810114989392549[83] = -6.2111801242236;
		out_8226810114989392549[84] = -Gji;
		out_8226810114989392549[85] = -Gjj;
		out_8226810114989392549[86] = -11.7647058823529;
		out_8226810114989392549[87] = -6.2111801242236;
		out_8226810114989392549[88] = -2*y[14]*(-u[4] + 1.0)*(1.0*y[14] - 2.5*y[23])/pow(pow(y[14], 2) + pow(y[23], 2), 2) + 1.0*(-u[4] + 1.0)/(pow(y[14], 2) + pow(y[23], 2)) + 17.9758860065765;
		out_8226810114989392549[89] = -2*y[23]*(-u[4] + 1.0)*(1.0*y[14] - 2.5*y[23])/pow(pow(y[14], 2) + pow(y[23], 2), 2) - 2.5*(-u[4] + 1.0)/(pow(y[14], 2) + pow(y[23], 2));

		return 0;
	}
	void PowerInMath::rhsQ_Back(double tt,
		double *y, double *yp,
		double *lamda, double *ypB,
		double *out_4658068923000172945, void *user_dataB)
	{
		//realtype *y,*out_4658068923000172945,*lamda;
		//double *u;

		//out_4658068923000172945=N_VGetArrayPointer(resQB);
		//y=N_VGetArrayPointer(yy);
		//lamda=N_VGetArrayPointer(yyB);
		DAEUserData* data;
		double *u;
		data = (DAEUserData*) user_dataB;
		u=data->p;


		out_4658068923000172945[0] = -lamda[15]*(16.3934426229508*y[6] - 18.6640510136486*cos(y[0])) - lamda[6]*(-16.3934426229508*y[15] + 18.6640510136486*sin(y[0]));
		out_4658068923000172945[1] = -lamda[17]*(5.52486187845304*y[8] - 6.63832552891652*cos(y[4])) - lamda[8]*(-5.52486187845304*y[17] + 6.63832552891652*sin(y[4]));
		out_4658068923000172945[2] = -lamda[10]*(-1.0*y[10] - 0.4*y[19])/(pow(y[10], 2) + pow(y[19], 2)) - lamda[19]*(0.4*y[10] - 1.0*y[19])/(pow(y[10], 2) + pow(y[19], 2));
		out_4658068923000172945[3] = -lamda[12]*(-1.0*y[12] - 0.27*y[21])/(pow(y[12], 2) + pow(y[21], 2)) - lamda[21]*(0.27*y[12] - 1.0*y[21])/(pow(y[12], 2) + pow(y[21], 2));
		out_4658068923000172945[4] = -lamda[14]*(-2.5*y[14] - 1.0*y[23])/(pow(y[14], 2) + pow(y[23], 2)) - lamda[23]*(1.0*y[14] - 2.5*y[23])/(pow(y[14], 2) + pow(y[23], 2));

		adddgdp(y, out_4658068923000172945);//see attachfunc.cpp
	}

}