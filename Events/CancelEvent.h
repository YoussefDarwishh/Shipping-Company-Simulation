#pragma once
#include "Event.h"


class CancelEvent:public Event
{
private:
	int ID;

public:
	CancelEvent(int ID, int EventDay, int EventHour,  Company* CompanyPTR);

	~CancelEvent();

	void Execute();
};

