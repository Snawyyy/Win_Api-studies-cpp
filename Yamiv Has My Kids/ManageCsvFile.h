#pragma once
#include <iostream>

#include "Windows.h"
#include "fstream"
#include <string>
#include <vector>
#include <array>


using namespace std;

void CreateCsvFile(const char FileName[]);
vector <array <string, 2>> ReadCsvFile(const char FileName[]);
string ReadCsvFileLine(int WantedLine);



