#pragma once
#include "Queue.h"
#include "PriorityQ.h"
#include "Cargo.h"
#include "LinkedLIst.h"
#include <fstream>
#include"UI.h"
#include"Truck.h"


class UI;
class Truck;
class Event;
class Company
{
private:
	UI* UserInput;
	int AuTop;
	int MaxWait;
	//Event lIst
	Queue<Event*> Events;

	//Waiting Cargo lIst    
	PriorityQueue<Cargo*> VIPCargos;
	Queue<Cargo*> SpecialCargos;
	Queue<Cargo*> NormalCargos;

	//Delivered Cargo lIsts
	Queue<Cargo*>NormalDelivered;
	Queue<Cargo*>SpecialDelivered;
	Queue<Cargo*>VIPDelivered;

	//Waiting Truck lIsts
	Queue<Truck*>WaitingNormalTrucks;
	Queue<Truck*>WaitingSpecialTrucks;
	Queue<Truck*>WaitingVIPTrucks;

	//Loading Trucks
	Truck* VIPLoadingTruck;
	Truck* SpecialLoadingTruck;
	Truck* NormalLoadingTruck;
	
	PriorityQueue<Truck*>MovingTrucks;
	
	//InCheckup
	Queue<Truck*>CheckupNormal;
	Queue<Truck*>CheckupSpecial;
	Queue<Truck*>CheckupVIP;

	int NormalCargoCount;
	int VIPCargoCount;
	int SpecialCargoCount;
	int NormalTruckCount;
	int NormalCargoCounTorg;
	int VIPTruckCount;
	int SpecialTruckCount;
	int AuToPromotedCount;
	float TrucksTotalactiveTime;
	int TotalTruckJournies;
	float TotalUtilization;

	int FinIshedDay;
	int FinIshedHour;

public:
	Company();
	~Company();
	void ReadInput(string s);
	void OutputFile(string s);
	void Simulate();
	void AddCargo(Cargo*Ptr, float Prio=0);
	void Cancel(int ID);
	void Promote(int ID, int Extra);
	bool IsFinIshed();
	void MoveToDelivered(Cargo*Ptr,int Type);
	void TrucksChangingg(int Day,int Hour);
	void Assign(int Day, int Hour);
	void MovingTruckSpecialCargo(int Day, int Hour);
	int GetCountLoading();
	void MovingTrucksFail(int Hour,int Day);
	void AuToPromote(int Day,int Hour);
	void CalculateTruckUtilization(int Day, int Hour);
	void MoveToWaitingCargo(Cargo* Ptr, int Type);


	Truck* GetVIPLoadingTruck();
	Truck* GetSpecialLoadingTruck();
	Truck* GetNormalLoadingTruck();
	Queue<Cargo*>* GetWaitingNormal();
	Queue<Cargo*>* GetDeliveredNormal();
	Queue<Cargo*>* GetWaitingSpecial();
	Queue<Cargo*>* GetDeliveredSpecial();
	Queue<Cargo*>* GetDeliveredVIP();
	PriorityQueue<Cargo*>* GetWaitingVIP();

	Queue<Truck*>* GetWaitingNormalTruck();
	Queue<Truck*>* GetWaitingVIPTruck();
	Queue<Truck*>* GetWaitingSpecialTruck();

	Queue<Truck*>*GetCheckupNormal();
	Queue<Truck*>*GetCheckupSpecial();
	Queue<Truck*>*GetCheckupVIP();

	PriorityQueue<Truck*>* GetMovingTrucks();
};