// ------------------------------------
// Name: Shane Winslow
// Assignment: Final Project Part 2
// ------------------------------------

// ------------------------------------
// Include
// ------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

// ------------------------------------
// Constants
// ------------------------------------
const int intARRAY_SIZE = 100;

// ------------------------------------
// User defined type
// ------------------------------------
typedef struct
{
	char strDate[50];
	char strState[50];
	char strCounty[50];
	char strRace[50];
	int intHouseholdNumber;
	float fltYearIncome;
} udtCensusRecord;

// ------------------------------------
// Prototypes
// ------------------------------------
void InitializeCensusRecordList(udtCensusRecord audtCensusRecordList[]);
void InitializeCensusRecord(udtCensusRecord* pudtCensusRecord);
void StringCopy(char strDestination[], char strSource[]);
void PopulateCensusRecordList(udtCensusRecord audtCensusRecordList[]);
int OpenInputFile(char strFileName[], FILE** ppfillInput);
void AppendCharacter(char strDestination[], char chrLettertoAppend);
int StringLength(char strSource[]);
void ModifyOriginalCensusRecord(char strSource[], int intStartingIndex);
void AddCensusRecordToArray(char strCensusRecord[], udtCensusRecord* pudtCensusRecord);
void AppendString(char strDestination[], char strSource[]);
void GetNextField(char strNextField[], char strAddress[]);
int FindLetterIndex(char strSource[], char chrLetterToFind);
void CopyWord(char strNextField[], char strAddress[], int intIndexEndPosition);
void Trim(char strSource[]);
bool IsWhiteSpace(char chrLetterToCheck);
void PrintCensusRecordList(udtCensusRecord audtCensusRecordList[]);
void PrintCensusRecord(int intIndex, udtCensusRecord udtCensus);
void PromptUserSelection(udtCensusRecord audtCensusRecordList[]);
void TotalHouseholdsSurveyed(udtCensusRecord audtCensusRecordList[]);
void TotalHouseholdsSurveyedCounty(udtCensusRecord audtCensusRecordList[]);
void TotalHouseholdbyRace(udtCensusRecord audtCensusRecordList[]);
void AverageHouseholdIncome(udtCensusRecord audtCensusRecordList[]);
void AverageHouseholdbyCountyState(udtCensusRecord audtCensusRecordList[]);
void AverageHouseholdbyRace(udtCensusRecord audtCensusRecordList[]);
void PercentageBelowPoverty(udtCensusRecord audtCensusRecordList[]);
void PercentageBelowPovertybyCountyState(udtCensusRecord audtCensusRecordList[]);
void PercentageBelowPovertybyRace(udtCensusRecord audtCensusRecordList[]);

// ------------------------------------
// Name: Main
// Abstract: This is where the program starts
// ------------------------------------
void main()
{
	udtCensusRecord audtCensusRecordList[100];
	InitializeCensusRecordList(audtCensusRecordList);
	PopulateCensusRecordList(&audtCensusRecordList);
	//PrintCensusRecordList(audtCensusRecordList);

	PromptUserSelection(audtCensusRecordList);

	printf("\n");
	system("pause");

}

// -----------------------------------
// Name: Initialize Census Record List
// Abstract: Initialize all the Census Records in the List
// -----------------------------------
void InitializeCensusRecordList(udtCensusRecord audtCensusRecordList[])
{
	int intIndex = 0;

	for (intIndex = 0; intIndex < intARRAY_SIZE; intIndex += 1)
	{
		//Pass a single array element by pointer
		InitializeCensusRecord(&audtCensusRecordList[intIndex]);
	}
}

// -----------------------------------
// Name: Initalize Census Record
// Abstract: Set all the values to 0 or empty strings.
// -----------------------------------
void InitializeCensusRecord(udtCensusRecord* pudtCensusRecord)
{
	//Use -> or *(). syntax. Both are functionally equivalent
	StringCopy(pudtCensusRecord->strDate, "");
	StringCopy(pudtCensusRecord->strState, "");
	StringCopy(pudtCensusRecord->strCounty, "");
	StringCopy(pudtCensusRecord->strRace, "");
	pudtCensusRecord->intHouseholdNumber = 0;
	pudtCensusRecord->fltYearIncome = 0.0;
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
// Name: Populate Census Record List
// Abstract: Load the census records from a file into the array.
// -----------------------------------
void PopulateCensusRecordList(udtCensusRecord audtCensusRecordList[])
{
	//Declare a file pointer
	FILE* pfillInput = 0;
	int intResultFlag = 0;
	char strBuffer[100] = "";
	char chrLetter = 0;
	int intIndex = 0;
	char strDestination[100] = "";

	//Try to open the file for reading (notice you have to double up the backslashes)
	intResultFlag = OpenInputFile("C:\\Users\\eseinhart\\Desktop\\ExampleProjects\\Github Portfolio\\C\\BaseCCensusProject\\Destination\\Census.txt", &pfillInput);

	//Was the file opened?
	if (intResultFlag == 1)
	{
		//Yes, read in records until end of file (EOF) - loop through lines inside txt file and store them
		while (feof(pfillInput) == 0)
		{
			//Declare new Source string
			char strSource[100] = "";

			//Sort through characters in line to store in Source string
			while (chrLetter != EOF)
			{
				chrLetter = fgetc(pfillInput);
				if (chrLetter == '\r') break;
				if (chrLetter == '\n') break;
				if (chrLetter == EOF) break;
				AppendCharacter(strSource, chrLetter);

			}

			//Once end of line with regular characters, begin to store Source string into structure variables
			while (chrLetter == '\r')
			{
				//Assign Source string to structure variables
				AddCensusRecordToArray(strSource, &audtCensusRecordList[intIndex]);

				//Move to next structure inside Structure Array List
				intIndex += 1;

				//break to move to next character after '\r' in txt file
				break;
			}
		}
		//Clean up
		fclose(pfillInput);
	}
}

// -----------------------------------
// Name: OpenInputFile
// Abstract: Open the file for reading. Return true if successful.
// -----------------------------------
int OpenInputFile(char strFileName[], FILE** ppfillInput)
{
	int intResultFlag = 0;

	//Open the file for reading
	*ppfillInput = fopen(strFileName, "rb");
	if (*ppfillInput != 0)
	{
		//Yes
		intResultFlag = 1;
	}
	else
	{
		//No
		printf("Error opening %s for reading!\n", strFileName);
	}

	return intResultFlag;
}

// -----------------------------------
// Name: AppendCharacter
// Abstract: Appends a single character to a string letter by letter
// -----------------------------------
void AppendCharacter(char strDestination[], char chrLettertoAppend)
{
	int intDestinationLength = 0;
	int intTerminationIndex = 0;

	//Find the length
	intDestinationLength = StringLength(strDestination);
	intTerminationIndex = intDestinationLength + 1;

	//Insert the character and terminate
	strDestination[intDestinationLength] = chrLettertoAppend;
	strDestination[intTerminationIndex] = 0;
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
// Name: AddCensusRecordToArray
// Abstract: Add census record to the array
// -----------------------------------
void AddCensusRecordToArray(char strCensusRecord[], udtCensusRecord* pudtCensusRecord)
{
	char strNextField[50] = "";
	char strCommaDelimiter[50] = ",";

	//Append a comma so parsing last field is just like all the others
	AppendString(strCensusRecord, strCommaDelimiter);

	//Date
	GetNextField(strNextField, strCensusRecord);
	StringCopy(pudtCensusRecord->strDate, strNextField);

	//State
	GetNextField(strNextField, strCensusRecord);
	StringCopy(pudtCensusRecord->strState, strNextField);

	//County
	GetNextField(strNextField, strCensusRecord);
	StringCopy(pudtCensusRecord->strCounty, strNextField);

	//Race
	GetNextField(strNextField, strCensusRecord);
	StringCopy(pudtCensusRecord->strRace, strNextField);

	//Number in Household
	GetNextField(strNextField, strCensusRecord);
	pudtCensusRecord->intHouseholdNumber = atoi(strNextField);

	//Household Yearly Income
	GetNextField(strNextField, strCensusRecord);
	pudtCensusRecord->fltYearIncome = atof(strNextField);
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

//------------------------------------
// Name: GetNextField
// Abstract: Retrieves the next field to be stored in structure item
// -----------------------------------
void GetNextField(char strNextField[], char strAddress[])
{
	char chrLettertoFind = ',';
	int intIndexofLetterToFind = 0;

	intIndexofLetterToFind = FindLetterIndex(strAddress, chrLettertoFind);
	CopyWord(strNextField, strAddress, intIndexofLetterToFind);
	Trim(strNextField);
	ModifyOriginalCensusRecord(strAddress, intIndexofLetterToFind);
	Trim(strAddress);
}

// -----------------------------------
// Name: ModifyOriginalCensusRecord
// Abstract: Create a substring of the original Census Record string
// -----------------------------------
void ModifyOriginalCensusRecord(char strSource[], int intStartingIndex)
{
	int intIndex = 0;
	int intDestinationIndex = 0;
	intIndex = intStartingIndex + 1;

	while (strSource[intIndex] != 0)
	{
		strSource[intDestinationIndex] = strSource[intIndex];
		intDestinationIndex += 1;
		intIndex += 1;
	}
	//terminate
	strSource[intDestinationIndex] = 0;
}

// -----------------------------------
// Name: FindLetterIndex
// Abstract: Find the first occurence of letter (case-sensitive) from left to right.
// -----------------------------------
int FindLetterIndex(char strSource[], char chrLetterToFind)
{
	int intLetterToFindIndex = -1;
	int intIndex = 0;

	//Check character
	while (strSource[intIndex] != 0)
	{
		//Is this the character for which we are looking
		if (strSource[intIndex] == chrLetterToFind)
		{
			//Yes, save the index
			intLetterToFindIndex = intIndex;

			//Stop searching
			break;
		}
		intIndex += 1;
	}
	return intLetterToFindIndex;
}

//-----------------------------------
//Name: Copy Word
//Abstract: Copies word according to indexed letter position
// -----------------------------------
void CopyWord(char strNextField[], char strAddress[], int intIndexEndPosition)
{
	int intIndex = 0;
	if (intIndexEndPosition == -1)
	{
		intIndexEndPosition = StringLength(strAddress);
	}

	for (intIndex = 0; intIndex < intIndexEndPosition; intIndex += 1)
	{
		strNextField[intIndex] = strAddress[intIndex];
	}
	//Teriminate
	strNextField[intIndex] = 0;
}

// -----------------------------------
// Name: Trim
// Abstract: Remove leading and trailing whitespace (space, tab or newline)
// -----------------------------------
void Trim(char strSource[])
{
	int intIndex = 0;
	int intFirstNonWhitespaceIndex = -1;
	int intLastNonWhitespaceIndex = 0;
	int intSourceIndex = 0;
	int intDestinationIndex = 0;

	//Default first non-whitespace character index to end of string in case string is all whitespace
	intFirstNonWhitespaceIndex = StringLength(strSource);

	//Find first non-whitespace character
	while (strSource[intIndex] != 0)
	{
		//Non-whitespace character?
		if (IsWhiteSpace(strSource[intIndex]) == false)
		{
			//Yes, save the index
			intFirstNonWhitespaceIndex = intIndex;

			//Stop searching!
			break;
		}
		//Next character
		intIndex += 1;
	}
	//Find the last non-whitespace character
	while (strSource[intIndex] != 0)
	{
		//Non-whitespace character?
		if (IsWhiteSpace(strSource[intIndex]) == false)
		{
			//Yes, save the index
			intLastNonWhitespaceIndex = intIndex;
		}

		//Next character
		intIndex += 1;
	}

	//Any non-whitespace characters?
	if (intFirstNonWhitespaceIndex >= 0)
	{
		//Yes, copy everything in between
		for (intSourceIndex = intFirstNonWhitespaceIndex; intSourceIndex <= intLastNonWhitespaceIndex; intSourceIndex += 1)
		{
			//Copy next character
			strSource[intDestinationIndex] = strSource[intSourceIndex];
			intDestinationIndex += 1;
		}
	}
	// Terminate
	strSource[intDestinationIndex] = 0;
}

// -----------------------------------
// Name: IsWhiteSpace
// Abstract: Return true if letter is a space, tab, newline or carriage return
// -----------------------------------
bool IsWhiteSpace(char chrLetterToCheck)
{
	bool blnIsWhiteSpace = false;

	//Space
	if (chrLetterToCheck == ' ') blnIsWhiteSpace = true;

	//Tab
	if (chrLetterToCheck == '\t') blnIsWhiteSpace = true;

	//Carriage Return
	if (chrLetterToCheck == '\r') blnIsWhiteSpace = true;

	//Line feed
	if (chrLetterToCheck == '\n') blnIsWhiteSpace = true;

	return blnIsWhiteSpace;
}

// -----------------------------------
// Name: PrintCensusRecordList
// Abstract: Print all the Census Records 
// -----------------------------------
void PrintCensusRecordList(udtCensusRecord audtCensusRecordList[])
{
	int intIndex = 0;

	while (audtCensusRecordList[intIndex].intHouseholdNumber != 0)
	{
		//Pass a single array element by pointer
		PrintCensusRecord(intIndex, audtCensusRecordList[intIndex]);
		intIndex += 1;
	}
}

// -----------------------------------
// Name: PrintAddress
// Abstract: Print all the structure field values
// -----------------------------------
void PrintCensusRecord(int intIndex, udtCensusRecord udtCensusRecord)
{
	printf("\n");
	printf("Census Record #%2d ---------------------------------------\n", intIndex + 1);
	printf("\tDate	: %s\n", udtCensusRecord.strDate);
	printf("\tState	: %s\n", udtCensusRecord.strState);
	printf("\tCounty	: %s\n", udtCensusRecord.strCounty);
	printf("\tRace	: %s\n", udtCensusRecord.strRace);
	printf("\tNumber in Household	: %d\n", udtCensusRecord.intHouseholdNumber);
	printf("\tYearly Household Income		: %f\n", udtCensusRecord.fltYearIncome);
}

// -----------------------------------
// Name: PromptUserSelection
// Abstract: Prompt User for certain information on census records
// -----------------------------------
void PromptUserSelection(udtCensusRecord audtCensusRecordList[])
{
	char chrUserSelection;
	do {
		//Initialize Variable

		printf("Please enter vale from the following options for information:\n");
		printf("\n");
		printf("A. Total Households Surveyed\n");
		printf("B. Total Household Surveyed by County\n");
		printf("C. Total Households Survey by Race\n");
		printf("D. Average Household Income\n");
		printf("E. Average Household Income by County and State\n");
		printf("F. Average Household Income by Race\n");
		printf("G. Percentage Below Poverty\n");
		printf("H. Percentage Below Poverty by County and State\n");
		printf("I. Percentage Below Poverty by Race\n");
		printf("\n");
		printf("Enter 'Z' to exit\n");
		printf("---------------------------------------\n");
		printf("Enter Selection:");
		scanf("%c", &chrUserSelection);
		while ((getchar()) != '\n');
		printf("\n");

		switch (chrUserSelection)
		{
		case 'A': TotalHouseholdsSurveyed(audtCensusRecordList);
			break;
		case 'B': TotalHouseholdsSurveyedCounty(audtCensusRecordList);
			break;
		case 'C': TotalHouseholdbyRace(audtCensusRecordList);
			break;
		case 'D': AverageHouseholdIncome(audtCensusRecordList);
			break;
		case 'E': AverageHouseholdbyCountyState(audtCensusRecordList);
			break;
		case 'F': AverageHouseholdbyRace(audtCensusRecordList);
			break;
		case 'G': PercentageBelowPoverty(audtCensusRecordList);
			break;
		case 'H': PercentageBelowPovertybyCountyState(audtCensusRecordList);
			break;
		case 'I': PercentageBelowPovertybyRace(audtCensusRecordList);
			break;
		}
	} while (chrUserSelection != 'Z');
}

// ---------------------------------
// Name: TotalHouseholdsSurveyed
// Abstract: Calculates the total number of census records collected
// ---------------------------------
void TotalHouseholdsSurveyed(udtCensusRecord audtCensusRecordList[])
{
	int intTotalNumberHouseholds = 0;
	int intIndex = 0;
	int intCount = 0;

	while (audtCensusRecordList[intIndex].intHouseholdNumber != 0)
	{
		intCount += 1;
		intIndex += 1;
	}

	printf("Total Households Surveyed: %d\n", intCount);
	printf("\n");
}

// ---------------------------------
// Name: TotalHouseholdsSurveyedPerCounty
// Abstract: Calculates the total number of census records collected per county
// ---------------------------------
void TotalHouseholdsSurveyedCounty(udtCensusRecord audtCensusRecordList[])
{
	int intTotalNumberHouseholdsKenton = 0;
	int intTotalNumberHouseholdsBoone = 0;
	int intTotalNumberHouseholdsButler = 0;
	int intTotalNumberHouseholdsHamilton = 0;
	int intIndex = 0;

	while (audtCensusRecordList[intIndex].intHouseholdNumber != 0)
	{
		if (strcmp(audtCensusRecordList[intIndex].strCounty, "Hamilton") == 0) { intTotalNumberHouseholdsHamilton += 1; }
		if (strcmp(audtCensusRecordList[intIndex].strCounty, "Butler") == 0) { intTotalNumberHouseholdsButler += 1; }
		if (strcmp(audtCensusRecordList[intIndex].strCounty, "Boone") == 0) { intTotalNumberHouseholdsBoone += 1; }
		if (strcmp(audtCensusRecordList[intIndex].strCounty, "Kenton") == 0) { intTotalNumberHouseholdsKenton += 1; }

		intIndex += 1;
	}

	printf("Total Househoulds Surveyed by County:\n");
	printf("\n");
	printf(" Hamilton: %d\n", intTotalNumberHouseholdsHamilton);
	printf(" Butler:   %d\n", intTotalNumberHouseholdsButler);
	printf(" Kenton:   %d\n", intTotalNumberHouseholdsKenton);
	printf(" Boone:    %d\n", intTotalNumberHouseholdsBoone);
	printf("\n");
}

// ---------------------------------
// Name: TotalHouseholdbyRace
// Abstract: Calculates the total number of census records collected by race
// ---------------------------------
void TotalHouseholdbyRace(udtCensusRecord audtCensusRecordList[])
{
	int intIndex = 0;
	int intCensusWhite = 0;
	int intCensusBlack = 0;
	int intCensusAsian = 0;
	int intCensusHispanic = 0;
	int intCensusOther = 0;

	while (audtCensusRecordList[intIndex].intHouseholdNumber != 0)
	{
		if (strcmp(audtCensusRecordList[intIndex].strRace, "Caucasian") == 0) { intCensusWhite += 1; }
		if (strcmp(audtCensusRecordList[intIndex].strRace, "African-American") == 0) { intCensusBlack += 1; }
		if (strcmp(audtCensusRecordList[intIndex].strRace, "Asian") == 0) { intCensusAsian += 1; }
		if (strcmp(audtCensusRecordList[intIndex].strRace, "Hispanic") == 0) { intCensusHispanic += 1; }
		if (strcmp(audtCensusRecordList[intIndex].strRace, "Other") == 0) { intCensusOther += 1; }

		intIndex += 1;
	}
	printf("Total Households Surveyed by Race\n");
	printf("\n");
	printf(" Caucasian:        %d\n", intCensusWhite);
	printf(" African-American: %d\n", intCensusBlack);
	printf(" Asian:            %d\n", intCensusAsian);
	printf(" Hispanic:         %d\n", intCensusHispanic);
	printf(" Other:            %d\n", intCensusOther);
	printf("\n");
}

// ---------------------------------
// Name: AverageHouseholdIncome
// Abstract: Calculates the average household income of all census records collected
// ---------------------------------
void AverageHouseholdIncome(udtCensusRecord audtCensusRecordList[])
{
	int intTotalNumberHouseholds = 0;
	float fltTotalHouseholdIncomes = 0.0;
	float fltAverageHouseholdIncome = 0.0;
	int intIndex = 0;
	int intCount = 0;

	while (audtCensusRecordList[intIndex].intHouseholdNumber != 0)
	{
		fltTotalHouseholdIncomes += audtCensusRecordList[intIndex].fltYearIncome;
		intCount += 1;
		intIndex += 1;
	}

	fltAverageHouseholdIncome = fltTotalHouseholdIncomes / intCount;

	printf("Average Yearly Household Income Surveyed: $%.2f\n", fltAverageHouseholdIncome);
	printf("\n");
}

// ---------------------------------
// Name: AverageHouseholdbyCountyState
// Abstract: Calculates the average household income by county and state
// ---------------------------------
void AverageHouseholdbyCountyState(udtCensusRecord audtCensusRecordList[])
{
	int intIndex = 0;

	int intTotalNumberHouseholdOhio = 0;
	int intTotalNumberHouseholdHamilton = 0;
	int intTotalNumberHouseholdButler = 0;
	int intTotalNumberHouseholdKentucky = 0;
	int intTotalNumberHouseholdKenton = 0;
	int intTotalNumberHouseholdBoone = 0;

	float fltAverageHouseholdOhio = 0.0;
	float fltAverageHouseholdHamilton = 0.0;
	float fltAverageHouseholdButler = 0.0;
	float fltAverageHouseholdKentucky = 0.0;
	float fltAverageHouseholdBoone = 0.0;
	float fltAverageHouseholdKenton = 0.0;

	float fltTotalYearlyOhio = 0.0;
	float fltTotalYearlyHamilton = 0.0;
	float fltTotalYearlyButler = 0.0;
	float fltTotalYearlyKentucky = 0.0;
	float fltTotalYearlyKenton = 0.0;
	float fltTotalYearlyBoone = 0.0;

	while (audtCensusRecordList[intIndex].intHouseholdNumber != 0)
	{
		if (strcmp(audtCensusRecordList[intIndex].strCounty, "Hamilton") == 0)
		{
			intTotalNumberHouseholdHamilton += 1;
			fltTotalYearlyHamilton += audtCensusRecordList[intIndex].fltYearIncome;
			intTotalNumberHouseholdOhio += 1;
			fltTotalYearlyOhio += audtCensusRecordList[intIndex].fltYearIncome;
		}
		if (strcmp(audtCensusRecordList[intIndex].strCounty, "Butler") == 0)
		{
			intTotalNumberHouseholdButler += 1;
			fltTotalYearlyButler += audtCensusRecordList[intIndex].fltYearIncome;
			intTotalNumberHouseholdOhio += 1;
			fltTotalYearlyOhio += audtCensusRecordList[intIndex].fltYearIncome;
		}
		if (strcmp(audtCensusRecordList[intIndex].strCounty, "Boone") == 0)
		{
			intTotalNumberHouseholdBoone += 1;
			fltTotalYearlyBoone += audtCensusRecordList[intIndex].fltYearIncome;
			intTotalNumberHouseholdKentucky += 1;
			fltTotalYearlyKentucky += audtCensusRecordList[intIndex].fltYearIncome;
		}
		if (strcmp(audtCensusRecordList[intIndex].strCounty, "Kenton") == 0)
		{
			intTotalNumberHouseholdKenton += 1;
			fltTotalYearlyKenton += audtCensusRecordList[intIndex].fltYearIncome;
			intTotalNumberHouseholdKentucky += 1;
			fltTotalYearlyKentucky += audtCensusRecordList[intIndex].fltYearIncome;
		}
		intIndex += 1;
	}

	fltAverageHouseholdHamilton = fltTotalYearlyHamilton / intTotalNumberHouseholdHamilton;
	fltAverageHouseholdButler = fltTotalYearlyButler / intTotalNumberHouseholdButler;
	fltAverageHouseholdKenton = fltTotalYearlyKenton / intTotalNumberHouseholdKenton;
	fltAverageHouseholdBoone = fltTotalYearlyBoone / intTotalNumberHouseholdBoone;
	fltAverageHouseholdOhio = fltTotalYearlyOhio / intTotalNumberHouseholdOhio;
	fltAverageHouseholdKentucky = fltTotalYearlyKentucky / intTotalNumberHouseholdKentucky;

	printf("Average Household Income by State and County\n");
	printf("\n");
	printf("Ohio:       $%.2f\n", fltAverageHouseholdOhio);
	printf("  Hamilton: $%.2f\n", fltAverageHouseholdHamilton);
	printf("  Butler:   $%.2f\n", fltAverageHouseholdButler);
	printf("Kentucky:   $%.2f\n", fltAverageHouseholdKentucky);
	printf("  Kenton:   $%.2f\n", fltAverageHouseholdKenton);
	printf("  Boone:    $%.2f\n", fltAverageHouseholdBoone);
	printf("\n");
}

// ---------------------------------
// Name: AverageHouseholdbyRace
// Abstract: Calculates the average household income by race
// ---------------------------------
void AverageHouseholdbyRace(udtCensusRecord audtCensusRecordList[])
{
	int intIndex = 0;

	int intTotalNumberHouseholdBlack = 0;
	int intTotalNumberHouseholdWhite = 0;
	int intTotalNumberHouseholdAsian = 0;
	int intTotalNumberHouseholdHispanic = 0;
	int intTotalNumberHouseholdOther = 0;

	float fltAverageHouseholdBlack = 0.0;
	float fltAverageHouseholdWhite = 0.0;
	float fltAverageHouseholdAsian = 0.0;
	float fltAverageHouseholdHispanic = 0.0;
	float fltAverageHouseholdOther = 0.0;

	float fltTotalYearlyBlack = 0.0;
	float fltTotalYearlyWhite = 0.0;
	float fltTotalYearlyAsian = 0.0;
	float fltTotalYearlyHispanic = 0.0;
	float fltTotalYearlyOther = 0.0;

	while (audtCensusRecordList[intIndex].intHouseholdNumber != 0)
	{
		if (strcmp(audtCensusRecordList[intIndex].strRace, "Caucasian") == 0)
		{
			intTotalNumberHouseholdWhite += 1;
			fltTotalYearlyWhite += audtCensusRecordList[intIndex].fltYearIncome;
		}
		if (strcmp(audtCensusRecordList[intIndex].strRace, "African-American") == 0)
		{
			intTotalNumberHouseholdBlack += 1;
			fltTotalYearlyBlack += audtCensusRecordList[intIndex].fltYearIncome;
		}
		if (strcmp(audtCensusRecordList[intIndex].strRace, "Asian") == 0)
		{
			intTotalNumberHouseholdAsian += 1;
			fltTotalYearlyAsian += audtCensusRecordList[intIndex].fltYearIncome;
		}
		if (strcmp(audtCensusRecordList[intIndex].strRace, "Hispanic") == 0)
		{
			intTotalNumberHouseholdHispanic += 1;
			fltTotalYearlyHispanic += audtCensusRecordList[intIndex].fltYearIncome;
		}
		if (strcmp(audtCensusRecordList[intIndex].strRace, "Other") == 0)
		{
			intTotalNumberHouseholdOther += 1;
			fltTotalYearlyOther += audtCensusRecordList[intIndex].fltYearIncome;
		}
		intIndex += 1;
	}
	fltAverageHouseholdWhite = fltTotalYearlyWhite / intTotalNumberHouseholdWhite;
	fltAverageHouseholdBlack = fltTotalYearlyBlack / intTotalNumberHouseholdBlack;
	fltAverageHouseholdAsian = fltTotalYearlyAsian / intTotalNumberHouseholdAsian;
	fltAverageHouseholdHispanic = fltTotalYearlyHispanic / intTotalNumberHouseholdHispanic;
	fltAverageHouseholdOther = fltTotalYearlyOther / intTotalNumberHouseholdOther;

	printf("Average Household by Race\n");
	printf("\n");
	printf(" Caucasian:        $%.2f\n", fltAverageHouseholdWhite);
	printf(" African-American: $%.2f\n", fltAverageHouseholdBlack);
	printf(" Asian:            $%.2f\n", fltAverageHouseholdAsian);
	printf(" Hispanic:         $%.2f\n", fltAverageHouseholdHispanic);
	printf(" Other:            $%.2f\n", fltAverageHouseholdOther);
	printf("\n");
}

// ---------------------------------
// Name: PercentageBelowPoverty
// Abstract: Calculates the percentage of census records below poverty
// ---------------------------------
void PercentageBelowPoverty(udtCensusRecord audtCensusRecordList[])
{
	int intIndex = 0;
	float fltTotalRecordsBelowPoverty = 0.0;
	int intTotalRecords = 0;
	float fltPercentageBelowPoverty = 0.0;

	while (audtCensusRecordList[intIndex].intHouseholdNumber != 0)
	{
		if (audtCensusRecordList[intIndex].intHouseholdNumber == 1 && audtCensusRecordList[intIndex].fltYearIncome < 12000.00) { fltTotalRecordsBelowPoverty += 1; }
		if (audtCensusRecordList[intIndex].intHouseholdNumber == 2 && audtCensusRecordList[intIndex].fltYearIncome < 18000.00) { fltTotalRecordsBelowPoverty += 1; }
		if (audtCensusRecordList[intIndex].intHouseholdNumber == 3 && audtCensusRecordList[intIndex].fltYearIncome < 25000.00) { fltTotalRecordsBelowPoverty += 1; }
		if (audtCensusRecordList[intIndex].intHouseholdNumber == 4 && audtCensusRecordList[intIndex].fltYearIncome < 30000.00) { fltTotalRecordsBelowPoverty += 1; }
		if (audtCensusRecordList[intIndex].intHouseholdNumber >= 5 && audtCensusRecordList[intIndex].fltYearIncome < 40000.00) { fltTotalRecordsBelowPoverty += 1; }

		intTotalRecords += 1;
		intIndex += 1;
	}
	fltPercentageBelowPoverty = (fltTotalRecordsBelowPoverty / intTotalRecords) * 100;

	printf("Percentage of Census Below Poverty: %.2f%%\n", fltPercentageBelowPoverty);
	printf("\n");
}

// ---------------------------------
// Name: PercentageBelowPovertybyCountyState
// Abstract: Calculates the percentage of census records below poverty by county and state
// ---------------------------------
void PercentageBelowPovertybyCountyState(udtCensusRecord audtCensusRecordList[])
{
	int intIndex = 0;

	float fltPovertyNumberKentucky = 0.0;
	float fltPovertyNumberOhio = 0.0;

	float fltPovertyNumberHamilton = 0.0;
	float fltPovertyNumberButler = 0.0;
	float fltPovertyNumberKenton = 0.0;
	float fltPovertyNumberBoone = 0.0;

	int intTotalNumberHamilton = 0;
	int intTotalNumberButler = 0;
	int intTotalNumberKenton = 0;
	int intTotalNumberBoone = 0;
	int intTotalNumberKentucky = 0;
	int intTotalNumberOhio = 0;

	float fltPovertyPercentHamilton = 0.0;
	float fltPovertyPercentButler = 0.0;
	float fltPovertyPercentBoone = 0.0;
	float fltPovertyPercentKenton = 0.0;
	float fltPovertyPercentOhio = 0.0;
	float fltPovertyPercentKentucky = 0.0;

	while (audtCensusRecordList[intIndex].intHouseholdNumber != 0)
	{
		int intPovertyCheck = 0;

		if (audtCensusRecordList[intIndex].intHouseholdNumber == 1 && audtCensusRecordList[intIndex].fltYearIncome < 12000.00) { intPovertyCheck += 1; }
		if (audtCensusRecordList[intIndex].intHouseholdNumber == 2 && audtCensusRecordList[intIndex].fltYearIncome < 18000.00) { intPovertyCheck += 1; }
		if (audtCensusRecordList[intIndex].intHouseholdNumber == 3 && audtCensusRecordList[intIndex].fltYearIncome < 25000.00) { intPovertyCheck += 1; }
		if (audtCensusRecordList[intIndex].intHouseholdNumber == 4 && audtCensusRecordList[intIndex].fltYearIncome < 30000.00) { intPovertyCheck += 1; }
		if (audtCensusRecordList[intIndex].intHouseholdNumber >= 5 && audtCensusRecordList[intIndex].fltYearIncome < 40000.00) { intPovertyCheck += 1; }


		if (strcmp(audtCensusRecordList[intIndex].strCounty, "Hamilton") == 0)
		{
			intTotalNumberHamilton += 1;
			intTotalNumberOhio += 1;
			if (intPovertyCheck == 1)
			{
				fltPovertyNumberHamilton += 1;
				fltPovertyNumberOhio += 1;
			}
		}
		if (strcmp(audtCensusRecordList[intIndex].strCounty, "Butler") == 0)
		{
			intTotalNumberButler += 1;
			intTotalNumberOhio += 1;
			if (intPovertyCheck == 1)
			{
				fltPovertyNumberButler += 1;
				fltPovertyNumberOhio += 1;
			}
		}
		if (strcmp(audtCensusRecordList[intIndex].strCounty, "Kenton") == 0)
		{
			intTotalNumberKenton += 1;
			intTotalNumberKentucky += 1;
			if (intPovertyCheck == 1)
			{
				fltPovertyNumberKenton += 1;
				fltPovertyNumberKentucky += 1;
			}
		}
		if (strcmp(audtCensusRecordList[intIndex].strCounty, "Boone") == 0)
		{
			intTotalNumberBoone += 1;
			intTotalNumberKentucky += 1;
			if (intPovertyCheck == 1)
			{
				fltPovertyNumberBoone += 1;
				fltPovertyNumberKentucky += 1;
			}
		}

		intIndex += 1;
	}

	fltPovertyPercentHamilton = (fltPovertyNumberHamilton / intTotalNumberHamilton) * 100;
	fltPovertyPercentButler = (fltPovertyNumberButler / intTotalNumberButler) * 100;
	fltPovertyPercentKenton = (fltPovertyNumberKenton / intTotalNumberKenton) * 100;
	fltPovertyPercentBoone = (fltPovertyNumberBoone / intTotalNumberBoone) * 100;
	fltPovertyPercentOhio = (fltPovertyNumberOhio / intTotalNumberOhio) * 100;
	fltPovertyPercentKentucky = (fltPovertyNumberKentucky / intTotalNumberKentucky) * 100;

	printf("Percentage of Poverty by State and County\n");
	printf("\n");
	printf("Ohio:       %.2f%%\n", fltPovertyPercentOhio);
	printf("  Hamilton: %.2f%%\n", fltPovertyPercentHamilton);
	printf("  Butler:   %.2f%%\n", fltPovertyPercentButler);
	printf("Kentucky:   %.2f%%\n", fltPovertyPercentKentucky);
	printf("  Kenton:   %.2f%%\n", fltPovertyPercentKenton);
	printf("  Boone:    %.2f%%\n", fltPovertyPercentBoone);
	printf("\n");
}

// ---------------------------------
// Name: PercentageBelowPovertybyRace
// Abstract: Calculates the percentage of census records below poverty by race
// ---------------------------------
void PercentageBelowPovertybyRace(udtCensusRecord audtCensusRecordList[])
{
	int intIndex = 0;

	float fltPovertyNumberWhite = 0.0;
	float fltPovertyNumberBlack = 0.0;
	float fltPovertyNumberAsian = 0.0;
	float fltPovertyNumberHispanic = 0.0;
	float fltPovertyNumberOther = 0.0;

	int intTotalNumberWhite = 0;
	int intTotalNumberBlack = 0;
	int intTotalNumberAsian = 0;
	int intTotalNumberHispanic = 0;
	int intTotalNumberOther = 0;

	float fltPovertyPercentWhite = 0.0;
	float fltPovertyPercentBlack = 0.0;
	float fltPovertyPercentAsian = 0.0;
	float fltPovertyPercentHispanic = 0.0;
	float fltPovertyPercentOther = 0.0;

	while (audtCensusRecordList[intIndex].intHouseholdNumber != 0)
	{
		int intPovertyCheck = 0;

		if (audtCensusRecordList[intIndex].intHouseholdNumber == 1 && audtCensusRecordList[intIndex].fltYearIncome < 12000.00) { intPovertyCheck += 1; }
		if (audtCensusRecordList[intIndex].intHouseholdNumber == 2 && audtCensusRecordList[intIndex].fltYearIncome < 18000.00) { intPovertyCheck += 1; }
		if (audtCensusRecordList[intIndex].intHouseholdNumber == 3 && audtCensusRecordList[intIndex].fltYearIncome < 25000.00) { intPovertyCheck += 1; }
		if (audtCensusRecordList[intIndex].intHouseholdNumber == 4 && audtCensusRecordList[intIndex].fltYearIncome < 30000.00) { intPovertyCheck += 1; }
		if (audtCensusRecordList[intIndex].intHouseholdNumber >= 5 && audtCensusRecordList[intIndex].fltYearIncome < 40000.00) { intPovertyCheck += 1; }


		if (strcmp(audtCensusRecordList[intIndex].strRace, "Caucasian") == 0)
		{
			intTotalNumberWhite += 1;
			if (intPovertyCheck == 1)
			{
				fltPovertyNumberWhite += 1;
			}
		}
		if (strcmp(audtCensusRecordList[intIndex].strRace, "African-American") == 0)
		{
			intTotalNumberBlack += 1;
			if (intPovertyCheck == 1)
			{
				fltPovertyNumberBlack += 1;
			}
		}
		if (strcmp(audtCensusRecordList[intIndex].strRace, "Asian") == 0)
		{
			intTotalNumberAsian += 1;
			if (intPovertyCheck == 1)
			{
				fltPovertyNumberAsian += 1;
			}
		}
		if (strcmp(audtCensusRecordList[intIndex].strRace, "Hispanic") == 0)
		{
			intTotalNumberHispanic += 1;
			if (intPovertyCheck == 1)
			{
				fltPovertyNumberHispanic += 1;
			}
		}
		if (strcmp(audtCensusRecordList[intIndex].strRace, "Other") == 0)
		{
			intTotalNumberOther += 1;
			if (intPovertyCheck == 1)
			{
				fltPovertyNumberOther += 1;
			}
		}
		intIndex += 1;
	}
	fltPovertyPercentWhite = (fltPovertyNumberWhite / intTotalNumberWhite) * 100;
	fltPovertyPercentBlack = (fltPovertyNumberBlack / intTotalNumberBlack) * 100;
	fltPovertyPercentAsian = (fltPovertyNumberAsian / intTotalNumberAsian) * 100;
	fltPovertyPercentHispanic = (fltPovertyNumberHispanic / intTotalNumberHispanic) * 100;
	fltPovertyPercentOther = (fltPovertyNumberOther / intTotalNumberOther) * 100;

	printf("Percentage of Poverty by Race\n");
	printf("\n");
	printf(" Caucasian:        %.2f%%\n", fltPovertyPercentWhite);
	printf(" African-American: %.2f%%\n", fltPovertyPercentBlack);
	printf(" Asian:            %.2f%%\n", fltPovertyPercentAsian);
	printf(" Hispanic:         %.2f%%\n", fltPovertyPercentHispanic);
	printf(" Other:            %.2f%%\n", fltPovertyPercentOther);
	printf("\n");
}
