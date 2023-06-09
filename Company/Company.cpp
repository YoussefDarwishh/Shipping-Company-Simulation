#include "Company.h"
#include <fstream>
#include"Preparation.h"
#include"PromoteEvent.h"
#include"CancelEvent.h"

//include the rest

Company::Company()
{
	UserInput = new UI();
	VIPLoadingTruck = nullptr;
	SpecialLoadingTruck = nullptr;
	NormalLoadingTruck = nullptr;

	NormalCargoCount=0;
	NormalCargoCounTorg = 0;
	VIPCargoCount=0;
	SpecialCargoCount=0;
	NormalTruckCount=0;
	VIPTruckCount=0;
	SpecialTruckCount=0;
	AuToPromotedCount=0;
	TrucksTotalactiveTime = 0;
	TotalTruckJournies = 0;
	TotalUtilization = 0;
}


Company::~Company()
{
	delete UserInput;
}

void Company::ReadInput(string s)
{
	ifstream File(s+".txt");
	int Number[3];
	int Speed[3];
	int Capacity[3];
	int journy;
	int Checkup[3];
	for (int i = 0; i < 3; i++)
	{
		File >> Number[i];
	}

	for (int i = 0; i < 3; i++)
	{
		File >> Speed[i];
	}
	for (int i = 0; i < 3; i++)
	{
		File >> Capacity[i];
	}
	File >> journy;
	for (int i = 0; i < 3; i++)
	{
		File >> Checkup[i];
	}
	Truck* Truckptr;
	for (int i = 0; i < Number[0]; i++)
	{
		Truckptr = new Truck(Speed[0], Capacity[0], Checkup[0], 1,i);
		WaitingNormalTrucks.EnQueue(Truckptr);
		NormalTruckCount++;
	}
	for (int i = 0; i < Number[1]; i++)
	{
		Truckptr = new Truck(Speed[1], Capacity[1], Checkup[1], 2,Number[0]+i);
		WaitingSpecialTrucks.EnQueue(Truckptr);
		SpecialTruckCount++;
	}
	for (int i = 0; i < Number[2]; i++)
	{
		Truckptr = new Truck(Speed[2], Capacity[2], Checkup[2], 3,Number[0]+Number[1]+i);
		WaitingVIPTrucks.EnQueue(Truckptr);
		VIPTruckCount++;
	}
	Truck::SetJournies(journy);

	int x;
	File >> x;
	AuTop = x;
	File >> x;
	MaxWait = x;
	File >> x;
	char Eventtype;
	char Cargotype;
	int Days;
	int Hours;
	int ID;
	int Distance;
	int TimeCargo;
	int Cost;
	Preparation* prepptr;
	CancelEvent* Cancelptr;
	PromoteEvent* promtptr;
	for (int i = 0; i < x; i++)
	{
		File >> Eventtype;
		if (Eventtype == 'R')
		{
			File >> Cargotype;
			File >> Days;
			File >> Eventtype;
			File >> Hours;
			File >> ID;
			File >> Distance;
			File >> TimeCargo;
			File >> Cost;
			if (Cargotype == 'N')
				NormalCargoCounTorg++;
			prepptr = new Preparation(Cargotype, ID, Distance, TimeCargo, Cost, Days,Hours,this); 
			Events.EnQueue(prepptr);
		}
		if (Eventtype == 'X')
		{
			File >> Days;
			File >> Eventtype;
			File >> Hours;
			File >> ID;
			Cancelptr = new CancelEvent(ID,Days,Hours, this);
			Events.EnQueue(Cancelptr);
		}
		if (Eventtype == 'P')
		{
			File >> Days;
			File >> Eventtype;
			File >> Hours;
			File >> ID;
			File >> Cost;
			promtptr = new PromoteEvent(ID, Cost,Days,Hours, this);
			Events.EnQueue(promtptr);

		}  
	}
}

void Company::OutputFile(string s)
{
	Cargo* Temp;
	Cargo* Normal = nullptr;
	Cargo* Special = nullptr;
	Cargo* VIP = nullptr;
	int NormalTime;
	int SpecialTime;
	int VIPTime;
	int TotalCargowait=0;
	int b;
	ofstream File(s + ".txt", ios::out);
	File.close();
	File.open(s + ".txt", ios::app);
	File << "CDT		ID		PT		WT		TID" << endl;
	while (!NormalDelivered.Isempty() || !SpecialDelivered.Isempty() || !VIPDelivered.Isempty())
	{
		Temp = nullptr;
		NormalDelivered.Peek(Normal); SpecialDelivered.Peek(Special); VIPDelivered.Peek(VIP);
		if (Normal)
			NormalTime = Normal->GetDayDelivered() * 24 + Normal->GetHourDelivered(); //i think de lazem tb2a fn Gowa Cargo?
		else
			NormalTime = 100000;
		if (Special)
			SpecialTime = Special->GetDayDelivered() * 24 + Special->GetHourDelivered();
		else
			SpecialTime = 100000;
		if (VIP)
			VIPTime = VIP->GetDayDelivered() * 24 + VIP->GetHourDelivered();
		else
			VIPTime = 100000;
		//kda lw = 100000 then its null
		if (NormalTime <= SpecialTime && NormalTime <= VIPTime && NormalTime != 100000)
		{
			NormalDelivered.DeQueue(Temp);
			NormalCargoCount++;
			Normal = nullptr;
		}
		else if (VIPTime <= NormalTime && VIPTime <= SpecialTime && VIPTime != 100000)
		{
			VIPDelivered.DeQueue(Temp);
			VIPCargoCount++;
			VIP = nullptr;
		}
		else if (SpecialTime != 100000)
		{
			SpecialDelivered.DeQueue(Temp);
			SpecialCargoCount++;
			Special = nullptr;
		}

		if (Temp)
		{
			File << Temp->GetDayDelivered() << ":" << Temp->GetHourDelivered() << "		";
			File << Temp->GetID() << "		";
			File << Temp->GetDayprepare() << ":" << Temp->GetHourPrepare() << "		";
			b = (Temp->GetDayWaited() - Temp->GetDayprepare()) * 24 + (Temp->GetHourWaited() - Temp->GetHourPrepare());
			File << b/24 << ":" << b%24 << "		";
			File << Temp->GetTruckID() << endl;
			TotalCargowait += (Temp->GetDayWaited() - Temp->GetDayprepare()) * 24 + (Temp->GetHourWaited() - Temp->GetHourPrepare());
			delete Temp;
		}
	}
	File << "----------------------------------------------------------"<<endl;
	File << "----------------------------------------------------------"<<endl;
	File << "Cargos: " << NormalCargoCount + SpecialCargoCount + VIPCargoCount << " [N: " << NormalCargoCount << ", S: " << SpecialCargoCount << ", V:" << VIPCargoCount << "]" << endl;
	File << "Cargo Avg Wait = " << (TotalCargowait/(NormalCargoCount + SpecialCargoCount + VIPCargoCount)/24) << ":" << TotalCargowait / (NormalCargoCount + SpecialCargoCount + VIPCargoCount)%24+1 << endl;
	File << "AuTo-Promoted Cargos: " << (1.0*AuToPromotedCount / NormalCargoCounTorg) * 100 << "%" << endl;
	File << "Trucks: " << NormalTruckCount + SpecialTruckCount + VIPTruckCount << " [N: " << NormalTruckCount << ", S: " << SpecialTruckCount << ", V:" << VIPTruckCount << "]" << endl;
	File << "Avg Active time = " << (1.0*TrucksTotalactiveTime/(NormalTruckCount + SpecialTruckCount + VIPTruckCount)/(FinIshedDay*24+FinIshedHour)*100) << "%"<<endl;
	File << "Avg Utilization =" << (1.0*TotalUtilization/(NormalTruckCount + SpecialTruckCount + VIPTruckCount))*100 << "%" << endl;
	File.close();
}

void Company::Simulate()
{
	ReadInput(UserInput->AskMode());
	int Day=0;
	int FinIshedHoura = 0;
	Event* Temp;
	srand(time(0));
	while (!IsFinIshed())
	{
		Events.Peek(Temp);

		for (int i = 0; i < 24; i++)
		{
			while (Temp->IsTime(i, Day))
			{
				Events.DeQueue(Temp);
				Temp->Execute();
				delete Temp;
				if (!Events.Peek(Temp))
					break;
			}
			AuToPromote(Day,i);
			if(i>=5 && i<=23)
				Assign(Day,i);
			MovingTruckSpecialCargo(Day, i);
			MovingTrucksFail(i, Day);
			TrucksChangingg(Day, i);
			UserInput->ModEffect(this,i,Day);
			if (IsFinIshed())
			{
				FinIshedHoura = i;
				break;
			}
		}
		Day++;
	}
	FinIshedDay = Day - 1;
	FinIshedHour = FinIshedHoura;
	CalculateTruckUtilization(FinIshedDay, FinIshedHour);
	OutputFile(UserInput->GetOutput());
}


void Company:: AddCargo (Cargo*Ptr, float Prio)
{
	if (Ptr->GetType() == 1)
		NormalCargos.EnQueue(Ptr);
	else if (Ptr->GetType() == 2)
		SpecialCargos.EnQueue(Ptr);
	else
		VIPCargos.EnQueue(Ptr,Prio); //we need To figure the Priority thing
}

void Company :: Cancel(int ID) 
{
	Queue<Cargo*>TempQueue;
	Cargo*Temp=nullptr;
	NormalCargos.Peek(Temp);
	if (!Temp)
		return;

	if (Temp->GetID() == ID)
	{
		NormalCargos.DeQueue(Temp);
		return;
	}

	while (Temp->GetID() != ID && !NormalCargos.Isempty()) //search for Cargo with the ID To be ReMoved
	{
		TempQueue.EnQueue(Temp);
		NormalCargos.DeQueue(Temp);
		NormalCargos.Peek(Temp);
	}
	if (Temp)
	{
		NormalCargos.DeQueue(Temp);
	}
	while (!NormalCargos.Isempty()) //Move rest Of Cargos in the TempQueue with the Cargo ReMoved
	{
		NormalCargos.DeQueue(Temp);
		TempQueue.EnQueue(Temp);
	}
	while (!TempQueue.Isempty()) //Move back To the Cargo lIst
	{
		TempQueue.DeQueue(Temp);
		NormalCargos.EnQueue(Temp);
	}
}

void Company :: Promote(int ID, int Extra)  
{
	Queue<Cargo*>TempQueue;
	Cargo*Temp = nullptr;
	if (NormalCargos.Isempty())
		return;
	while (!NormalCargos.Isempty()) //empty Queue until ID Is found
	{
		NormalCargos.DeQueue(Temp);
		if (Temp->GetID() == ID)
			break;
		TempQueue.EnQueue(Temp);

	}
	if(Temp->GetID() == ID)
		VIPCargos.EnQueue(Temp,Temp->Promote(Extra)); //Promote wa5da el Extra 
	while (!NormalCargos.Isempty()) //Move rest Of Cargos in the TempQueue with the Cargo ReMoved
	{
		NormalCargos.DeQueue(Temp);
		TempQueue.EnQueue(Temp);
	}
	while (!TempQueue.Isempty()) //Move back To the Cargo lIst
	{
		TempQueue.DeQueue(Temp);
		NormalCargos.EnQueue(Temp);
	}
}

bool Company::IsFinIshed()
{
	return NormalCargos.Isempty()&&SpecialCargos.Isempty()&&VIPCargos.Isempty()&&Events.Isempty()&&(NormalLoadingTruck==nullptr)&&(SpecialLoadingTruck==nullptr)&&(VIPLoadingTruck==nullptr)&&MovingTrucks.Isempty()&&CheckupNormal.Isempty()&& CheckupSpecial.Isempty()&& CheckupVIP.Isempty();
}

void Company::MoveToDelivered(Cargo* Ptr, int Type)
{
	if(Type==1)
		NormalDelivered.EnQueue(Ptr);
	if (Type == 2)
		SpecialDelivered.EnQueue(Ptr);
	if (Type == 3)
		VIPDelivered.EnQueue(Ptr);
}





void Company::TrucksChangingg(int Day, int Hour)
{
	bool NoOther=false;
	Truck* Ptr;
	if (VIPLoadingTruck)     //should the Loading Truck Move or not
	{
			if (VIPCargos.Isempty() && Events.Isempty())
				NoOther = true;
		if (VIPLoadingTruck->Isfull()|| (NoOther && VIPLoadingTruck->FinIshedLoading()))
		{
			VIPLoadingTruck->Departed(Hour, Day);
			MovingTrucks.EnQueue(VIPLoadingTruck, VIPLoadingTruck->PriorityWhileMoving());
			VIPLoadingTruck = nullptr;
		}
	}
	if (NormalLoadingTruck)    //should the Loading Truck Move or not
	{
		NoOther = false;
			if (NormalCargos.Isempty() && Events.Isempty())
				NoOther = true;
		if (NormalLoadingTruck->Isfull() || NormalLoadingTruck->hasurgentCargo()|| (NoOther&&NormalLoadingTruck->FinIshedLoading()))
		{
			NormalLoadingTruck->Departed(Hour, Day);
			MovingTrucks.EnQueue(NormalLoadingTruck, NormalLoadingTruck->PriorityWhileMoving());
			NormalLoadingTruck = nullptr;
		}
	}
	if (SpecialLoadingTruck)    //should the Loading Truck Move or not
	{
		NoOther = false;
			if (SpecialCargos.Isempty() && Events.Isempty())
				NoOther = true;
		if (SpecialLoadingTruck->Isfull() || SpecialLoadingTruck->hasurgentCargo()|| (NoOther && SpecialLoadingTruck->FinIshedLoading()))  //Moves if no other Cargo needs Being Loaded or if It Loaded a MaxWait Cargo or if full
		{
			SpecialLoadingTruck->Departed(Hour, Day);
			MovingTrucks.EnQueue(SpecialLoadingTruck, SpecialLoadingTruck->PriorityWhileMoving());
			SpecialLoadingTruck = nullptr;
		}
	}
	while (MovingTrucks.Peek(Ptr))   //checks if any Moving Truck Is back
	{
		if (Ptr->FinIshedtrip(Hour, Day))   
		{
			int Type = Ptr->GetType();
			if (Ptr->GoToCheckup(Hour,Day))   //if yes chck if It needs check up
			{
				if (Type == 1)
					CheckupNormal.EnQueue(Ptr);
				if (Type == 2)
					CheckupSpecial.EnQueue(Ptr);
				if (Type == 3)
					CheckupVIP.EnQueue(Ptr);
			}
			else
			{
				if (Type == 1)
				{
					WaitingNormalTrucks.EnQueue(Ptr);
				}
				if (Type == 2)
				{
					WaitingSpecialTrucks.EnQueue(Ptr);
				}
				if (Type == 3)
				{
					WaitingVIPTrucks.EnQueue(Ptr);
				}
			}
			MovingTrucks.DeQueue(Ptr);
		}
		else
			break;
	}


	while (CheckupNormal.Peek(Ptr))    //checks if any Cargo FinIshed Checkup To return To Waiting
	{
		if (Ptr->FinIshedCheckup(Hour, Day))
		{
			WaitingNormalTrucks.EnQueue(Ptr);
			CheckupNormal.DeQueue(Ptr);
		}
		else
			break;
	}
	while (CheckupSpecial.Peek(Ptr))
	{
		if (Ptr->FinIshedCheckup(Hour, Day))
		{
			WaitingSpecialTrucks.EnQueue(Ptr);
			CheckupSpecial.DeQueue(Ptr);
		}
		else
			break;
	}
	while (CheckupVIP.Peek(Ptr))
	{
		if (Ptr->FinIshedCheckup(Hour, Day))
		{
			WaitingVIPTrucks.EnQueue(Ptr);
			CheckupVIP.DeQueue(Ptr);
		}
		else
			break;
	}

}

void Company::Assign(int Day, int Hour)
{
	if (NormalLoadingTruck)     //decreasing the LoadTime bending
		NormalLoadingTruck->DecrementloadTime();
	if (SpecialLoadingTruck)
		SpecialLoadingTruck->DecrementloadTime();
	if (VIPLoadingTruck)
		VIPLoadingTruck->DecrementloadTime();


	Cargo* Temp;
	bool enQueued = false;
	Truck* Ptr;

	if (VIPCargos.Peek(Temp))
	{

		if (VIPLoadingTruck)   //checking if LoadingTruck exIsts
		{
			if (VIPLoadingTruck->loadCargo(Temp))   //try Loading
			{
				enQueued = true;
				if (Hour + Temp->GetloadTime() < 24)
				{
					Temp->SetDayWaited(Day);
					Temp->SetHourWaited(Hour);
				}
				else
				{
					Temp->SetDayWaited(Day + 1);
					Temp->SetHourWaited(24 - Hour);
				}
				VIPLoadingTruck->StartOfLoading(Hour, Day);
			}
		}
		else
		{
			if (WaitingVIPTrucks.Peek(Ptr)) //checking if will Move a VIP Truck from Waiting To load
			{
				if (Ptr->IsenoughCargo(VIPCargos.Count(), false))
				{
					WaitingVIPTrucks.DeQueue(Ptr);
					VIPLoadingTruck = Ptr;
					VIPLoadingTruck->loadCargo(Temp);
					enQueued = true;
					Temp->SetDayWaited(Day);
					Temp->SetHourWaited(Hour);
					VIPLoadingTruck->StartOfLoading(Hour, Day);
				}
			}
		}
		if (VIPLoadingTruck == nullptr)  //checks if no exIsting VIP 
		{
			if (WaitingVIPTrucks.Isempty())                       //no Waiting VIP Available or we alReady have a Normal Truck Loading VIP
				if (WaitingNormalTrucks.Peek(Ptr))
				{
					if (Ptr->IsenoughCargo(VIPCargos.Count(), false))
					{
						WaitingNormalTrucks.DeQueue(Ptr);
						VIPLoadingTruck = Ptr;
						VIPLoadingTruck->loadCargo(Temp);
						enQueued = true;
						Temp->SetDayWaited(Day);
						Temp->SetHourWaited(Hour);
						VIPLoadingTruck->StartOfLoading(Hour, Day);
					}
				}

			if ((WaitingVIPTrucks.Isempty() && WaitingNormalTrucks.Isempty()) && !enQueued) //same but with Special
				if (WaitingSpecialTrucks.Peek(Ptr))
				{
					if (Ptr->IsenoughCargo(VIPCargos.Count(), false))
					{
						WaitingSpecialTrucks.DeQueue(Ptr);
						VIPLoadingTruck = Ptr;
						VIPLoadingTruck->loadCargo(Temp);
						enQueued = true;
						Temp->SetDayWaited(Day);
						Temp->SetHourWaited(Hour);
						VIPLoadingTruck->StartOfLoading(Hour, Day);
					}
				}
		}
		
	

	if (Events.Isempty() && !enQueued && !VIPLoadingTruck&&(WaitingNormalTrucks.Count() != 0 || WaitingNormalTrucks.Count() == NormalTruckCount) && (WaitingSpecialTrucks.Count() != 0 || WaitingSpecialTrucks.Count() == SpecialTruckCount) && (WaitingVIPTrucks.Count() != 0 || WaitingVIPTrucks.Count() == VIPTruckCount)) //VIP have no MaxWait rule so To check if It Is the last Truck
	{
		if (!WaitingVIPTrucks.DeQueue(Ptr))
		if (!WaitingNormalTrucks.DeQueue(Ptr))
		   WaitingSpecialTrucks.DeQueue(Ptr);
			
			
	    VIPLoadingTruck = Ptr;
		Ptr->loadCargo(Temp);
		Temp->SetDayWaited(Day);
		Temp->SetHourWaited(Hour);
		enQueued = true;
		Ptr->StartOfLoading(Hour, Day);
	}

	if (enQueued)
		VIPCargos.DeQueue(Temp);
    }

	
	if (SpecialCargos.Peek(Temp))    //Special Cargo only loads in Special Trucks
	{
		if (SpecialLoadingTruck)
		{
			if (SpecialLoadingTruck->loadCargo(Temp))
			{
				SpecialCargos.DeQueue(Temp);
				Temp->SetDayWaited(Day);
				Temp->SetHourWaited(Hour);
				SpecialLoadingTruck->StartOfLoading(Hour, Day);
			}
		}
		else
		{
			if (WaitingSpecialTrucks.Peek(Ptr))
			{
				if (Ptr->IsenoughCargo(SpecialCargos.Count(), Temp->TimeWaited(Hour, Day) >= MaxWait))
				{
					WaitingSpecialTrucks.DeQueue(Ptr);
					SpecialLoadingTruck = Ptr;
					SpecialLoadingTruck->loadCargo(Temp);
					SpecialCargos.DeQueue(Temp);
					enQueued = true;
					Temp->SetDayWaited(Day);
					Temp->SetHourWaited(Hour);
					SpecialLoadingTruck->StartOfLoading(Hour, Day);
				}
			}

		}
	}
	enQueued = false;
	if (NormalCargos.Peek(Temp))   //doing the same with the VIP Cargos To Normal Cargos
	{

		if (NormalLoadingTruck)
		{
			if (NormalLoadingTruck->loadCargo(Temp))
			{
				enQueued = true;
				Temp->SetDayWaited(Day);
				Temp->SetHourWaited(Hour);
				NormalLoadingTruck->StartOfLoading(Hour, Day);
			}
		}
		else
		{
			if (WaitingNormalTrucks.Peek(Ptr))
			{
				if (Ptr->IsenoughCargo(NormalCargos.Count(), Temp->TimeWaited(Hour,Day)>=MaxWait))
				{
					WaitingNormalTrucks.DeQueue(Ptr);
					NormalLoadingTruck = Ptr;
					NormalLoadingTruck->loadCargo(Temp);
					enQueued = true;
					Temp->SetDayWaited(Day);
					Temp->SetHourWaited(Hour);
					NormalLoadingTruck->StartOfLoading(Hour, Day);
				}

			}


		}
		if(NormalLoadingTruck == nullptr)
		{
			if (WaitingNormalTrucks.Isempty()&& !enQueued)
			{
					
				if (WaitingVIPTrucks.Peek(Ptr))
				{
					if (Ptr->IsenoughCargo(NormalCargos.Count(), Temp->TimeWaited(Hour, Day) >= MaxWait))
					{
						WaitingVIPTrucks.DeQueue(Ptr);
						NormalLoadingTruck = Ptr;
						NormalLoadingTruck->loadCargo(Temp);
						enQueued = true;
						Temp->SetDayWaited(Day);
						Temp->SetHourWaited(Hour);
						NormalLoadingTruck->StartOfLoading(Hour, Day);
					}
				}	
			}
		}
		if (enQueued)
			NormalCargos.DeQueue(Temp);
	}
}

void Company::MovingTruckSpecialCargo(int Day, int Hour)
{
	Truck* Truckptr;
	Queue<Truck*>TruckQueue;
	while (MovingTrucks.DeQueue(Truckptr))  //loops on Moving Trucks checking the if alReady Delivered Cargos
	{
		Truckptr->Cargodelievery(Hour, Day, this);
		TruckQueue.EnQueue(Truckptr);
	}
	while (TruckQueue.DeQueue(Truckptr))
	{
		MovingTrucks.EnQueue(Truckptr, Truckptr->PriorityWhileMoving());
	}
}

int Company::GetCountLoading()
{
	int Count = 0;
	if (NormalLoadingTruck)
		Count++;
	if (SpecialLoadingTruck)
		Count++;
	if (VIPLoadingTruck)
		Count++;
	return Count;
}

void Company::MovingTrucksFail(int Hour,int Day)
{
	Truck* Truckptr;
	Queue<Truck*>TruckQueue;
	while (MovingTrucks.DeQueue(Truckptr))   //checks if any Trucks Failed
	{
		if (Truckptr->Failed(this,Hour,Day))
		{
			UserInput->PrintFail();
			if (Truckptr->GetType() == 1)
				CheckupNormal.EnQueue(Truckptr);
			if (Truckptr->GetType() == 2)
				CheckupSpecial.EnQueue(Truckptr);
			if (Truckptr->GetType() == 3)
				CheckupVIP.EnQueue(Truckptr);
			
		}
		else
		TruckQueue.EnQueue(Truckptr);
	}
	while (TruckQueue.DeQueue(Truckptr))
	{
		MovingTrucks.EnQueue(Truckptr, Truckptr->PriorityWhileMoving());
	}

}

Truck* Company::GetVIPLoadingTruck()
{
	return VIPLoadingTruck;
}

Truck* Company::GetSpecialLoadingTruck()
{
	return SpecialLoadingTruck;
}

Truck* Company::GetNormalLoadingTruck()
{
	return NormalLoadingTruck;
}


Queue<Cargo*>* Company::GetWaitingNormal()
{
	return &NormalCargos;
}

Queue<Cargo*>* Company::GetDeliveredNormal()
{
	return &NormalDelivered;
}

Queue<Cargo*>* Company::GetWaitingSpecial()
{
	return &SpecialCargos;
}

Queue<Cargo*>* Company::GetDeliveredSpecial()
{
	return &SpecialDelivered;
}

Queue<Cargo*>* Company::GetDeliveredVIP()
{
	return &VIPDelivered;
}

PriorityQueue<Cargo*>* Company::GetWaitingVIP()
{
	return &VIPCargos;
}

Queue<Truck*>* Company::GetWaitingNormalTruck()
{
	return &WaitingNormalTrucks;
}

Queue<Truck*>* Company::GetWaitingVIPTruck()
{
	return &WaitingVIPTrucks;
}

Queue<Truck*>* Company::GetWaitingSpecialTruck()
{
	return &WaitingSpecialTrucks;
}

Queue<Truck*>* Company::GetCheckupNormal()
{
	return &CheckupNormal;
}

Queue<Truck*>* Company::GetCheckupSpecial()
{
	return &CheckupSpecial;
}

Queue<Truck*>* Company::GetCheckupVIP()
{
	return &CheckupVIP;
}




PriorityQueue<Truck*>* Company::GetMovingTrucks()
{
	return &MovingTrucks;
}


void Company::AuToPromote(int Day,int Hour)
{
	Cargo*c;
	bool p=true;
	while(p) 
	{
		if (NormalCargos.Peek(c))
			if (c->TimeWaited(Hour, Day) >= AuTop * 24)
			{
				NormalCargos.DeQueue(c);
				VIPCargos.EnQueue(c, c->Promote(0));
				AuToPromotedCount++;
			}
			else { p = false; }
		else
			p = false;

	}
}

void Company::CalculateTruckUtilization(int Day, int Hour)
{
	Truck* Temp;
	while (WaitingNormalTrucks.DeQueue(Temp))
	{
		TotalUtilization += Temp->CalculateUtilization(Day, Hour);
		TrucksTotalactiveTime += Temp->GetTotalactiveTime();
		TotalTruckJournies += Temp->GetTotalJournies();
		delete Temp;
	}

	while (WaitingSpecialTrucks.DeQueue(Temp))
	{
		TotalUtilization += Temp->CalculateUtilization(Day, Hour);
		TrucksTotalactiveTime += Temp->GetTotalactiveTime();
		TotalTruckJournies += Temp->GetTotalJournies();
		delete Temp;
	}

	while (WaitingVIPTrucks.DeQueue(Temp))
	{
		TotalUtilization += Temp->CalculateUtilization(Day, Hour);
		TrucksTotalactiveTime += Temp->GetTotalactiveTime();
		TotalTruckJournies += Temp->GetTotalJournies();
		delete Temp;
	}
}

void Company::MoveToWaitingCargo(Cargo* Ptr, int Type)
{
	if (Type == 1)
		NormalCargos.EnQueue(Ptr);
	if (Type == 2)
		SpecialCargos.EnQueue(Ptr);
	if (Type == 3)
		VIPCargos.EnQueue(Ptr,Ptr->CalculatePriority());
}