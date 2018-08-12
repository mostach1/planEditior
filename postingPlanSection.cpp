#include<fstream>
#include<string>
#include "postingPlanSection.h"
using namespace std;

const int section_lines = 19; //number of calculation in section

void addNewSection(fstream &inputFile, fstream &outputFile, inputSectionInfo &inputValue)
{
	string sectionLine[19]; //table with lines
	string line;
	int number_of_calculation_counter = 0; //count how many lines contain "wanted" posting plan
	clearSectionLinesTable(sectionLine);

	///////////////PATTERNS/////////////////////
	string postingPlan = "#PLAN:" + std::to_string(inputValue.in_planNumber) + ":#";
	string nextPostingPlan = "#PLAN:" + std::to_string(inputValue.in_planNumber + 1) + ":#";
	string wantedPlanBody = std::to_string(inputValue.in_planNumber) + "  ";

	int lines_counter = 0;
	bool goodPlanFoundedFlag = false;
	bool beforeWantedPlanFlag = true;
	bool afterWantedPlanAdded = false;
	
	while (getline(inputFile, line, '\n')) //read all lines from input file
	{
		if (beforeWantedPlanFlag) //write all lines before wanted plan to output file 
			outputFile << line << endl;

		if (isWantedPlan(line, postingPlan)) //find wated plan
		{
			goodPlanFoundedFlag = true;
			beforeWantedPlanFlag = false;
		}
		else if (isNextPlan(line, nextPostingPlan)) //find next plan and set goodPlanFoundedFlag to false
		{
			goodPlanFoundedFlag = false;
			//crating own section and adding to outputfile
			fillSectionLinesTable(sectionLine, inputValue, number_of_calculation_counter);
			saveToFile(outputFile, sectionLine);
			afterWantedPlanAdded = true;
		}

		if (goodPlanFoundedFlag && isWanted(line, wantedPlanBody))
		{
			number_of_calculation_counter++;
			outputFile << line << endl;
		}

		if (afterWantedPlanAdded) //added rest postingPlans
			outputFile << line << endl;

		lines_counter++;
	} //while
}

bool isWanted(const std::string & line, string wantedPlanBody)
{
	// if wanted posting plan body return true
	return (line.find(wantedPlanBody) != string::npos);
}

bool isWantedPlan(const std::string & line, string postingPlan)
{
	// if wanted posting plan return true
	return (line.find(postingPlan) != string::npos);
}

bool isNextPlan(const std::string & line, string postingNextPlan)
{
	// if next posting plan return true
	return (line.find(postingNextPlan) != string::npos);
}

void clearSectionLinesTable(string (&sectionLine)[19])
{
	for (int i = 0; i < 19; i++)
	{
		sectionLine[i] = "";
	}
}

void fillSectionLinesTable(string(&sectionLine)[19], inputSectionInfo &inputValue, int &number_of_calculation_counter)
{
	int number_of_section = number_of_calculation_counter / section_lines; //number of section which plan contains
	string constantStarter = to_string(inputValue.in_planNumber) + "  " + to_string(number_of_section + 1) + "  ";
	sectionLine[0] = constantStarter + "0   FOR_EACH_MATCHING_ROW_IN_OBJECT_DO_TASK(OBJ_LEVEL_TAG_TO_SCAN=H." + to_string(inputValue.in_objLevelNumber) + "." + to_string(inputValue.in_tagToScanNumber) + ",VAL_TO_MATCH=E." + to_string(inputValue.in_valToMatchNumber) + ")";
	sectionLine[1] = constantStarter + "1   LEDGER_ACCOUNT=" + to_string(inputValue.in_ledger_account_number);
	sectionLine[2] = constantStarter + "2   SHARE_CLASS=TF";
	sectionLine[3] = constantStarter + "3   LEDGER_AMOUNT=R." + to_string(inputValue.in_ledger_amount);
	sectionLine[4] = constantStarter + "4   LEDGER_DR_CR=" + inputValue.in_ledger_debit_credit;
	sectionLine[5] = constantStarter + "5   ACCOUNT=E.5";
	sectionLine[6] = constantStarter + "6   ASSET=E.10";
	sectionLine[7] = constantStarter + "7   ACCTG_BASIS=E.21";
	sectionLine[8] = constantStarter + "8   ASSET_CURRENCY=E.85";
	sectionLine[9] = constantStarter + "9   ACCT_CURRENCY=E.85";
	sectionLine[10] = constantStarter + "10  OPEN_EVENT_ID=E.15";
	sectionLine[11] = constantStarter + "11  CLS_EVENT_ID=0";
	sectionLine[12] = constantStarter + "12  EVENT_ID=E.25";
	sectionLine[13] = constantStarter + "13  POST_DT=E.30";
	sectionLine[14] = constantStarter + "14  TRADE_DT=E.35";
	sectionLine[15] = constantStarter + "15  ACCTG_DT=E.36";
	sectionLine[16] = constantStarter + "16  HISTORY_TYPE=E.20";
	sectionLine[17] = constantStarter + "17  MNTHLY_ACCT_PER_DATE=E.4733";
	sectionLine[18] = constantStarter + "18  NAV_ID=E.3196";
}

void saveToFile(fstream &outputFile, string(&sectionLine)[19])
{
	for (int i = 0; i < 19; i++)
	{
		outputFile << sectionLine[i] << endl;
	}
}
