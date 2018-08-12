#include<iostream>
#include<fstream>
#include<string>
#include"postingPlanSection.h"
using namespace std;

bool isWantedPlan(const std::string & line, string postingPlan);
bool isNextPlan(const std::string & line, string postingNextPlan);
bool isWanted(const std::string & line, string wantedPlan);

int main()
{
	fstream inputFile("postmtrx.dat", ios::in); //input file
	remove("postmtrx_tmp.dat"); //remove file if exist
	fstream outputFile("postmtrx_tmp.dat", ios::out | ios::app); //output file

	if (!inputFile.is_open())
		cout << "Cannot open a file" << endl;
	else
		cout << "File opened succesfully"<<endl;

	inputSectionInfo inputValue;
	inputValue.in_planNumber = 3;
	inputValue.in_objLevelNumber = 150;
	inputValue.in_tagToScanNumber = 35; 
	inputValue.in_valToMatchNumber = 20;
	inputValue.in_ledger_account_number = 567854001;
	inputValue.in_ledger_amount = 599;
	inputValue.in_ledger_debit_credit = "cr";

	addNewSection(inputFile, outputFile, inputValue);
	//addNewPlan();

	inputFile.close();
	outputFile.close();
	system("pause");

	return 0;
}
