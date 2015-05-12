#include "TSECConfig.h"

namespace TSEC
{
    Diary::Diary(string JournalFileName,string JournalFileExName,int ShowLevelInt,int FileLevelInt)
    {
        //myProfile=oneProfile;
        jour_id=++jour_counter;
        bool Success = true;
        //string JournalFileName;
        //string JournalFileExName;
        string JournalFileNameTimeStamp;
        //string SnapFileName;
        Index JournalTimeStamp=0;
        //Index ShowLevelInt=0;
        //Index FileLevelInt=0;

        //Success &= myProfile->ReadOption("JournalFileName",JournalFileName);
        //Success &= myProfile->ReadOption("JournalFileExName",JournalFileExName);
        //Success &= myProfile->ReadOption("JournalFileNameTimeStamp",JournalTimeStamp);
        //Success &= myProfile->ReadOption("JournalShowLevel",ShowLevelInt);
        //Success &= myProfile->ReadOption("JournalFileLevel",FileLevelInt);
        //Success &= myProfile->ReadOption("JournalFileSync",IsSync);
        //Success &= myProfile->ReadOption("SnapFileName",SnapFileName);
        ShowLevel=Int2LogType(ShowLevelInt);
        FileLevel=Int2LogType(FileLevelInt);

        if (JournalTimeStamp!=1)
        {
            /*if (MPI::COMM_WORLD.Get_size ()>1)
            {
                FullFileName=JournalFileName+"_"+ConvertToString(MPI::COMM_WORLD.Get_rank())+"."+JournalFileExName;
                SnapFileName=SnapFileName+"_"+ConvertToString(MPI::COMM_WORLD.Get_rank())+".m";
            }
            else*/
            {
                FullFileName=JournalFileName+"."+JournalFileExName;
            }
        }
        else
        {
            time_t t_tmp;
            time(&t_tmp);
            JournalFileNameTimeStamp=TimeToString(*(localtime(&t_tmp)));
            FullFileName=JournalFileName+"-"+JournalFileNameTimeStamp+"."+JournalFileExName;
        }
        assert(Success);
        if (IsSync)
        {
            LogHandle.open(FullFileName.c_str());
            HotLine(Log,"Diary is ready with synchronous mode",jour_id);
        }
        else
        {
            HotLine(Log,"Diary is ready with asynchronous mode",jour_id);
        }
        //SnapHandle.open(SnapFileName.c_str());

        LDsize_max = -1;
        //HotLine(CheckPoint,"Diary");
    }
    Diary::~Diary()
    {
        Index IsADC04Tuning = 0;
        //myProfile->ReadOption("ADC04Tuning",IsADC04Tuning);
        if (IsADC04Tuning!=0)
        {
            HotLine(Log,"Best LDsize for ADC04",LDsize_max);
        }

        if (!IsSync)
        {
            HotLine(Log,"Asynchronous Diary begins to work",jour_id);
            LogHandle.open(FullFileName.c_str());
            for(list<JournalElement>::iterator it=Journal.begin();
                it!=Journal.end();
                it++)
            {
                LogHandle<<TimeToString(it->DataTime)<<it->Message<<endl;
            }
            HotLine(Log,"Journal File Synchronization is done",jour_id);
            IsSync=1;
        }
        HotLine(Log,"Diary says bye~",jour_id);
        LogHandle.close();
        SnapHandle.close();
    }
    Diary::LogType Diary::Int2LogType(Index Int)
    {
        switch(Int)
        {
            case 0:            return Debug;
            case 1:            return Log;
            case 2:            return CheckPoint;
            case 3:            return MileStone;
            case 4:            return Warning;
            case 5:            return Error;
            case 6:            return None;
            default:        {cout<<"wrong logtype"<<endl;exit(1);}
        }
    }
    template <class T> string Diary::ConvertToString(T i)
    {
        stringstream ss;
        ss << i;
        return ss.str();
    }

    string Diary::TimeToString(tm t)
    {
        stringstream ss;
        ss    <<"["
            <<ConvertToString(t.tm_year+1900);
        ss.width(2);
        ss.fill('0');
        ss  <<resetiosflags(ios::right);
        ss    <<ConvertToString(t.tm_mon+1);
		ss.width(2);
		ss.fill('0');
		ss  <<resetiosflags(ios::right);
        ss  <<ConvertToString(t.tm_mday)
            <<"][";
		ss.width(2);
		ss.fill('0');
		ss  <<resetiosflags(ios::right);
        ss    <<ConvertToString(t.tm_hour);
		ss.width(2);
		ss.fill('0');
		ss  <<resetiosflags(ios::right);
        ss    <<ConvertToString(t.tm_min);
		ss.width(2);
		ss.fill('0');
		ss  <<resetiosflags(ios::right);
        ss  <<ConvertToString(t.tm_sec);
        ss    <<"]";
        return ss.str();
    }
    string Diary::TypeToString(LogType type)
    {
        switch(type)
        {
        case Debug:            return "Debug";
        case Log:            return "Log";
        case CheckPoint:    return "CheckPoint";
        case MileStone:        return "MileStone";
        case Warning:        return "Warning";
        case Error:            return "Error";
        case None:            return "None";
        }
        return "Error";
    }

    void Diary::HotLine(LogType type, string Message)
    {
        JournalElement op;
        time_t t_tmp;
        time(&t_tmp);
        //op.ClockStamp=MPI_Wtime();
        op.ClockStamp=clock();
        op.DataTime=*(localtime(&t_tmp));
        op.Type=type;
        op.Message=Message;
        Journal.push_back(op);

        //if (MPI::COMM_WORLD.Get_rank ()==0)
        {
            if ((type>=ShowLevel)&&(type!=CheckPoint))
            {
                cout<<TimeToString(op.DataTime)<<Message<<endl;
            }
        }
        if (type>=FileLevel && IsSync)
        {
            LogHandle<<TimeToString(op.DataTime)<<Message<<endl;
        }
        if (type==Error) 
        {
            cout<<TimeToString(op.DataTime)<<"PSPOS is going to shutdown because an Error hotline is received"<<endl;
            exit(-1);
        }
        else if (type==CheckPoint)
        {
            //MPI::COMM_WORLD.Barrier();
            //assert(MPI::COMM_WORLD.Get_size()>0);
        }
    }
    void Diary::HotLine(LogType type, string Message, Index data)
    {
        HotLine(type,Message+" ("+ConvertToString(data)+")");
    }
    void Diary::HotLine(LogType type, string Message, Number data)
    {
        HotLine(type,Message+" ("+ConvertToString(data)+")");
    }
    void Diary::HotLine(LogType type, string Message, string data)
    {
        HotLine(type,Message+" ("+ConvertToString(data)+")");
    }
    void Diary::Statistics()
    {
        //HotLine(CheckPoint,"Journal CPU Time Statistics");
        //vector <SummaryRecode> Summary;
        vector <CopyRecode>    temp;
        list<JournalElement>::iterator it=Journal.begin();
        while (it!=Journal.end())
        {
            if (it->Type==CheckPoint)
            {
                CopyRecode op;
                op.Name=it->Message;
                op.Time=it->ClockStamp;
                temp.push_back(op);
            }
            it++;
        }
        ClockJour sum=0;
        for(int i=0;i<temp.size()-1;i++)
        {
            int found=-1;
            for(int j=0;j<Summary.size();j++)
            {
                if (Summary[j].Name==temp[i].Name)
                {
                    found=j;
                    break;
                }
            }
            if (found==-1)
            {
                SummaryRecode op;
                op.Name=temp[i].Name;
                op.Time=(temp[i+1].Time-temp[i].Time);//CLOCKS_PER_SEC;
                Summary.push_back(op);
            }    
            else
            {
                Summary[found].Time+=(temp[i+1].Time-temp[i].Time);///CLOCKS_PER_SEC;
            }
        }
        cout<<"================================================="<<endl;
        cout<<"       CPU time analysis tools by SuperDaii      "<<endl;
        cout<<"-------------------------------------------------"<<endl;
        LogHandle<<"================================================="<<endl;
        LogHandle<<"       CPU time analysis tools by SuperDaii      "<<endl;
        LogHandle<<"-------------------------------------------------"<<endl;
        for(int i=0;i<Summary.size();i++)
        {
            cout<<"    * "<<Summary[i].Name<<"\t"<<" = \t"<<setprecision(3)<<fixed<<(Summary[i].Time)<<" seconds"<<endl;
            LogHandle<<"    * "<<Summary[i].Name<<"\t"<<" = \t"<<setprecision(3)<<fixed<<(Summary[i].Time)<<" seconds"<<endl;
            sum+=Summary[i].Time;
        }
        Number SumSim = 0.0;
        for (Index i=0;i<Summary.size();i++)
        {
            if (Summary[i].Name.compare(0,4,"Sim ")==0) SumSim += Summary[i].Time;
        }
        cout<<"    + "<<"Total Sim Time"<<"\t"<<" = \t"<<setprecision(3)<<fixed<<SumSim<<" seconds"<<endl;
        LogHandle<<"    + "<<"Total Sim Time"<<"\t"<<" = \t"<<setprecision(3)<<fixed<<SumSim<<" seconds"<<endl;
        cout<<"-------------------------------------------------"<<endl;
        cout<<"                       Total = "<<setprecision(3)<<fixed<<(sum)<<" seconds"<<endl;
        cout<<"================================================="<<endl;
        LogHandle<<"-------------------------------------------------"<<endl;
        LogHandle<<"                       Total = "<<setprecision(3)<<fixed<<(sum)<<" seconds"<<endl;
        LogHandle<<"================================================="<<endl;
    }

    void Diary::StatisticsBackGround()
    {
        //HotLine(CheckPoint,"Journal CPU Time Statistics");
        vector <SummaryRecode> Summary;
        vector <CopyRecode>    temp;
        list<JournalElement>::iterator it=Journal.begin();
        while (it!=Journal.end())
        {
            if (it->Type==CheckPoint)
            {
                CopyRecode op;
                op.Name=it->Message;
                op.Time=it->ClockStamp;
                temp.push_back(op);
            }
            it++;
        }
        ClockJour sum=0;
        for(int i=0;i<temp.size()-1;i++)
        {
            int found=-1;
            for(int j=0;j<Summary.size();j++)
            {
                if (Summary[j].Name==temp[i].Name)
                {
                    found=j;
                    break;
                }
            }
            if (found==-1)
            {
                SummaryRecode op;
                op.Name=temp[i].Name;
                op.Time=temp[i+1].Time-temp[i].Time;
                Summary.push_back(op);
            }    
            else
            {
                Summary[found].Time+=(temp[i+1].Time-temp[i].Time);
            }
        }
        LogHandle<<"================================================="<<endl;
        LogHandle<<"       CPU time analysis tools by SuperDaii      "<<endl;
        LogHandle<<"-------------------------------------------------"<<endl;
        Number TimePDSystem = 0.0;
        for(int i=0;i<Summary.size();i++)
        {
            LogHandle<<"    * "<<Summary[i].Name<<"\t"<<" = \t"<<setprecision(3)<<fixed<<(Summary[i].Time)<<" seconds"<<endl;
            sum+=Summary[i].Time;
            if ((Summary[i].Name.compare(0,6,"RIPM: ")==0)||(Summary[i].Name.compare(0,6,"Matrix")==0))
                TimePDSystem += Summary[i].Time;
        }
        LogHandle<<"    * "<<"PDSystem"<<"\t"<<" = \t"<<setprecision(3)<<fixed<<TimePDSystem<<" seconds"<<endl;

        LogHandle<<"-------------------------------------------------"<<endl;
        LogHandle<<"                       Total = "<<setprecision(3)<<fixed<<(sum)<<" seconds"<<endl;
        LogHandle<<"================================================="<<endl;
    }

    void Diary::SelfTest()
    {
        cout<<"======================================================="<<endl;
        cout<<" This is "<<jour_id<<"/"<<jour_counter<<" Diary Self-Testing"<<endl;
        //cout<<" I am linked with Profile #"<<myProfile->pro_id<<endl;
        cout<<" Diary is running on "<<((IsSync)?("synchronous"):("asynchronous"))<<"mode"<<endl;
        cout<<" PrintLevel: Show("<<ShowLevel<<") File("<<FileLevel<<")"<<endl;
        cout<<" Operating Log File Name: "<<FullFileName<<endl;
        cout<<"-------------------------------------------------------"<<endl;
        cout<<" I will show my Journal as below ..."<<endl;
        for(list<JournalElement>::iterator it=Journal.begin();
            it!=Journal.end();
            it++)
        {
            cout<<TimeToString(it->DataTime)<<"["<<TypeToString(it->Type)<<"]"<<it->Message<<endl;
        }
        cout<<"======================================================="<<endl;
    }

    Index Diary::jour_counter=0;
    void Diary::Snap(string SpotName, Number data)
    {
        SnapHandle<<setprecision(20)<<endl<<SpotName<<" = "<<data<<endl;
    }
    void Diary::Snap(string SpotName, Index data)
    {
        SnapHandle<<setprecision(20)<<endl<<SpotName<<" = "<<data<<endl;
    }/*
    void Diary::Snap(string SpotName, dVector &data)
    {
        SnapHandle<<endl<<SpotName<<" = ["<<endl;
        for(Index i=0;i<data.dim;i++)
        {
            SnapHandle<<setprecision(20)<<data[i]<<"; \t";
        }
        SnapHandle<<" ];"<<endl;
    }
    void Diary::Snap(string SpotName, SparseMatrix &data)
    {
        SnapHandle<<setprecision(12);
        if (!data.IsCompressed)
        {
            SnapHandle<<endl<<"%% Sparse Matrix "<<SpotName<<endl;
            SnapHandle<<SpotName<<"_iRow"<<" = ["<<endl;
            for(Index i=0;i<data.nnz;i++)
            {
                SnapHandle<<data.iRow[i]<<"; \t";
            }
            SnapHandle<<" ];"<<endl;
            SnapHandle<<SpotName<<"_jCol"<<" = ["<<endl;
            for(Index i=0;i<data.nnz;i++)
            {
                SnapHandle<<data.jCol[i]<<"; \t";
            }
            SnapHandle<<" ];"<<endl;
            SnapHandle<<SpotName<<"_data"<<" = ["<<endl;
            for(Index i=0;i<data.nnz;i++)
            {
                SnapHandle<<setprecision(20)<<data.data[i]<<"; \t";
            }
            SnapHandle<<" ];"<<endl;
            SnapHandle<<SpotName<<" = sparse("<<SpotName<<"_iRow+1, "<<SpotName<<"_jCol+1, "<<SpotName<<"_data, "<<data.n<<", "<<data.m<<" );"<<endl;
            //SnapHandle<<"clear "
        }
        else
        {
            // Print Compressed Sparse Matrix
            assert(data.iRow[0]==1);
            
            SnapHandle<<endl<<"%% Sparse Matrix "<<SpotName<<endl;
            SnapHandle<<SpotName<<"_iRow"<<" = ["<<endl;
            for(Index i=0;i<data.n;i++)
            {
                for(Index j=data.iRow[i];j<=data.iRow[i+1]-1;j++)
                    SnapHandle<<i+1<<"; \t";
            }
            SnapHandle<<" ];"<<endl;
            SnapHandle<<SpotName<<"_jCol"<<" = ["<<endl;
            for(Index i=0;i<data.nnz;i++)
            {
                SnapHandle<<data.jCol[i]<<"; \t";
            }
            SnapHandle<<" ];"<<endl;
            SnapHandle<<SpotName<<"_data"<<" = ["<<endl;
            for(Index i=0;i<data.nnz;i++)
            {
                SnapHandle<<setprecision(20)<<data.data[i]<<"; \t";
            }
            SnapHandle<<" ];"<<endl;
            SnapHandle<<SpotName<<" = sparse("<<SpotName<<"_iRow, "<<SpotName<<"_jCol, "<<SpotName<<"_data, "<<data.n<<", "<<data.m<<" );"<<endl;
        }
    }
    void Diary::Snap(string SpotName, DenseMatrix &Z)
    {
        assert(Z.IsAllocated);
        SnapHandle<<endl<<SpotName<<" = ["<<endl;
        for(Index i=0;i<Z.n;i++)
        {
            for(Index j=0;j<Z.m;j++)
            {
                if (Z.IsComplex)
                    SnapHandle<<setprecision(20)<<Z.real[i*Z.m+j]<<"+1i*("<<Z.imag[i*Z.m+j]<<")\t";
                else
                    SnapHandle<<setprecision(20)<<Z.data[i*Z.m+j]<<"\t";
            }
            SnapHandle<<";\n";
        }
        SnapHandle<<" ];"<<endl;
    }*/
    void Diary::ADC04LDsizeRecord(ADC<Number>* f,Index nsize)
    {
        Index LDsize_opt_this=-1;
        ADC_fillin(f,nsize,LDsize_opt_this);
        if (LDsize_opt_this>LDsize_max)
        {
            LDsize_max = LDsize_opt_this;
        }
    }
    
}
