#pragma once
#include "Event.h"
#include "Cargo.h"
class Company;
class Preparation:public Event
{

private:
	Cargo*Cargoptr;

public:

	Preparation(char Type, int ID, int Distance, int LoadTime, int Cost, int EventDay,int EventHour, Company* CompanyPTR);
	virtual void Execute();
	~Preparation();
};

