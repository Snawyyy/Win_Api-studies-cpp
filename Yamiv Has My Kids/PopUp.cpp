#include "PopUp.h"


VOID CALLBACK TimerProc() //The Function called when the timer's time is up.
{
    vector <array <string, 2>> Text = ReadCsvFile("TaskList.csv");

    int TaskMinutes = stoi(Text[1][0].substr(2, 2)); //crude way of outputing the Minutes from the string

    std::cout << TaskMinutes << std::endl; //debug

    PopUp(Text[1][0].c_str(), "BibiNet"); // commend that creates a popup
    KillTimer(nullptr, 1);

}
void PopUp(const char* PopUpMessage, const char* PopUpTitle)
{
	MessageBox(NULL, PopUpMessage, PopUpTitle, MB_OKCANCEL);
}

void TimedNotification()
{
    SYSTEMTIME St;
    if (CalculateRemTime() != 0)
    {
    GetLocalTime(&St); //gets Local time.

        SetTimer(nullptr,            //handle to main window (there is no main window)
            1,                           //timer identifier
            CalculateRemTime(),          //time.
            (TIMERPROC)&TimerProc);       // calls the function that pops the Popup.
    }
}

int CalculateRemTime()
{
    int RemHours;
    int RemMinutes;

    SYSTEMTIME St;
    GetLocalTime(&St); //gets Local time.
    int CapturedHours = St.wHour;
    int CapturedMinutes = St.wMinute;
    
    vector <array <string, 2>> Text = ReadCsvFile("TaskList.csv");
    int TaskHour = stoi(Text[1][0].substr(0, 2)); //crude way of outputing the Hour from the string
    int TaskMinutes = stoi(Text[1][0].substr(2, 2)); //crude way of outputing the Minutes from the string
    if (CapturedHours <= TaskHour){
        if (CapturedMinutes <= TaskMinutes)
        {
            RemHours = TaskHour - CapturedHours;
            RemMinutes = TaskMinutes - CapturedMinutes;

            RemHours = RemHours * 36000000;
            RemMinutes = RemMinutes * 60000;
            return (RemHours + RemMinutes);
        }
    }
    else {
        KillTimer(nullptr, 1);
        return 0;
    }
}
