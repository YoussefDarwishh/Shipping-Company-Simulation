#pragma once
#include <iostream>
#include "PriorityQ.h"
#include "Cargo.h"
#include "Company.h"
#include <cstdlib>

using namespace std;
class Company; 
class Truck
{
	int TimeSpentunLoading;
	int Speed;
	int ID;
	int Capacity;
	static int NumberOfJournies;
	int Checkupduration;
	int Type;  // 1 for Normal 2 for Special 3 for VIP
	PriorityQueue<Cargo*> CarriedCargo;
	int BeingLoaded;
	int Cargotype;
	float MaximumDistance;
	int NumberOfJourniesDone;
	int DayOfStartLoading;
	int HourOfStartLoading;
	int DayOfDepart;
	int HourOfDepart;
	int DayOfCheckup;
	int HourOfCheckup;
	bool MaxWait;
	int TotalLoadingTime;
	int TotalCargoDelivered;
	float TotalTruckactiveTime;

public:
	Truck(int Speed, int Capacity, int Checkup, int Type, int ID);
	static void SetJournies(int x);
	int GetID();
	friend ostream& operator<<(ostream& OS, const Truck* Truck);
	bool loadCargo(Cargo* CargoPTR);
	bool Isfull();
	float PriorityWhileMoving();
	bool GoToCheckup(int Hour,int Day);
	void Departed(int Hour, int Day);
	bool FinIshedtrip(int Hour, int Day);
	bool hasurgentCargo();
	int GetType();
	bool FinIshedCheckup(int Hour, int Day);
	void Cargodelievery(int Hour, int Day,Company*CompanyPTR);
	bool Failed(Company* CompanyPTR,int Hour,int Day);
	PriorityQueue<Cargo*>* GetCargoQueue();
	bool StartedLoading();
	bool IsenoughCargo(int AvailableCargos, bool WaitedMaxWait);
	void DecrementloadTime();
	float CalculateactiveTime();
	float CalculateUtilization(int Day, int Hour);
	float GetTotalactiveTime();
	int GetTotalJournies();
	bool FinIshedLoading();
	bool CarriesCargo() const;
	void PrintCarriedCargo() const;
	void StartOfLoading(int Hour, int Day);
};