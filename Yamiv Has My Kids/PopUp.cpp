#include "PopUp.h"



VOID CALLBACK TimerProc(PVOID TimerQueue, BOOLEAN TimerOrWaitFired) //The Function called when the timer's time is up.
{
    vector <array <string, 2>> Text = ReadCsvFile("TaskList.csv");

    PopUp(Text[1][0].c_str(), "BibiNet"); // commend that creates a popup
    HANDLE Timer = 0;
    DeleteTimerQueueTimer(TimerQueue, Timer,NULL);
    return;
}
void PopUp(const char* PopUpMessage, const char* PopUpTitle)
{
	MessageBox(NULL, PopUpMessage, PopUpTitle, MB_OKCANCEL);
}

void TimedNotification()
{
    SYSTEMTIME St;
    HANDLE Timer = 0;
    HANDLE TimerQueue = CreateTimerQueue();
    if (TimerQueue == NULL)
    {
        cout << "Timer Queue failed" << endl;
    }


    GetLocalTime(&St); //gets Local time.
    if (CalculateRemTime() != 0)
    {
        CreateTimerQueueTimer(
            &Timer,
            TimerQueue,
            (WAITORTIMERCALLBACK)TimerProc,
            TimerQueue,
            CalculateRemTime(),
            0,
            0
        );
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
    int TaskMinutes = stoi(Text[1][0].substr(3, 2)); //crude way of outputing the Minutes from the string
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
