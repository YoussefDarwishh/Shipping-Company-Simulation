#pragma once
#include"Company.h"
class Company;
class Event
{
private:
	int EventDay;
	int EventHour;

protected:
	Company* CompanyPtr;

public:
	Event(int Day,int Hour,Company*CompanyPTR);
	virtual void Execute() = 0;
	bool IsTime(int Hours, int Day);
	virtual ~Event();
};