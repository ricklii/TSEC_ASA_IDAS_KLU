# ifndef DIARY_H
# define DIARY_H

namespace TSEC
{
	class Diary
	{
	public:
		enum LogType {Debug,Log,CheckPoint,MileStone,Warning,Error,None};
		Diary(string JournalFileName,string JournalFileExName,int ShowLevelInt,int FileLevelInt);
		~Diary();
		void HotLine(LogType type, string Message);
		void HotLine(LogType type, string Message, Index data);
        void HotLine(LogType type, string Message, Number data);
        void HotLine(LogType type, string Message, string data);
		void Snap(string SpotName, Number data);
		void Snap(string SpotName, Index data);
		//void Snap(string SpotName, dVector &data);
		//void Snap(string SpotName, SparseMatrix &data);
        //void Snap(string SpotName, DenseMatrix &Z);
		void Statistics();
        void StatisticsBackGround();
		void SelfTest();
        ofstream LogHandle;
        struct SummaryRecode
        {
            string Name;
            Number Time;
        };
        vector <SummaryRecode> Summary;
        Index LDsize_max;
        void ADC04LDsizeRecord(ADC<Number>* f,Index nsize);
	private:
		static Index jour_counter;
        typedef double ClockJour;


		struct JournalElement
		{
			ClockJour ClockStamp;
			tm DataTime;
			LogType Type;
			string Message;
		};
        struct CopyRecode
        {
            string Name;
            ClockJour Time;
        };
		//Profile* myProfile;
		Index jour_id;
		Index IsSync;
		LogType FileLevel;
		LogType ShowLevel;
		string FullFileName;
		ofstream SnapHandle;
		list<JournalElement> Journal;
		LogType Int2LogType(Index Int);
		template <class T> string ConvertToString(T i);
		string TimeToString(tm t);
		string TypeToString(LogType type);
	};
}
# endif