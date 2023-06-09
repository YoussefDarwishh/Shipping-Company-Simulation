#include <iostream>
#include "Queue.h"
#include<fstream>
#include"Company.h"

using namespace std;

int main()
{
	Company* CompanyPTR=new Company();
	CompanyPTR->Simulate();
	delete CompanyPTR;
	return 0;
}