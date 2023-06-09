#pragma once
#include <iostream>
using namespace std;
class Cargo
{
	int Type;  //1 Normal 2 Special 3 VIP
	int ID;
	int Distance;
	int LoadTime;
	int Cost;
	int HourPrepare;
	int DayPrepare;
	int DayWaited;
	int HourWaited;
	int DayDelivered;
	int HourDelivered;
	int TruckID;
public:
	Cargo();
	Cargo(char Type, int ID, int Distance, int LoadTime,int Cost,int Hours,int Days);
	float Promote(int Extra);
	int GetID();
	int GetType();
	int GetHourPrepare();
	int GetDayprepare();
	int GetHourWaited();
	int GetDayWaited();
	int GetDayDelivered();
	int GetHourDelivered();
	int GetTruckID();
	float CalculatePriority();
	int GetDistance() const;
	int GetloadTime() const;
	int TimeWaited(int Hours, int Days);
	void SetDayWaited(int Day);
	void SetHourWaited(int Hour);
	void SetDayDelivered(int Day);
	void SetHourDelivered(int Hour);
	void SetTruckID(int ID);
	int CalculateCargoWait(int Day, int Hour);



	friend ostream& operator<<(ostream& OS, const Cargo* Cargo);
};