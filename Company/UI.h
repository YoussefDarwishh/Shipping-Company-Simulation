#pragma once
#include<iostream>
#include"Company.h"
#include <chrono>
#include <thread>
#include <string>
class Company;
using namespace std;
class UI
{
	string OutputFile;
	int Mode;
public:
	string AskMode();
	void ModEffect(Company* CompanyPTR,int Hour,int Day);
	void Print(Company* CompanyPTR);
	string GetOutput() const;
	void PrintFail();
};