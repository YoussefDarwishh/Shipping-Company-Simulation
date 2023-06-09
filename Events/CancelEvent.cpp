#include "CancelEvent.h"
CancelEvent::CancelEvent(int ID, int EventDay, int EventHour, Company* CompanyPTR) : Event(EventDay,EventHour, CompanyPTR)
{
	ID = ID;
}

CancelEvent::~CancelEvent()
{

}

void CancelEvent:: Execute()
{
	CompanyPtr->Cancel(ID);

}