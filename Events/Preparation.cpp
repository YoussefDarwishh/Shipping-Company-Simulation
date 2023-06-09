#include "Preparation.h"
Preparation:: Preparation(char Type, int ID, int Distance, int LoadTime, int Cost, int EventDay,int EventHour, Company* CompanyPTR) : Event(EventDay,EventHour, CompanyPTR)
{
	Cargoptr = new Cargo(Type, ID, Distance, LoadTime, Cost,EventHour,EventDay);
}


void Preparation:: Execute()
{
	if (Cargoptr->GetType() == 3)
	{
		CompanyPtr->AddCargo(Cargoptr, Cargoptr->CalculatePriority());
		return;

	}
	CompanyPtr->AddCargo(Cargoptr);
}


Preparation::~Preparation()
{
}
