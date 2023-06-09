#include "Truck.h"
#include<iostream>
#include<Time.h>

int Truck::NumberOfJournies = 0;
Truck::Truck(int Speed, int Capacity, int Checkup, int Type, int ID)
{
	Speed = Speed;
	Capacity = Capacity;
	Checkupduration = Checkup;
	Type = Type;
	ID = ID;
	BeingLoaded = 0;
	Cargotype = -1;
	MaximumDistance = -1;
	NumberOfJourniesDone = 0;
	MaxWait = false;
	TotalLoadingTime = 0;
	TotalCargoDelivered = 0;
	TotalTruckactiveTime = 0;
	TimeSpentunLoading = 0;
}

void Truck::SetJournies(int x)
{
	NumberOfJournies = x;
}

int Truck::GetID()
{
	return ID;
}

bool Truck::loadCargo(Cargo* CargoPTR)
{
	if (BeingLoaded != 0)
	{
		return false;

	}
	if (MaxWait&&CarriedCargo.Count()!=0)
		return false;

	if (CarriedCargo.Count() >= Capacity)
		return false;

	if (Cargotype == -1)
	{
		Cargotype = CargoPTR->GetType();
	}
	else
	{
		if (Cargotype != CargoPTR->GetType())
			return false;
	}

	CarriedCargo.EnQueue(CargoPTR, (1.0/CargoPTR->GetDistance()));
	BeingLoaded = CargoPTR->GetloadTime();
	TotalLoadingTime += BeingLoaded;
	if (CargoPTR->GetDistance() > MaximumDistance)
		MaximumDistance = CargoPTR->GetDistance();
	return true;
}

bool Truck::Isfull()
{

	return (Capacity==CarriedCargo.Count())&&(BeingLoaded==0);
}

float Truck::PriorityWhileMoving()
{
	return 1.0/((MaximumDistance / Speed)+HourOfDepart+24*DayOfDepart);
}


bool Truck::GoToCheckup(int Hour, int Day)
{
	bool chckup = ((NumberOfJourniesDone % NumberOfJournies)==0) && (NumberOfJourniesDone != 0);
	if (chckup)
	{
		HourOfCheckup = Hour;
		DayOfCheckup = Day;
	}

	return chckup ;
}

void Truck::Departed(int Hour, int Day)
{
	HourOfDepart = Hour;
	DayOfDepart = Day;
}

bool Truck::FinIshedtrip(int Hour, int Day)
{
	bool FinIshed = (TotalLoadingTime + HourOfDepart + DayOfDepart * 24 + 2*MaximumDistance / Speed) <= (Hour + Day * 24);
	if (FinIshed)
	{
		TotalTruckactiveTime += CalculateactiveTime();
		TimeSpentunLoading = 0;
		MaximumDistance = -1;
		Cargotype = -1;
		HourOfDepart = 0;
		DayOfDepart = 0;
		BeingLoaded = 0;
		MaxWait = false;
		NumberOfJourniesDone++;
		TotalLoadingTime = 0;
	}
	return FinIshed;
}

bool Truck::hasurgentCargo()
{

	return MaxWait&&(BeingLoaded==0);
}

int Truck::GetType()
{
	return Type;
}

bool Truck::FinIshedCheckup(int Hour, int Day)
{
	
	bool FinIshedCheckup = ((Hour + Day * 24) == (Checkupduration + HourOfCheckup + DayOfCheckup * 24));
	if (FinIshedCheckup)
	{
		HourOfCheckup = 0;
		DayOfCheckup = 0;
	}
	return FinIshedCheckup;
	
}

void Truck::Cargodelievery(int Hour, int Day,Company*CompanyPTR)
{
	Cargo* CargoPTR;
	while (CarriedCargo.Peek(CargoPTR))
	{

		if (((1.0*CargoPTR->GetDistance() / Speed )+ (DayOfDepart * 24 )+ HourOfDepart+TimeSpentunLoading+CargoPTR->GetloadTime()) <= (Hour + Day * 24))
		{
			CarriedCargo.DeQueue(CargoPTR);
			TotalCargoDelivered++;
			TimeSpentunLoading += CargoPTR->GetloadTime();
			//ana ba7ot 7aGet statIstics hna
			CargoPTR->SetDayDelivered(Day);
			CargoPTR->SetHourDelivered(Hour);
			CargoPTR->SetTruckID(ID);
			CompanyPTR->MoveToDelivered(CargoPTR,Cargotype);
		}
		else
			break;

	}
}

bool Truck::Failed(Company* CompanyPTR,int Hour,int Day) 
{
	bool Fail=false;
	if (rand())   //small chance Of Failier
		Fail = true;
	if (Fail)
	{
		Cargo* CargoPTR;
		while (CarriedCargo.DeQueue(CargoPTR))
		{
			CompanyPTR->MoveToWaitingCargo(CargoPTR, Cargotype);
		}

		TotalTruckactiveTime += CalculateactiveTime();
		TimeSpentunLoading = 0;
		MaximumDistance = -1;
		Cargotype = -1;
		HourOfDepart = 0;
		DayOfDepart = 0;
		BeingLoaded = 0;
		MaxWait = false;
		NumberOfJourniesDone++;
		TotalLoadingTime = 0;
		HourOfCheckup = Hour;
		DayOfCheckup = Day;
		
		
	}

	
	return Fail;
}

PriorityQueue<Cargo*>* Truck::GetCargoQueue()
{
	return &CarriedCargo;
}

bool Truck::StartedLoading()
{
	return (BeingLoaded != 0);
}

bool Truck::IsenoughCargo(int AvailableCargos, bool WaitedMaxWait)
{
	if (!WaitedMaxWait)
	{
		if ((AvailableCargos + CarriedCargo.Count()) < Capacity)
			return false;
	}
	else
		MaxWait = true;
	return true;
}

void Truck::DecrementloadTime()
{
	if (BeingLoaded > 0)
		BeingLoaded--;
}


float Truck::CalculateactiveTime()
{
	return (DayOfDepart-DayOfStartLoading)*24 + (HourOfDepart-HourOfStartLoading) + 1.0 * MaximumDistance / Speed + TotalLoadingTime; //x2 for Loading + unLoading
}

float Truck::CalculateUtilization(int Day, int Hour)
{
	int TotalsimulationTime = Day * 24 + Hour;
	if (NumberOfJourniesDone == 0)
		return 0;
	else
	{
		return (((1.0*TotalCargoDelivered) / (1.0*Capacity * NumberOfJourniesDone)) * (1.0*TotalTruckactiveTime / TotalsimulationTime));
	}
}

float Truck::GetTotalactiveTime()
{
	return TotalTruckactiveTime;
}

int Truck::GetTotalJournies()
{
	return NumberOfJourniesDone;
}

bool Truck::FinIshedLoading()
{
	return BeingLoaded == 0;
}

bool Truck::CarriesCargo() const
{
	return !CarriedCargo.Isempty();
}

void Truck::PrintCarriedCargo() const
{
	CarriedCargo.Print();
}

void Truck::StartOfLoading(int Hour, int Day)
{
	if (CarriedCargo.Count() == 1)
	{
		DayOfStartLoading = Day;
		HourOfStartLoading = Hour;
	}
}

ostream& operator<<(ostream& OS, const Truck* Truck)
{
	if (Truck->CarriesCargo())
	{
		if (Truck->Cargotype == 1)
		{
			cout << Truck->ID;
			cout << "[";
			Truck->PrintCarriedCargo();
			cout << "]";
		}
		else if (Truck->Cargotype == 2)
		{
			cout << Truck->ID;
			cout << "(";
			Truck->PrintCarriedCargo();
			cout << ")";
		}
		else
		{
			cout << Truck->ID;
			cout << "{";
			Truck->PrintCarriedCargo();
			cout << "}";
		}
	}
	else
		cout << Truck->ID;
	return OS;
	
	
}
