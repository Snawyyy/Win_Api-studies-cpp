#include "ManageCsvFile.h"


void CreateCsvFile(const char FileName[])
{

	HANDLE TaskFile =CreateFileA(
		FileName,		    //Name of the created file
		GENERIC_WRITE,			//Write
		0,						//Prevents other processes from managing file
		NULL,					//secirty
		CREATE_NEW,				//Crates new file if it one isnt present
		FILE_ATTRIBUTE_NORMAL,	
		NULL);

	if (TaskFile == INVALID_HANDLE_VALUE) //Opening or creating error
	{
		cout << "Failed to create file" << endl;
		return;
	}

	char buffer[] = "Time,Task";
	DWORD dwBytesToWrite = strlen(buffer) * sizeof(char);
	DWORD dwBytesWritten = 0;

	WriteFile(
		TaskFile,			//The file handle
		(void*)buffer,		//Start of buffer to write
		dwBytesToWrite,		//Numbers of bytes to write
		&dwBytesWritten,	//Numbers of bytes to written to the file
		NULL);				//Synchronous write

	if (dwBytesWritten == dwBytesToWrite) //Console outputs to show success or failure
	{
		cout << "File write successfull" << endl;
	}
	else if (dwBytesWritten > 0)
	{
		cout << "File write partially successful" << endl;
	}
	else
	{
		cout << "File write Failed" << endl;
	}
	
	CloseHandle(TaskFile); //Closes the file
	return;
}

vector <array <string, 2>> ReadCsvFile(const char FileName[]) //maybe make name an value, (const char FileName[])
{
	int Trys = 0;
	start:
	HANDLE TaskFile = CreateFileA(
		FileName,		    //Name of the created file
		GENERIC_READ,			//Write
		0,						//Prevents other processes from managing file
		NULL,					//secirty
		OPEN_EXISTING,				//Crates new file if it one isnt present
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (TaskFile == INVALID_HANDLE_VALUE) //File opening error, assumes there is no File and attampts to create a one 
	{
		cout << "Failed to open" << endl;
		cout << "Trying to create File" << endl;
		CreateCsvFile(FileName);
		if (Trys <= 2) { Trys++; goto start; }  
		else { cout << "FAILURE (idk maybe check the folder)" << endl; } 
	}

	constexpr size_t BUFSIZE = 256;

	char buffer[BUFSIZE]=""; //crates an empty buffer to store the text data from the csv file.
	DWORD dwBytesToRead = BUFSIZE - 1;
	DWORD dwBytesRead = 0;

	ReadFile(
		TaskFile,			//The file handle
		(void*)buffer,		//Buffer that holds text
		dwBytesToRead,		//Buffer size -1
		&dwBytesRead,		//Numbers of bytes Read
		NULL);				//Overlapped IO

	if (dwBytesRead > 0) //if read anything, ouotput it
	{
		buffer[dwBytesRead] = '\0';
		cout << "Csv File Contents:" << endl << buffer << endl;
		int LineCounter = 0;
		vector <array <string,2>> TaskData; //2d vector with 2 columns to store data in a more "code readable" way.
		char Line[BUFSIZE];
		TaskData.push_back({ "Temporary","Temporary" });

		DWORD row = 0; //initalizes the variables used
		DWORD column = 0;
		DWORD dwBytesAdded = 0;
		int j = 0;
		cout << endl;
		cout << endl;
		for (DWORD i = 0; i <= dwBytesRead; i++) //Goes throgh every byte in the buffer.
		{
			if (buffer[i] == '\n' || buffer[i] == '\0') // If its the end of the line, then...
			{
				Line[dwBytesAdded] = '\0';				//trims the empty parts of the char array.
				TaskData[row][column] = (Line);			//adds the line aka "char array" into the 2d string vector.
				cout << "column added: "<<Line<< endl; 
				column=0;							    
				row++;									
				cout << "New Row" << endl;
				TaskData.push_back({ "Temporary","Temporary" }); //initalizes the next vector.
				dwBytesAdded = 0;
				j = 0;
			}
			else { Line[j] = buffer[i]; dwBytesAdded++; j++; } //adds the current char from the buffer into the line.
			if (buffer[i] == ',') //next column.
			{
				Line[dwBytesAdded-1] = '\0';				
				TaskData[row][column] = (Line);			
				cout << "column added: "<< Line << endl; 
				column++;								
				if (column == 2) { column = 0; }
				dwBytesAdded = 0;
				j = 0;
			}
		}
		cout << endl;
		cout << endl;

		//other approch that i had given up on:
		// 
		//string** TaskData = new string* [Counter]; //allocate 2d string array to store the date in a more "code readable" way.
		//for (size_t i = 0; i < Counter; i++)
		//{
		//	TaskData[i] = new string[Counter];
		//}
		CloseHandle(TaskFile);
		return TaskData;
	}
	else { cout << "file seems to be empty" << endl; }
	CloseHandle(TaskFile);
}

string ReadCsvFileLine(int WantedLine)
{
	static fstream file;
	file.open("Exemple.csv");
	static string Line;
	static string hour;
	static string minute;

	static int lineNum = 0;
	getline(file, Line);
	while (getline(file, Line))
	{
		lineNum++;
		if (lineNum == WantedLine)
		{
			return Line;
		}
	}
	file.close();

}



