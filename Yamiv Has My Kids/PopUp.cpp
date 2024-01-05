#include "PopUp.h"



VOID CALLBACK TimerProc(int Index, BOOLEAN TimerOrWaitFired) //The Function called when the timer's time is up.
{
    vector <array <string, 2>> Text = ReadCsvFile("TaskList.csv");

    PopUp(Text[Index][0].c_str(), Text[Index][1].c_str()); // commend that creates a popup
    HANDLE Timer = 0;
    return;
}
void PopUp(const char* PopUpMessage, const char* PopUpTitle)
{
	MessageBox(NULL, PopUpMessage, PopUpTitle, MB_OKCANCEL);
}

void TimedNotification()    //Timed Popups manager from csv file.
{
    SYSTEMTIME St;
    HANDLE Timer = 0;
    HANDLE TimerQueue = CreateTimerQueue();
    if (TimerQueue == NULL)
    {
        cout << "Timer Queue failed" << endl;
    }

    vector <array <string, 2>> Text = ReadCsvFile("TaskList.csv");

    for (int i = 1; i < (Text.size()-1); i++)// reason for minus 1 is that the last one is the initialized column (prevents from trying to read an empty Column)
    {
        if (CalculateRemTime(i, Text) != 0)
        {
            CreateTimerQueueTimer(
                &Timer,
                TimerQueue,
                (WAITORTIMERCALLBACK)TimerProc,
                (PVOID)i,
                CalculateRemTime(i, Text),
                0,
                0
            );
        }
    }

}

int CalculateRemTime(int Index, vector <array <string, 2>> Text)
{
    int RemHours;
    int RemMinutes;

    SYSTEMTIME St;
    GetLocalTime(&St); //gets Local time.
    int CapturedHours = St.wHour;
    int CapturedMinutes = St.wMinute;
    
    int TaskHour = stoi(Text[Index][0].substr(0, 2)); //crude way of outputing the Hour from the string
    int TaskMinutes = stoi(Text[Index][0].substr(3, 2)); //crude way of outputing the Minutes from the string
    if (CapturedHours <= TaskHour){
        if (CapturedMinutes <= TaskMinutes)
        {
            RemHours = TaskHour - CapturedHours;
            RemMinutes = TaskMinutes - CapturedMinutes;

            RemHours = RemHours * 36000000;
            RemMinutes = RemMinutes * 60000;
            return (RemHours + RemMinutes - (St.wSecond * 1000) - St.wMilliseconds);
        }
    }
        return 0;
}
