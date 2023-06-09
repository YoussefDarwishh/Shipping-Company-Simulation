#include "Event.h"
Event::Event(int Day,int Hour,Company*Ptr)
{
	EventDay = Day;
	EventHour = Hour;
	CompanyPtr = Ptr;
}
bool Event::IsTime(int Hours, int Days)
{
	return (EventDay == Days && EventHour == Hours);
}

Event::~Event()
{
}