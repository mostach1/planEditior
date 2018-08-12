#include <iostream>
#include<fstream>
#include<string>
using namespace std;

struct inputSectionInfo
{
	int in_planNumber;
	int in_objLevelNumber;
	int in_tagToScanNumber;
	int in_valToMatchNumber;
	int in_ledger_account_number;
	int in_ledger_amount;
	string in_ledger_debit_credit;

	inputSectionInfo() : in_planNumber(0),
		in_objLevelNumber(0),
		in_tagToScanNumber(0),
		in_valToMatchNumber(0),
		in_ledger_account_number(0),
		in_ledger_amount(0),
		in_ledger_debit_credit("")
	{}

};

void addNewSection(fstream &inputFile, fstream &outputFile, inputSectionInfo &inputValue);
static void saveToFile(fstream &outputFile, string(&sectionLine)[19]);
static void fillSectionLinesTable(string(&sectionLine)[19], inputSectionInfo &inputValue, int &number_of_calculation_counter);
static void clearSectionLinesTable(string(&sectionLine)[19]);
static bool isNextPlan(const std::string & line, string postingNextPlan);
static bool isWantedPlan(const std::string & line, string postingPlan);
static bool isWanted(const std::string & line, string wantedPlanBody);
