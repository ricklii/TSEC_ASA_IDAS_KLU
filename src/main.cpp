#include "TSECConfig.h"

int main(int argv, char* argc[])
{
    using namespace TSEC;

    //bool Success=true;
    //Index tmp=0;
    //Profile myProfile(argv,argc);

	Diary myDiary("Journal","txt",0,0);
	
	PowerInMath myPowerInMath(&myDiary);

	Optimizer myTSEC(&myDiary,&myPowerInMath);

	std::cout<<"here"<<std::endl;
	myTSEC.Init();

	myTSEC.myAnalyzer->Sim_TransitionTeriod();


}