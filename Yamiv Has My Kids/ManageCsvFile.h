#pragma once
#include <iostream>

#include "Windows.h"
#include "fstream"
#include <string>
#include <vector>
#include <array>


using namespace std;

void CreateCsvFile(const char FileName[]);
void ReadCsvFile(const char FileName[]);
string ReadCsvFileLine(int WantedLine);



