#pragma once
#include <iostream>

#include "windows.h"
#include "string"
#include "ManageCsvFile.h"

using namespace std;

void TimedNotification();
void PopUp(const extern char* PopUpMessage, const extern char* PopUpTitle);
int CalculateRemTime(int Index, vector <array <string, 2>> Text);