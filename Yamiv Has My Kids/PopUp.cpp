#include <iostream>

#include "PopUp.h"
#include "windows.h"
#include "string"
#include "ReadCsvFile.h"


inline void PopUp(const char* PopUpMessage, const char* PopUpTitle)
{
	MessageBox(NULL, PopUpMessage, PopUpTitle, MB_OKCANCEL);
}

int CalculateRemTime()
{
    int RemHours;
    int RemMinutes;

    SYSTEMTIME St;
    GetLocalTime(&St); //gets Local time.
    
    std::string Text = ReadCsvFileLine(1);
    int Hour = ((Text[0] - 48) * 10 + Text[1] - 48); //crude way of outputing the Hour from the string
    int Minutes = ((Text[3] - 48) * 10 + Text[4] - 48); //crude way of outputing the Minutes from the string
    if (St.wHour > Hour){
        if (St.wMinute> Minutes)
        {
            RemHours = Hour - St.wHour;
            RemMinutes = Minutes - St.wMinute;

            RemHours = RemHours * 36000000;
            RemMinutes = RemMinutes * 60000;
            return (RemHours + RemMinutes);
        }
    }
    else {
        return 1000;
    }
}
