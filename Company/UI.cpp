#include "UI.h"

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; 

string UI::AskMode()
{
    string InputFilename;
    cout << "Hello Please enter the name Of the Input File ";
    cin >> InputFilename;
    cout << endl << "Please enter the Output File name ";
    cin >> OutputFile;

    cout<<endl<< "Please select the Mode you prefer by entering the corrosponding Number:" << endl << "1)interactive" << endl << "2)step-by-step" << endl << "3)silent Mode" << endl;
    int x;
    cin >> x;
    while (x != 1 && x != 2 && x != 3)
    {
        cout << "the Number you entered Is invalid,please choose a valid Number ";
        cin >> x;
        cout << endl;
    }
    Mode = x;
    return InputFilename;
}

void UI::ModEffect(Company*CompanyPTR,int Hour, int Day)
{
    if (Mode == 1)
    {
        while (1)
        {
            if (cin.get() == '\n')
             break;
             else
                cout << "please press enter To Countinue" << endl;
        }
        cout << "Current Time (Day:Hour) " << Day << ":" << Hour<<endl;
        Print(CompanyPTR);
    }
    
    if (Mode == 2)
    {
        sleep_until(system_clock::now() + seconds(1));
        cout << "Current Time (Day:Hour) " << Day << ":" << Hour << endl;
        Print(CompanyPTR);
        cout << endl;
    }
    if (Mode == 3&&CompanyPTR->IsFinIshed())
    {
        cout << " Silent Mode" << endl << "Simulation Starts..." << endl << "Simulation Ends, Output File created" << endl;
    }
}

void UI::Print(Company*CompanyPTR)
{
    cout << CompanyPTR->GetWaitingNormal()->Count() + CompanyPTR->GetWaitingSpecial()->Count() + CompanyPTR->GetWaitingVIP()->Count();
    cout << " " << "Waiting Cargos: " << "[";
    CompanyPTR->GetWaitingNormal()->Print();
    cout << "]";
    cout << " (";
    CompanyPTR->GetWaitingSpecial()->Print();
    cout << ")";
    cout << " {";
    CompanyPTR->GetWaitingVIP()->Print();
    cout << "}" << endl;
    cout << "--------------------------" << endl;
    cout << CompanyPTR->GetDeliveredNormal()->Count() + CompanyPTR->GetDeliveredSpecial()->Count() + CompanyPTR->GetDeliveredVIP()->Count();
    cout << " Delivered Cargos:";
    cout << " [";
    CompanyPTR->GetDeliveredNormal()->Print();
    cout << "]";
    cout << " (";
    CompanyPTR->GetDeliveredSpecial()->Print();
    cout << ")";
    cout << " {";
    CompanyPTR->GetDeliveredVIP()->Print();
    cout << "}" << endl;
    cout << "--------------------------" << endl;
    cout << CompanyPTR->GetCountLoading();
    cout << " " << "Loading Trucks: ";
    if (CompanyPTR->GetNormalLoadingTruck())
    {
        cout << CompanyPTR->GetNormalLoadingTruck()->GetID() << " [";
CompanyPTR->GetNormalLoadingTruck()->GetCargoQueue()->Print();
        cout << "] ";
    }

    if (CompanyPTR->GetSpecialLoadingTruck())
    {
        cout << CompanyPTR->GetSpecialLoadingTruck()->GetID() << " (";
        CompanyPTR->GetSpecialLoadingTruck()->GetCargoQueue()->Print();
        cout << ") ";
    }

    if (CompanyPTR->GetVIPLoadingTruck())
    {
        cout << CompanyPTR->GetVIPLoadingTruck()->GetID() << " {";
        CompanyPTR->GetVIPLoadingTruck()->GetCargoQueue()->Print();
        cout << "} ";
    }
    cout << endl << "--------------------------" << endl;
    cout << CompanyPTR->GetMovingTrucks()->Count(); 
    cout << " Moving Cargos:";
    CompanyPTR->GetMovingTrucks()->Print();
    cout << endl << "--------------------------" << endl;
    cout << CompanyPTR->GetCheckupNormal()->Count() + CompanyPTR->GetCheckupSpecial()->Count() + CompanyPTR->GetCheckupVIP()->Count();
    cout << "In-Checkup Trucks:";
    cout << " [";
    CompanyPTR->GetCheckupNormal()->Print();
    cout << "]";
    cout << " (";
    CompanyPTR->GetCheckupSpecial()->Print();
    cout << ")";
    cout << " {";
    CompanyPTR->GetCheckupVIP()->Print();
    cout << "}" << endl;
    cout << "--------------------------" << endl;
    cout << CompanyPTR->GetWaitingNormalTruck()->Count() + CompanyPTR->GetWaitingSpecialTruck()->Count() + CompanyPTR->GetWaitingVIPTruck()->Count();
    cout << " " << "Empty Trucks: " << "[";
    CompanyPTR->GetWaitingNormalTruck()->Print();
    cout << "]";
    cout << " (";
    CompanyPTR->GetWaitingSpecialTruck()->Print();
    cout << ")";
    cout << " {";
    CompanyPTR->GetWaitingVIPTruck()->Print();
    cout << "}" << endl;
    cout << "--------------------------" << endl<<endl;
}

string UI::GetOutput() const
{
    return OutputFile;
}

void UI::PrintFail()
{
    if(Mode!=3)
        cout << "Failure Of Truck has occured (bonus)" << endl;
}