// ------------------------------------
// Name: Shane Winslow
// Assignment: Final Project Part 1 Collect Census Information
// ------------------------------------

// ------------------------------------
// Include
// ------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

// ------------------------------------
// Constants
// ------------------------------------

// ------------------------------------
// User defined type
// ------------------------------------

// ------------------------------------
// Prototypes
// ------------------------------------
void GetDate(char strDate[], char strInput[]);
void AppendString(char strDestination[], char strSource[]);
int StringLength(char strSource[]);
void AppendComma(char strDestination[]);
void StringCopy(char strDestination[], char strSource[]);
void GetState(int* intUserEntry, int* intStateCheck, char strState[], char strInput[]);
void GetCounty(int* intUserEntry, int intStateCheck, char strCounty[], char strInput[]);
void GetKentuckyCounties(int intUserEntry, char strCounty[]);
void GetOhioCounties(int intUserEntry, char strCounty[]);
void GetRace(int* intUserEntry, char strRace[], char strInput[]);
void GetHouseholdNumber(int* intHouseholdNumber, char strHouseholdNumber[], char strInput[]);
void GetHouseholdYearlyIncome(float* fltYearlyIncome, char strYearlyIncome[], char strInput[]);
void StoreEntry(char strInput[]);
void AppendEndline(char strDestination[]);

// ------------------------------------
// Name: Main
// Abstract: This is where the program starts
// ------------------------------------
void main()
{
	//Initialize variables
	int blnUserFinished = 0;
	int intResultFlag = 0;

	do {
		//Initialize Variables
		char strInput[100] = "";
		char strDate[80];
		int intUserEntry = -1;
		char strState[50];
		char strCounty[50];
		char strRace[50];
		int intHouseholdNumber = 0;
		char strHouseholdNumber[12];
		float fltYearlyIncome = 0.0;
		char strYearlyIncome[50];
		int intStateCheck = 0;

		GetDate(strDate, strInput);
		GetState(&intUserEntry, &intStateCheck, strState, strInput);
		GetCounty(&intUserEntry, intStateCheck, strCounty, strInput);
		GetRace(&intUserEntry, strRace, strInput);
		GetHouseholdNumber(&intHouseholdNumber, strHouseholdNumber, strInput);
		GetHouseholdYearlyIncome(&fltYearlyIncome, strYearlyIncome, strInput);

		StoreEntry(strInput);

		printf("Terminate program?\n");
		printf("Enter 1 - Yes, 2 - No:");
		scanf("%d", &blnUserFinished);
		printf("\n");

	} while (blnUserFinished != 1);
}


// -----------------------------------
// Name: Get Date
// Abstract: Collects the date according to the system date
// -----------------------------------
void GetDate(char strDate[], char strInput[])
{
	//Get Date
	time_t rawtime;
	struct tm* info;

	time(&rawtime);

	info = localtime(&rawtime);

	strftime(strDate, 80, "%x", info);

	AppendString(strInput, strDate);
	AppendComma(strInput);
}

// -----------------------------------
// Name: AppendString
// Abstract: Append the source to the end of the destintion.
// -----------------------------------
void AppendString(char strDestination[], char strSource[])
{
	int intDestinationLength = 0;
	int intIndex = 0;

	//Find the length
	intDestinationLength = StringLength(strDestination);
	//Copy each character
	while (strSource[intIndex] != 0)
	{
		strDestination[intDestinationLength + intIndex] = strSource[intIndex];
		intIndex += 1;
	}
	//Terminate
	strDestination[intDestinationLength + intIndex] = 0;
}

// -----------------------------------
// Name: StringLength
// Abstract: Return the string length
// -----------------------------------
int StringLength(char strSource[])
{
	int intIndex = 0;
	int intLength = 0;

	//Pre-test because string may be empty
	while (strSource[intIndex] != 0)
	{
		if (strSource[intIndex] < 32 || strSource[intIndex] > 126) break;
		intIndex += 1;
	}

	intLength = intIndex;
	return intLength;
}

// -----------------------------------
// Name: AppendComma
// Abstract: Append a comma and space to end of string
// -----------------------------------
void AppendComma(char strDestination[])
{
	int intDestinationLength = 0;
	int intIndex = 0;
	char chrComma[5] = ", ";

	//Find the length
	intDestinationLength = StringLength(strDestination);
	//Copy each character
	while (chrComma[intIndex] != 0)
	{
		strDestination[intDestinationLength + intIndex] = chrComma[intIndex];
		intIndex += 1;
	}
	//Terminate
	strDestination[intDestinationLength + intIndex] = 0;
}

// -----------------------------------
// Name: StringCopy
// Abstract: Copy the source to the destination
// -----------------------------------
void StringCopy(char strDestination[], char strSource[])
{
	int intIndex = 0;

	//Copy each character
	while (strSource[intIndex] != 0)
	{
		strDestination[intIndex] = strSource[intIndex];
		intIndex += 1;
	}
	//Terminate
	strDestination[intIndex] = 0;
}

// -----------------------------------
// Name: Get State
// Abstract: Collects the state according to the user input
// -----------------------------------
void GetState(int* intUserEntry, int* intStateCheck, char strState[], char strInput[])
{
	//Get State
	do {
		printf("Question 1: What State are you in?\n");
		printf("1 - Ohio\n");
		printf("2 - Kentucky\n");
		printf("Enter Response:");
		scanf("%d", &(*intUserEntry));
		printf("\n");

		if (*intUserEntry == 1)
		{
			*intStateCheck = 1;
			char strOhio[50] = "Ohio";
			StringCopy(strState, strOhio);
		}
		else
		{
			*intStateCheck = 2;
			char strKentucky[50] = "Kentucky";
			StringCopy(strState, strKentucky);
		}
	} while (*intUserEntry > 2 || *intUserEntry < 1);
	AppendString(strInput, strState);
	AppendComma(strInput);
}

// -----------------------------------
// Name: Get County
// Abstract: Collects the county according to the user input
// -----------------------------------
void GetCounty(int* intUserEntry, int intStateCheck, char strCounty[], char strInput[])
{
	//reset user entry variable
	*intUserEntry = -1;

	if (intStateCheck == 2)
	{
		GetKentuckyCounties(&intUserEntry, strCounty);
	}
	else
	{
		GetOhioCounties(&intUserEntry, strCounty);
	}
	AppendString(strInput, strCounty);
	AppendComma(strInput);
}

// -----------------------------------
// Name: GetKentuckyCounties
// Abstract: Get counties belonging to Kentucky
// -----------------------------------
void GetKentuckyCounties(int* intUserEntry, char strCounty[])
{
	char strKenton[50] = "Kenton";
	char strBoone[50] = "Boone";

	do {
		printf("Question 2: Which county do you belong?\n");
		printf("1 - Kenton\n");
		printf("2 - Boone\n");
		printf("Enter Response:");
		scanf("%d", &(*intUserEntry));
		printf("\n");

		if (*intUserEntry == 1)
		{
			StringCopy(strCounty, strKenton);
		}
		else
		{
			StringCopy(strCounty, strBoone);
		}
	} while (*intUserEntry > 2 || *intUserEntry < 0);

}

// -----------------------------------
// Name: GetOhioCounties
// Abstract: Get counties belonging to Ohio
// -----------------------------------
void GetOhioCounties(int* intUserEntry, char strCounty[])
{
	char strHamilton[50] = "Hamilton";
	char strButler[50] = "Butler";
	do {
		printf("Question 2: Which county do you belong?\n");
		printf("1 - Hamilton\n");
		printf("2 - Butler\n");
		printf("Enter Response:");
		scanf("%d", &(*intUserEntry));
		printf("\n");

		if (*intUserEntry == 1)
		{
			StringCopy(strCounty, strHamilton);
		}
		else
		{
			StringCopy(strCounty, strButler);
		}
	} while (*intUserEntry > 2 || *intUserEntry < 0);
}

// -----------------------------------
// Name: GetRace
// Abstract: Get the race of the head of household
// -----------------------------------
void GetRace(int* intUserEntry, char strRace[], char strInput[])
{
	//Get Race
	do {
		//reset user entry variable
		*intUserEntry = -1;

		printf("Question 3: What is the race for the head of household?\n");
		printf("1 - Caucasian\n");
		printf("2 - African-American\n");
		printf("3 - Asian\n");
		printf("4 - Hispanic\n");
		printf("5 - Other\n");
		printf("Enter Response:");
		scanf("%d", &(*intUserEntry));
		printf("\n");

		char strWhite[50] = "Caucasian";
		char strBlack[50] = "African-American";
		char strAsian[50] = "Asian";
		char strHispanic[50] = "Hispanic";
		char strOther[50] = "Other";

		switch (*intUserEntry)
		{
		case 1: StringCopy(strRace, strWhite);
			break;
		case 2: StringCopy(strRace, strBlack);
			break;
		case 3: StringCopy(strRace, strAsian);
			break;
		case 4: StringCopy(strRace, strHispanic);
			break;
		case 5: StringCopy(strRace, strOther);
			break;
		}

	} while (intUserEntry > 5 && intUserEntry < 1);

	AppendString(strInput, strRace);
	AppendComma(strInput);
}

// -----------------------------------
// Name: GetHouseholdNumber
// Abstract: Get the number of individuals within the household
// -----------------------------------
void GetHouseholdNumber(int* intHouseholdNumber, char strHouseholdNumber[], char strInput[])
{
	//Get Number in Household
	do {
		printf("Question 4: How many individuals do you have in your household?\n");
		printf("Enter value:");
		scanf("%d", &(*intHouseholdNumber));
		printf("\n");

	} while (*intHouseholdNumber <= 0);

	sprintf(strHouseholdNumber, "%d", *intHouseholdNumber);
	AppendString(strInput, strHouseholdNumber);
	AppendComma(strInput);
}

// -----------------------------------
// Name: Get Household Yearly Income
// Abstract: Gets the household yearly income
// -----------------------------------
void GetHouseholdYearlyIncome(float* fltYearlyIncome, char strYearlyIncome[], char strInput[])
{
	//Get Household Yearly Income
	do {
		printf("Question 5: What is your household yearly income?\n");
		printf("Enter value:");
		scanf("%f", &(*fltYearlyIncome));
		printf("\n");

	} while (*fltYearlyIncome <= 0);

	sprintf(strYearlyIncome, "%.2f", *fltYearlyIncome);
	AppendString(strInput, strYearlyIncome);
	AppendEndline(strInput);
}

// -----------------------------------
// Name: AppendNewline
// Abstract: Append an newline and carriage return to end of input string
// -----------------------------------
void AppendEndline(char strDestination[])
{
	int intDestinationLength = 0;
	int intIndex = 0;
	char strNewline[5] = "\n";

	//Find the length
	intDestinationLength = StringLength(strDestination);
	//Copy each character
	while (strNewline[intIndex] != 0)
	{
		strDestination[intDestinationLength + intIndex] = strNewline[intIndex];
		intIndex += 1;
	}
	//Terminate
	strDestination[intDestinationLength + intIndex] = 0;
}

// -----------------------------------
// Name: StoreEntry
// Abstract: Stores new entry in external text file
// -----------------------------------
void StoreEntry(char strInput[])
{
	FILE* fp;
	//Try to open the file for reading (notice you have to double up the backslashes)
	fp = fopen("C:\\Users\\eseinhart\\Desktop\\ExampleProjects\\testC\\Destination\\Census.txt", "a");

	//Insert String into text file
	fputs(strInput, fp);

	//Close connection to text file
	fclose(fp);
}