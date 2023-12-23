#include <iostream>

#include "ReadCsvFile.h"
#include "Windows.h"
#include "fstream"

using namespace std;


inline string ReadCsvFileLine(int WantedLine)
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



