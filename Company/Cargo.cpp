#include "Cargo.h"

Cargo::Cargo()
{
}



Cargo::Cargo(char Type, int ID, int Distance, int LoadTime, int Cost,int Hours,int Days)
{
	ID = ID;
	Distance = Distance;
	Cost = Cost;
	LoadTime = LoadTime;
	HourPrepare = Hours;
	DayPrepare = Days;
	if (Type =='N')
		Type = 1;
	if (Type == 'V')
		Type = 3;
	if (Type == 'S')
		Type = 2;

	DayWaited=-1;
	HourWaited=-1;
	DayDelivered=-1;
	HourDelivered=-1;
	TruckID = -1;
}

float Cargo::Promote(int Extra)
{
	if (Type == 1)
	{
		Type = 3;
		Cost += Extra;
		return CalculatePriority();     //will return the Priority Of the Cargo after Being VIP To Move It in the lIst
	}
}

int Cargo::GetID()
{
	return ID;
}

int Cargo::GetType()
{
	return Type;
}

int Cargo::GetHourPrepare()
{
	return HourPrepare;
}

int Cargo::GetDayprepare()
{
	return DayPrepare;
}

int Cargo::GetHourWaited()
{
	return HourWaited;
}

int Cargo::GetDayWaited()
{
	return DayWaited;
}

int Cargo::GetDayDelivered()
{
	return DayDelivered;
}

int Cargo::GetHourDelivered()
{
	return HourDelivered;
}

int Cargo::GetTruckID()
{
	return TruckID;
}

float Cargo::CalculatePriority()
{
	return (float)(1.0*Cost/(Distance*LoadTime));
}



int Cargo::GetDistance() const
{
	return Distance;
}

int Cargo::GetloadTime() const
{
	return LoadTime;
}

int Cargo::TimeWaited(int Hours, int Days)
{
	return Days * 24 + Hours - HourPrepare - DayPrepare * 24;
}





ostream& operator<<(ostream& OS, const Cargo* Cargo)
{
	cout << Cargo->ID;
	return OS;
}



void Cargo::SetDayWaited(int Day)
{
	DayWaited = Day;
}



void Cargo::SetHourWaited(int Hour)
{
	HourWaited = Hour;
}

void Cargo::SetDayDelivered(int Day)
{
	DayDelivered = Day;
}

void Cargo::SetHourDelivered(int Hour)
{
	HourDelivered = Hour;
}

void Cargo::SetTruckID(int ID)
{
	TruckID = ID;
}

int Cargo::CalculateCargoWait(int Day, int Hour)
{
	if ((Hour - HourPrepare)<0)
		return (Day - DayPrepare) * 24 + -(Hour - HourPrepare) + LoadTime;
	return (Day - DayPrepare) * 24 + (Hour - HourPrepare) + LoadTime;
}