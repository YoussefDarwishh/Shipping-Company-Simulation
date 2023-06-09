#include "PromoteEvent.h"
PromoteEvent::PromoteEvent(int ID, int Extra, int EventDay, int EventHour, Company* CompanyPTR) : Event(EventDay,EventHour, CompanyPTR)
{
	ID = ID;
	ExtraMoney = Extra;
}


void PromoteEvent::Execute()
{
	CompanyPtr->Promote(ID, ExtraMoney);

}



PromoteEvent::~PromoteEvent()
{

}