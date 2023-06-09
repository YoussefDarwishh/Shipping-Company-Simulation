#pragma once
#include "Event.h"
#include "Cargo.h"

class PromoteEvent:public Event
{
private:
int ID;
int ExtraMoney;


public:
	PromoteEvent(int ID, int Extra, int EventDay, int EventHour, Company* CompanyPTR);
	void Execute();
	~PromoteEvent();
};

